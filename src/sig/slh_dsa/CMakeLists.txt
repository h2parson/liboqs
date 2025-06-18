# SPDX-License-Identifier: MIT

set(_SLH_DSA_OBJS "")

if(OQS_ENABLE_SIG_SLH_DSA)
    add_library(slh_dsa_c OBJECT
        sig_slh_dsa_pure_sha2_128s.c
        sig_slh_dsa_sha256_prehash_sha2_128s.c
        sig_slh_dsa_pure_shake_256f.c
        slh_dsa_wrappers.c
        slh_dsa_c/sha2_256.c
        slh_dsa_c/sha2_512.c
        slh_dsa_c/sha3_api.c
        slh_dsa_c/sha3_f1600.c
        slh_dsa_c/slh_dsa.c
        slh_dsa_c/slh_prehash.c
        slh_dsa_c/slh_sha2.c
        slh_dsa_c/slh_shake.c
    )
    target_include_directories(slh_dsa_c PRIVATE ${CMAKE_CURRENT_LIST_DIR}/slh_dsa_c)
    set(_SLH_DSA_OBJS ${_SLH_DSA_OBJS} $<TARGET_OBJECTS:slh_dsa_c>)
endif()

set(SLH_DSA_OBJS ${_SLH_DSA_OBJS} PARENT_SCOPE)
