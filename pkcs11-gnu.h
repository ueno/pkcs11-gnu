/* pkcs11-gnu.h
   Copyright 2006, 2007 g10 Code GmbH
   Copyright 2006 Andreas Jellinghaus
   Copyright 2017, 2021-2026 Red Hat, Inc.

   This file is free software; as a special exception the author gives
   unlimited permission to copy and/or distribute it, with or without
   modifications, as long as this notice is preserved.

   This file is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY, to the extent permitted by law; without even
   the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
   PURPOSE.  */

/* Please submit any changes back to the p11-kit project at
   https://github.com/p11-glue/p11-kit/, so that
   they can be picked up by other projects from there as well.  */

/* This file provides the PKCS #11 API in a form that complies better
   with the GNU coding standard.  It used to be the CRYPTOKI_GNU mode of
   p11-kit's pkcs11.h; that header is now based on the standard
   definitions and includes this file when CRYPTOKI_GNU is defined.

   This interface is frozen at PKCS #11 3.2: definitions introduced by
   later versions of the standard are only available through the
   standard names.

   The following changes are made to the specification:

   All structure types are changed to a "struct ck_foo" where CK_FOO
   is the type name in PKCS #11.

   All non-structure types are changed to ck_foo_t where CK_FOO is the
   lowercase version of the type name in PKCS #11.  The basic types
   (CK_ULONG et al.) are removed without substitute.

   All members of structures are modified in the following way: Type
   indication prefixes are removed, and underscore characters are
   inserted before words.  Then the result is lowercased.

   Note that function names are still in the original case, as they
   need for ABI compatibility.

   CK_FALSE, CK_TRUE and NULL_PTR are removed without substitute.  Use
   <stdbool.h>.

   The structure layouts, constants and function signatures are
   identical to the standard ones, so a module or application built
   with this header interoperates with one built with the standard
   header.  The two headers cannot be used in the same translation
   unit, though.  */

#ifndef PKCS11_GNU_H
#define PKCS11_GNU_H 1

#if defined(_PD_PKCS11_) || defined(_PKCS11_H_)
#error "pkcs11-gnu.h cannot be used together with the standard PKCS #11 header"
#endif

#ifndef CRYPTOKI_GNU
#define CRYPTOKI_GNU 1
#endif

