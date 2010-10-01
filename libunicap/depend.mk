# robotpkg depend.mk for:	brics/libunicap
# Created:	 Azamat BRSU on 18 Aug 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
LIBUNICAP_DEPEND_MK:= ${LIBUNICAP_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		libunicap
endif

ifeq (+,$(LIBUNICAP_DEPEND_MK))
PREFER.libunicap?=	robotpkg

DEPEND_USE+=		libunicap

DEPEND_ABI.libunicap?=	libunicap>=1.0.1
DEPEND_DIR.libunicap?=	../../brics/libunicap

SYSTEM_SEARCH.libunicap=\
	include/unicap/unicap.h
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
