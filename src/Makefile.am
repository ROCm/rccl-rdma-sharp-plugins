#
# Copyright (C) Mellanox Technologies Ltd. 2019-2020.  ALL RIGHTS RESERVED.
# See file LICENSE for terms.
#

lib_LTLIBRARIES     = librccl-net.la

librccl_net_la_CPPFLAGS = -I$(top_srcdir)/include
librccl_net_la_CFLAGS   = $(CFLAGS) -DGNU_SOURCE
librccl_net_la_LIBADD   =
librccl_net_la_LDFLAGS  = $(LDFLAGS)

librccl_net_la_SOURCES = \
	ibvwrap.c \
	utils.c	\
	p2p_plugin.c \
	ib_plugin.c

if HAVE_UCX_PLUGIN
librccl_net_la_CPPFLAGS += -DHAVE_UCX_PLUGIN $(UCX_CPPFLAGS)
librccl_net_la_LIBADD   += $(UCX_LIBADD)
librccl_net_la_LDFLAGS  += $(UCX_LDFLAGS)
librccl_net_la_SOURCES  += \
	ucx_plugin.c \
	ucx_rma_plugin.c
endif

if HAVE_SHARP_PLUGIN
librccl_net_la_CPPFLAGS += -DHAVE_SHARP_PLUGIN $(SHARP_CPPFLAGS)
librccl_net_la_LIBADD   += $(SHARP_LIBADD)
librccl_net_la_LDFLAGS  += $(SHARP_LDFLAGS)
librccl_net_la_SOURCES  += sharp_plugin.c
endif