#if defined(__cplusplus)
extern "C" {
#endif


/* The version of cryptoki we implement.  The revision is changed with
   each modification of this file.  */
#define CRYPTOKI_VERSION_MAJOR                  3
#define CRYPTOKI_VERSION_MINOR                  2
#define CRYPTOKI_VERSION_REVISION               0
#define CRYPTOKI_LEGACY_VERSION_MAJOR           2
#define CRYPTOKI_LEGACY_VERSION_MINOR           40
#define P11_KIT_CRYPTOKI_VERSION_REVISION       0

/* System dependencies.  */

#if defined(_WIN32) || defined(CRYPTOKI_FORCE_WIN32)

/* There is a matching pop below.  */
#pragma pack(push, cryptoki, 1)

#ifdef CRYPTOKI_EXPORTS
#define CK_SPEC __declspec(dllexport)
#else
#define CK_SPEC __declspec(dllimport)
#endif

#else

#define CK_SPEC

#endif





/* CK_ATTRIBUTE_TYPE */
#define CKA_CLASS                               (0UL)
#define CKA_TOKEN                               (1UL)
#define CKA_PRIVATE                             (2UL)
#define CKA_LABEL                               (3UL)
#define CKA_UNIQUE_ID                           (4UL)
#define CKA_APPLICATION                         (0x10UL)
#define CKA_VALUE                               (0x11UL)
#define CKA_OBJECT_ID                           (0x12UL)
#define CKA_CERTIFICATE_TYPE                    (0x80UL)
#define CKA_ISSUER                              (0x81UL)
#define CKA_SERIAL_NUMBER                       (0x82UL)
#define CKA_AC_ISSUER                           (0x83UL)
#define CKA_OWNER                               (0x84UL)
#define CKA_ATTR_TYPES                          (0x85UL)
#define CKA_TRUSTED                             (0x86UL)
#define CKA_CERTIFICATE_CATEGORY                (0x87UL)
#define CKA_JAVA_MIDP_SECURITY_DOMAIN           (0x88UL)
#define CKA_URL                                 (0x89UL)
#define CKA_HASH_OF_SUBJECT_PUBLIC_KEY          (0x8aUL)
#define CKA_HASH_OF_ISSUER_PUBLIC_KEY           (0x8bUL)
#define CKA_NAME_HASH_ALGORITHM                 (0x8cUL)
#define CKA_CHECK_VALUE                         (0x90UL)
#define CKA_KEY_TYPE                            (0x100UL)
#define CKA_SUBJECT                             (0x101UL)
#define CKA_ID                                  (0x102UL)
#define CKA_SENSITIVE                           (0x103UL)
#define CKA_ENCRYPT                             (0x104UL)
#define CKA_DECRYPT                             (0x105UL)
#define CKA_WRAP                                (0x106UL)
#define CKA_UNWRAP                              (0x107UL)
#define CKA_SIGN                                (0x108UL)
#define CKA_SIGN_RECOVER                        (0x109UL)
#define CKA_VERIFY                              (0x10aUL)
#define CKA_VERIFY_RECOVER                      (0x10bUL)
#define CKA_DERIVE                              (0x10cUL)
#define CKA_START_DATE                          (0x110UL)
#define CKA_END_DATE                            (0x111UL)
#define CKA_MODULUS                             (0x120UL)
#define CKA_MODULUS_BITS                        (0x121UL)
#define CKA_PUBLIC_EXPONENT                     (0x122UL)
#define CKA_PRIVATE_EXPONENT                    (0x123UL)
#define CKA_PRIME_1                             (0x124UL)
#define CKA_PRIME_2                             (0x125UL)
#define CKA_EXPONENT_1                          (0x126UL)
#define CKA_EXPONENT_2                          (0x127UL)
#define CKA_COEFFICIENT                         (0x128UL)
#define CKA_PUBLIC_KEY_INFO                     (0x129UL)
#define CKA_PRIME                               (0x130UL)
#define CKA_SUBPRIME                            (0x131UL)
#define CKA_BASE                                (0x132UL)
#define CKA_PRIME_BITS                          (0x133UL)
#define CKA_SUBPRIME_BITS                       (0x134UL)
#define CKA_SUB_PRIME_BITS                      (0x134UL)
#define CKA_VALUE_BITS                          (0x160UL)
#define CKA_VALUE_LEN                           (0x161UL)
#define CKA_EXTRACTABLE                         (0x162UL)
#define CKA_LOCAL                               (0x163UL)
#define CKA_NEVER_EXTRACTABLE                   (0x164UL)
#define CKA_ALWAYS_SENSITIVE                    (0x165UL)
#define CKA_KEY_GEN_MECHANISM                   (0x166UL)
#define CKA_MODIFIABLE                          (0x170UL)
#define CKA_COPYABLE                            (0x171UL)
#define CKA_DESTROYABLE                         (0x172UL)
#define CKA_ECDSA_PARAMS                        (0x180UL)
#define CKA_EC_PARAMS                           (0x180UL)
#define CKA_EC_POINT                            (0x181UL)
#define CKA_SECONDARY_AUTH                      (0x200UL)
#define CKA_AUTH_PIN_FLAGS                      (0x201UL)
#define CKA_ALWAYS_AUTHENTICATE                 (0x202UL)
#define CKA_WRAP_WITH_TRUSTED                   (0x210UL)
#define CKA_OTP_FORMAT                          (0x220UL)
#define CKA_OTP_LENGTH                          (0x221UL)
#define CKA_OTP_TIME_INTERVAL                   (0x222UL)
#define CKA_OTP_USER_FRIENDLY_MODE              (0x223UL)
#define CKA_OTP_CHALLENGE_REQUIREMENT           (0x224UL)
#define CKA_OTP_TIME_REQUIREMENT                (0x225UL)
#define CKA_OTP_COUNTER_REQUIREMENT             (0x226UL)
#define CKA_OTP_PIN_REQUIREMENT                 (0x227UL)
#define CKA_OTP_USER_IDENTIFIER                 (0x22aUL)
#define CKA_OTP_SERVICE_IDENTIFIER              (0x22bUL)
#define CKA_OTP_SERVICE_LOGO                    (0x22cUL)
#define CKA_OTP_SERVICE_LOGO_TYPE               (0x22dUL)
#define CKA_OTP_COUNTER                         (0x22eUL)
#define CKA_OTP_TIME                            (0x22fUL)
#define CKA_GOSTR3410_PARAMS                    (0x250UL)
#define CKA_GOSTR3411_PARAMS                    (0x251UL)
#define CKA_GOST28147_PARAMS                    (0x252UL)
#define CKA_HW_FEATURE_TYPE                     (0x300UL)
#define CKA_RESET_ON_INIT                       (0x301UL)
#define CKA_HAS_RESET                           (0x302UL)
#define CKA_PIXEL_X                             (0x400UL)
#define CKA_PIXEL_Y                             (0x401UL)
#define CKA_RESOLUTION                          (0x402UL)
#define CKA_CHAR_ROWS                           (0x403UL)
#define CKA_CHAR_COLUMNS                        (0x404UL)
#define CKA_COLOR                               (0x405UL)
#define CKA_BITS_PER_PIXEL                      (0x406UL)
#define CKA_CHAR_SETS                           (0x480UL)
#define CKA_ENCODING_METHODS                    (0x481UL)
#define CKA_MIME_TYPES                          (0x482UL)
#define CKA_MECHANISM_TYPE                      (0x500UL)
#define CKA_REQUIRED_CMS_ATTRIBUTES             (0x501UL)
#define CKA_DEFAULT_CMS_ATTRIBUTES              (0x502UL)
#define CKA_SUPPORTED_CMS_ATTRIBUTES            (0x503UL)
#define CKA_WRAP_TEMPLATE                       (CKF_ARRAY_ATTRIBUTE | 0x211UL)
#define CKA_UNWRAP_TEMPLATE                     (CKF_ARRAY_ATTRIBUTE | 0x212UL)
#define CKA_DERIVE_TEMPLATE                     (CKF_ARRAY_ATTRIBUTE | 0x213UL)
#define CKA_ALLOWED_MECHANISMS                  (CKF_ARRAY_ATTRIBUTE | 0x600UL)
#define CKA_PROFILE_ID                          (0x601UL)
#define CKA_X2RATCHET_BAG                       (0x602UL)
#define CKA_X2RATCHET_BAGSIZE                   (0x603UL)
#define CKA_X2RATCHET_BOBS1STMSG                (0x604UL)
#define CKA_X2RATCHET_CKR                       (0x605UL)
#define CKA_X2RATCHET_CKS                       (0x606UL)
#define CKA_X2RATCHET_DHP                       (0x607UL)
#define CKA_X2RATCHET_DHR                       (0x608UL)
#define CKA_X2RATCHET_DHS                       (0x609UL)
#define CKA_X2RATCHET_HKR                       (0x60aUL)
#define CKA_X2RATCHET_HKS                       (0x60bUL)
#define CKA_X2RATCHET_ISALICE                   (0x60cUL)
#define CKA_X2RATCHET_NHKR                      (0x60dUL)
#define CKA_X2RATCHET_NHKS                      (0x60eUL)
#define CKA_X2RATCHET_NR                        (0x60fUL)
#define CKA_X2RATCHET_NS                        (0x610UL)
#define CKA_X2RATCHET_PNS                       (0x611UL)
#define CKA_X2RATCHET_RK                        (0x612UL)
#define CKA_HSS_LEVELS                          (0x617UL)
#define CKA_HSS_LMS_TYPE                        (0x618UL)
#define CKA_HSS_LMOTS_TYPE                      (0x619UL)
#define CKA_HSS_LMS_TYPES                       (0x61AUL)
#define CKA_HSS_LMOTS_TYPES                     (0x61BUL)
#define CKA_HSS_KEYS_REMAINING                  (0x61CUL)
#define CKA_PARAMETER_SET                       (0x61DUL)
#define CKA_OBJECT_VALIDATION_FLAGS             (0x61EUL)
#define CKA_VALIDATION_TYPE                     (0x61FUL)
#define CKA_VALIDATION_VERSION                  (0x620UL)
#define CKA_VALIDATION_LEVEL                    (0x621UL)
#define CKA_VALIDATION_MODULE_ID                (0x622UL)
#define CKA_VALIDATION_FLAG                     (0x623UL)
#define CKA_VALIDATION_AUTHORITY_TYPE           (0x624UL)
#define CKA_VALIDATION_COUNTRY                  (0x625UL)
#define CKA_VALIDATION_CERTIFICATE_IDENTIFIER   (0x626UL)
#define CKA_VALIDATION_CERTIFICATE_URI          (0x627UL)
#define CKA_VALIDATION_VENDOR_URI               (0x628UL)
#define CKA_VALIDATION_PROFILE                  (0x629UL)
#define CKA_ENCAPSULATE_TEMPLATE                (0x62AUL)
#define CKA_DECAPSULATE_TEMPLATE                (0x62BUL)
#define CKA_TRUST_SERVER_AUTH                   (0x62CUL)
#define CKA_TRUST_CLIENT_AUTH                   (0x62DUL)
#define CKA_TRUST_CODE_SIGNING                  (0x62EUL)
#define CKA_TRUST_EMAIL_PROTECTION              (0x62FUL)
#define CKA_TRUST_IPSEC_IKE                     (0x630UL)
#define CKA_TRUST_TIME_STAMPING                 (0x631UL)
#define CKA_TRUST_OCSP_SIGNING                  (0x632UL)
#define CKA_ENCAPSULATE                         (0x633UL)
#define CKA_DECAPSULATE                         (0x634UL)
#define CKA_HASH_OF_CERTIFICATE                 (0x635UL)
#define CKA_PUBLIC_CRC64_VALUE                  (0x636UL)
#define CKA_SEED                                (0x637UL)
#define CKA_VENDOR_DEFINED                      ((unsigned long) (1UL << 31))

/* CK_CERTIFICATE_CATEGORY */
#define CK_CERTIFICATE_CATEGORY_UNSPECIFIED     (0UL)
#define CK_CERTIFICATE_CATEGORY_TOKEN_USER      (1UL)
#define CK_CERTIFICATE_CATEGORY_AUTHORITY       (2UL)
#define CK_CERTIFICATE_CATEGORY_OTHER_ENTITY    (3UL)

/* CK_CERTIFICATE_TYPE */
#define CKC_X_509                               (0UL)
#define CKC_X_509_ATTR_CERT                     (1UL)
#define CKC_WTLS                                (2UL)
#define CKC_VENDOR_DEFINED                      ((unsigned long) (1UL << 31))
#define CKC_OPENPGP                             (CKC_VENDOR_DEFINED|0x504750UL)

/* KDFs */
#define CKD_NULL                                (0x01UL)
#define CKD_SHA1_KDF                            (0x02UL)
#define CKD_SHA1_KDF_ASN1                       (0x03UL)
#define CKD_SHA1_KDF_CONCATENATE                (0x04UL)
#define CKD_SHA224_KDF                          (0x05UL)
#define CKD_SHA256_KDF                          (0x06UL)
#define CKD_SHA384_KDF                          (0x07UL)
#define CKD_SHA512_KDF                          (0x08UL)
#define CKD_CPDIVERSIFY_KDF                     (0x09UL)
#define CKD_SHA3_224_KDF                        (0x0aUL)
#define CKD_SHA3_256_KDF                        (0x0bUL)
#define CKD_SHA3_384_KDF                        (0x0cUL)
#define CKD_SHA3_512_KDF                        (0x0dUL)
#define CKD_SHA1_KDF_SP800                      (0x0eUL)
#define CKD_SHA224_KDF_SP800                    (0x0fUL)
#define CKD_SHA256_KDF_SP800                    (0x10UL)
#define CKD_SHA384_KDF_SP800                    (0x11UL)
#define CKD_SHA512_KDF_SP800                    (0x12UL)
#define CKD_SHA3_224_KDF_SP800                  (0x13UL)
#define CKD_SHA3_256_KDF_SP800                  (0x14UL)
#define CKD_SHA3_384_KDF_SP800                  (0x15UL)
#define CKD_SHA3_512_KDF_SP800                  (0x16UL)
#define CKD_BLAKE2B_160_KDF                     (0x17UL)
#define CKD_BLAKE2B_256_KDF                     (0x18UL)
#define CKD_BLAKE2B_384_KDF                     (0x19UL)
#define CKD_BLAKE2B_512_KDF                     (0x1aUL)

/* CK_GENERATOR_FUNCTION */
#define CKG_NO_GENERATE                         (0UL)
#define CKG_GENERATE                            (1UL)
#define CKG_GENERATE_COUNTER                    (2UL)
#define CKG_GENERATE_RANDOM                     (3UL)
#define CKG_GENERATE_COUNTER_XOR                (4UL)

/* CK_FLAGS */
#define CKF_TOKEN_PRESENT                       (1UL << 0)
#define CKF_REMOVABLE_DEVICE                    (1UL << 1)
#define CKF_HW_SLOT                             (1UL << 2)
#define CKF_ARRAY_ATTRIBUTE                     (1UL << 30)

#define CKF_LIBRARY_CANT_CREATE_OS_THREADS      (1UL << 0)
#define CKF_OS_LOCKING_OK                       (1UL << 1)

#define CKF_HKDF_SALT_NULL                      (1UL << 0)
#define CKF_HKDF_SALT_DATA                      (1UL << 1)
#define CKF_HKDF_SALT_KEY                       (1UL << 2)

#define CKF_INTERFACE_FORK_SAFE                 (1UL)

#define CKF_EC_F_P                              (1UL << 20)
#define CKF_EC_F_2M                             (1UL << 21)
#define CKF_EC_ECPARAMETERS                     (1UL << 22)
#define CKF_EC_OID                              (1UL << 23)
#define CKF_EC_NAMEDCURVE                       (1UL << 23)
#define CKF_EC_UNCOMPRESS                       (1UL << 24)
#define CKF_EC_COMPRESS                         (1UL << 25)
#define CKF_EC_CURVENAME                        (1UL << 26)
#define CKF_ENCAPSULATE                         (1UL << 28)
#define CKF_DECAPSULATE                         (1UL << 29)

#define CKF_HW                                  (1UL << 0)
#define CKF_MESSAGE_ENCRYPT                     (1UL << 1)
#define CKF_MESSAGE_DECRYPT                     (1UL << 2)
#define CKF_MESSAGE_SIGN                        (1UL << 3)
#define CKF_MESSAGE_VERIFY                      (1UL << 4)
#define CKF_MULTI_MESSAGE                       (1UL << 5)
#define CKF_FIND_OBJECTS                        (1UL << 6)
#define CKF_ENCRYPT                             (1UL << 8)
#define CKF_DECRYPT                             (1UL << 9)
#define CKF_DIGEST                              (1UL << 10)
#define CKF_SIGN                                (1UL << 11)
#define CKF_SIGN_RECOVER                        (1UL << 12)
#define CKF_VERIFY                              (1UL << 13)
#define CKF_VERIFY_RECOVER                      (1UL << 14)
#define CKF_GENERATE                            (1UL << 15)
#define CKF_GENERATE_KEY_PAIR                   (1UL << 16)
#define CKF_WRAP                                (1UL << 17)
#define CKF_UNWRAP                              (1UL << 18)
#define CKF_DERIVE                              (1UL << 19)
#define CKF_EXTENSION                           ((unsigned long) (1UL << 31))
/* Flags for message-based functions */
#define CKF_END_OF_MESSAGE                      (0x1UL)
/* OTP mechanism flags */
#define CKF_NEXT_OTP                            (0x01UL)
#define CKF_EXCLUDE_TIME                        (0x02UL)
#define CKF_EXCLUDE_COUNTER                     (0x04UL)
#define CKF_EXCLUDE_CHALLENGE                   (0x08UL)
#define CKF_EXCLUDE_PIN                         (0x10UL)
#define CKF_USER_FRIENDLY_OTP                   (0x20UL)

/* Flags for C_WaitForSlotEvent.  */
#define CKF_DONT_BLOCK                          (1UL)

#define CKF_RW_SESSION                          (1UL << 1)
#define CKF_SERIAL_SESSION                      (1UL << 2)
#define CKF_ASYNC_SESSION                       (1UL << 3)

#define CKF_RNG                                 (1UL << 0)
#define CKF_WRITE_PROTECTED                     (1UL << 1)
#define CKF_LOGIN_REQUIRED                      (1UL << 2)
#define CKF_USER_PIN_INITIALIZED                (1UL << 3)
#define CKF_RESTORE_KEY_NOT_NEEDED              (1UL << 5)
#define CKF_CLOCK_ON_TOKEN                      (1UL << 6)
#define CKF_PROTECTED_AUTHENTICATION_PATH       (1UL << 8)
#define CKF_DUAL_CRYPTO_OPERATIONS              (1UL << 9)
#define CKF_TOKEN_INITIALIZED                   (1UL << 10)
#define CKF_SECONDARY_AUTHENTICATION            (1UL << 11)
#define CKF_USER_PIN_COUNT_LOW                  (1UL << 16)
#define CKF_USER_PIN_FINAL_TRY                  (1UL << 17)
#define CKF_USER_PIN_LOCKED                     (1UL << 18)
#define CKF_USER_PIN_TO_BE_CHANGED              (1UL << 19)
#define CKF_SO_PIN_COUNT_LOW                    (1UL << 20)
#define CKF_SO_PIN_FINAL_TRY                    (1UL << 21)
#define CKF_SO_PIN_LOCKED                       (1UL << 22)
#define CKF_SO_PIN_TO_BE_CHANGED                (1UL << 23)
#define CKF_ERROR_STATE                         (1UL << 24)
#define CKF_SEED_RANDOM_REQUIRED                (1UL << 25)
#define CKF_ASYNC_SESSION_SUPPORTED             (1UL << 26)

/* CK_HW_FEATURE_TYPE */
#define CKH_MONOTONIC_COUNTER                   (1UL)
#define CKH_CLOCK                               (2UL)
#define CKH_USER_INTERFACE                      (3UL)
#define CKH_VENDOR_DEFINED                      ((unsigned long) (1UL << 31))

/* CK_HEDGE_TYPE */
#define CKH_HEDGE_PREFERRED                     (0UL)
#define CKH_HEDGE_REQUIRED                      (1UL)
#define CKH_DETERMINISTIC_REQUIRED              (2UL)

/* CK_JAVA_MIDP_SECURITY_DOMAIN */
#define CK_SECURITY_DOMAIN_UNSPECIFIED          (0UL)
#define CK_SECURITY_DOMAIN_MANUFACTURER         (1UL)
#define CK_SECURITY_DOMAIN_OPERATOR             (2UL)
#define CK_SECURITY_DOMAIN_THIRD_PARTY          (3UL)

/* CK_KEY_TYPE */
#define CKK_RSA                                 (0UL)
#define CKK_DSA                                 (1UL)
#define CKK_DH                                  (2UL)
#define CKK_ECDSA                               (3UL)
#define CKK_EC                                  (3UL)
#define CKK_X9_42_DH                            (4UL)
#define CKK_KEA                                 (5UL)
#define CKK_GENERIC_SECRET                      (0x10UL)
#define CKK_RC2                                 (0x11UL)
#define CKK_RC4                                 (0x12UL)
#define CKK_DES                                 (0x13UL)
#define CKK_DES2                                (0x14UL)
#define CKK_DES3                                (0x15UL)
#define CKK_CAST                                (0x16UL)
#define CKK_CAST3                               (0x17UL)
#define CKK_CAST128                             (0x18UL)
#define CKK_RC5                                 (0x19UL)
#define CKK_IDEA                                (0x1aUL)
#define CKK_SKIPJACK                            (0x1bUL)
#define CKK_BATON                               (0x1cUL)
#define CKK_JUNIPER                             (0x1dUL)
#define CKK_CDMF                                (0x1eUL)
#define CKK_AES                                 (0x1fUL)
#define CKK_BLOWFISH                            (0x20UL)
#define CKK_TWOFISH                             (0x21UL)
#define CKK_SECURID                             (0x22UL)
#define CKK_HOTP                                (0x23UL)
#define CKK_ACTI                                (0x24UL)
#define CKK_CAMELLIA                            (0x25UL)
#define CKK_ARIA                                (0x26UL)
#define CKK_MD5_HMAC                            (0x27UL)
#define CKK_SHA_1_HMAC                          (0x28UL)
#define CKK_RIPEMD128_HMAC                      (0x29UL)
#define CKK_RIPEMD160_HMAC                      (0x2aUL)
#define CKK_SHA256_HMAC                         (0x2bUL)
#define CKK_SHA384_HMAC                         (0x2cUL)
#define CKK_SHA512_HMAC                         (0x2dUL)
#define CKK_SHA224_HMAC                         (0x2eUL)
#define CKK_SEED                                (0x2fUL)
#define CKK_GOSTR3410                           (0x30UL)
#define CKK_GOSTR3411                           (0x31UL)
#define CKK_GOST28147                           (0x32UL)
#define CKK_CHACHA20                            (0x33UL)
#define CKK_POLY1305                            (0x34UL)
#define CKK_AES_XTS                             (0x35UL)
#define CKK_SHA3_224_HMAC                       (0x36UL)
#define CKK_SHA3_256_HMAC                       (0x37UL)
#define CKK_SHA3_384_HMAC                       (0x38UL)
#define CKK_SHA3_512_HMAC                       (0x39UL)
#define CKK_BLAKE2B_160_HMAC                    (0x3aUL)
#define CKK_BLAKE2B_256_HMAC                    (0x3bUL)
#define CKK_BLAKE2B_384_HMAC                    (0x3cUL)
#define CKK_BLAKE2B_512_HMAC                    (0x3dUL)
#define CKK_SALSA20                             (0x3eUL)
#define CKK_X2RATCHET                           (0x3fUL)
#define CKK_EC_EDWARDS                          (0x40UL)
#define CKK_EC_MONTGOMERY                       (0x41UL)
#define CKK_HKDF                                (0x42UL)
#define CKK_SHA512_224_HMAC                     (0x43UL)
#define CKK_SHA512_256_HMAC                     (0x44UL)
#define CKK_SHA512_T_HMAC                       (0x45UL)
#define CKK_HSS                                 (0x46UL)
#define CKK_XMSS                                (0x47UL)
#define CKK_XMSSMT                              (0x48UL)
#define CKK_ML_KEM                              (0x49UL)
#define CKK_ML_DSA                              (0x4AUL)
#define CKK_SLH_DSA                             (0x4BUL)
#define CKK_VENDOR_DEFINED                      ((unsigned long) (1UL << 31))

/* CK_MECHANISM_TYPE */
#define CKM_RSA_PKCS_KEY_PAIR_GEN               (0UL)
#define CKM_RSA_PKCS                            (1UL)
#define CKM_RSA_9796                            (2UL)
#define CKM_RSA_X_509                           (3UL)
#define CKM_MD2_RSA_PKCS                        (4UL)
#define CKM_MD5_RSA_PKCS                        (5UL)
#define CKM_SHA1_RSA_PKCS                       (6UL)
#define CKM_RIPEMD128_RSA_PKCS                  (7UL)
#define CKM_RIPEMD160_RSA_PKCS                  (8UL)
#define CKM_RSA_PKCS_OAEP                       (9UL)
#define CKM_RSA_X9_31_KEY_PAIR_GEN              (0xaUL)
#define CKM_RSA_X9_31                           (0xbUL)
#define CKM_SHA1_RSA_X9_31                      (0xcUL)
#define CKM_RSA_PKCS_PSS                        (0xdUL)
#define CKM_SHA1_RSA_PKCS_PSS                   (0xeUL)
#define CKM_ML_KEM_KEY_PAIR_GEN                 (0xfUL)
#define CKM_DSA_KEY_PAIR_GEN                    (0x10UL)
#define CKM_DSA                                 (0x11UL)
#define CKM_DSA_SHA1                            (0x12UL)
#define CKM_DSA_SHA224                          (0x13UL)
#define CKM_DSA_SHA256                          (0x14UL)
#define CKM_DSA_SHA384                          (0x15UL)
#define CKM_DSA_SHA512                          (0x16UL)
#define CKM_ML_KEM                              (0x17UL)
#define CKM_DSA_SHA3_224                        (0x18UL)
#define CKM_DSA_SHA3_256                        (0x19UL)
#define CKM_DSA_SHA3_384                        (0x1AUL)
#define CKM_DSA_SHA3_512                        (0x1BUL)
#define CKM_ML_DSA_KEY_PAIR_GEN                 (0x1CUL)
#define CKM_ML_DSA                              (0x1DUL)
#define CKM_HASH_ML_DSA                         (0x1FUL)
#define CKM_DH_PKCS_KEY_PAIR_GEN                (0x20UL)
#define CKM_DH_PKCS_DERIVE                      (0x21UL)
#define CKM_HASH_ML_DSA_SHA224                  (0x23UL)
#define CKM_HASH_ML_DSA_SHA256                  (0x24UL)
#define CKM_HASH_ML_DSA_SHA384                  (0x25UL)
#define CKM_HASH_ML_DSA_SHA512                  (0x26UL)
#define CKM_HASH_ML_DSA_SHA3_224                (0x27UL)
#define CKM_HASH_ML_DSA_SHA3_256                (0x28UL)
#define CKM_HASH_ML_DSA_SHA3_384                (0x29UL)
#define CKM_HASH_ML_DSA_SHA3_512                (0x2AUL)
#define CKM_HASH_ML_DSA_SHAKE128                (0x2BUL)
#define CKM_HASH_ML_DSA_SHAKE256                (0x2CUL)
#define CKM_SLH_DSA_KEY_PAIR_GEN                (0x2DUL)
#define CKM_SLH_DSA                             (0x2EUL)
#define CKM_X9_42_DH_KEY_PAIR_GEN               (0x30UL)
#define CKM_X9_42_DH_DERIVE                     (0x31UL)
#define CKM_X9_42_DH_HYBRID_DERIVE              (0x32UL)
#define CKM_X9_42_MQV_DERIVE                    (0x33UL)
#define CKM_HASH_SLH_DSA                        (0x34UL)
#define CKM_HASH_SLH_DSA_SHA224                 (0x36UL)
#define CKM_HASH_SLH_DSA_SHA256                 (0x37UL)
#define CKM_HASH_SLH_DSA_SHA384                 (0x38UL)
#define CKM_HASH_SLH_DSA_SHA512                 (0x39UL)
#define CKM_HASH_SLH_DSA_SHA3_224               (0x3AUL)
#define CKM_HASH_SLH_DSA_SHA3_256               (0x3BUL)
#define CKM_HASH_SLH_DSA_SHA3_384               (0x3CUL)
#define CKM_HASH_SLH_DSA_SHA3_512               (0x3DUL)
#define CKM_HASH_SLH_DSA_SHAKE128               (0x3EUL)
#define CKM_HASH_SLH_DSA_SHAKE256               (0x3FUL)
#define CKM_SHA256_RSA_PKCS                     (0x40UL)
#define CKM_SHA384_RSA_PKCS                     (0x41UL)
#define CKM_SHA512_RSA_PKCS                     (0x42UL)
#define CKM_SHA256_RSA_PKCS_PSS                 (0x43UL)
#define CKM_SHA384_RSA_PKCS_PSS                 (0x44UL)
#define CKM_SHA512_RSA_PKCS_PSS                 (0x45UL)
#define CKM_SHA224_RSA_PKCS                     (0x46UL)
#define CKM_SHA224_RSA_PKCS_PSS                 (0x47UL)
#define CKM_SHA512_224                          (0x48UL)
#define CKM_SHA512_224_HMAC                     (0x49UL)
#define CKM_SHA512_224_HMAC_GENERAL             (0x4aUL)
#define CKM_SHA512_224_KEY_DERIVATION           (0x4bUL)
#define CKM_SHA512_256                          (0x4cUL)
#define CKM_SHA512_256_HMAC                     (0x4dUL)
#define CKM_SHA512_256_HMAC_GENERAL             (0x4eUL)
#define CKM_SHA512_256_KEY_DERIVATION           (0x4fUL)
#define CKM_SHA512_T                            (0x50UL)
#define CKM_SHA512_T_HMAC                       (0x51UL)
#define CKM_SHA512_T_HMAC_GENERAL               (0x52UL)
#define CKM_SHA512_T_KEY_DERIVATION             (0x53UL)
#define CKM_TLS12_EXTENDED_MASTER_KEY_DERIVE    (0x56UL)
#define CKM_TLS12_EXTENDED_MASTER_KEY_DERIVE_DH (0x57UL)
#define CKM_SHA3_256_RSA_PKCS                   (0x60UL)
#define CKM_SHA3_384_RSA_PKCS                   (0x61UL)
#define CKM_SHA3_512_RSA_PKCS                   (0x62UL)
#define CKM_SHA3_256_RSA_PKCS_PSS               (0x63UL)
#define CKM_SHA3_384_RSA_PKCS_PSS               (0x64UL)
#define CKM_SHA3_512_RSA_PKCS_PSS               (0x65UL)
#define CKM_SHA3_224_RSA_PKCS                   (0x66UL)
#define CKM_SHA3_224_RSA_PKCS_PSS               (0x67UL)
#define CKM_RC2_KEY_GEN                         (0x100UL)
#define CKM_RC2_ECB                             (0x101UL)
#define CKM_RC2_CBC                             (0x102UL)
#define CKM_RC2_MAC                             (0x103UL)
#define CKM_RC2_MAC_GENERAL                     (0x104UL)
#define CKM_RC2_CBC_PAD                         (0x105UL)
#define CKM_RC4_KEY_GEN                         (0x110UL)
#define CKM_RC4                                 (0x111UL)
#define CKM_DES_KEY_GEN                         (0x120UL)
#define CKM_DES_ECB                             (0x121UL)
#define CKM_DES_CBC                             (0x122UL)
#define CKM_DES_MAC                             (0x123UL)
#define CKM_DES_MAC_GENERAL                     (0x124UL)
#define CKM_DES_CBC_PAD                         (0x125UL)
#define CKM_DES2_KEY_GEN                        (0x130UL)
#define CKM_DES3_KEY_GEN                        (0x131UL)
#define CKM_DES3_ECB                            (0x132UL)
#define CKM_DES3_CBC                            (0x133UL)
#define CKM_DES3_MAC                            (0x134UL)
#define CKM_DES3_MAC_GENERAL                    (0x135UL)
#define CKM_DES3_CBC_PAD                        (0x136UL)
#define CKM_DES3_CMAC_GENERAL                   (0x137UL)
#define CKM_DES3_CMAC                           (0x138UL)
#define CKM_CDMF_KEY_GEN                        (0x140UL)
#define CKM_CDMF_ECB                            (0x141UL)
#define CKM_CDMF_CBC                            (0x142UL)
#define CKM_CDMF_MAC                            (0x143UL)
#define CKM_CDMF_MAC_GENERAL                    (0x144UL)
#define CKM_CDMF_CBC_PAD                        (0x145UL)
#define CKM_DES_OFB64                           (0x150UL)
#define CKM_DES_OFB8                            (0x151UL)
#define CKM_DES_CFB64                           (0x152UL)
#define CKM_DES_CFB8                            (0x153UL)
#define CKM_MD2                                 (0x200UL)
#define CKM_MD2_HMAC                            (0x201UL)
#define CKM_MD2_HMAC_GENERAL                    (0x202UL)
#define CKM_MD5                                 (0x210UL)
#define CKM_MD5_HMAC                            (0x211UL)
#define CKM_MD5_HMAC_GENERAL                    (0x212UL)
#define CKM_SHA_1                               (0x220UL)
#define CKM_SHA_1_HMAC                          (0x221UL)
#define CKM_SHA_1_HMAC_GENERAL                  (0x222UL)
#define CKM_RIPEMD128                           (0x230UL)
#define CKM_RIPEMD128_HMAC                      (0x231UL)
#define CKM_RIPEMD128_HMAC_GENERAL              (0x232UL)
#define CKM_RIPEMD160                           (0x240UL)
#define CKM_RIPEMD160_HMAC                      (0x241UL)
#define CKM_RIPEMD160_HMAC_GENERAL              (0x242UL)
#define CKM_SHA256                              (0x250UL)
#define CKM_SHA256_HMAC                         (0x251UL)
#define CKM_SHA256_HMAC_GENERAL                 (0x252UL)
#define CKM_SHA224                              (0x255UL)
#define CKM_SHA224_HMAC                         (0x256UL)
#define CKM_SHA224_HMAC_GENERAL                 (0x257UL)
#define CKM_SHA384                              (0x260UL)
#define CKM_SHA384_HMAC                         (0x261UL)
#define CKM_SHA384_HMAC_GENERAL                 (0x262UL)
#define CKM_SHA512                              (0x270UL)
#define CKM_SHA512_HMAC                         (0x271UL)
#define CKM_SHA512_HMAC_GENERAL                 (0x272UL)
#define CKM_SECURID_KEY_GEN                     (0x280UL)
#define CKM_SECURID                             (0x282UL)
#define CKM_HOTP_KEY_GEN                        (0x290UL)
#define CKM_HOTP                                (0x291UL)
#define CKM_ACTI                                (0x2a0UL)
#define CKM_ACTI_KEY_GEN                        (0x2a1UL)
#define CKM_SHA3_256                            (0x2b0UL)
#define CKM_SHA3_256_HMAC                       (0x2b1UL)
#define CKM_SHA3_256_HMAC_GENERAL               (0x2b2UL)
#define CKM_SHA3_256_KEY_GEN                    (0x2b3UL)
#define CKM_SHA3_224                            (0x2b5UL)
#define CKM_SHA3_224_HMAC                       (0x2b6UL)
#define CKM_SHA3_224_HMAC_GENERAL               (0x2b7UL)
#define CKM_SHA3_224_KEY_GEN                    (0x2b8UL)
#define CKM_SHA3_384                            (0x2c0UL)
#define CKM_SHA3_384_HMAC                       (0x2c1UL)
#define CKM_SHA3_384_HMAC_GENERAL               (0x2c2UL)
#define CKM_SHA3_384_KEY_GEN                    (0x2c3UL)
#define CKM_SHA3_512                            (0x2d0UL)
#define CKM_SHA3_512_HMAC                       (0x2d1UL)
#define CKM_SHA3_512_HMAC_GENERAL               (0x2d2UL)
#define CKM_SHA3_512_KEY_GEN                    (0x2d3UL)
#define CKM_CAST_KEY_GEN                        (0x300UL)
#define CKM_CAST_ECB                            (0x301UL)
#define CKM_CAST_CBC                            (0x302UL)
#define CKM_CAST_MAC                            (0x303UL)
#define CKM_CAST_MAC_GENERAL                    (0x304UL)
#define CKM_CAST_CBC_PAD                        (0x305UL)
#define CKM_CAST3_KEY_GEN                       (0x310UL)
#define CKM_CAST3_ECB                           (0x311UL)
#define CKM_CAST3_CBC                           (0x312UL)
#define CKM_CAST3_MAC                           (0x313UL)
#define CKM_CAST3_MAC_GENERAL                   (0x314UL)
#define CKM_CAST3_CBC_PAD                       (0x315UL)
#define CKM_CAST5_KEY_GEN                       (0x320UL)
#define CKM_CAST128_KEY_GEN                     (0x320UL)
#define CKM_CAST5_ECB                           (0x321UL)
#define CKM_CAST128_ECB                         (0x321UL)
#define CKM_CAST5_CBC                           (0x322UL)
#define CKM_CAST128_CBC                         (0x322UL)
#define CKM_CAST5_MAC                           (0x323UL)
#define CKM_CAST128_MAC                         (0x323UL)
#define CKM_CAST5_MAC_GENERAL                   (0x324UL)
#define CKM_CAST128_MAC_GENERAL                 (0x324UL)
#define CKM_CAST5_CBC_PAD                       (0x325UL)
#define CKM_CAST128_CBC_PAD                     (0x325UL)
#define CKM_RC5_KEY_GEN                         (0x330UL)
#define CKM_RC5_ECB                             (0x331UL)
#define CKM_RC5_CBC                             (0x332UL)
#define CKM_RC5_MAC                             (0x333UL)
#define CKM_RC5_MAC_GENERAL                     (0x334UL)
#define CKM_RC5_CBC_PAD                         (0x335UL)
#define CKM_IDEA_KEY_GEN                        (0x340UL)
#define CKM_IDEA_ECB                            (0x341UL)
#define CKM_IDEA_CBC                            (0x342UL)
#define CKM_IDEA_MAC                            (0x343UL)
#define CKM_IDEA_MAC_GENERAL                    (0x344UL)
#define CKM_IDEA_CBC_PAD                        (0x345UL)
#define CKM_GENERIC_SECRET_KEY_GEN              (0x350UL)
#define CKM_CONCATENATE_BASE_AND_KEY            (0x360UL)
#define CKM_CONCATENATE_BASE_AND_DATA           (0x362UL)
#define CKM_CONCATENATE_DATA_AND_BASE           (0x363UL)
#define CKM_XOR_BASE_AND_DATA                   (0x364UL)
#define CKM_EXTRACT_KEY_FROM_KEY                (0x365UL)
#define CKM_SSL3_PRE_MASTER_KEY_GEN             (0x370UL)
#define CKM_SSL3_MASTER_KEY_DERIVE              (0x371UL)
#define CKM_SSL3_KEY_AND_MAC_DERIVE             (0x372UL)
#define CKM_SSL3_MASTER_KEY_DERIVE_DH           (0x373UL)
#define CKM_TLS_PRE_MASTER_KEY_GEN              (0x374UL)
#define CKM_TLS_MASTER_KEY_DERIVE               (0x375UL)
#define CKM_TLS_KEY_AND_MAC_DERIVE              (0x376UL)
#define CKM_TLS_MASTER_KEY_DERIVE_DH            (0x377UL)
#define CKM_TLS_PRF                             (0x378UL)
#define CKM_SSL3_MD5_MAC                        (0x380UL)
#define CKM_SSL3_SHA1_MAC                       (0x381UL)
#define CKM_MD5_KEY_DERIVATION                  (0x390UL)
#define CKM_MD2_KEY_DERIVATION                  (0x391UL)
#define CKM_SHA1_KEY_DERIVATION                 (0x392UL)
#define CKM_SHA256_KEY_DERIVATION               (0x393UL)
#define CKM_SHA384_KEY_DERIVATION               (0x394UL)
#define CKM_SHA512_KEY_DERIVATION               (0x395UL)
#define CKM_SHA224_KEY_DERIVATION               (0x396UL)
#define CKM_SHA3_256_KEY_DERIVATION             (0x397UL)
#define CKM_SHA3_256_KEY_DERIVE                 (0x397UL)
#define CKM_SHA3_224_KEY_DERIVATION             (0x398UL)
#define CKM_SHA3_224_KEY_DERIVE                 (0x398UL)
#define CKM_SHA3_384_KEY_DERIVATION             (0x399UL)
#define CKM_SHA3_384_KEY_DERIVE                 (0x399UL)
#define CKM_SHA3_512_KEY_DERIVATION             (0x39aUL)
#define CKM_SHA3_512_KEY_DERIVE                 (0x39aUL)
#define CKM_SHAKE_128_KEY_DERIVATION            (0x39bUL)
#define CKM_SHAKE_128_KEY_DERIVE                (0x39bUL)
#define CKM_SHAKE_256_KEY_DERIVATION            (0x39cUL)
#define CKM_SHAKE_256_KEY_DERIVE                (0x39cUL)
#define CKM_PBE_MD2_DES_CBC                     (0x3a0UL)
#define CKM_PBE_MD5_DES_CBC                     (0x3a1UL)
#define CKM_PBE_MD5_CAST_CBC                    (0x3a2UL)
#define CKM_PBE_MD5_CAST3_CBC                   (0x3a3UL)
#define CKM_PBE_MD5_CAST5_CBC                   (0x3a4UL)
#define CKM_PBE_MD5_CAST128_CBC                 (0x3a4UL)
#define CKM_PBE_SHA1_CAST5_CBC                  (0x3a5UL)
#define CKM_PBE_SHA1_CAST128_CBC                (0x3a5UL)
#define CKM_PBE_SHA1_RC4_128                    (0x3a6UL)
#define CKM_PBE_SHA1_RC4_40                     (0x3a7UL)
#define CKM_PBE_SHA1_DES3_EDE_CBC               (0x3a8UL)
#define CKM_PBE_SHA1_DES2_EDE_CBC               (0x3a9UL)
#define CKM_PBE_SHA1_RC2_128_CBC                (0x3aaUL)
#define CKM_PBE_SHA1_RC2_40_CBC                 (0x3abUL)
#define CKM_PKCS5_PBKD2                         (0x3b0UL)
#define CKM_PBA_SHA1_WITH_SHA1_HMAC             (0x3c0UL)
#define CKM_WTLS_PRE_MASTER_KEY_GEN             (0x3d0UL)
#define CKM_WTLS_MASTER_KEY_DERIVE              (0x3d1UL)
#define CKM_WTLS_MASTER_KEY_DERIVE_DH_ECC       (0x3d2UL)
#define CKM_WTLS_PRF                            (0x3d3UL)
#define CKM_WTLS_SERVER_KEY_AND_MAC_DERIVE      (0x3d4UL)
#define CKM_WTLS_CLIENT_KEY_AND_MAC_DERIVE      (0x3d5UL)
#define CKM_TLS10_MAC_SERVER                    (0x3d6UL)
#define CKM_TLS10_MAC_CLIENT                    (0x3d7UL)
#define CKM_TLS12_MAC                           (0x3d8UL)
#define CKM_TLS12_KDF                           (0x3d9UL)
#define CKM_TLS12_MASTER_KEY_DERIVE             (0x3e0UL)
#define CKM_TLS12_KEY_AND_MAC_DERIVE            (0x3e1UL)
#define CKM_TLS12_MASTER_KEY_DERIVE_DH          (0x3e2UL)
#define CKM_TLS12_KEY_SAFE_DERIVE               (0x3e3UL)
#define CKM_TLS_MAC                             (0x3e4UL)
#define CKM_TLS_KDF                             (0x3e5UL)
#define CKM_KEY_WRAP_LYNKS                      (0x400UL)
#define CKM_KEY_WRAP_SET_OAEP                   (0x401UL)
#define CKM_CMS_SIG                             (0x500UL)
#define CKM_KIP_DERIVE                          (0x510UL)
#define CKM_KIP_WRAP                            (0x511UL)
#define CKM_KIP_MAC                             (0x512UL)
#define CKM_CAMELLIA_KEY_GEN                    (0x550UL)
#define CKM_CAMELLIA_ECB                        (0x551UL)
#define CKM_CAMELLIA_CBC                        (0x552UL)
#define CKM_CAMELLIA_MAC                        (0x553UL)
#define CKM_CAMELLIA_MAC_GENERAL                (0x554UL)
#define CKM_CAMELLIA_CBC_PAD                    (0x555UL)
#define CKM_CAMELLIA_ECB_ENCRYPT_DATA           (0x556UL)
#define CKM_CAMELLIA_CBC_ENCRYPT_DATA           (0x557UL)
#define CKM_CAMELLIA_CTR                        (0x558UL)
#define CKM_ARIA_KEY_GEN                        (0x560UL)
#define CKM_ARIA_ECB                            (0x561UL)
#define CKM_ARIA_CBC                            (0x562UL)
#define CKM_ARIA_MAC                            (0x563UL)
#define CKM_ARIA_MAC_GENERAL                    (0x564UL)
#define CKM_ARIA_CBC_PAD                        (0x565UL)
#define CKM_ARIA_ECB_ENCRYPT_DATA               (0x566UL)
#define CKM_ARIA_CBC_ENCRYPT_DATA               (0x567UL)
#define CKM_SEED_KEY_GEN                        (0x650UL)
#define CKM_SEED_ECB                            (0x651UL)
#define CKM_SEED_CBC                            (0x652UL)
#define CKM_SEED_MAC                            (0x653UL)
#define CKM_SEED_MAC_GENERAL                    (0x654UL)
#define CKM_SEED_CBC_PAD                        (0x655UL)
#define CKM_SEED_ECB_ENCRYPT_DATA               (0x656UL)
#define CKM_SEED_CBC_ENCRYPT_DATA               (0x657UL)
#define CKM_SKIPJACK_KEY_GEN                    (0x1000UL)
#define CKM_SKIPJACK_ECB64                      (0x1001UL)
#define CKM_SKIPJACK_CBC64                      (0x1002UL)
#define CKM_SKIPJACK_OFB64                      (0x1003UL)
#define CKM_SKIPJACK_CFB64                      (0x1004UL)
#define CKM_SKIPJACK_CFB32                      (0x1005UL)
#define CKM_SKIPJACK_CFB16                      (0x1006UL)
#define CKM_SKIPJACK_CFB8                       (0x1007UL)
#define CKM_SKIPJACK_WRAP                       (0x1008UL)
#define CKM_SKIPJACK_PRIVATE_WRAP               (0x1009UL)
#define CKM_SKIPJACK_RELAYX                     (0x100aUL)
#define CKM_KEA_KEY_PAIR_GEN                    (0x1010UL)
#define CKM_KEA_KEY_DERIVE                      (0x1011UL)
#define CKM_KEA_DERIVE                          (0x1012UL)
#define CKM_FORTEZZA_TIMESTAMP                  (0x1020UL)
#define CKM_BATON_KEY_GEN                       (0x1030UL)
#define CKM_BATON_ECB128                        (0x1031UL)
#define CKM_BATON_ECB96                         (0x1032UL)
#define CKM_BATON_CBC128                        (0x1033UL)
#define CKM_BATON_COUNTER                       (0x1034UL)
#define CKM_BATON_SHUFFLE                       (0x1035UL)
#define CKM_BATON_WRAP                          (0x1036UL)
#define CKM_ECDSA_KEY_PAIR_GEN                  (0x1040UL)
#define CKM_EC_KEY_PAIR_GEN                     (0x1040UL)
#define CKM_ECDSA                               (0x1041UL)
#define CKM_ECDSA_SHA1                          (0x1042UL)
#define CKM_ECDSA_SHA224                        (0x1043UL)
#define CKM_ECDSA_SHA256                        (0x1044UL)
#define CKM_ECDSA_SHA384                        (0x1045UL)
#define CKM_ECDSA_SHA512                        (0x1046UL)
#define CKM_EC_KEY_PAIR_GEN_W_EXTRA_BITS        (0x140bUL)
#define CKM_ECDH1_DERIVE                        (0x1050UL)
#define CKM_ECDH1_COFACTOR_DERIVE               (0x1051UL)
#define CKM_ECMQV_DERIVE                        (0x1052UL)
#define CKM_ECDH_AES_KEY_WRAP                   (0x1053UL)
#define CKM_RSA_AES_KEY_WRAP                    (0x1054UL)
#define CKM_JUNIPER_KEY_GEN                     (0x1060UL)
#define CKM_JUNIPER_ECB128                      (0x1061UL)
#define CKM_JUNIPER_CBC128                      (0x1062UL)
#define CKM_JUNIPER_COUNTER                     (0x1063UL)
#define CKM_JUNIPER_SHUFFLE                     (0x1064UL)
#define CKM_JUNIPER_WRAP                        (0x1065UL)
#define CKM_FASTHASH                            (0x1070UL)
#define CKM_AES_XTS                             (0x1071UL)
#define CKM_AES_XTS_KEY_GEN                     (0x1072UL)
#define CKM_AES_KEY_GEN                         (0x1080UL)
#define CKM_AES_ECB                             (0x1081UL)
#define CKM_AES_CBC                             (0x1082UL)
#define CKM_AES_MAC                             (0x1083UL)
#define CKM_AES_MAC_GENERAL                     (0x1084UL)
#define CKM_AES_CBC_PAD                         (0x1085UL)
#define CKM_AES_CTR                             (0x1086UL)
#define CKM_AES_GCM                             (0x1087UL)
#define CKM_AES_CCM                             (0x1088UL)
#define CKM_AES_CTS                             (0x1089UL)
#define CKM_AES_CMAC                            (0x108aUL)
#define CKM_AES_CMAC_GENERAL                    (0x108bUL)
#define CKM_AES_XCBC_MAC                        (0x108cUL)
#define CKM_AES_XCBC_MAC_96                     (0x108dUL)
#define CKM_AES_GMAC                            (0x108eUL)
#define CKM_BLOWFISH_KEY_GEN                    (0x1090UL)
#define CKM_BLOWFISH_CBC                        (0x1091UL)
#define CKM_TWOFISH_KEY_GEN                     (0x1092UL)
#define CKM_TWOFISH_CBC                         (0x1093UL)
#define CKM_BLOWFISH_CBC_PAD                    (0x1094UL)
#define CKM_TWOFISH_CBC_PAD                     (0x1095UL)
#define CKM_DES_ECB_ENCRYPT_DATA                (0x1100UL)
#define CKM_DES_CBC_ENCRYPT_DATA                (0x1101UL)
#define CKM_DES3_ECB_ENCRYPT_DATA               (0x1102UL)
#define CKM_DES3_CBC_ENCRYPT_DATA               (0x1103UL)
#define CKM_AES_ECB_ENCRYPT_DATA                (0x1104UL)
#define CKM_AES_CBC_ENCRYPT_DATA                (0x1105UL)
#define CKM_GOSTR3410_KEY_PAIR_GEN              (0x1200UL)
#define CKM_GOSTR3410                           (0x1201UL)
#define CKM_GOSTR3410_WITH_GOSTR3411            (0x1202UL)
#define CKM_GOSTR3410_KEY_WRAP                  (0x1203UL)
#define CKM_GOSTR3410_DERIVE                    (0x1204UL)
#define CKM_GOSTR3411                           (0x1210UL)
#define CKM_GOSTR3411_HMAC                      (0x1211UL)
#define CKM_GOST28147_KEY_GEN                   (0x1220UL)
#define CKM_GOST28147_ECB                       (0x1221UL)
#define CKM_GOST28147                           (0x1222UL)
#define CKM_GOST28147_MAC                       (0x1223UL)
#define CKM_GOST28147_KEY_WRAP                  (0x1224UL)
#define CKM_CHACHA20_KEY_GEN                    (0x1225UL)
#define CKM_CHACHA20                            (0x1226UL)
#define CKM_POLY1305_KEY_GEN                    (0x1227UL)
#define CKM_POLY1305                            (0x1228UL)
#define CKM_DSA_PARAMETER_GEN                   (0x2000UL)
#define CKM_DH_PKCS_PARAMETER_GEN               (0x2001UL)
#define CKM_X9_42_DH_PARAMETER_GEN              (0x2002UL)
#define CKM_DSA_PROBABILISTIC_PARAMETER_GEN     (0x2003UL)
#define CKM_DSA_PROBABLISTIC_PARAMETER_GEN      (0x2003UL)
#define CKM_DSA_SHAWE_TAYLOR_PARAMETER_GEN      (0x2004UL)
#define CKM_DSA_FIPS_G_GEN                      (0x2005UL)
#define CKM_AES_OFB                             (0x2104UL)
#define CKM_AES_CFB64                           (0x2105UL)
#define CKM_AES_CFB8                            (0x2106UL)
#define CKM_AES_CFB128                          (0x2107UL)
#define CKM_AES_CFB1                            (0x2108UL)
#define CKM_AES_KEY_WRAP                        (0x2109UL)
#define CKM_AES_KEY_WRAP_PAD                    (0x210aUL)
#define CKM_AES_KEY_WRAP_KWP                    (0x210BUL)
#define CKM_AES_KEY_WRAP_PKCS7                  (0x210CUL)
#define CKM_RSA_PKCS_TPM_1_1                    (0x4001UL)
#define CKM_RSA_PKCS_OAEP_TPM_1_1               (0x4002UL)
#define CKM_SHA_1_KEY_GEN                       (0x4003UL)
#define CKM_SHA224_KEY_GEN                      (0x4004UL)
#define CKM_SHA256_KEY_GEN                      (0x4005UL)
#define CKM_SHA384_KEY_GEN                      (0x4006UL)
#define CKM_SHA512_KEY_GEN                      (0x4007UL)
#define CKM_SHA512_224_KEY_GEN                  (0x4008UL)
#define CKM_SHA512_256_KEY_GEN                  (0x4009UL)
#define CKM_SHA512_T_KEY_GEN                    (0x400aUL)
#define CKM_NULL                                (0x400bUL)
#define CKM_BLAKE2B_160                         (0x400cUL)
#define CKM_BLAKE2B_160_HMAC                    (0x400dUL)
#define CKM_BLAKE2B_160_HMAC_GENERAL            (0x400eUL)
#define CKM_BLAKE2B_160_KEY_DERIVE              (0x400fUL)
#define CKM_BLAKE2B_160_KEY_GEN                 (0x4010UL)
#define CKM_BLAKE2B_256                         (0x4011UL)
#define CKM_BLAKE2B_256_HMAC                    (0x4012UL)
#define CKM_BLAKE2B_256_HMAC_GENERAL            (0x4013UL)
#define CKM_BLAKE2B_256_KEY_DERIVE              (0x4014UL)
#define CKM_BLAKE2B_256_KEY_GEN                 (0x4015UL)
#define CKM_BLAKE2B_384                         (0x4016UL)
#define CKM_BLAKE2B_384_HMAC                    (0x4017UL)
#define CKM_BLAKE2B_384_HMAC_GENERAL            (0x4018UL)
#define CKM_BLAKE2B_384_KEY_DERIVE              (0x4019UL)
#define CKM_BLAKE2B_384_KEY_GEN                 (0x401aUL)
#define CKM_BLAKE2B_512                         (0x401bUL)
#define CKM_BLAKE2B_512_HMAC                    (0x401cUL)
#define CKM_BLAKE2B_512_HMAC_GENERAL            (0x401dUL)
#define CKM_BLAKE2B_512_KEY_DERIVE              (0x401eUL)
#define CKM_BLAKE2B_512_KEY_GEN                 (0x401fUL)
#define CKM_SALSA20                             (0x4020UL)
#define CKM_CHACHA20_POLY1305                   (0x4021UL)
#define CKM_SALSA20_POLY1305                    (0x4022UL)
#define CKM_X3DH_INITIALIZE                     (0x4023UL)
#define CKM_X3DH_RESPOND                        (0x4024UL)
#define CKM_X2RATCHET_INITIALIZE                (0x4025UL)
#define CKM_X2RATCHET_RESPOND                   (0x4026UL)
#define CKM_X2RATCHET_ENCRYPT                   (0x4027UL)
#define CKM_X2RATCHET_DECRYPT                   (0x4028UL)
#define CKM_XEDDSA                              (0x4029UL)
#define CKM_HKDF_DERIVE                         (0x402aUL)
#define CKM_HKDF_DATA                           (0x402bUL)
#define CKM_HKDF_KEY_GEN                        (0x402cUL)
#define CKM_SALSA20_KEY_GEN                     (0x402dUL)
#define CKM_ECDSA_SHA3_224                      (0x1047UL)
#define CKM_ECDSA_SHA3_256                      (0x1048UL)
#define CKM_ECDSA_SHA3_384                      (0x1049UL)
#define CKM_ECDSA_SHA3_512                      (0x104aUL)
#define CKM_EC_EDWARDS_KEY_PAIR_GEN             (0x1055UL)
#define CKM_EC_MONTGOMERY_KEY_PAIR_GEN          (0x1056UL)
#define CKM_EDDSA                               (0x1057UL)
#define CKM_SP800_108_COUNTER_KDF               (0x3acUL)
#define CKM_SP800_108_FEEDBACK_KDF              (0x3adUL)
#define CKM_SP800_108_DOUBLE_PIPELINE_KDF       (0x3AEUL)
#define CKM_IKE2_PRF_PLUS_DERIVE                (0x402EUL)
#define CKM_IKE_PRF_DERIVE                      (0x402FUL)
#define CKM_IKE1_PRF_DERIVE                     (0x4030UL)
#define CKM_IKE1_EXTENDED_DERIVE                (0x4031UL)
#define CKM_HSS_KEY_PAIR_GEN                    (0x4032UL)
#define CKM_HSS                                 (0x4033UL)
#define CKM_XMSS_KEY_PAIR_GEN                   (0x4034UL)
#define CKM_XMSSMT_KEY_PAIR_GEN                 (0x4035UL)
#define CKM_XMSS                                (0x4036UL)
#define CKM_XMSSMT                              (0x4037UL)
#define CKM_ECDH_X_AES_KEY_WRAP                 (0x4038UL)
#define CKM_ECDH_COF_AES_KEY_WRAP               (0x4039UL)
#define CKM_PUB_KEY_FROM_PRIV_KEY               (0x403AUL)
#define CKM_VENDOR_DEFINED                      ((unsigned long) (1UL << 31))

/* CK_NOTIFICATION */
#define CKN_SURRENDER                           (0UL)
#define CKN_OTP_CHANGED                         (1UL)

/* CK_OBJECT_CLASS */
#define CKO_DATA                                (0UL)
#define CKO_CERTIFICATE                         (1UL)
#define CKO_PUBLIC_KEY                          (2UL)
#define CKO_PRIVATE_KEY                         (3UL)
#define CKO_SECRET_KEY                          (4UL)
#define CKO_HW_FEATURE                          (5UL)
#define CKO_DOMAIN_PARAMETERS                   (6UL)
#define CKO_MECHANISM                           (7UL)
#define CKO_OTP_KEY                             (8UL)
#define CKO_PROFILE                             (9UL)
#define CKO_VALIDATION                          (0xaUL)
#define CKO_TRUST                               (0xbUL)
#define CKO_VENDOR_DEFINED                      ((unsigned long) (1UL << 31))

/* CK_OTP_PARAM_TYPE */
#define CK_OTP_VALUE                            (0UL)
#define CK_OTP_PIN                              (1UL)
#define CK_OTP_CHALLENGE                        (2UL)
#define CK_OTP_TIME                             (3UL)
#define CK_OTP_COUNTER                          (4UL)
#define CK_OTP_FLAGS                            (5UL)
#define CK_OTP_OUTPUT_LENGTH                    (6UL)
#define CK_OTP_OUTPUT_FORMAT                    (7UL)
#define CK_OTP_FORMAT                           (7UL)

/* CK_PKCS5_PBKD2_PSEUDO_RANDOM_FUNCTION_TYPE */
#define CKP_PKCS5_PBKD2_HMAC_SHA1               (1UL)
#define CKP_PKCS5_PBKD2_HMAC_GOSTR3411          (2UL)
#define CKP_PKCS5_PBKD2_HMAC_SHA224             (3UL)
#define CKP_PKCS5_PBKD2_HMAC_SHA256             (4UL)
#define CKP_PKCS5_PBKD2_HMAC_SHA384             (5UL)
#define CKP_PKCS5_PBKD2_HMAC_SHA512             (6UL)
#define CKP_PKCS5_PBKD2_HMAC_SHA512_224         (7UL)
#define CKP_PKCS5_PBKD2_HMAC_SHA512_256         (8UL)

/* CK_ML_DSA_PARAMETER_SET_TYPE */
#define CKP_ML_DSA_44                           (1UL)
#define CKP_ML_DSA_65                           (2UL)
#define CKP_ML_DSA_87                           (3UL)

/* CK_ML_KEM_PARAMETER_SET_TYPE */
#define CKP_ML_KEM_512                          (1UL)
#define CKP_ML_KEM_768                          (2UL)
#define CKP_ML_KEM_1024                         (3UL)

/* CK_SLH_DSA_PARAMETER_SET_TYPE */
#define CKP_SLH_DSA_SHA2_128S                   (1UL)
#define CKP_SLH_DSA_SHAKE_128S                  (2UL)
#define CKP_SLH_DSA_SHA2_128F                   (3UL)
#define CKP_SLH_DSA_SHAKE_128F                  (4UL)
#define CKP_SLH_DSA_SHA2_192S                   (5UL)
#define CKP_SLH_DSA_SHAKE_192S                  (6UL)
#define CKP_SLH_DSA_SHA2_192F                   (7UL)
#define CKP_SLH_DSA_SHAKE_192F                  (8UL)
#define CKP_SLH_DSA_SHA2_256S                   (9UL)
#define CKP_SLH_DSA_SHAKE_256S                  (0xaUL)
#define CKP_SLH_DSA_SHA2_256F                   (0xbUL)
#define CKP_SLH_DSA_SHAKE_256F                  (0xcUL)

/* CK_PKCS5_PBKDF2_SALT_SOURCE_TYPE */
#define CKZ_SALT_SPECIFIED                      (0x1UL)

/* CK_PRF_DATA_TYPE */
#define CK_SP800_108_ITERATION_VARIABLE         (1UL)
#define CK_SP800_108_OPTIONAL_COUNTER           (2UL)
#define CK_SP800_108_COUNTER                    (2UL)
#define CK_SP800_108_DKM_LENGTH                 (3UL)
#define CK_SP800_108_BYTE_ARRAY                 (4UL)
#define CK_SP800_108_KEY_HANDLE                 (5UL)

/* CK_PROFILE_ID */
#define CKP_INVALID_ID                          (0UL)
#define CKP_BASELINE_PROVIDER                   (1UL)
#define CKP_EXTENDED_PROVIDER                   (2UL)
#define CKP_AUTHENTICATION_TOKEN                (3UL)
#define CKP_PUBLIC_CERTIFICATES_TOKEN           (4UL)
#define CKP_COMPLETE_PROVIDER                   (5UL)
#define CKP_HKDF_TLS_TOKEN                      (6UL)
#define CKP_VENDOR_DEFINED                      (1UL << 31)

/* CK_RSA_PKCS_MGF_TYPE */
#define CKG_MGF1_SHA1                           (0x1UL)
#define CKG_MGF1_SHA224                         (0x5UL)
#define CKG_MGF1_SHA256                         (0x2UL)
#define CKG_MGF1_SHA384                         (0x3UL)
#define CKG_MGF1_SHA512                         (0x4UL)
#define CKG_MGF1_SHA3_224                       (0x6UL)
#define CKG_MGF1_SHA3_256                       (0x7UL)
#define CKG_MGF1_SHA3_384                       (0x8UL)
#define CKG_MGF1_SHA3_512                       (0x9UL)

/* CK_RSA_PKCS_OAEP_SOURCE_TYPE */
#define CKZ_DATA_SPECIFIED                      (0x1UL)

/* CK_RV */
#define CKR_OK                                  (0UL)
#define CKR_CANCEL                              (1UL)
#define CKR_HOST_MEMORY                         (2UL)
#define CKR_SLOT_ID_INVALID                     (3UL)
#define CKR_GENERAL_ERROR                       (5UL)
#define CKR_FUNCTION_FAILED                     (6UL)
#define CKR_ARGUMENTS_BAD                       (7UL)
#define CKR_NO_EVENT                            (8UL)
#define CKR_NEED_TO_CREATE_THREADS              (9UL)
#define CKR_CANT_LOCK                           (0xaUL)
#define CKR_ATTRIBUTE_READ_ONLY                 (0x10UL)
#define CKR_ATTRIBUTE_SENSITIVE                 (0x11UL)
#define CKR_ATTRIBUTE_TYPE_INVALID              (0x12UL)
#define CKR_ATTRIBUTE_VALUE_INVALID             (0x13UL)
#define CKR_ACTION_PROHIBITED                   (0x1bUL)
#define CKR_DATA_INVALID                        (0x20UL)
#define CKR_DATA_LEN_RANGE                      (0x21UL)
#define CKR_DEVICE_ERROR                        (0x30UL)
#define CKR_DEVICE_MEMORY                       (0x31UL)
#define CKR_DEVICE_REMOVED                      (0x32UL)
#define CKR_ENCRYPTED_DATA_INVALID              (0x40UL)
#define CKR_ENCRYPTED_DATA_LEN_RANGE            (0x41UL)
#define CKR_AEAD_DECRYPT_FAILED                 (0x42UL)
#define CKR_FUNCTION_CANCELED                   (0x50UL)
#define CKR_FUNCTION_NOT_PARALLEL               (0x51UL)
#define CKR_FUNCTION_NOT_SUPPORTED              (0x54UL)
#define CKR_KEY_HANDLE_INVALID                  (0x60UL)
#define CKR_KEY_SIZE_RANGE                      (0x62UL)
#define CKR_KEY_TYPE_INCONSISTENT               (0x63UL)
#define CKR_KEY_NOT_NEEDED                      (0x64UL)
#define CKR_KEY_CHANGED                         (0x65UL)
#define CKR_KEY_NEEDED                          (0x66UL)
#define CKR_KEY_INDIGESTIBLE                    (0x67UL)
#define CKR_KEY_FUNCTION_NOT_PERMITTED          (0x68UL)
#define CKR_KEY_NOT_WRAPPABLE                   (0x69UL)
#define CKR_KEY_UNEXTRACTABLE                   (0x6aUL)
#define CKR_MECHANISM_INVALID                   (0x70UL)
#define CKR_MECHANISM_PARAM_INVALID             (0x71UL)
#define CKR_OBJECT_HANDLE_INVALID               (0x82UL)
#define CKR_OPERATION_ACTIVE                    (0x90UL)
#define CKR_OPERATION_NOT_INITIALIZED           (0x91UL)
#define CKR_PIN_INCORRECT                       (0xa0UL)
#define CKR_PIN_INVALID                         (0xa1UL)
#define CKR_PIN_LEN_RANGE                       (0xa2UL)
#define CKR_PIN_EXPIRED                         (0xa3UL)
#define CKR_PIN_LOCKED                          (0xa4UL)
#define CKR_SESSION_CLOSED                      (0xb0UL)
#define CKR_SESSION_COUNT                       (0xb1UL)
#define CKR_SESSION_HANDLE_INVALID              (0xb3UL)
#define CKR_SESSION_PARALLEL_NOT_SUPPORTED      (0xb4UL)
#define CKR_SESSION_READ_ONLY                   (0xb5UL)
#define CKR_SESSION_EXISTS                      (0xb6UL)
#define CKR_SESSION_READ_ONLY_EXISTS            (0xb7UL)
#define CKR_SESSION_READ_WRITE_SO_EXISTS        (0xb8UL)
#define CKR_SIGNATURE_INVALID                   (0xc0UL)
#define CKR_SIGNATURE_LEN_RANGE                 (0xc1UL)
#define CKR_TEMPLATE_INCOMPLETE                 (0xd0UL)
#define CKR_TEMPLATE_INCONSISTENT               (0xd1UL)
#define CKR_TOKEN_NOT_PRESENT                   (0xe0UL)
#define CKR_TOKEN_NOT_RECOGNIZED                (0xe1UL)
#define CKR_TOKEN_WRITE_PROTECTED               (0xe2UL)
#define CKR_UNWRAPPING_KEY_HANDLE_INVALID       (0xf0UL)
#define CKR_UNWRAPPING_KEY_SIZE_RANGE           (0xf1UL)
#define CKR_UNWRAPPING_KEY_TYPE_INCONSISTENT    (0xf2UL)
#define CKR_USER_ALREADY_LOGGED_IN              (0x100UL)
#define CKR_USER_NOT_LOGGED_IN                  (0x101UL)
#define CKR_USER_PIN_NOT_INITIALIZED            (0x102UL)
#define CKR_USER_TYPE_INVALID                   (0x103UL)
#define CKR_USER_ANOTHER_ALREADY_LOGGED_IN      (0x104UL)
#define CKR_USER_TOO_MANY_TYPES                 (0x105UL)
#define CKR_WRAPPED_KEY_INVALID                 (0x110UL)
#define CKR_WRAPPED_KEY_LEN_RANGE               (0x112UL)
#define CKR_WRAPPING_KEY_HANDLE_INVALID         (0x113UL)
#define CKR_WRAPPING_KEY_SIZE_RANGE             (0x114UL)
#define CKR_WRAPPING_KEY_TYPE_INCONSISTENT      (0x115UL)
#define CKR_RANDOM_SEED_NOT_SUPPORTED           (0x120UL)
#define CKR_RANDOM_NO_RNG                       (0x121UL)
#define CKR_DOMAIN_PARAMS_INVALID               (0x130UL)
#define CKR_CURVE_NOT_SUPPORTED                 (0x140UL)
#define CKR_BUFFER_TOO_SMALL                    (0x150UL)
#define CKR_SAVED_STATE_INVALID                 (0x160UL)
#define CKR_INFORMATION_SENSITIVE               (0x170UL)
#define CKR_STATE_UNSAVEABLE                    (0x180UL)
#define CKR_CRYPTOKI_NOT_INITIALIZED            (0x190UL)
#define CKR_CRYPTOKI_ALREADY_INITIALIZED        (0x191UL)
#define CKR_MUTEX_BAD                           (0x1a0UL)
#define CKR_MUTEX_NOT_LOCKED                    (0x1a1UL)
#define CKR_NEW_PIN_MODE                        (0x1b0UL)
#define CKR_NEXT_OTP                            (0x1b1UL)
#define CKR_EXCEEDED_MAX_ITERATIONS             (0x1b5UL)
#define CKR_FIPS_SELF_TEST_FAILED               (0x1b6UL)
#define CKR_LIBRARY_LOAD_FAILED                 (0x1b7UL)
#define CKR_PIN_TOO_WEAK                        (0x1b8UL)
#define CKR_PUBLIC_KEY_INVALID                  (0x1b9UL)
#define CKR_FUNCTION_REJECTED                   (0x200UL)
#define CKR_TOKEN_RESOURCE_EXCEEDED             (0x201UL)
#define CKR_OPERATION_CANCEL_FAILED             (0x202UL)
#define CKR_KEY_EXHAUSTED                       (0x203UL)
#define CKR_PENDING                             (0x204UL)
#define CKR_SESSION_ASYNC_NOT_SUPPORTED         (0x205UL)
#define CKR_SEED_RANDOM_REQUIRED                (0x206UL)
#define CKR_OPERATION_NOT_VALIDATED             (0x207UL)
#define CKR_TOKEN_NOT_INITIALIZED               (0x208UL)
#define CKR_PARAMETER_SET_NOT_SUPPORTED         (0x209UL)
#define CKR_VENDOR_DEFINED                      ((unsigned long) (1UL << 31))

/* CK_SP800_108_DKM_LENGTH_METHOD */
#define CK_SP800_108_DKM_LENGTH_SUM_OF_KEYS     (1UL)
#define CK_SP800_108_DKM_LENGTH_SUM_OF_SEGMENTS (2UL)

/* CK_STATE */
#define CKS_RO_PUBLIC_SESSION                   (0UL)
#define CKS_RO_USER_FUNCTIONS                   (1UL)
#define CKS_RW_PUBLIC_SESSION                   (2UL)
#define CKS_RW_USER_FUNCTIONS                   (3UL)
#define CKS_RW_SO_FUNCTIONS                     (4UL)

/* CK_SESSION_VALIDATION_FLAGS_TYPE */
#define CKS_LAST_VALIDATION_OK                  (1UL)

/* CK_TRUST */
#define CKT_TRUST_UNKNOWN                       (0UL)
#define CKT_TRUSTED                             (1UL)
#define CKT_TRUST_ANCHOR                        (2UL)
#define CKT_NOT_TRUSTED                         (3UL)
#define CKT_TRUST_MUST_VERIFY_TRUST             (4UL)

/* CK_USER_TYPE */
#define CKU_SO                                  (0UL)
#define CKU_USER                                (1UL)
#define CKU_CONTEXT_SPECIFIC                    (2UL)

/* CK_VALIDATION_AUTHORITY_TYPE */
#define CKV_AUTHORITY_TYPE_UNSPECIFIED          (0UL)
#define CKV_AUTHORITY_TYPE_NIST_CMVP            (1UL)
#define CKV_AUTHORITY_TYPE_COMMON_CRITERIA      (2UL)

/* CK_VALIDATION_TYPE */
#define CKV_TYPE_UNSPECIFIED                    (0UL)
#define CKV_TYPE_SOFTWARE                       (1UL)
#define CKV_TYPE_HARDWARE                       (2UL)
#define CKV_TYPE_FIRMWARE                       (3UL)
#define CKV_TYPE_HYBRID                         (4UL)

/* Attribute and other constants related to OTP */
#define CK_OTP_FORMAT_DECIMAL                   (0UL)
#define CK_OTP_FORMAT_HEXADECIMAL               (1UL)
#define CK_OTP_FORMAT_ALPHANUMERIC              (2UL)
#define CK_OTP_FORMAT_BINARY                    (3UL)
#define CK_OTP_PARAM_IGNORED                    (0UL)
#define CK_OTP_PARAM_OPTIONAL                   (1UL)
#define CK_OTP_PARAM_MANDATORY                  (2UL)

#define CK_UNAVAILABLE_INFORMATION              ((unsigned long)-1L)
#define CK_EFFECTIVELY_INFINITE                 (0UL)
#define CK_INVALID_HANDLE                       (0UL)



typedef unsigned long ck_attribute_type_t;
typedef unsigned long ck_certificate_category_t;
typedef unsigned long ck_certificate_type_t;
typedef unsigned long ck_ec_kdf_type_t;
typedef unsigned long ck_extract_params_t;
typedef unsigned long ck_flags_t;
typedef unsigned long ck_generator_function_t;
typedef unsigned long ck_hss_levels_t;
typedef unsigned long ck_hw_feature_type_t;
typedef unsigned long ck_java_midp_security_domain_t;
typedef unsigned long ck_key_type_t;
typedef unsigned long ck_lms_type_t;
typedef unsigned long ck_lmots_type_t;
typedef unsigned long ck_mac_general_params_t;
typedef unsigned long ck_mechanism_type_t;
typedef unsigned long ck_notification_t;
typedef unsigned long ck_object_class_t;
typedef unsigned long ck_object_handle_t;
typedef unsigned long ck_otp_param_type_t;
typedef unsigned long ck_pkcs5_pbkd2_pseudo_random_function_type_t;
typedef unsigned long ck_pkcs5_pbkdf2_salt_source_type_t;
typedef unsigned long ck_prf_data_type_t;
typedef unsigned long ck_profile_id_t;
typedef unsigned long ck_rc2_params_t;
typedef unsigned long ck_rsa_pkcs_mgf_type_t;
typedef unsigned long ck_rsa_pkcs_oaep_source_type_t;
typedef unsigned long ck_rv_t;
typedef unsigned long ck_session_handle_t;
typedef unsigned long ck_slot_id_t;
typedef unsigned long ck_sp800_108_dkm_length_method_t;
typedef unsigned long ck_state_t;
typedef unsigned long ck_user_type_t;
typedef unsigned long ck_x2ratchet_kdf_type_t;
typedef unsigned long ck_x3dh_kdf_type_t;
typedef unsigned long ck_x9_42_dh_kdf_type_t;
typedef unsigned long ck_xeddsa_hash_type_t;
typedef unsigned long ck_hedge_type_t;
typedef unsigned long ck_ml_dsa_parameter_set_type_t;
typedef unsigned long ck_ml_kem_parameter_set_type_t;
typedef unsigned long ck_session_validation_flags_type_t;
typedef unsigned long ck_slh_dsa_parameter_set_type_t;
typedef unsigned long ck_trust_t;
typedef unsigned long ck_validation_authority_type_t;
typedef unsigned long ck_validation_type_t;
typedef unsigned long ck_xmssmt_parameter_set_type_t;
typedef unsigned long ck_xmss_parameter_set_type_t;

typedef ck_mechanism_type_t ck_sp800_108_prf_type_t;
typedef ck_otp_param_type_t ck_param_type;
typedef ck_profile_id_t ck_profile_id;
typedef ck_ec_kdf_type_t ck_ec_kdf_t;

typedef ck_rv_t (*ck_createmutex_t)     (void **mutex);
typedef ck_rv_t (*ck_destroymutex_t)    (void *mutex);
typedef ck_rv_t (*ck_lockmutex_t)       (void *mutex);
typedef ck_rv_t (*ck_unlockmutex_t)     (void *mutex);
typedef ck_rv_t (*ck_notify_t)          (ck_session_handle_t session,
					 ck_notification_t event,
					 void *application);



struct ck_attribute
{
  ck_attribute_type_t type;
  void *value;
  unsigned long value_len;
};

struct ck_c_initialize_args
{
  ck_createmutex_t create_mutex;
  ck_destroymutex_t destroy_mutex;
  ck_lockmutex_t lock_mutex;
  ck_unlockmutex_t unlock_mutex;
  ck_flags_t flags;
  void *reserved;
};

struct ck_date
{
  unsigned char year[4];
  unsigned char month[2];
  unsigned char day[2];
};

struct ck_derived_key
{
  struct ck_attribute *templ;
  unsigned long attribute_count;
  ck_object_handle_t *key_ptr;
};

struct ck_version
{
  unsigned char major;
  unsigned char minor;
};

struct ck_info
{
  struct ck_version cryptoki_version;
  unsigned char manufacturer_id[32];
  ck_flags_t flags;
  unsigned char library_description[32];
  struct ck_version library_version;
};

struct ck_interface {
  char *interface_name_ptr;
  void *function_list_ptr;
  ck_flags_t flags;
};

struct ck_mechanism
{
  ck_mechanism_type_t mechanism;
  void *parameter;
  unsigned long parameter_len;
};

struct ck_mechanism_info
{
  unsigned long min_key_size;
  unsigned long max_key_size;
  ck_flags_t flags;
};

struct ck_session_info
{
  ck_slot_id_t slot_id;
  ck_state_t state;
  ck_flags_t flags;
  unsigned long device_error;
};

struct ck_slot_info
{
  unsigned char slot_description[64];
  unsigned char manufacturer_id[32];
  ck_flags_t flags;
  struct ck_version hardware_version;
  struct ck_version firmware_version;
};

struct ck_token_info
{
  unsigned char label[32];
  unsigned char manufacturer_id[32];
  unsigned char model[16];
  unsigned char serial_number[16];
  ck_flags_t flags;
  unsigned long max_session_count;
  unsigned long session_count;
  unsigned long max_rw_session_count;
  unsigned long rw_session_count;
  unsigned long max_pin_len;
  unsigned long min_pin_len;
  unsigned long total_public_memory;
  unsigned long free_public_memory;
  unsigned long total_private_memory;
  unsigned long free_private_memory;
  struct ck_version hardware_version;
  struct ck_version firmware_version;
  unsigned char utc_time[16];
};

struct ck_aes_cbc_encrypt_data_params {
  unsigned char iv[16];
  unsigned char *data_params;
  unsigned long length;
};

struct ck_aes_ccm_params {
  unsigned long data_len;
  unsigned char *nonce_ptr;
  unsigned long nonce_len;
  unsigned char *aad_ptr;
  unsigned long aad_len;
  unsigned long mac_len;
};

struct ck_aes_ctr_params {
  unsigned long counter_bits;
  unsigned char cb[16];
};

struct ck_aes_gcm_params {
  unsigned char *iv_ptr;
  unsigned long iv_len;
  unsigned long iv_bits;
  unsigned char *aad_ptr;
  unsigned long aad_len;
  unsigned long tag_bits;
};

struct ck_aria_cbc_encrypt_data_params {
  unsigned char iv[16];
  unsigned char *data_params;
  unsigned long length;
};

struct ck_async_data {
  unsigned long version_num;
  unsigned char *value;
  unsigned long value_len;
  ck_object_handle_t object_handle;
  ck_object_handle_t additional_object_handle;
};

struct ck_camellia_cbc_encrypt_data_params {
  unsigned char iv[16];
  unsigned char *data_params;
  unsigned long length;
};

struct ck_camellia_ctr_params {
  unsigned long counter_bits;
  unsigned char cb[16];
};

struct ck_ccm_message_params {
  unsigned long data_len;
  unsigned char *nonce_ptr;
  unsigned long nonce_len;
  unsigned long nonce_fixed_bits;
  ck_generator_function_t nonce_generator;
  unsigned char *mac_ptr;
  unsigned long mac_len;
};

struct ck_ccm_params {
  unsigned long data_len;
  unsigned char *nonce;
  unsigned long nonce_len;
  unsigned char *aad;
  unsigned long aad_len;
  unsigned long mac_len;
};

struct ck_ccm_wrap_params {
  unsigned long data_len;
  unsigned char *nonce_ptr;
  unsigned long nonce_len;
  unsigned long nonce_fixed_bits;
  ck_generator_function_t nonce_generator;
  unsigned char *aad_ptr;
  unsigned long aad_len;
  unsigned long mac_len;
};

struct ck_chacha20_params {
  unsigned char *block_counter;
  unsigned long block_counter_bits;
  unsigned char *nonce_ptr;
  unsigned long nonce_bits;
};

struct ck_cms_sig_params {
  ck_object_handle_t certificate_handle;
  struct ck_mechanism *signing_mechanism_ptr;
  struct ck_mechanism *digest_mechanism_ptr;
  unsigned char *content_type;
  unsigned char *requested_attributes;
  unsigned long requested_attributes_len;
  unsigned char *required_attributes;
  unsigned long required_attributes_len;
};

struct ck_des_cbc_encrypt_data_params {
  unsigned char iv[8];
  unsigned char *data_params;
  unsigned long length;
};

struct ck_dsa_parameter_gen_param {
  ck_mechanism_type_t hash;
  unsigned char *seed_ptr;
  unsigned long seed_len;
  unsigned long index;
};

struct ck_ecdh_aes_key_wrap_params {
  unsigned long aes_key_bits;
  ck_ec_kdf_type_t kdf;
  unsigned long shared_data_len;
  unsigned char *shared_data;
};

struct ck_ecdh1_derive_params {
  ck_ec_kdf_type_t kdf;
  unsigned long shared_data_len;
  unsigned char *shared_data;
  unsigned long public_data_len;
  unsigned char *public_data;
};

struct ck_ecdh2_derive_params {
  ck_ec_kdf_type_t kdf;
  unsigned long shared_data_len;
  unsigned char *shared_data;
  unsigned long public_data_len;
  unsigned char *public_data;
  unsigned long private_data_len;
  ck_object_handle_t private_data;
  unsigned long public_data_len2;
  unsigned char *public_data2;
};

struct ck_ecmqv_derive_params {
  ck_ec_kdf_type_t kdf;
  unsigned long shared_data_len;
  unsigned char *shared_data;
  unsigned long public_data_len;
  unsigned char *public_data;
  unsigned long private_data_len;
  ck_object_handle_t private_data;
  unsigned long public_data_len2;
  unsigned char *public_data2;
  ck_object_handle_t public_key;
};

struct ck_eddsa_params {
  unsigned char flag;
  unsigned long context_data_len;
  unsigned char *context_data;
};

struct ck_gcm_message_params {
  unsigned char *iv_ptr;
  unsigned long iv_len;
  unsigned long iv_fixed_bits;
  ck_generator_function_t iv_generator;
  unsigned char *tag_ptr;
  unsigned long tag_bits;
};

struct ck_gcm_params {
  unsigned char *iv_ptr;
  unsigned long iv_len;
  unsigned long iv_bits;
  unsigned char *aad_ptr;
  unsigned long aad_len;
  unsigned long tag_bits;
};

struct ck_gcm_wrap_params {
  unsigned char *iv_ptr;
  unsigned long iv_len;
  unsigned long iv_fixed_bits;
  ck_generator_function_t iv_generator;
  unsigned char *aad_ptr;
  unsigned long aad_len;
  unsigned long tag_bits;
};

struct ck_gostr3410_derive_params {
  ck_ec_kdf_type_t kdf;
  unsigned char *public_data;
  unsigned long public_data_len;
  unsigned char *ukm_ptr;
  unsigned long ukm_len;
};

struct ck_gostr3410_key_wrap_params {
  unsigned char *wrap_oid;
  unsigned long wrap_oid_len;
  unsigned char *ukm_ptr;
  unsigned long ukm_len;
  ck_object_handle_t key;
};

struct ck_hash_sign_additional_context {
  ck_hedge_type_t hedge_variant;
  unsigned char *context_ptr;
  unsigned long context_len;
  ck_mechanism_type_t hash;
};

struct ck_hkdf_params {
  unsigned char extract;
  unsigned char expand;
  ck_mechanism_type_t prf_hash_mechanism;
  unsigned long salt_type;
  unsigned char *salt_ptr;
  unsigned long salt_len;
  ck_object_handle_t salt_key;
  unsigned char *info;
  unsigned long info_len;
};

struct ck_kea_derive_params {
  unsigned char is_sender;
  unsigned long random_len;
  unsigned char *random_a;
  unsigned char *random_b;
  unsigned long public_data_len;
  unsigned char *public_data;
};

struct ck_key_derivation_string_data {
  unsigned char *string_data;
  unsigned long string_data_len;
};

struct ck_key_wrap_set_oaep_params {
  unsigned char bc;
  unsigned char *x_ptr;
  unsigned long x_len;
};

struct ck_kip_params {
  struct ck_mechanism *mechanism_ptr;
  ck_object_handle_t key;
  unsigned char *seed_ptr;
  unsigned long seed_len;
};

typedef struct ck_otp_param {
  ck_otp_param_type_t type;
  void *value;
  unsigned long value_len;
} ck_otp_param;

typedef struct ck_otp_params {
  struct ck_otp_param *params;
  unsigned long count;
} ck_otp_params;

typedef struct ck_otp_signature_info
{
  struct ck_otp_param *params;
  unsigned long count;
} ck_otp_signature_info;

struct ck_pbe_params {
  unsigned char *init_vector;
  unsigned char *password_ptr;
  unsigned long password_len;
  unsigned char *salt_ptr;
  unsigned long salt_len;
  unsigned long iteration;
};

struct ck_pkcs5_pbkd2_params {
  ck_pkcs5_pbkdf2_salt_source_type_t salt_source;
  void *salt_source_data;
  unsigned long salt_source_data_len;
  unsigned long iterations;
  ck_pkcs5_pbkd2_pseudo_random_function_type_t prf;
  void *prf_data;
  unsigned long prf_data_len;
  unsigned char *password_ptr;
  unsigned long *password_len;
};

struct ck_pkcs5_pbkd2_params2 {
  ck_pkcs5_pbkdf2_salt_source_type_t salt_source;
  void *salt_source_data;
  unsigned long salt_source_data_len;
  unsigned long iterations;
  ck_pkcs5_pbkd2_pseudo_random_function_type_t prf;
  void *prf_data;
  unsigned long prf_data_len;
  unsigned char *password_ptr;
  unsigned long password_len;
};

struct ck_prf_data_param {
  ck_prf_data_type_t type;
  void *value;
  unsigned long value_len;
};

struct ck_rc2_cbc_params {
  unsigned long effective_bits;
  unsigned char iv[8];
};

struct ck_rc2_mac_general_params {
  unsigned long effective_bits;
  unsigned long mac_length;
};

struct ck_rc5_cbc_params {
  unsigned long word_size;
  unsigned long rounds;
  unsigned char *iv_ptr;
  unsigned long iv_len;
};

struct ck_rc5_mac_general_params {
  unsigned long word_size;
  unsigned long rounds;
  unsigned long mac_length;
};

struct ck_rc5_params {
  unsigned long word_size;
  unsigned long rounds;
};

struct ck_rsa_pkcs_oaep_params {
  ck_mechanism_type_t hash_alg;
  ck_rsa_pkcs_mgf_type_t mgf;
  ck_rsa_pkcs_oaep_source_type_t source;
  void *source_data;
  unsigned long source_data_len;
};

struct ck_rsa_aes_key_wrap_params {
  unsigned long aes_key_bits;
  struct ck_rsa_pkcs_oaep_params *oaep_params;
};

struct ck_rsa_pkcs_pss_params {
  ck_mechanism_type_t hash_alg;
  ck_rsa_pkcs_mgf_type_t mgf;
  unsigned long s_len;
};

struct ck_salsa20_chacha20_poly1305_msg_params {
  unsigned char *nonce_ptr;
  unsigned long nonce_bits;
  unsigned char *tag_ptr;
};

struct ck_salsa20_chacha20_poly1305_params {
  unsigned char *nonce_ptr;
  unsigned long nonce_bits;
  unsigned char *aad_ptr;
  unsigned long aad_len;
};

struct ck_salsa20_params {
  unsigned char *block_counter;
  unsigned char *nonce_ptr;
  unsigned long nonce_bits;
};

struct ck_seed_cbc_encrypt_data_params {
  unsigned char iv[16];
  unsigned char *data_params;
  unsigned long length;
};

struct ck_sign_additional_context {
  ck_hedge_type_t hedge_variant;
  unsigned char *context_ptr;
  unsigned long context_len;
};

struct ck_skipjack_private_wrap_params {
  unsigned long password_len;
  unsigned char *password_ptr;
  unsigned long public_data_len;
  unsigned char *public_data;
  unsigned long p_and_g_len;
  unsigned long q_len;
  unsigned long random_len;
  unsigned char *random_a_ptr;
  unsigned char *prime_p;
  unsigned char *base_g;
  unsigned char *subprime_q;
};

struct ck_skipjack_relayx_params {
  unsigned long old_wrapped_x_len;
  unsigned char *old_wrapped_x;
  unsigned long old_password_len;
  unsigned char *old_password;
  unsigned long old_public_data_len;
  unsigned char *old_public_data;
  unsigned long old_random_len;
  unsigned char *old_random_a;
  unsigned long new_password_len;
  unsigned char *new_password;
  unsigned long new_public_data_len;
  unsigned char *new_public_data;
  unsigned long new_random_len;
  unsigned char *new_random_a;
};

struct ck_sp800_108_counter_format {
  unsigned char little_endian;
  unsigned long width_in_bits;
};

struct ck_sp800_108_dkm_length_format {
  ck_sp800_108_dkm_length_method_t dkm_length_method;
  unsigned char little_endian;
  unsigned long width_in_bits;
};

struct ck_sp800_108_feedback_kdf_params {
  ck_sp800_108_prf_type_t prf_type;
  unsigned long number_of_data_params;
  struct ck_prf_data_param *data_params_ptr;
  unsigned long iv_len;
  unsigned char *iv_ptr;
  unsigned long additional_derived_keys_len;
  struct ck_derived_key *additional_derived_keys;
};

struct ck_tls12_extended_master_key_derive_params {
  ck_mechanism_type_t prf_hash_mechanism;
  unsigned char *session_hash_ptr;
  unsigned long session_hash_len;
  struct ck_version *version_ptr;
};

struct ck_sp800_108_kdf_params {
  ck_sp800_108_prf_type_t prf_type;
  unsigned long number_of_data_params;
  struct ck_prf_data_param *data_params_ptr;
  unsigned long additional_derived_keys_len;
  struct ck_derived_key *additional_derived_keys;
};

struct ck_x2ratchet_initialize_params {
  unsigned char *sk;
  ck_object_handle_t peer_public_prekey;
  ck_object_handle_t peer_public_identity;
  ck_object_handle_t own_public_identity;
  unsigned char encrypted_header;
  unsigned long curve;
  ck_mechanism_type_t aead_mechanism;
  ck_x2ratchet_kdf_type_t kdf_mechanism;
};

struct ck_x2ratchet_respond_params {
  unsigned char *sk;
  ck_object_handle_t own_prekey;
  ck_object_handle_t initiator_identity;
  ck_object_handle_t own_public_identity;
  unsigned char encrypted_header;
  unsigned long curve;
  ck_mechanism_type_t aead_mechanism;
  ck_x2ratchet_kdf_type_t kdf_mechanism;
};

struct ck_x3dh_initiate_params {
  ck_x3dh_kdf_type_t kdf;
  ck_object_handle_t peer_identity;
  ck_object_handle_t peer_prekey;
  unsigned char *prekey_signature;
  unsigned char *onetime_key;
  ck_object_handle_t own_identity;
  ck_object_handle_t own_ephemeral;
};

struct ck_x3dh_respond_params {
  ck_x3dh_kdf_type_t kdf;
  unsigned char *identity_id;
  unsigned char *prekey_id;
  unsigned char *onetime_id;
  ck_object_handle_t initiator_identity;
  unsigned char *initiator_ephemeral;
};

struct ck_x9_42_dh1_derive_params {
  ck_x9_42_dh_kdf_type_t kdf;
  unsigned long other_info_len;
  unsigned char *other_info;
  unsigned long public_data_len;
  unsigned char *public_data;
};

struct ck_x9_42_dh2_derive_params {
  ck_x9_42_dh_kdf_type_t kdf;
  unsigned long other_info_len;
  unsigned char *other_info;
  unsigned long public_data_len;
  unsigned char *public_data;
  unsigned long private_data_len;
  ck_object_handle_t private_data;
  unsigned long public_data_len2;
  unsigned char *public_data2;
};

struct ck_x9_42_mqv_derive_params {
  ck_x9_42_dh_kdf_type_t kdf;
  unsigned long other_info_len;
  unsigned char *other_info;
  unsigned long public_data_len;
  unsigned char *public_data;
  unsigned long private_data_len;
  ck_object_handle_t private_data;
  unsigned long public_data_len2;
  unsigned char *public_data2;
  ck_object_handle_t public_key;
};

struct ck_xeddsa_params {
  ck_xeddsa_hash_type_t hash;
};

struct specified_params {
  ck_hss_levels_t levels;
  ck_lms_type_t lm_type[8];
  ck_lmots_type_t lm_ots_type[8];
};

struct ck_ike_prf_derive_params {
  ck_mechanism_type_t prf_mechanism;
  unsigned char data_as_key;
  unsigned char rekey;
  unsigned char *ni_ptr;
  unsigned long ni_len;
  unsigned char *nr_ptr;
  unsigned long nr_len;
  ck_object_handle_t new_key;
};

struct ck_ike1_extended_derive_params {
  ck_mechanism_type_t prf_mechanism;
  unsigned char has_key_gxy;
  ck_object_handle_t key_gxy;
  unsigned char *extra_data;
  unsigned long extra_data_len;
};

struct ck_ike1_prf_derive_params {
  ck_mechanism_type_t prf_mechanism;
  unsigned char has_prev_key;
  ck_object_handle_t key_gxy;
  ck_object_handle_t prev_key;
  unsigned char *cky_i_ptr;
  unsigned long cky_i_len;
  unsigned char *cky_r_ptr;
  unsigned long cky_r_len;
  unsigned char key_number;
};

struct ck_ike2_prf_plus_derive_params {
  ck_mechanism_type_t prf_mechanism;
  unsigned char has_seed_key;
  ck_object_handle_t seed_key;
  unsigned char *seed_data;
  unsigned long seed_data_len;
};

struct ck_ssl3_key_mat_out {
  ck_object_handle_t client_mac_secret;
  ck_object_handle_t server_mac_secret;
  ck_object_handle_t client_key;
  ck_object_handle_t server_key;
  unsigned char *iv_client;
  unsigned char *iv_server;
};

struct ck_ssl3_random_data {
  unsigned char *client_random_ptr;
  unsigned long client_random_len;
  unsigned char *server_random_ptr;
  unsigned long server_random_len;
};

struct ck_ssl3_key_mat_params {
  unsigned long mac_size_in_bits;
  unsigned long key_size_in_bits;
  unsigned long iv_size_in_bits;
  unsigned char is_export;
  struct ck_ssl3_random_data random_info;
  struct ck_ssl3_key_mat_out *returned_key_material;
};

struct ck_ssl3_master_key_derive_params {
  struct ck_ssl3_random_data random_info;
  struct ck_version *version_ptr;
};

struct ck_tls_kdf_params {
  ck_mechanism_type_t prf_mechanism;
  unsigned char *label_ptr;
  unsigned long label_length;
  struct ck_ssl3_random_data random_info;
  unsigned char *context_data;
  unsigned long context_data_length;
};

struct ck_tls_mac_params {
  ck_mechanism_type_t prf_hash_mechanism;
  unsigned long mac_length;
  unsigned long server_or_client;
};

struct ck_tls_prf_params {
  unsigned char *seed_ptr;
  unsigned long seed_len;
  unsigned char *label_ptr;
  unsigned long label_len;
  unsigned char *output_ptr;
  unsigned long *output_len_ptr;
};

struct ck_tls12_key_mat_params {
  unsigned long mac_size_in_bits;
  unsigned long key_size_in_bits;
  unsigned long iv_size_in_bits;
  unsigned char is_export;
  struct ck_ssl3_random_data random_info;
  struct ck_ssl3_key_mat_out *returned_key_material;
  ck_mechanism_type_t prf_hash_mechanism;
};

struct ck_tls12_master_key_derive_params {
  struct ck_ssl3_random_data random_info;
  struct ck_version *version_ptr;
  ck_mechanism_type_t prf_hash_mechanism;
};

struct ck_wtls_key_mat_out {
  ck_object_handle_t mac_secret;
  ck_object_handle_t key;
  unsigned char *i_v_ptr;
};

struct ck_wtls_random_data {
  unsigned char *client_random_ptr;
  unsigned long client_random_len;
  unsigned char *server_random_ptr;
  unsigned long server_random_len;
};

struct ck_wtls_key_mat_params {
  ck_mechanism_type_t digest_mechanism;
  unsigned long mac_size_in_bits;
  unsigned long key_size_in_bits;
  unsigned long iv_size_in_bits;
  unsigned long sequence_number;
  unsigned char is_export;
  struct ck_wtls_random_data random_info;
  struct ck_wtls_key_mat_out *returned_key_material;
};

struct ck_wtls_master_key_derive_params {
  ck_mechanism_type_t digest_mechanism;
  struct ck_wtls_random_data random_info;
  unsigned char *version_ptr;
};

struct ck_wtls_prf_params {
  ck_mechanism_type_t digest_mechanism;
  unsigned char *seed_ptr;
  unsigned long seed_len;
  unsigned char *label_ptr;
  unsigned long label_len;
  unsigned char *output_ptr;
  unsigned long *output_len_ptr;
};



/* Forward reference.  */
struct ck_function_list;
struct ck_function_list_3_0;
struct ck_function_list_3_2;

#define _CK_DECLARE_FUNCTION(name, args)        \
typedef ck_rv_t (*CK_ ## name) args;                \
ck_rv_t CK_SPEC name args

_CK_DECLARE_FUNCTION (C_Initialize, (void *init_args));
_CK_DECLARE_FUNCTION (C_Finalize, (void *reserved));
_CK_DECLARE_FUNCTION (C_GetInfo, (struct ck_info *info));
_CK_DECLARE_FUNCTION (C_GetFunctionList,
		      (struct ck_function_list **function_list));

_CK_DECLARE_FUNCTION (C_GetSlotList,
		      (unsigned char token_present, ck_slot_id_t *slot_list,
		       unsigned long *count));
_CK_DECLARE_FUNCTION (C_GetSlotInfo,
		      (ck_slot_id_t slot_id, struct ck_slot_info *info));
_CK_DECLARE_FUNCTION (C_GetTokenInfo,
		      (ck_slot_id_t slot_id, struct ck_token_info *info));
_CK_DECLARE_FUNCTION (C_WaitForSlotEvent,
		      (ck_flags_t flags, ck_slot_id_t *slot, void *reserved));
_CK_DECLARE_FUNCTION (C_GetMechanismList,
		      (ck_slot_id_t slot_id,
		       ck_mechanism_type_t *mechanism_list,
		       unsigned long *count));
_CK_DECLARE_FUNCTION (C_GetMechanismInfo,
		      (ck_slot_id_t slot_id, ck_mechanism_type_t type,
		       struct ck_mechanism_info *info));
_CK_DECLARE_FUNCTION (C_InitToken,
		      (ck_slot_id_t slot_id, unsigned char *pin,
		       unsigned long pin_len, unsigned char *label));
_CK_DECLARE_FUNCTION (C_InitPIN,
		      (ck_session_handle_t session, unsigned char *pin,
		       unsigned long pin_len));
_CK_DECLARE_FUNCTION (C_SetPIN,
		      (ck_session_handle_t session, unsigned char *old_pin,
		       unsigned long old_len, unsigned char *new_pin,
		       unsigned long new_len));

_CK_DECLARE_FUNCTION (C_OpenSession,
		      (ck_slot_id_t slot_id, ck_flags_t flags,
		       void *application, ck_notify_t notify,
		       ck_session_handle_t *session));
_CK_DECLARE_FUNCTION (C_CloseSession, (ck_session_handle_t session));
_CK_DECLARE_FUNCTION (C_CloseAllSessions, (ck_slot_id_t slot_id));
_CK_DECLARE_FUNCTION (C_GetSessionInfo,
		      (ck_session_handle_t session,
		       struct ck_session_info *info));
_CK_DECLARE_FUNCTION (C_GetOperationState,
		      (ck_session_handle_t session,
		       unsigned char *operation_state,
		       unsigned long *operation_state_len));
_CK_DECLARE_FUNCTION (C_SetOperationState,
		      (ck_session_handle_t session,
		       unsigned char *operation_state,
		       unsigned long operation_state_len,
		       ck_object_handle_t encryption_key,
		       ck_object_handle_t authentication_key));
_CK_DECLARE_FUNCTION (C_Login,
		      (ck_session_handle_t session, ck_user_type_t user_type,
		       unsigned char *pin, unsigned long pin_len));
_CK_DECLARE_FUNCTION (C_Logout, (ck_session_handle_t session));

_CK_DECLARE_FUNCTION (C_CreateObject,
		      (ck_session_handle_t session,
		       struct ck_attribute *templ,
		       unsigned long count, ck_object_handle_t *object));
_CK_DECLARE_FUNCTION (C_CopyObject,
		      (ck_session_handle_t session, ck_object_handle_t object,
		       struct ck_attribute *templ, unsigned long count,
		       ck_object_handle_t *new_object));
_CK_DECLARE_FUNCTION (C_DestroyObject,
		      (ck_session_handle_t session,
		       ck_object_handle_t object));
_CK_DECLARE_FUNCTION (C_GetObjectSize,
		      (ck_session_handle_t session,
		       ck_object_handle_t object,
		       unsigned long *size));
_CK_DECLARE_FUNCTION (C_GetAttributeValue,
		      (ck_session_handle_t session,
		       ck_object_handle_t object,
		       struct ck_attribute *templ,
		       unsigned long count));
_CK_DECLARE_FUNCTION (C_SetAttributeValue,
		      (ck_session_handle_t session,
		       ck_object_handle_t object,
		       struct ck_attribute *templ,
		       unsigned long count));
_CK_DECLARE_FUNCTION (C_FindObjectsInit,
		      (ck_session_handle_t session,
		       struct ck_attribute *templ,
		       unsigned long count));
_CK_DECLARE_FUNCTION (C_FindObjects,
		      (ck_session_handle_t session,
		       ck_object_handle_t *object,
		       unsigned long max_object_count,
		       unsigned long *object_count));
_CK_DECLARE_FUNCTION (C_FindObjectsFinal,
		      (ck_session_handle_t session));

_CK_DECLARE_FUNCTION (C_EncryptInit,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       ck_object_handle_t key));
_CK_DECLARE_FUNCTION (C_Encrypt,
		      (ck_session_handle_t session,
		       unsigned char *data, unsigned long data_len,
		       unsigned char *encrypted_data,
		       unsigned long *encrypted_data_len));
_CK_DECLARE_FUNCTION (C_EncryptUpdate,
		      (ck_session_handle_t session,
		       unsigned char *part, unsigned long part_len,
		       unsigned char *encrypted_part,
		       unsigned long *encrypted_part_len));
_CK_DECLARE_FUNCTION (C_EncryptFinal,
		      (ck_session_handle_t session,
		       unsigned char *last_encrypted_part,
		       unsigned long *last_encrypted_part_len));

_CK_DECLARE_FUNCTION (C_DecryptInit,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       ck_object_handle_t key));
_CK_DECLARE_FUNCTION (C_Decrypt,
		      (ck_session_handle_t session,
		       unsigned char *encrypted_data,
		       unsigned long encrypted_data_len,
		       unsigned char *data, unsigned long *data_len));
