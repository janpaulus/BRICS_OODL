# robotpkg depend.mk for:	brics/brics-3d
# Created:	 Jan Paulus on 12 Oct 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
BRICS_3D_DEPEND_MK:= ${BRICS_3D_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		brics-3d
endif

ifeq (+,$(BRICS_3D_DEPEND_MK))
PREFER.brics-3d?=	robotpkg

DEPEND_USE+=		brics-3d

DEPEND_ABI.brics-3d?=	brics-3d>=2.0.9
DEPEND_DIR.brics-3d?=	../../brics/brics-3d

SYSTEM_SEARCH.brics-3d=\
	include/zmq.h
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
