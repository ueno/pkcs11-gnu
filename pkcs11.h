/* pkcs11.h
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

/* This file provides the PKCS #11 API as defined by the standard,
   using the public domain headers from
   https://github.com/latchset/pkcs11-headers, plus the additions
   p11-kit's pkcs11.h has historically provided:

   This header file does not require any macro definitions by the user
   (like CK_DEFINE_FUNCTION etc).  In fact, it defines those macros
   for you.

   Deprecated definitions are available unless PKCS11_NO_DEPRECATED
   is defined before including this header file.

   There is an additional API available that does comply better to the
   GNU coding standard.  It can be switched on by defining
   CRYPTOKI_GNU before including this header file, and is provided by
   pkcs11-gnu.h; see that file for details.  */

#ifndef PKCS11_H
#define PKCS11_H 1

#ifdef CRYPTOKI_GNU

#include "pkcs11-gnu.h"

#else  /* !CRYPTOKI_GNU */

#ifndef CRYPTOKI_COMPAT
#define CRYPTOKI_COMPAT 1
#endif

#if !defined(PKCS11_DEPRECATED) && !defined(PKCS11_NO_DEPRECATED)
#define PKCS11_DEPRECATED 1
#endif

/* For NULL.  */
#include <stddef.h>

/* The public domain header only packs structures on Windows.  */
#if defined(CRYPTOKI_FORCE_WIN32) && !defined(_WIN32)
#pragma pack(push, cryptoki, 1)
#endif

#include "public-domain/3.2/pkcs11.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* Version of the p11-kit additions.  */
#define CRYPTOKI_VERSION_REVISION               CRYPTOKI_VERSION_AMENDMENT
#define CRYPTOKI_LEGACY_VERSION_MAJOR           2
#define CRYPTOKI_LEGACY_VERSION_MINOR           40
#define P11_KIT_CRYPTOKI_VERSION_REVISION       0

#if defined(_WIN32) || defined(CRYPTOKI_FORCE_WIN32)
#ifdef CRYPTOKI_EXPORTS
#define CK_SPEC __declspec(dllexport)
#else
#define CK_SPEC __declspec(dllimport)
#endif
#else
#define CK_SPEC
#endif

#define CK_DEFINE_FUNCTION(retval, name) retval CK_SPEC name

#ifndef CK_DISABLE_TRUE_FALSE
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#endif

/* Definitions missing from the public domain header, or no longer in
   the standard.  */
#define CKC_OPENPGP                             (CKC_VENDOR_DEFINED|0x504750UL)
#define CK_OTP_FORMAT                           CK_OTP_OUTPUT_FORMAT

typedef long int CK_LONG;
typedef CK_OTP_PARAM_TYPE CK_PARAM_TYPE;

/* Never defined, kept for source compatibility.  */
typedef struct CK_OTP_MECHANISM_INFO CK_OTP_MECHANISM_INFO;
typedef struct CK_OTP_MECHANISM_INFO *CK_OTP_MECHANISM_INFO_PTR;

/* Declared but not defined in the public domain 3.2 header; remove
   once pkcs11-headers defines it.  */
struct specifiedParams {
    CK_HSS_LEVELS levels;
    CK_LMS_TYPE lm_type[8];
    CK_LMOTS_TYPE lm_ots_type[8];
};

