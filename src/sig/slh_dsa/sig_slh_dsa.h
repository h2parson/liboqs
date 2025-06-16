// SPDX-License-Identifier: MIT

#ifndef OQS_SIG_SLH_DSA_H
#define OQS_SIG_SLH_DSA_H

#include <oqs/oqs.h>

#if defined(OQS_ENABLE_SIG_slh_dsa_pure_sha2_128s)
#define OQS_SIG_slh_dsa_pure_sha2_128s_length_public_key 32
#define OQS_SIG_slh_dsa_pure_sha2_128s_length_secret_key 64
#define OQS_SIG_slh_dsa_pure_sha2_128s_length_signature 7856

OQS_SIG *OQS_SIG_slh_dsa_pure_sha2_128s_new(void);
OQS_API OQS_STATUS OQS_SIG_slh_dsa_pure_sha2_128s_keypair(uint8_t *public_key, uint8_t *secret_key);
OQS_API OQS_STATUS OQS_SIG_slh_dsa_pure_sha2_128s_sign(uint8_t *signature, size_t *signature_len, const uint8_t *message, size_t message_len, const uint8_t *secret_key);
OQS_API OQS_STATUS OQS_SIG_slh_dsa_pure_sha2_128s_verify(const uint8_t *message, size_t message_len, const uint8_t *signature, size_t signature_len, const uint8_t *public_key);
OQS_API OQS_STATUS OQS_SIG_slh_dsa_pure_sha2_128s_sign_with_ctx_str(uint8_t *signature, size_t *signature_len, const uint8_t *message, size_t message_len, const uint8_t *ctx, size_t ctxlen, const uint8_t *secret_key);
OQS_API OQS_STATUS OQS_SIG_slh_dsa_pure_sha2_128s_verify_with_ctx_str(const uint8_t *message, size_t message_len, const uint8_t *signature, size_t signature_len, const uint8_t *ctx, size_t ctxlen, const uint8_t *public_key);
#endif

#endif