_CK_DECLARE_FUNCTION (C_DecryptUpdate,
		      (ck_session_handle_t session,
		       unsigned char *encrypted_part,
		       unsigned long encrypted_part_len,
		       unsigned char *part, unsigned long *part_len));
_CK_DECLARE_FUNCTION (C_DecryptFinal,
		      (ck_session_handle_t session,
		       unsigned char *last_part,
		       unsigned long *last_part_len));

_CK_DECLARE_FUNCTION (C_DigestInit,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism));
_CK_DECLARE_FUNCTION (C_Digest,
		      (ck_session_handle_t session,
		       unsigned char *data, unsigned long data_len,
		       unsigned char *digest,
		       unsigned long *digest_len));
_CK_DECLARE_FUNCTION (C_DigestUpdate,
		      (ck_session_handle_t session,
		       unsigned char *part, unsigned long part_len));
_CK_DECLARE_FUNCTION (C_DigestKey,
		      (ck_session_handle_t session, ck_object_handle_t key));
_CK_DECLARE_FUNCTION (C_DigestFinal,
		      (ck_session_handle_t session,
		       unsigned char *digest,
		       unsigned long *digest_len));

_CK_DECLARE_FUNCTION (C_SignInit,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       ck_object_handle_t key));
_CK_DECLARE_FUNCTION (C_Sign,
		      (ck_session_handle_t session,
		       unsigned char *data, unsigned long data_len,
		       unsigned char *signature,
		       unsigned long *signature_len));
