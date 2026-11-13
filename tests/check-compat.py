#!/usr/bin/env python3
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.

"""Check that a candidate PKCS #11 header is source and ABI compatible
with a reference header.

Every name the reference header exports (macros, typedefs, struct tags,
struct members and functions) is turned into compile-time assertions
about its existence, type, value and layout.  The assertions are then
compiled against the candidate header and each failing one is reported
as a gap.

Known, intentional differences can be listed in an expectations file,
one "<kind> <name>" pattern per line (fnmatch syntax, '#' comments).
The script exits with status 1 if there are gaps not covered by the
expectations, and warns about expectations that no longer match.
"""

import argparse
import collections
import fnmatch
import json
import os
import re
import subprocess
import sys
import tempfile

INT_TYPES = [
    'int', 'unsigned int', 'long', 'unsigned long',
    'long long', 'unsigned long long',
]


class Toolchain:
    def __init__(self, cc, flags, workdir):
        self.cc = cc
        self.flags = flags
        self.workdir = workdir
        self.counter = 0

    def write(self, text, suffix='.c'):
        self.counter += 1
        path = os.path.join(self.workdir, 'tu%d%s' % (self.counter, suffix))
        with open(path, 'w') as f:
            f.write(text)
        return path

    def run(self, args, check=True):
        proc = subprocess.run([self.cc] + self.flags + args,
                              capture_output=True, text=True)
        if check and proc.returncode != 0:
            sys.exit('compiler failed: %s\n%s' % (' '.join(args), proc.stderr))
        return proc

    def macros(self, src):
        out = self.run(['-E', '-dM', self.write(src)]).stdout
        macros = {}
        for line in out.splitlines():
            m = re.match(r'#define (\w+)(\(.*?\))?(?: (.*))?$', line)
            if m:
                macros[m.group(1)] = (m.group(2) is not None, m.group(3) or '')
        return macros

    def ast(self, src):
        out = self.run(['-fsyntax-only', '-Xclang', '-ast-dump=json',
                        self.write(src)]).stdout
        return json.loads(out)

    def errors(self, src):
        """Compile SRC and return {line: [messages]} for errors in it."""
        path = self.write(src)
        proc = self.run(['-fsyntax-only', '-ferror-limit=0',
                         '-fno-caret-diagnostics', path], check=False)
        errors = collections.defaultdict(list)
        others = []
        for line in proc.stderr.splitlines():
            m = re.match(r'(.*?):(\d+):\d+: (?:fatal )?error: (.*)', line)
            if not m:
                continue
            if os.path.samefile(m.group(1), path):
                errors[int(m.group(2))].append(m.group(3))
            else:
                others.append(line)
        return errors, others

    def execute(self, src):
        exe = os.path.join(self.workdir, 'prog%d' % self.counter)
        self.run([self.write(src), '-o', exe])
        return subprocess.run([exe], capture_output=True, text=True,
                              check=True).stdout


class Header:
    """Names exported by a header, minus those of an empty translation unit."""

    def __init__(self, tc, include, baseline):
        self.src = '#include "%s"\n' % include
        macros = tc.macros(self.src)
        self.macros = {k: v for k, v in macros.items()
                       if k not in baseline.macros}
        self.typedefs = {}
        self.records = {}
        self.functions = {}
        for node in tc.ast(self.src).get('inner', []):
            if node.get('isImplicit'):
                continue
            kind = node.get('kind')
            name = node.get('name')
            if kind == 'TypedefDecl':
                if name not in baseline.typedefs:
                    self.typedefs[name] = node['type']['qualType']
            elif kind == 'RecordDecl' and name and \
                    node.get('completeDefinition'):
                tag = '%s %s' % (node['tagUsed'], name)
                fields = [(f['name'], f['type']['qualType'])
                          for f in node.get('inner', [])
                          if f.get('kind') == 'FieldDecl']
                self.records[tag] = fields
            elif kind == 'FunctionDecl' and name not in baseline.functions:
                self.functions[name] = node['type']['qualType']


class Baseline:
    def __init__(self, tc):
        self.macros = tc.macros('')
        self.typedefs = set()
        self.functions = set()
        for node in tc.ast('').get('inner', []):
            if node.get('kind') == 'TypedefDecl':
                self.typedefs.add(node['name'])
            elif node.get('kind') == 'FunctionDecl':
                self.functions.add(node['name'])


def compilable(tc, src, names, template):
    """Return the NAMES for which TEMPLATE compiles after SRC."""
    lines = [template.replace('%s', name) for name in names]
    errors, _ = tc.errors(src + '\n'.join(lines) + '\n')
    offset = src.count('\n') + 1
    return [n for i, n in enumerate(names) if offset + i not in errors]


