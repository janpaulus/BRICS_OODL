#
# Copyright (c) 2010 LAAS/CNRS
# All rights reserved.
#
# Permission to use, copy, modify, and distribute this software for any purpose
# with or without   fee is hereby granted, provided   that the above  copyright
# notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS  SOFTWARE INCLUDING ALL  IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS. IN NO EVENT SHALL THE AUTHOR  BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR  ANY DAMAGES WHATSOEVER RESULTING  FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION,   ARISING OUT OF OR IN    CONNECTION WITH THE USE   OR
# PERFORMANCE OF THIS SOFTWARE.
#
#
DEPEND_DEPTH:=		${DEPEND_DEPTH}+
LIBPCAP_DEPEND_MK:=	${LIBPCAP_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		libcap
endif

ifeq (+,$(LIBPCAP_DEPEND_MK)) # ---------------------------------------------

PREFER.libpcap?=	system

DEPEND_USE+=		libpcap

DEPEND_ABI.libpcap?=	libpcap>=1

SYSTEM_SEARCH.libpcap=	\
	'include/pcap.h'						\
	'lib/libpcap.{a,so,dylib}'

SYSTEM_PKG.Linux-fedora.libpcap=	libpcap-devel
SYSTEM_PKG.Linux-ubuntu.libpcap=	libpcap-dev
SYSTEM_PKG.Linux-debian.libpcap=	libpcap-dev

endif # LIBPCAP_DEPEND_MK -------------------------------------------------

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