_CK_DECLARE_FUNCTION (C_SignUpdate,
		      (ck_session_handle_t session,
		       unsigned char *part, unsigned long part_len));
_CK_DECLARE_FUNCTION (C_SignFinal,
		      (ck_session_handle_t session,
		       unsigned char *signature,
		       unsigned long *signature_len));
_CK_DECLARE_FUNCTION (C_SignRecoverInit,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       ck_object_handle_t key));
_CK_DECLARE_FUNCTION (C_SignRecover,
		      (ck_session_handle_t session,
		       unsigned char *data, unsigned long data_len,
		       unsigned char *signature,
		       unsigned long *signature_len));

_CK_DECLARE_FUNCTION (C_VerifyInit,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       ck_object_handle_t key));
_CK_DECLARE_FUNCTION (C_Verify,
		      (ck_session_handle_t session,
		       unsigned char *data, unsigned long data_len,
		       unsigned char *signature,
		       unsigned long signature_len));
_CK_DECLARE_FUNCTION (C_VerifyUpdate,
		      (ck_session_handle_t session,
		       unsigned char *part, unsigned long part_len));
_CK_DECLARE_FUNCTION (C_VerifyFinal,
		      (ck_session_handle_t session,
		       unsigned char *signature,
		       unsigned long signature_len));
