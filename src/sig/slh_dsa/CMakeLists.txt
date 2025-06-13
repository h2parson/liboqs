# SPDX-License-Identifier: MIT

set(_SLH_DSA_OBJS "")

if(OQS_ENABLE_SIG_slh_dsa)
    add_library(slh_dsa_c OBJECT sha2_256.c sha2_512.c sha3_api.c sha3_f1600.c slh_dsa.c slh_prehash.c slh_sha2.c slh_shake.c)
    target_include_directories(slh_dsa_c PRIVATE ${CMAKE_CURRENT_LIST_DIR}/slh_dsa_c)
    set(_SLH_DSA_OBJS ${_SLH_DSA_OBJS} $<TARGET_OBJECTS:slh_dsa_c>)
endif()

set(SLH_DSA_OBJS ${_SLH_DSA_OBJS} PARENT_SCOPE)
