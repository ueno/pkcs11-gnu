# pkcs11-gnu

A replacement for p11-kit's `common/pkcs11.h` that is based on the
public domain headers from [pkcs11-headers](../pkcs11-headers), with
the GNU coding style API (`CRYPTOKI_GNU`) split out into its own
header, following the
[idea](https://github.com/p11-glue/p11-kit/issues/185) from 2018. This
would make it easier to update the `pkcs11.h` to the latest standard.

## Header files

- `pkcs11.h`: the standard API.  It includes
  `public-domain/3.2/pkcs11.h` and adds what p11-kit's header has
  historically provided on top of it: `CK_DEFINE_FUNCTION`, `CK_SPEC`,
  `TRUE`/`FALSE`, `CRYPTOKI_LEGACY_VERSION_*`, deprecated names,
  `CRYPTOKI_FORCE_WIN32` packing, and macros mapping the old struct tags
  (`struct _CK_ATTRIBUTE`, `struct ck_gcm_params`, ...) to the standard
  ones.  With `CRYPTOKI_GNU` defined it includes `pkcs11-gnu.h` instead.
- `pkcs11-gnu.h`: the GNU coding style API, extracted verbatim from the
  `CRYPTOKI_GNU` mode of p11-kit's header and frozen at PKCS #11 3.2.  It
  cannot be combined with the standard header in one translation unit.

## Testing

```console
$ make check
```

`tests/check-compat.py` turns every macro, typedef, struct tag, struct
member and function exported by a reference header into compile-time
assertions (existence, type, value, size, alignment, offset) and compiles
them against a candidate header; every failing assertion is reported as
a gap.  Intentional gaps are listed, with reasons, in
`tests/expected-*.txt`.  `make check` runs it:

| Target               | Reference                         | Mode                            |
|----------------------|-----------------------------------|---------------------------------|
| `check-compat`       | p11-kit `common/pkcs11.h`         | default                         |
| `check-gnu`          | p11-kit `common/pkcs11.h`         | `CRYPTOKI_GNU`                  |
| `check-oasis`        | OASIS 3.2 headers (`tests/oasis.h`) | default                       |

`check-build` additionally compiles both modes as C and C++ with gcc and
clang using `-Wall -Wextra -Werror`.

Paths can be overridden with `PKCS11_HEADERS=` and `REFERENCE=`.  The
checker can also be run directly, e.g. to compare any two headers:

```console
$ python3 -I tests/check-compat.py --reference old.h --candidate new.h -- -I...
```