_CK_DECLARE_FUNCTION (C_VerifyRecoverInit,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       ck_object_handle_t key));
_CK_DECLARE_FUNCTION (C_VerifyRecover,
		      (ck_session_handle_t session,
		       unsigned char *signature,
		       unsigned long signature_len,
		       unsigned char *data,
		       unsigned long *data_len));

_CK_DECLARE_FUNCTION (C_DigestEncryptUpdate,
		      (ck_session_handle_t session,
		       unsigned char *part, unsigned long part_len,
		       unsigned char *encrypted_part,
		       unsigned long *encrypted_part_len));
_CK_DECLARE_FUNCTION (C_DecryptDigestUpdate,
		      (ck_session_handle_t session,
		       unsigned char *encrypted_part,
		       unsigned long encrypted_part_len,
		       unsigned char *part,
		       unsigned long *part_len));
_CK_DECLARE_FUNCTION (C_SignEncryptUpdate,
		      (ck_session_handle_t session,
		       unsigned char *part, unsigned long part_len,
		       unsigned char *encrypted_part,
		       unsigned long *encrypted_part_len));
_CK_DECLARE_FUNCTION (C_DecryptVerifyUpdate,
		      (ck_session_handle_t session,
		       unsigned char *encrypted_part,
		       unsigned long encrypted_part_len,
		       unsigned char *part,
		       unsigned long *part_len));

