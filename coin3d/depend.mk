# robotpkg depend.mk for:	brics/coin-3d
# Created:			Michael Reckhaus on 07 Oct 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
COIN-3D_DEPEND_MK:= ${COIN-3D_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		coin-3d
endif

ifeq (+,$(COIN-3D_DEPEND_MK))
PREFER.coin-3d?=	robotpkg

DEPEND_USE+=		coin-3d

DEPEND_ABI.coin-3d?=	coin-3d>=3.1.3
DEPEND_DIR.coin-3d?=	../../brics/coin-3d

SYSTEM_SEARCH.coin-3d=\
	libs/libCoin.la
	libs/libCoin.so
	libs/libCoin.so.60
	libs/pkgconfig/Coin.pc
	libs/libCoin.so.60.1.3
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
