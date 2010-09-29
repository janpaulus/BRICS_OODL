# robotpkg depend.mk for:	brics/hokuyo-urg
# Created:			Michael Reckhaus on 24 Aug 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
HOKUYO_URG_DEPEND_MK:= ${HOKUYO_URG_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		hokuyo-urg
endif

ifeq (+,$(HOKUYO_URG_DEPEND_MK))
PREFER.hokuyo-urg?=	robotpkg

DEPEND_USE+=		hokuyo-urg

DEPEND_ABI.hokuyo-urg?=	hokuyo-urg>=0.8.11
DEPEND_DIR.hokuyo-urg?=	../../brics/hokuyo-urg

SYSTEM_SEARCH.hokuyo-urg=\
  include/urg/UrgCtrl.h
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