_CK_DECLARE_FUNCTION (C_GenerateKey,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       struct ck_attribute *templ,
		       unsigned long count,
		       ck_object_handle_t *key));
_CK_DECLARE_FUNCTION (C_GenerateKeyPair,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       struct ck_attribute *public_key_template,
		       unsigned long public_key_attribute_count,
		       struct ck_attribute *private_key_template,
		       unsigned long private_key_attribute_count,
		       ck_object_handle_t *public_key,
		       ck_object_handle_t *private_key));
_CK_DECLARE_FUNCTION (C_WrapKey,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       ck_object_handle_t wrapping_key,
		       ck_object_handle_t key,
		       unsigned char *wrapped_key,
		       unsigned long *wrapped_key_len));
_CK_DECLARE_FUNCTION (C_UnwrapKey,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       ck_object_handle_t unwrapping_key,
		       unsigned char *wrapped_key,
		       unsigned long wrapped_key_len,
		       struct ck_attribute *templ,
		       unsigned long attribute_count,
		       ck_object_handle_t *key));
_CK_DECLARE_FUNCTION (C_DeriveKey,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       ck_object_handle_t base_key,
		       struct ck_attribute *templ,
		       unsigned long attribute_count,
		       ck_object_handle_t *key));

_CK_DECLARE_FUNCTION (C_SeedRandom,
		      (ck_session_handle_t session, unsigned char *seed,
		       unsigned long seed_len));
