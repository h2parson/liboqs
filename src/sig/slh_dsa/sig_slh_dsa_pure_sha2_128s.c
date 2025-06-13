// SPDX-License-Identifier: MIT

#include <stdlib.h>

#include "sig_slh_dsa.h"

// #if defined(OQS_ENABLE_SIG_slh_dsa_pure_sha2_128s)
OQS_SIG *OQS_SIG_slh_dsa_pure_sha2_128s_new(void) {

	OQS_SIG *sig = OQS_MEM_malloc(sizeof(OQS_SIG));
	if (sig == NULL) {
		return NULL;
	}
	sig->method_name = OQS_SIG_alg_slh_dsa_pure_sha2_128s;
	sig->alg_version = "FIPS205";

	sig->claimed_nist_level = 1;
	sig->euf_cma = true;
	sig->suf_cma = true;
	sig->sig_with_ctx_support = true;

	sig->length_public_key = OQS_SIG_slh_dsa_pure_sha2_128s_length_public_key;
	sig->length_secret_key = OQS_SIG_slh_dsa_pure_sha2_128s_length_secret_key;
	sig->length_signature = OQS_SIG_slh_dsa_pure_sha2_128s_length_signature;

	sig->keypair = OQS_SIG_slh_dsa_pure_sha2_128s_keypair;
	sig->sign = OQS_SIG_slh_dsa_pure_sha2_128s_sign;
	sig->verify = OQS_SIG_slh_dsa_pure_sha2_128s_verify;
	sig->sign_with_ctx_str = OQS_SIG_slh_dsa_pure_sha2_128s_sign_with_ctx_str;
	sig->verify_with_ctx_str = OQS_SIG_slh_dsa_pure_sha2_128s_verify_with_ctx_str;

	return sig;
}

extern int slh_dsa_pure_sha2_128s_keypair(uint8_t *pk, uint8_t *sk);
extern int slh_dsa_pure_sha2_128s_signature(uint8_t *sig, size_t *siglen, const uint8_t *m, size_t mlen, const uint8_t *ctx, size_t ctxlen, const uint8_t *sk);
extern int slh_dsa_pure_sha2_128s_verify(const uint8_t *sig, size_t siglen, const uint8_t *m, size_t mlen, const uint8_t *ctx, size_t ctxlen, const uint8_t *pk);

OQS_API OQS_STATUS OQS_SIG_slh_dsa_pure_sha2_128s_keypair(uint8_t *public_key, uint8_t *secret_key) {
	return (OQS_STATUS) slh_dsa_pure_sha2_128s_keypair(public_key, secret_key);
}

OQS_API OQS_STATUS OQS_SIG_slh_dsa_pure_sha2_128s_sign(uint8_t *signature, size_t *signature_len, const uint8_t *message, size_t message_len, const uint8_t *secret_key) {
	return (OQS_STATUS) slh_dsa_pure_sha2_128s_signature(signature, signature_len, message, message_len, NULL, 0, secret_key);
}

OQS_API OQS_STATUS OQS_SIG_slh_dsa_pure_sha2_128s_verify(const uint8_t *message, size_t message_len, const uint8_t *signature, size_t signature_len, const uint8_t *public_key) {
	return (OQS_STATUS) slh_dsa_pure_sha2_128s_verify(signature, signature_len, message, message_len, NULL, 0, public_key);
}

OQS_API OQS_STATUS OQS_SIG_slh_dsa_pure_sha2_128s_sign_with_ctx_str(uint8_t *signature, size_t *signature_len, const uint8_t *message, size_t message_len, const uint8_t *ctx_str, size_t ctx_str_len, const uint8_t *secret_key) {
	return (OQS_STATUS) slh_dsa_pure_sha2_128s_signature(signature, signature_len, message, message_len, ctx_str, ctx_str_len, secret_key);
}

OQS_API OQS_STATUS OQS_SIG_slh_dsa_pure_sha2_128s_verify_with_ctx_str(const uint8_t *message, size_t message_len, const uint8_t *signature, size_t signature_len, const uint8_t *ctx_str, size_t ctx_str_len, const uint8_t *public_key) {
	return (OQS_STATUS) slh_dsa_pure_sha2_128s_verify(signature, signature_len, message, message_len, ctx_str, ctx_str_len, public_key);
}
// #endif
