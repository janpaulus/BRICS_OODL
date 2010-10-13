# robotpkg depend.mk for:	brics/unicap
# Created:	 Azamat BRSU on 18 Aug 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
UNICAP_DEPEND_MK:= ${UNICAP_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		unicap
endif

ifeq (+,$(UNICAP_DEPEND_MK))
PREFER.unicap?=	robotpkg

DEPEND_USE+=		unicap

DEPEND_ABI.unicap?=	unicap>=0.9.8
DEPEND_DIR.unicap?=	../../brics/unicap

SYSTEM_SEARCH.unicap=\
	include/unicap/unicap.h
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