_CK_DECLARE_FUNCTION (C_GenerateRandom,
		      (ck_session_handle_t session,
		       unsigned char *random_data,
		       unsigned long random_len));

_CK_DECLARE_FUNCTION (C_GetFunctionStatus, (ck_session_handle_t session));
_CK_DECLARE_FUNCTION (C_CancelFunction, (ck_session_handle_t session));

_CK_DECLARE_FUNCTION (C_GetInterfaceList,
		      (struct ck_interface *interfaces_list,
		       unsigned long *count));
_CK_DECLARE_FUNCTION (C_GetInterface,
		      (unsigned char *interface_name,
		       struct ck_version *version,
		       struct ck_interface **interface_,
		       ck_flags_t flags));

_CK_DECLARE_FUNCTION (C_LoginUser,
		      (ck_session_handle_t session,
		       ck_user_type_t user_type,
		       unsigned char *pin,
		       unsigned long pin_len,
		       unsigned char *username,
		       unsigned long username_len));

_CK_DECLARE_FUNCTION (C_SessionCancel,
		      (ck_session_handle_t session,
		       ck_flags_t flags));

_CK_DECLARE_FUNCTION (C_MessageEncryptInit,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       ck_object_handle_t key));
_CK_DECLARE_FUNCTION (C_EncryptMessage,
		      (ck_session_handle_t session,
		       void *parameter,
		       unsigned long parameter_len,
		       unsigned char *associated_data,
		       unsigned long associated_data_len,
		       unsigned char *plaintext,
		       unsigned long plaintext_len,
		       unsigned char *ciphertext,
		       unsigned long *ciphertext_len));
