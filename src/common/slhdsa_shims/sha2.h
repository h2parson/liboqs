#ifndef SHA2_H
#define SHA2_H

#include <oqs/sha2.h>

/* sha2 data structures */
#define sha2_224_t SLH_sha2_224_t
#define sha2_256_t SLH_sha2_256_t
#define sha2_384_t SLH_sha2_384_t
#define sha2_512_t SLH_sha2_512_t

/* single call sha2 functions */
#define sha2_224 OQS_SHA2_sha224
#define sha2_256 OQS_SHA2_sha256
#define sha2_384 OQS_SHA2_sha384
#define sha2_512 OQS_SHA2_sha512
#define sha2_512_224 OQS_SHA2_sha512_224
#define sha2_512_256 OQS_SHA2_sha512_256

/* sha2 init functions */
#define sha2_224_init SLH_SHIM_sha224_inc_init
#define sha2_256_init SLH_SHIM_sha256_inc_init
#define sha2_384_init SLH_SHIM_sha384_inc_init
#define sha2_512_init SLH_SHIM_sha512_inc_init
#define sha2_512_224_init SLH_SHIM_sha512_224_inc_init
#define sha2_512_256_init SLH_SHIM_sha512_256_inc_init

/* slhdsa shims versions of SLHDSA sha256 ctx */
typedef struct
{
  uint32_t s[8 + 24];
  size_t i, len;
} SLH_sha2_256_t;

typedef SLH_sha2_256_t SLH_sha2_224_t;

typedef struct
{
  uint64_t s[8 + 24];
  size_t i, len;
} SLH_sha2_512_t;

typedef SLH_sha2_512_t SLH_sha2_384_t;

/* prototypes */
void SLH_SHIM_sha224_inc_init(SLH_sha2_224_t *slh_ctx);
void SLH_SHIM_sha256_inc_init(SLH_sha2_256_t *slh_ctx);
void SLH_SHIM_sha384_inc_init(SLH_sha2_384_t *slh_ctx);
void SLH_SHIM_sha512_inc_init(SLH_sha2_512_t *slh_ctx);

#endif /* SHA2_H */
