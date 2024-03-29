#
# Copyright (C) Mellanox Technologies Ltd. 2019.  ALL RIGHTS RESERVED.
# Modifications Copyright (c) 2021 Advanced Micro Devices, Inc. All rights reserved.
#
# See file LICENSE for terms.
#
AC_PREREQ([2.63])

AC_COPYRIGHT([Copyright (C) 2019 Mellanox Technologies Ltd. All rights reserved.])

define([rccl_rdma_sharp_plugins_ver_major], 1)
define([rccl_rdma_sharp_plugins_ver_minor], 0)

AC_INIT([rccl-rdma-sharp-plugins], [rccl_rdma_sharp_plugins_ver_major.rccl_rdma_sharp_plugins_ver_minor], [rccl-maintainer@amd.com], [],[https://github.com/ROCmSoftwarePlatform/rccl-rdma-sharp-plugins])

AM_INIT_AUTOMAKE([1.10 foreign tar-ustar subdir-objects])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AM_MAINTAINER_MODE
AC_CONFIG_MACRO_DIR([m4])

AC_USE_SYSTEM_EXTENSIONS
AC_GNU_SOURCE
AC_CONFIG_HEADERS([config.h])

LT_INIT
RPM_RELEASE=1
MAJOR_VERSION=rccl_rdma_sharp_plugins_ver_major
MINOR_VERSION=rccl_rdma_sharp_plugins_ver_minor
VERSION=$MAJOR_VERSION.$MINOR_VERSION

AC_SUBST(RPM_RELEASE)
AC_SUBST(VERSION)
AC_SUBST(MAJOR_VERSION)
AC_SUBST(MINOR_VERSION)
AC_SUBST([BUILD_DATE], [$(date +'%b/%d/%Y')])
AC_SUBST([BUILD_TIME], [$(date +'%H:%M:%S')])

# Checks for programs.
AC_GNU_SOURCE
AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_CXX
AM_PROG_AS
AC_PROG_SED
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_HEADER_STDC
LT_LIB_M

AC_ARG_ENABLE([debug],AS_HELP_STRING([--enable-debug], [Enable extra debugging code (default is NO).]),
              [], [enable_debug=no])

if test $enable_debug = yes; then
	AC_DEFINE([ENABLE_DEBUG], [1], [Enable debugging code])
	CFLAGS="$CFLAGS -O0 -g3 -Werror"
else
	CFLAGS="$CFLAGS -O3 -DNDEBUG -Werror"
fi

#check for hip
AC_DEFINE([__HIP_PLATFORM_AMD__], [], [Use AMD Platform])
AC_ARG_WITH([hip],
            [AC_HELP_STRING([--with-hip=PATH],
            [Path to non-standard HIP installation])],
            [AS_IF([test -d $withval/lib64], [hip_libdir="lib64"], [hip_libdir="lib"])
             CFLAGS="-I$withval/include $CFLAGS"
             LDFLAGS="-L$withval/$hip_libdir $LDFLAGS"],
            [CFLAGS="-I/opt/rocm/include $CFLAGS"
             LDFLAGS="-L/opt/rocm/lib $LDFLAGS"])

AC_CHECK_HEADER(       [hip/hip_runtime.h], [], [AC_MSG_FAILURE([HIP runtime header files not found])])
AC_CHECK_LIB([amdhip64], [hipMalloc],     [], [AC_MSG_FAILURE([HIP runtime libs not found])])

#check for verbs
AC_ARG_WITH([verbs],
            [AC_HELP_STRING([--with-verbs(=DIR)],
            [Build Infiniband  support, adding DIR/include, DIR/lib, and DIR/lib64 to the search path for headers and libraries])],
            [CFLAGS="-I$with_verbs/include $CFLAGS"
             LDFLAGS="-L$with_verbs/lib64 -L$with_verbs/lib -libverbs $LDFLAGS"],
            [CFLAGS="-I/usr/include $CFLAGS"
             LDFLAGS="-L/usr/lib64 -L/usr/lib -libverbs $LDFLAGS"])

AC_CHECK_HEADER(        [infiniband/verbs.h],  [],[AC_MSG_FAILURE([ibverbs header files not found])])
AC_CHECK_LIB([ibverbs], [ibv_get_device_list], [],[AC_MSG_FAILURE([libibverbs not found]);])

AC_CHECK_DECLS([IBV_ACCESS_RELAXED_ORDERING, IBV_QPF_GRH_REQUIRED], [], [],
                    [[#include <infiniband/verbs.h>]])

# check for ucx
AM_CONDITIONAL([HAVE_UCX_PLUGIN], [false])
m4_include([m4/ucx.m4])
CHECK_UCX
AC_MSG_RESULT([UCX support: $ucx_happy])

# check for sharp
AM_CONDITIONAL([HAVE_SHARP_PLUGIN], [false])
m4_include([m4/sharp.m4])
CHECK_SHARP
AC_MSG_RESULT([SHARP support: $sharp_happy])

#check for required headers
AC_CHECK_HEADERS([limits.h stdlib.h string.h unistd.h], [],
                 [AC_MSG_FAILURE([unable to find required headers])])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 rccl-rdma-sharp-plugins.spec
                 rccl-rdma-sharp-plugins.pc
                 debian/changelog
                 debian/control
                 debian/rules
                ])
AC_OUTPUT

echo "NCCL-RDMA-SHARP Plugin has been configured."