def integer_macros(tc, ref):
    """Return the object-like macros that are integer constant expressions,
    with their value and type as seen with the reference header."""
    names = sorted(n for n, (func, _) in ref.macros.items() if not func)
    names = compilable(tc, ref.src, names,
                       '_Static_assert((%s) == (%s) + 0, "");')

    generic = ', '.join('%s: "%s"' % (t, t) for t in INT_TYPES)
    prog = ['#include <stdio.h>', ref.src, 'int main(void) {']
    for name in names:
        prog.append('printf("%%s %%llu %%s\\n", "%s", '
                    '(unsigned long long)(%s), '
                    '_Generic((%s), %s, default: "other"));'
                    % (name, name, name, generic))
    prog.append('return 0; }')
    values = {}
    for line in tc.execute('\n'.join(prog) + '\n').splitlines():
        name, value, ctype = line.split(' ', 2)
        values[name] = (int(value), ctype)
    return values


def layouts(tc, ref):
    """Return sizes of typedefs/records and offsets of fields."""
    prog = ['#include <stdio.h>', '#include <stddef.h>', ref.src,
            'int main(void) {']
    complete = compilable(tc, ref.src, sorted(ref.typedefs),
                          '_Static_assert(sizeof(%s) > 0, "");')
    for name in complete:
        prog.append('printf("typedef %s %%zu %%zu\\n", sizeof(%s), '
                    '_Alignof(%s));' % (name, name, name))
    for tag, fields in sorted(ref.records.items()):
        prog.append('printf("record %s %%zu %%zu\\n", sizeof(%s), '
                    '_Alignof(%s));' % (tag.replace(' ', '/'), tag, tag))
        for field, _ in fields:
            prog.append('printf("field %s.%s %%zu\\n", offsetof(%s, %s));'
                        % (tag.replace(' ', '/'), field, tag, field))
    prog.append('return 0; }')
    result = {}
    for line in tc.execute('\n'.join(prog) + '\n').splitlines():
        kind, name, *values = line.split()
        result[(kind, name.replace('/', ' '))] = [int(v) for v in values]
    return result


class Checks:
    """A translation unit made of one assertion per line."""

    def __init__(self, src, skip=()):
        self.lines = src.rstrip('\n').split('\n')
        self.checks = {}
        self.skip = set(skip)
        self.skipped = set()

    def add(self, kind, name, what, *code):
        if (kind, name, what) in self.skip:
            self.skipped.add((kind, name))
            return
        # Each check owns all of its lines, so that an error anywhere
        # in it is attributed to it.
        for line in code:
            self.lines.append(line)
            self.checks[len(self.lines)] = (kind, name, what)

    def text(self):
        return '\n'.join(self.lines) + '\n'


def build_checks(ref, cand_src, values, layout, check_types, skip=()):
    c = Checks('#include <stddef.h>\n' + cand_src, skip)

    for name, (func, _) in sorted(ref.macros.items()):
        c.add('macro', name, 'not defined',
              '#ifndef %s' % name, '#error missing', '#endif')
        if name in values:
            value, ctype = values[name]
            c.add('macro-value', name, 'value is not %#x' % value,
                  '#ifdef %s' % name,
                  '_Static_assert((unsigned long long)(%s) == %dULL, "");'
                  % (name, value), '#endif')
            if check_types and ctype != 'other':
                c.add('macro-type', name, 'type is not %s' % ctype,
                      '#ifdef %s' % name,
                      '_Static_assert(__builtin_types_compatible_p('
                      '__typeof__(%s), %s), "");' % (name, ctype), '#endif')

    for name, qualtype in sorted(ref.typedefs.items()):
        c.add('typedef', name, 'not declared',
              'typedef %s __chk_typedef_%s;' % (name, name))
        c.add('typedef-type', name, 'not compatible with %s' % qualtype,
              '_Static_assert(__builtin_types_compatible_p(%s, %s), "");'
              % (name, qualtype))
        size = layout.get(('typedef', name))
        if size:
            c.add('typedef-layout', name, 'size/alignment is not %d/%d'
                  % tuple(size),
                  '_Static_assert(sizeof(%s) == %d && _Alignof(%s) == %d, "");'
                  % (name, size[0], name, size[1]))

    for tag, fields in sorted(ref.records.items()):
        size = layout[('record', tag)]
        c.add('tag', tag, 'not a complete type',
              '_Static_assert(sizeof(%s) > 0, "");' % tag)
        c.add('tag-layout', tag, 'size/alignment is not %d/%d' % tuple(size),
              '_Static_assert(sizeof(%s) == %d && _Alignof(%s) == %d, "");'
              % (tag, size[0], tag, size[1]))
        for field, qualtype in fields:
            member = '%s.%s' % (tag, field)
            offset = layout[('field', member)][0]
            c.add('member', member, 'missing or not at offset %d' % offset,
                  '_Static_assert(offsetof(%s, %s) == %d, "");'
                  % (tag, field, offset))
            c.add('member-type', member, 'not compatible with %s' % qualtype,
                  '_Static_assert(__builtin_types_compatible_p('
                  '__typeof__(((%s *)0)->%s), %s), "");'
                  % (tag, field, qualtype))

    for name, qualtype in sorted(ref.functions.items()):
        c.add('function', name, 'not declared or not compatible with %s'
              % qualtype,
              '_Static_assert(__builtin_types_compatible_p('
              '__typeof__(%s), %s), "");' % (name, qualtype))
    return c