_CK_DECLARE_FUNCTION (C_EncryptMessageBegin,
		      (ck_session_handle_t session,
		       void *parameter,
		       unsigned long parameter_len,
		       unsigned char *associated_data,
		       unsigned long associated_data_len));
_CK_DECLARE_FUNCTION (C_EncryptMessageNext,
		      (ck_session_handle_t session,
		       void *parameter,
		       unsigned long parameter_len,
		       unsigned char *plaintext_part,
		       unsigned long plaintext_part_len,
		       unsigned char *ciphertext_part,
		       unsigned long *ciphertext_part_len,
		       ck_flags_t flags));
_CK_DECLARE_FUNCTION (C_MessageEncryptFinal,
		      (ck_session_handle_t session));

_CK_DECLARE_FUNCTION (C_MessageDecryptInit,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       ck_object_handle_t key));
_CK_DECLARE_FUNCTION (C_DecryptMessage,
		      (ck_session_handle_t session,
		       void *parameter,
		       unsigned long parameter_len,
		       unsigned char *associated_data,
		       unsigned long associated_data_len,
		       unsigned char *ciphertext,
		       unsigned long ciphertext_len,
		       unsigned char *plaintext,
		       unsigned long *plaintext_len));
_CK_DECLARE_FUNCTION (C_DecryptMessageBegin,
		      (ck_session_handle_t session,
		       void *parameter,
		       unsigned long parameter_len,
		       unsigned char *associated_data,
		       unsigned long associated_data_len));
_CK_DECLARE_FUNCTION (C_DecryptMessageNext,
		      (ck_session_handle_t session,
		       void *parameter,
		       unsigned long parameter_len,
		       unsigned char *ciphertext_part,
		       unsigned long ciphertext_part_len,
		       unsigned char *plaintext_part,
		       unsigned long *plaintext_part_len,
		       ck_flags_t flags));
_CK_DECLARE_FUNCTION (C_MessageDecryptFinal,
		      (ck_session_handle_t session));

_CK_DECLARE_FUNCTION (C_MessageSignInit,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       ck_object_handle_t key));
_CK_DECLARE_FUNCTION (C_SignMessage,
		      (ck_session_handle_t session,
		       void *parameter,
		       unsigned long parameter_len,
		       unsigned char *data,
		       unsigned long data_len,
		       unsigned char *signature,
		       unsigned long *signature_len));
_CK_DECLARE_FUNCTION (C_SignMessageBegin,
		      (ck_session_handle_t session,
		       void *parameter,
		       unsigned long parameter_len));
_CK_DECLARE_FUNCTION (C_SignMessageNext,
		      (ck_session_handle_t session,
		       void *parameter,
		       unsigned long parameter_len,
		       unsigned char *data,
		       unsigned long data_len,
		       unsigned char *signature,
		       unsigned long *signature_len));
_CK_DECLARE_FUNCTION (C_MessageSignFinal,
		      (ck_session_handle_t session));

_CK_DECLARE_FUNCTION (C_MessageVerifyInit,
		      (ck_session_handle_t session,
		       struct ck_mechanism *mechanism,
		       ck_object_handle_t key));
_CK_DECLARE_FUNCTION (C_VerifyMessage,
		      (ck_session_handle_t session,
		       void *parameter,
		       unsigned long parameter_len,
		       unsigned char *data,
		       unsigned long data_len,
		       unsigned char *signature,
		       unsigned long signature_len));
_CK_DECLARE_FUNCTION (C_VerifyMessageBegin,
		      (ck_session_handle_t session,
		       void *parameter,
		       unsigned long parameter_len));
_CK_DECLARE_FUNCTION (C_VerifyMessageNext,
		      (ck_session_handle_t session,
		       void *parameter,
		       unsigned long parameter_len,
		       unsigned char *data,
		       unsigned long data_len,
		       unsigned char *signature,
		       unsigned long signature_len));
_CK_DECLARE_FUNCTION (C_MessageVerifyFinal,
		      (ck_session_handle_t session));

_CK_DECLARE_FUNCTION (C_EncapsulateKey,
                      (ck_session_handle_t session,
                       struct ck_mechanism *mechanism,
                       ck_object_handle_t public_key,
                       struct ck_attribute *templ,
                       unsigned long attribute_count,
                       unsigned char *ciphertext,
                       unsigned long *ciphertext_len,
                       ck_object_handle_t *key_ptr));
_CK_DECLARE_FUNCTION (C_DecapsulateKey,
                      (ck_session_handle_t session,
                       struct ck_mechanism *mechanism,
                       ck_object_handle_t private_key,
                       struct ck_attribute *templ,
                       unsigned long attribute_count,
                       unsigned char *ciphertext,
                       unsigned long ciphertext_len,
                       ck_object_handle_t *key_ptr));
_CK_DECLARE_FUNCTION (C_VerifySignatureInit,
                      (ck_session_handle_t session,
                       struct ck_mechanism *mechanism,
                       ck_object_handle_t key,
                       unsigned char *signature,
                       unsigned long signature_len));
_CK_DECLARE_FUNCTION (C_VerifySignature,
                      (ck_session_handle_t session,
                       unsigned char *data,
                       unsigned long data_len));
_CK_DECLARE_FUNCTION (C_VerifySignatureUpdate,
                      (ck_session_handle_t session,
		       unsigned char *part,
                       unsigned long part_len));
_CK_DECLARE_FUNCTION (C_VerifySignatureFinal,
                      (ck_session_handle_t session));
_CK_DECLARE_FUNCTION (C_GetSessionValidationFlags,
                      (ck_session_handle_t session,
                       ck_session_validation_flags_type_t type,
                       ck_flags_t *flags_ptr));
_CK_DECLARE_FUNCTION (C_AsyncComplete,
                      (ck_session_handle_t session,
                       unsigned char *function_name,
                       struct ck_async_data *result));
_CK_DECLARE_FUNCTION (C_AsyncGetID,
                      (ck_session_handle_t session,
                       unsigned char *function_name,
                       unsigned long *id_ptr));
_CK_DECLARE_FUNCTION (C_AsyncJoin,
                      (ck_session_handle_t session,
                       unsigned char *function_name,
                       unsigned long id,
                       unsigned char *data,
                       unsigned long data_len));
_CK_DECLARE_FUNCTION (C_WrapKeyAuthenticated,
                      (ck_session_handle_t session,
                       struct ck_mechanism *mechanism,
                       ck_object_handle_t wrapping_key,
                       ck_object_handle_t key,
                       unsigned char *associated_data,
                       unsigned long associated_data_len,
                       unsigned char *wrapped_key,
                       unsigned long *wrapped_key_len));
_CK_DECLARE_FUNCTION (C_UnwrapKeyAuthenticated,
                      (ck_session_handle_t session,
                       struct ck_mechanism *mechanism,
                       ck_object_handle_t unwrapping_key,
                       unsigned char *wrapped_key,
                       unsigned long wrapped_key_len,
                       struct ck_attribute *templ,
                       unsigned long attribute_count,
                       unsigned char *associated_data,
                       unsigned long associated_data_len,
                       ck_object_handle_t *key_ptr));

#define CK_FUNCTION_LIST_ \
  struct ck_version version; \
  CK_C_Initialize C_Initialize; \
  CK_C_Finalize C_Finalize; \
  CK_C_GetInfo C_GetInfo; \
  CK_C_GetFunctionList C_GetFunctionList; \
  CK_C_GetSlotList C_GetSlotList; \
  CK_C_GetSlotInfo C_GetSlotInfo; \
  CK_C_GetTokenInfo C_GetTokenInfo; \
  CK_C_GetMechanismList C_GetMechanismList; \
  CK_C_GetMechanismInfo C_GetMechanismInfo; \
  CK_C_InitToken C_InitToken; \
  CK_C_InitPIN C_InitPIN; \
  CK_C_SetPIN C_SetPIN; \
  CK_C_OpenSession C_OpenSession; \
  CK_C_CloseSession C_CloseSession; \
  CK_C_CloseAllSessions C_CloseAllSessions; \
  CK_C_GetSessionInfo C_GetSessionInfo; \
  CK_C_GetOperationState C_GetOperationState; \
  CK_C_SetOperationState C_SetOperationState; \
  CK_C_Login C_Login; \
  CK_C_Logout C_Logout; \
  CK_C_CreateObject C_CreateObject; \
  CK_C_CopyObject C_CopyObject; \
  CK_C_DestroyObject C_DestroyObject; \
  CK_C_GetObjectSize C_GetObjectSize; \
  CK_C_GetAttributeValue C_GetAttributeValue; \
  CK_C_SetAttributeValue C_SetAttributeValue; \
  CK_C_FindObjectsInit C_FindObjectsInit; \
  CK_C_FindObjects C_FindObjects; \
  CK_C_FindObjectsFinal C_FindObjectsFinal; \
  CK_C_EncryptInit C_EncryptInit; \
  CK_C_Encrypt C_Encrypt; \
  CK_C_EncryptUpdate C_EncryptUpdate; \
  CK_C_EncryptFinal C_EncryptFinal; \
  CK_C_DecryptInit C_DecryptInit; \
  CK_C_Decrypt C_Decrypt; \
  CK_C_DecryptUpdate C_DecryptUpdate; \
  CK_C_DecryptFinal C_DecryptFinal; \
  CK_C_DigestInit C_DigestInit; \
  CK_C_Digest C_Digest; \
  CK_C_DigestUpdate C_DigestUpdate; \
  CK_C_DigestKey C_DigestKey; \
  CK_C_DigestFinal C_DigestFinal; \
  CK_C_SignInit C_SignInit; \
  CK_C_Sign C_Sign; \
  CK_C_SignUpdate C_SignUpdate; \
  CK_C_SignFinal C_SignFinal; \
  CK_C_SignRecoverInit C_SignRecoverInit; \
  CK_C_SignRecover C_SignRecover; \
  CK_C_VerifyInit C_VerifyInit; \
  CK_C_Verify C_Verify; \
  CK_C_VerifyUpdate C_VerifyUpdate; \
  CK_C_VerifyFinal C_VerifyFinal; \
  CK_C_VerifyRecoverInit C_VerifyRecoverInit; \
  CK_C_VerifyRecover C_VerifyRecover; \
  CK_C_DigestEncryptUpdate C_DigestEncryptUpdate; \
  CK_C_DecryptDigestUpdate C_DecryptDigestUpdate; \
  CK_C_SignEncryptUpdate C_SignEncryptUpdate; \
  CK_C_DecryptVerifyUpdate C_DecryptVerifyUpdate; \
  CK_C_GenerateKey C_GenerateKey; \
  CK_C_GenerateKeyPair C_GenerateKeyPair; \
  CK_C_WrapKey C_WrapKey; \
  CK_C_UnwrapKey C_UnwrapKey; \
  CK_C_DeriveKey C_DeriveKey; \
  CK_C_SeedRandom C_SeedRandom; \
  CK_C_GenerateRandom C_GenerateRandom; \
  CK_C_GetFunctionStatus C_GetFunctionStatus; \
  CK_C_CancelFunction C_CancelFunction; \
  CK_C_WaitForSlotEvent C_WaitForSlotEvent;

#define CK_FUNCTION_LIST_3_0_ \
  CK_C_GetInterfaceList C_GetInterfaceList; \
  CK_C_GetInterface C_GetInterface; \
  CK_C_LoginUser C_LoginUser; \
  CK_C_SessionCancel C_SessionCancel; \
  CK_C_MessageEncryptInit C_MessageEncryptInit; \
  CK_C_EncryptMessage C_EncryptMessage; \
  CK_C_EncryptMessageBegin C_EncryptMessageBegin; \
  CK_C_EncryptMessageNext C_EncryptMessageNext; \
  CK_C_MessageEncryptFinal C_MessageEncryptFinal; \
  CK_C_MessageDecryptInit C_MessageDecryptInit; \
  CK_C_DecryptMessage C_DecryptMessage; \
  CK_C_DecryptMessageBegin C_DecryptMessageBegin; \
  CK_C_DecryptMessageNext C_DecryptMessageNext; \
  CK_C_MessageDecryptFinal C_MessageDecryptFinal; \
  CK_C_MessageSignInit C_MessageSignInit; \
  CK_C_SignMessage C_SignMessage; \
  CK_C_SignMessageBegin C_SignMessageBegin; \
  CK_C_SignMessageNext C_SignMessageNext; \
  CK_C_MessageSignFinal C_MessageSignFinal; \
  CK_C_MessageVerifyInit C_MessageVerifyInit; \
  CK_C_VerifyMessage C_VerifyMessage; \
  CK_C_VerifyMessageBegin C_VerifyMessageBegin; \
  CK_C_VerifyMessageNext C_VerifyMessageNext; \
  CK_C_MessageVerifyFinal C_MessageVerifyFinal;

#define CK_FUNCTION_LIST_3_2_ \
  CK_C_EncapsulateKey C_EncapsulateKey; \
  CK_C_DecapsulateKey C_DecapsulateKey; \
  CK_C_VerifySignatureInit C_VerifySignatureInit; \
  CK_C_VerifySignature C_VerifySignature; \
  CK_C_VerifySignatureUpdate C_VerifySignatureUpdate; \
  CK_C_VerifySignatureFinal C_VerifySignatureFinal; \
  CK_C_GetSessionValidationFlags C_GetSessionValidationFlags; \
  CK_C_AsyncComplete C_AsyncComplete; \
  CK_C_AsyncGetID C_AsyncGetID; \
  CK_C_AsyncJoin C_AsyncJoin; \
  CK_C_WrapKeyAuthenticated C_WrapKeyAuthenticated; \
  CK_C_UnwrapKeyAuthenticated C_UnwrapKeyAuthenticated;

struct ck_function_list
{
  CK_FUNCTION_LIST_
};

struct ck_function_list_3_0
{
  CK_FUNCTION_LIST_
  CK_FUNCTION_LIST_3_0_
};

struct ck_function_list_3_2
{
  CK_FUNCTION_LIST_
  CK_FUNCTION_LIST_3_0_
  CK_FUNCTION_LIST_3_2_
};


/* System dependencies.  */
#if defined(_WIN32) || defined(CRYPTOKI_FORCE_WIN32)
#pragma pack(pop, cryptoki)
#endif

#if defined(__cplusplus)
}
#endif

#endif        /* PKCS11_GNU_H */
