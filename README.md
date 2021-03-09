# rccl-rdma-sharp-plugins

rccl-rdma-sharp plugin enables RDMA and Switch based collectives(SHARP)
with [AMD's RCCL](https://github.com/ROCmSoftwarePlatform/rccl) library

## Overview

## Requirements

* MOFED
* HIP
* SHARP
* RCCL
* GPUDirectRDMA plugin

## Build Instructions

### build system requirements

* HIP
* SHARP
* MOFED

Plugin uses GNU autotools for its build system. You can build it as follows:


```
$ ./autogen.sh
$ ./configure
$ make
$ make install
```

The following flags enabled to build with custom dependencies


```
  --with-verbs=PATH       Path to non-standard libibverbs installation
  --with-sharp=PATH       Path to non-standard SHARP installation
  --with-hip=PATH        Path to non-standard HIP installation
```


