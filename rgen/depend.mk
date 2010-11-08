# robotpkg depend.mk for:	brics/rgen
# Created:			Michael Reckhaus on 05 Nov 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
RGEN_DEPEND_MK:= ${RGEN_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		rgen
endif

ifeq (+,$(RGEN_DEPEND_MK))
PREFER.rgen?=	robotpkg

DEPEND_USE+=		rgen

DEPEND_ABI.rgen?=	rgen>=0.5
DEPEND_DIR.rgen?=	../../brics/rgen

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