/* Structure tags previously used for the standard types.  */
#define _CK_ATTRIBUTE                                    CK_ATTRIBUTE
#define _CK_C_INITIALIZE_ARGS                            CK_C_INITIALIZE_ARGS
#define _CK_DATE                                         CK_DATE
#define _CK_FUNCTION_LIST                                CK_FUNCTION_LIST
#define _CK_FUNCTION_LIST_3_0                            CK_FUNCTION_LIST_3_0
#define _CK_FUNCTION_LIST_3_2                            CK_FUNCTION_LIST_3_2
#define _CK_INFO                                         CK_INFO
#define _CK_MECHANISM                                    CK_MECHANISM
#define _CK_MECHANISM_INFO                               CK_MECHANISM_INFO
#define _CK_SESSION_INFO                                 CK_SESSION_INFO
#define _CK_SLOT_INFO                                    CK_SLOT_INFO
#define _CK_TOKEN_INFO                                   CK_TOKEN_INFO
#define _CK_VERSION                                      CK_VERSION
#define ck_aes_cbc_encrypt_data_params                   CK_AES_CBC_ENCRYPT_DATA_PARAMS
#define ck_aes_ccm_params                                CK_AES_CCM_PARAMS
#define ck_aes_ctr_params                                CK_AES_CTR_PARAMS
#define ck_aes_gcm_params                                CK_AES_GCM_PARAMS
#define ck_aria_cbc_encrypt_data_params                  CK_ARIA_CBC_ENCRYPT_DATA_PARAMS
#define ck_async_data                                    CK_ASYNC_DATA
#define ck_camellia_cbc_encrypt_data_params              CK_CAMELLIA_CBC_ENCRYPT_DATA_PARAMS
#define ck_camellia_ctr_params                           CK_CAMELLIA_CTR_PARAMS
#define ck_ccm_message_params                            CK_CCM_MESSAGE_PARAMS
#define ck_ccm_params                                    CK_CCM_PARAMS
#define ck_ccm_wrap_params                               CK_CCM_WRAP_PARAMS
#define ck_chacha20_params                               CK_CHACHA20_PARAMS
#define ck_cms_sig_params                                CK_CMS_SIG_PARAMS
#define ck_derived_key                                   CK_DERIVED_KEY
#define ck_des_cbc_encrypt_data_params                   CK_DES_CBC_ENCRYPT_DATA_PARAMS
#define ck_dsa_parameter_gen_param                       CK_DSA_PARAMETER_GEN_PARAM
#define ck_ecdh1_derive_params                           CK_ECDH1_DERIVE_PARAMS
#define ck_ecdh2_derive_params                           CK_ECDH2_DERIVE_PARAMS
#define ck_ecdh_aes_key_wrap_params                      CK_ECDH_AES_KEY_WRAP_PARAMS
#define ck_ecmqv_derive_params                           CK_ECMQV_DERIVE_PARAMS
#define ck_eddsa_params                                  CK_EDDSA_PARAMS
#define ck_gcm_message_params                            CK_GCM_MESSAGE_PARAMS
#define ck_gcm_params                                    CK_GCM_PARAMS
#define ck_gcm_wrap_params                               CK_GCM_WRAP_PARAMS
#define ck_gostr3410_derive_params                       CK_GOSTR3410_DERIVE_PARAMS
#define ck_gostr3410_key_wrap_params                     CK_GOSTR3410_KEY_WRAP_PARAMS
#define ck_hash_sign_additional_context                  CK_HASH_SIGN_ADDITIONAL_CONTEXT
#define ck_hkdf_params                                   CK_HKDF_PARAMS
#define ck_ike1_extended_derive_params                   CK_IKE1_EXTENDED_DERIVE_PARAMS
#define ck_ike1_prf_derive_params                        CK_IKE1_PRF_DERIVE_PARAMS
#define ck_ike2_prf_plus_derive_params                   CK_IKE2_PRF_PLUS_DERIVE_PARAMS
#define ck_ike_prf_derive_params                         CK_IKE_PRF_DERIVE_PARAMS
#define ck_kea_derive_params                             CK_KEA_DERIVE_PARAMS
#define ck_key_derivation_string_data                    CK_KEY_DERIVATION_STRING_DATA
#define ck_key_wrap_set_oaep_params                      CK_KEY_WRAP_SET_OAEP_PARAMS
#define ck_kip_params                                    CK_KIP_PARAMS
#define ck_pbe_params                                    CK_PBE_PARAMS
#define ck_pkcs5_pbkd2_params                            CK_PKCS5_PBKD2_PARAMS
#define ck_pkcs5_pbkd2_params2                           CK_PKCS5_PBKD2_PARAMS2
#define ck_prf_data_param                                CK_PRF_DATA_PARAM
#define ck_rc2_cbc_params                                CK_RC2_CBC_PARAMS
#define ck_rc2_mac_general_params                        CK_RC2_MAC_GENERAL_PARAMS
#define ck_rc5_cbc_params                                CK_RC5_CBC_PARAMS
#define ck_rc5_mac_general_params                        CK_RC5_MAC_GENERAL_PARAMS
#define ck_rc5_params                                    CK_RC5_PARAMS
#define ck_rsa_aes_key_wrap_params                       CK_RSA_AES_KEY_WRAP_PARAMS
#define ck_rsa_pkcs_oaep_params                          CK_RSA_PKCS_OAEP_PARAMS
#define ck_rsa_pkcs_pss_params                           CK_RSA_PKCS_PSS_PARAMS
#define ck_salsa20_chacha20_poly1305_msg_params          CK_SALSA20_CHACHA20_POLY1305_MSG_PARAMS
#define ck_salsa20_chacha20_poly1305_params              CK_SALSA20_CHACHA20_POLY1305_PARAMS
#define ck_salsa20_params                                CK_SALSA20_PARAMS
#define ck_seed_cbc_encrypt_data_params                  CK_SEED_CBC_ENCRYPT_DATA_PARAMS
#define ck_sign_additional_context                       CK_SIGN_ADDITIONAL_CONTEXT
#define ck_skipjack_private_wrap_params                  CK_SKIPJACK_PRIVATE_WRAP_PARAMS
#define ck_skipjack_relayx_params                        CK_SKIPJACK_RELAYX_PARAMS
#define ck_sp800_108_counter_format                      CK_SP800_108_COUNTER_FORMAT
#define ck_sp800_108_dkm_length_format                   CK_SP800_108_DKM_LENGTH_FORMAT
#define ck_sp800_108_feedback_kdf_params                 CK_SP800_108_FEEDBACK_KDF_PARAMS
#define ck_sp800_108_kdf_params                          CK_SP800_108_KDF_PARAMS
#define ck_ssl3_key_mat_out                              CK_SSL3_KEY_MAT_OUT
#define ck_ssl3_key_mat_params                           CK_SSL3_KEY_MAT_PARAMS
#define ck_ssl3_master_key_derive_params                 CK_SSL3_MASTER_KEY_DERIVE_PARAMS
#define ck_ssl3_random_data                              CK_SSL3_RANDOM_DATA
#define ck_tls12_extended_master_key_derive_params       CK_TLS12_EXTENDED_MASTER_KEY_DERIVE_PARAMS
#define ck_tls12_key_mat_params                          CK_TLS12_KEY_MAT_PARAMS
#define ck_tls12_master_key_derive_params                CK_TLS12_MASTER_KEY_DERIVE_PARAMS
#define ck_tls_kdf_params                                CK_TLS_KDF_PARAMS
#define ck_tls_mac_params                                CK_TLS_MAC_PARAMS
#define ck_tls_prf_params                                CK_TLS_PRF_PARAMS
#define ck_wtls_key_mat_out                              CK_WTLS_KEY_MAT_OUT
#define ck_wtls_key_mat_params                           CK_WTLS_KEY_MAT_PARAMS
#define ck_wtls_master_key_derive_params                 CK_WTLS_MASTER_KEY_DERIVE_PARAMS
#define ck_wtls_prf_params                               CK_WTLS_PRF_PARAMS
#define ck_wtls_random_data                              CK_WTLS_RANDOM_DATA
#define ck_x2ratchet_initialize_params                   CK_X2RATCHET_INITIALIZE_PARAMS
#define ck_x2ratchet_respond_params                      CK_X2RATCHET_RESPOND_PARAMS
#define ck_x3dh_initiate_params                          CK_X3DH_INITIATE_PARAMS
#define ck_x3dh_respond_params                           CK_X3DH_RESPOND_PARAMS
#define ck_x9_42_dh1_derive_params                       CK_X9_42_DH1_DERIVE_PARAMS
#define ck_x9_42_dh2_derive_params                       CK_X9_42_DH2_DERIVE_PARAMS
#define ck_x9_42_mqv_derive_params                       CK_X9_42_MQV_DERIVE_PARAMS
#define ck_xeddsa_params                                 CK_XEDDSA_PARAMS
#define specified_params                                 specifiedParams
#define ck_otp_mechanism_info                            CK_OTP_MECHANISM_INFO

#if defined(__cplusplus)
}
#endif

#if defined(CRYPTOKI_FORCE_WIN32) && !defined(_WIN32)
#pragma pack(pop, cryptoki)
#endif

#endif /* !CRYPTOKI_GNU */

#endif /* PKCS11_H */
