# robotpkg depend.mk for:	brics/coin3d
# Created:			Michael Reckhaus on 07 Oct 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
COIN3D_DEPEND_MK:= ${COIN3D_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		coin3d
endif

ifeq (+,$(COIN3D_DEPEND_MK))
PREFER.coin3d?=	robotpkg

DEPEND_USE+=		coin3d

DEPEND_ABI.coin3d?=	coin3d>=3.1.3
DEPEND_DIR.coin3d?=	../../brics/coin3d

SYSTEM_SEARCH.coin3d=\
  include/SoWinLeaveScope.h\
  include/SoDebug.h
endif

#SYSTEM_PKG.Linux.coin3d=libcoin40-dev

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
