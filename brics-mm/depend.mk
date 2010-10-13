# robotpkg depend.mk for:	brics/brics-mm
# Created:	 Jan Paulus on 12 Oct 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
BRICS_MM_DEPEND_MK:= ${BRICS_MM_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		brics-mm
endif

ifeq (+,$(BRICS_MM_DEPEND_MK))
PREFER.brics-mm?=	robotpkg

DEPEND_USE+=		brics-mm

DEPEND_ABI.brics-mm?=	brics-mm>=2.0.9
DEPEND_DIR.brics-mm?=	../../brics/brics-mm

SYSTEM_SEARCH.brics-mm=\
	include/zmq.h
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
