#!/bin/sh
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.

# Compile pkcs11.h in both modes as C and C++ with the available
# compilers, warnings enabled, and check that pkcs11-gnu.h refuses to be
# mixed with the standard header.  Extra arguments are passed to the
# compilers (e.g. -I for pkcs11-headers).

srcdir=$(cd "$(dirname "$0")/.." && pwd)
tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT
status=0

cat > "$tmpdir/test.c" <<EOF
#include "pkcs11.h"
#include "pkcs11.h"

#ifdef CRYPTOKI_GNU
static struct ck_attribute attr = { CKA_CLASS, 0, 0 };
static struct ck_function_list *list;
static ck_rv_t rv = CKR_OK;
#define VALUE_LEN attr.value_len
#else
static CK_ATTRIBUTE attr = { CKA_CLASS, NULL_PTR, 0 };
static CK_FUNCTION_LIST_PTR list;
static CK_RV rv = CKR_OK;
static CK_BBOOL b = CK_TRUE;
#define VALUE_LEN attr.ulValueLen
#endif

int main (void)
{
	return (int) (rv + VALUE_LEN) + (list == 0 ? 0 : 1);
}
EOF
cp "$tmpdir/test.c" "$tmpdir/test.cc"

run () {
	if "$@" > "$tmpdir/log" 2>&1; then
		echo "PASS: $*" | sed "s|$tmpdir/||g"
	else
		echo "FAIL: $*" | sed "s|$tmpdir/||g"
		cat "$tmpdir/log"
		status=1
	fi
}

for cc in gcc clang; do
	command -v $cc > /dev/null || continue
	for mode in "" -DCRYPTOKI_GNU=1; do
		run $cc -std=c99 -Wall -Wextra -Werror -Wno-unused-variable \
			-I"$srcdir" "$@" $mode -c "$tmpdir/test.c" -o "$tmpdir/test.o"
	done
done
for cxx in g++ clang++; do
	command -v $cxx > /dev/null || continue
	for mode in "" -DCRYPTOKI_GNU=1; do
		run $cxx -Wall -Wextra -Werror -Wno-unused-variable \
			-I"$srcdir" "$@" $mode -c "$tmpdir/test.cc" -o "$tmpdir/test.o"
	done
done

# pkcs11-gnu.h must refuse to be mixed with the standard header.
printf '#include "public-domain/3.2/pkcs11.h"\n#include "pkcs11-gnu.h"\n' \
	> "$tmpdir/mix.c"
if cc -I"$srcdir" "$@" -c "$tmpdir/mix.c" -o "$tmpdir/mix.o" \
	> "$tmpdir/log" 2>&1; then
	echo "FAIL: mixing pkcs11-gnu.h with the standard header compiled"
	status=1
elif grep -q "cannot be used together" "$tmpdir/log"; then
	echo "PASS: mixing pkcs11-gnu.h with the standard header is rejected"
else
	echo "FAIL: mixing pkcs11-gnu.h with the standard header: unexpected error"
	cat "$tmpdir/log"
	status=1
fi

exit $status
