#include <oqs/oqs.h>
#include <string.h>
#include "sha2.h"
#include "oqs/common.h"
#include "oqs/sha2.h"

void OQS_to_SLH_sha2_224_ctx(OQS_SHA2_sha224_ctx *oqs_sha2_224_in, SLH_sha2_224_t *slh_sha2_224_out);
void SLH_to_OQS_sha2_224_ctx(SLH_sha2_224_t *slh_sha2_224_in, OQS_SHA2_sha224_ctx *oqs_sha2_224_out);
void OQS_to_SLH_sha2_256_ctx(OQS_SHA2_sha256_ctx *oqs_sha2_256_in, SLH_sha2_256_t *slh_sha2_256_out);
void SLH_to_OQS_sha2_256_ctx(SLH_sha2_256_t *slh_sha2_256_in, OQS_SHA2_sha256_ctx *oqs_sha2_256_out);
void OQS_to_SLH_sha2_384_ctx(OQS_SHA2_sha384_ctx *oqs_sha2_384_in, SLH_sha2_384_t *slh_sha2_384_out);
void SLH_to_OQS_sha2_384_ctx(SLH_sha2_384_t *slh_sha2_384_in, OQS_SHA2_sha384_ctx *oqs_sha2_384_out);
void OQS_to_SLH_sha2_512_ctx(OQS_SHA2_sha512_ctx *oqs_sha2_512_in, SLH_sha2_512_t *slh_sha2_512_out);
void SLH_to_OQS_sha2_512_ctx(SLH_sha2_512_t *slh_sha2_512_in, OQS_SHA2_sha512_ctx *oqs_sha2_512_out);

/* Input an OQS sha2_224 data structure and output coresponding SLH data structure */
void OQS_to_SLH_sha2_224_ctx(OQS_SHA2_sha224_ctx *oqs_sha2_224_in, SLH_sha2_224_t *slh_sha2_224_out){
    OQS_SHA2_sha256_ctx *oqs_sha2_224 = (OQS_SHA2_sha256_ctx*) oqs_sha2_224_in;
    SLH_sha2_256_t *slh_sha2_224 = (SLH_sha2_256_t*) slh_sha2_224_out;

    OQS_to_SLH_sha2_256_ctx(oqs_sha2_224, slh_sha2_224);
}

/* Input an SLH sha2_224 data structure and output coresponding OQS data structure */
void SLH_to_OQS_sha2_224_ctx(SLH_sha2_224_t *slh_sha2_224_in, OQS_SHA2_sha224_ctx *oqs_sha2_224_out){
    SLH_sha2_256_t *slh_sha2_224 = (SLH_sha2_256_t*) slh_sha2_224_in;
    OQS_SHA2_sha256_ctx *oqs_sha2_224 = (OQS_SHA2_sha256_ctx*) oqs_sha2_224_out;

    SLH_to_OQS_sha2_256_ctx(slh_sha2_224, oqs_sha2_224);
}

/* Input an OQS sha2_256 data structure and output coresponding SLH data structure */
void OQS_to_SLH_sha2_256_ctx(OQS_SHA2_sha256_ctx *oqs_sha2_256_in, SLH_sha2_256_t *slh_sha2_256_out){
    OQS_EXIT_IF_NULLPTR(oqs_sha2_256_in, "SLHDSA SHA2 shims");
    OQS_EXIT_IF_NULLPTR(slh_sha2_256_out, "SLHDSA SHA2 shims");

    memcpy(slh_sha2_256_out->s, oqs_sha2_256_in->ctx, 4*8);
    memcpy(slh_sha2_256_out->s + 8, oqs_sha2_256_in->data, 4*16);
    memset(slh_sha2_256_out->s + 8+16, 0, 4*8);
    memcpy(&slh_sha2_256_out->i, &oqs_sha2_256_in->data_len, sizeof(size_t));
    memcpy(&slh_sha2_256_out->len, oqs_sha2_256_in->ctx + 4*8, sizeof(size_t));
}

/* Input an SLH sha2_256 data structure and output coresponding OQS data structure */
void SLH_to_OQS_sha2_256_ctx(SLH_sha2_256_t *slh_sha2_256_in, OQS_SHA2_sha256_ctx *oqs_sha2_256_out){
    OQS_EXIT_IF_NULLPTR(slh_sha2_256_in, "SLHDSA SHA2 shims");
    OQS_EXIT_IF_NULLPTR(oqs_sha2_256_out, "SLHDSA SHA2 shims");

    memcpy(oqs_sha2_256_out->ctx, slh_sha2_256_in->s, 4*8);
    memcpy(oqs_sha2_256_out->ctx + 4*8, &slh_sha2_256_in->len, sizeof(size_t));
    memcpy(&oqs_sha2_256_out->data_len, &slh_sha2_256_in->i, sizeof(size_t));
    memcpy(oqs_sha2_256_out->data, slh_sha2_256_in->s + 8, 4*16);
    memset(oqs_sha2_256_out->data + 4*16, 0, 4*16);
}

