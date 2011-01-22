# robotpkg depend.mk for:	brics/soem
# Created: Jan Paulus on 27 Oct 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
SOEM_DEPEND_MK:= ${SOEM_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		soem
endif

ifeq (+,$(SOEM_DEPEND_MK))
PREFER.soem?=	robotpkg

DEPEND_USE+=		soem

DEPEND_ABI.soem?=	soem>=1.2.4
DEPEND_DIR.soem?=	../../brics/soem

SYSTEM_SEARCH.soem=\
	include/soem/src/ethercatbase.h \
  lib/libsoem.a
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