def load_expected(path):
    patterns = []
    if path:
        with open(path) as f:
            for line in f:
                line = line.split('#', 1)[0].strip()
                if line:
                    kind, name = line.split(None, 1)
                    patterns.append((kind, name))
    return patterns


def main():
    parser = argparse.ArgumentParser(description=__doc__.split('\n\n')[0])
    parser.add_argument('--reference', required=True,
                        help='reference header (e.g. the current pkcs11.h)')
    parser.add_argument('--candidate', required=True,
                        help='header to check against the reference')
    parser.add_argument('--expected', help='expected gaps file')
    parser.add_argument('--cc', default=os.environ.get('CC_CLANG', 'clang'),
                        help='clang compatible compiler (default: clang)')
    parser.add_argument('--no-macro-types', action='store_true',
                        help='do not compare the types of constants')
    parser.add_argument('-v', '--verbose', action='store_true',
                        help='also list names only the candidate exports')
    parser.add_argument('flags', nargs='*', metavar='-- FLAGS',
                        help='extra compiler flags (e.g. -I, -D)')
    args = parser.parse_args()

    with tempfile.TemporaryDirectory() as workdir:
        tc = Toolchain(args.cc, ['-std=gnu11'] + args.flags, workdir)
        baseline = Baseline(tc)
        ref = Header(tc, os.path.abspath(args.reference), baseline)
        cand = Header(tc, os.path.abspath(args.candidate), baseline)
        values = integer_macros(tc, ref)
        layout = layouts(tc, ref)
        # Checks which do not even hold for the reference header (e.g.
        # types clang cannot spell back) are not meaningful.
        checks = build_checks(ref, ref.src, values, layout,
                              not args.no_macro_types)
        errors, _ = tc.errors(checks.text())
        unverifiable = {checks.checks[line] for line in errors
                        if line in checks.checks}
        checks = build_checks(ref, cand.src, values, layout,
                              not args.no_macro_types, unverifiable)
        errors, others = tc.errors(checks.text())

    if others:
        print('Errors outside of the checks (candidate header broken?):')
        for line in others:
            print('  ' + line)
        return 1

    gaps = {}
    for line, messages in sorted(errors.items()):
        if line not in checks.checks:
            print('error in preamble at line %d: %s' % (line, messages))
            return 1
        kind, name, what = checks.checks[line]
        gaps.setdefault((kind, name), (what, messages[0]))

    expected = load_expected(args.expected)
    used = set()
    unexpected = []
    known = []
    for (kind, name), info in sorted(gaps.items()):
        match = [p for p in expected
                 if fnmatch.fnmatchcase(kind, p[0]) and
                 fnmatch.fnmatchcase(name, p[1])]
        used.update(match)
        (known if match else unexpected).append((kind, name, info))

    total = len(set(checks.checks.values()))
    print('%s vs %s: %d checks, %d gaps (%d expected), %d unverifiable'
          % (args.candidate, args.reference, total, len(gaps), len(known),
             len(checks.skipped)))
    for title, items in (('Unexpected gaps', unexpected),
                         ('Expected gaps', known)):
        if items:
            print('%s:' % title)
            for kind, name, (what, message) in items:
                print('  %-14s %-40s %s' % (kind, name, what))
                if title.startswith('Unexpected'):
                    print('  %-14s %-40s   (%s)' % ('', '', message))
    for kind, name in expected:
        if (kind, name) not in used:
            print('warning: expectation "%s %s" matched nothing'
                  % (kind, name))

    if args.verbose:
        print('Unverifiable: %s' % ' '.join(
            '%s:%s' % k for k in sorted(checks.skipped)))
        extra = sorted(set(cand.macros) - set(ref.macros)) + \
            sorted(set(cand.typedefs) - set(ref.typedefs)) + \
            sorted(set(cand.records) - set(ref.records)) + \
            sorted(set(cand.functions) - set(ref.functions))
        print('Only in candidate (%d): %s' % (len(extra), ' '.join(extra)))

    return 1 if unexpected else 0


if __name__ == '__main__':
    sys.exit(main())