/* Input an OQS sha2_384 data structure and output coresponding SLH data structure */
void OQS_to_SLH_sha2_384_ctx(OQS_SHA2_sha384_ctx *oqs_sha2_384_in, SLH_sha2_384_t *slh_sha2_384_out){
    OQS_SHA2_sha256_ctx *oqs_sha2_384 = (OQS_SHA2_sha256_ctx*) oqs_sha2_384_in;
    SLH_sha2_256_t *slh_sha2_384 = (SLH_sha2_256_t*) slh_sha2_384_out;

    OQS_to_SLH_sha2_256_ctx(oqs_sha2_384, slh_sha2_384);
}

/* Input an SLH sha2_384 data structure and output coresponding OQS data structure */
void SLH_to_OQS_sha2_384_ctx(SLH_sha2_384_t *slh_sha2_384_in, OQS_SHA2_sha384_ctx *oqs_sha2_384_out){
    SLH_sha2_256_t *slh_sha2_384 = (SLH_sha2_256_t*) slh_sha2_384_in;
    OQS_SHA2_sha256_ctx *oqs_sha2_384 = (OQS_SHA2_sha256_ctx*) oqs_sha2_384_out;

    SLH_to_OQS_sha2_256_ctx(slh_sha2_384, oqs_sha2_384);
}

/* Input an OQS sha2_512 data structure and output coresponding SLH data structure */
void OQS_to_SLH_sha2_512_ctx(OQS_SHA2_sha512_ctx *oqs_sha2_512_in, SLH_sha2_512_t *slh_sha2_512_out){
    OQS_EXIT_IF_NULLPTR(oqs_sha2_512_in, "SLHDSA SHA2 shims");
    OQS_EXIT_IF_NULLPTR(slh_sha2_512_out, "SLHDSA SHA2 shims");

    memcpy(slh_sha2_512_out->s, oqs_sha2_512_in->ctx, 8*8);
    memcpy(slh_sha2_512_out->s + 8, oqs_sha2_512_in->data, 8*16);
    memset(slh_sha2_512_out->s + 8+16, 0, 8*8);
    memcpy(&slh_sha2_512_out->i, &oqs_sha2_512_in->data_len, sizeof(size_t));
    memcpy(&slh_sha2_512_out->len, oqs_sha2_512_in->ctx + 8*8, sizeof(size_t));
}

/* Input an SLH sha2_512 data structure and output coresponding OQS data structure */
void SLH_to_OQS_sha2_512_ctx(SLH_sha2_512_t *slh_sha2_512_in, OQS_SHA2_sha512_ctx *oqs_sha2_512_out){
    OQS_EXIT_IF_NULLPTR(slh_sha2_512_in, "SLHDSA SHA2 shims");
    OQS_EXIT_IF_NULLPTR(oqs_sha2_512_out, "SLHDSA SHA2 shims");

    memcpy(oqs_sha2_512_out->ctx, slh_sha2_512_in->s, 8*8);
    memcpy(oqs_sha2_512_out->ctx + 8*8, &slh_sha2_512_in->len, sizeof(size_t));
    memcpy(&oqs_sha2_512_out->data_len, &slh_sha2_512_in->i, sizeof(size_t));
    memcpy(oqs_sha2_512_out->data, slh_sha2_512_in->s + 8, 8*16);
}

/* shim function for sha2_224_init */
void SLH_SHIM_sha224_inc_init(SLH_sha2_224_t *slh_ctx) {
    OQS_SHA2_sha224_ctx *oqs_ctx = OQS_MEM_malloc(sizeof(OQS_SHA2_sha224_ctx));
    OQS_SHA2_sha224_inc_init(oqs_ctx);
    OQS_to_SLH_sha2_224_ctx(oqs_ctx, slh_ctx);
    OQS_MEM_insecure_free(oqs_ctx);
}

/* shim function for sha2_256_init */
void SLH_SHIM_sha256_inc_init(SLH_sha2_256_t *slh_ctx) {
    OQS_SHA2_sha256_ctx *oqs_ctx = OQS_MEM_malloc(sizeof(OQS_SHA2_sha256_ctx));
    OQS_SHA2_sha256_inc_init(oqs_ctx);
    OQS_to_SLH_sha2_256_ctx(oqs_ctx, slh_ctx);
    OQS_MEM_insecure_free(oqs_ctx);
}

/* shim function for sha2_384_init */
void SLH_SHIM_sha384_inc_init(SLH_sha2_384_t *slh_ctx) {
    OQS_SHA2_sha384_ctx *oqs_ctx = OQS_MEM_malloc(sizeof(OQS_SHA2_sha384_ctx));
    OQS_SHA2_sha384_inc_init(oqs_ctx);
    OQS_to_SLH_sha2_384_ctx(oqs_ctx, slh_ctx);
    OQS_MEM_insecure_free(oqs_ctx);
}

/* shim function for sha2_512_init */
void SLH_SHIM_sha512_inc_init(SLH_sha2_512_t *slh_ctx) {
    OQS_SHA2_sha512_ctx *oqs_ctx = OQS_MEM_malloc(sizeof(OQS_SHA2_sha512_ctx));
    OQS_SHA2_sha512_inc_init(oqs_ctx);
    OQS_to_SLH_sha2_512_ctx(oqs_ctx, slh_ctx);
    OQS_MEM_insecure_free(oqs_ctx);
}
