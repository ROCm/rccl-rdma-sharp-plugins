/*************************************************************************
 * Copyright (c) 2016-2018, NVIDIA CORPORATION. All rights reserved.
 * Modifications Copyright (c) 2021 Advanced Micro Devices, Inc. All rights reserved.
 *
 * See LICENSE.txt for license information
 ************************************************************************/

#ifndef NCCL_UTILS_H_
#define NCCL_UTILS_H_

#include "nccl.h"
#include <stdint.h>

#if defined(__HIP_PLATFORM_HCC__) || defined(__HCC__) || defined(__HIPCC__)
#define LOAD(VAR) __atomic_load_n((VAR), __ATOMIC_SEQ_CST)
#define STORE(DST, SRC) __atomic_store_n((DST), (SRC), __ATOMIC_SEQ_CST)
#else
#define LOAD(VAR) *(VAR)
#define STORE(DST, SRC) *(DST) = (SRC)
#endif

#define NCCL_STATIC_ASSERT(_cond, _msg) \
    switch(0) {case 0:case (_cond):;}

ncclResult_t ncclIbMalloc(void** ptr, size_t size);
ncclResult_t getHostName(char* hostname, int maxlen);
uint64_t getHostHash();
uint64_t getPidHash();

struct netIf {
  char prefix[64];
  int port;
};

int parseStringList(const char* string, struct netIf* ifList, int maxList);
int matchIfList(const char* string, int port, struct netIf* ifList, int listSize, int matchExact);
int readFileNumber(long *value, const char *filename_fmt, ...);
const char *get_plugin_lib_path();

#endif
