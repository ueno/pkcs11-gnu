# Run "make check" to compare pkcs11.h and pkcs11-gnu.h with p11-kit's
# current pkcs11.h and with the OASIS headers, and to compile them with
# the available compilers.

PKCS11_HEADERS ?= pkcs11-headers
P11_KIT ?= p11-kit

PYTHON ?= python3
CLANG ?= clang

check:: check-compat check-gnu check-oasis check-build

check-compat::
	$(PYTHON) -I tests/check-compat.py --cc $(CLANG) \
		--reference $(P11_KIT)/common/pkcs11.h --candidate pkcs11.h \
		--expected tests/expected-compat.txt -- -I$(PKCS11_HEADERS)

check-gnu::
	$(PYTHON) -I tests/check-compat.py --cc $(CLANG) \
		--reference $(P11_KIT)/common/pkcs11.h --candidate pkcs11.h \
		--expected tests/expected-gnu.txt -- -I$(PKCS11_HEADERS) -DCRYPTOKI_GNU=1

check-oasis::
	$(PYTHON) -I tests/check-compat.py --cc $(CLANG) \
		--reference tests/oasis.h --candidate pkcs11.h \
		--expected tests/expected-oasis.txt -- -I$(PKCS11_HEADERS)

check-build::
	$(SHELL) tests/check-build.sh -I$(PKCS11_HEADERS)
