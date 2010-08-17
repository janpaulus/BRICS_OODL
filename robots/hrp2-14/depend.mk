# robotpkg depend.mk for:	robots/hrp2_14
# Created:			Anthony Mallet on Wed, 14 May 2008
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
HRP2_14_DEPEND_MK:=	${HRP2_14_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		hrp2_14
endif

ifeq (+,$(HRP2_14_DEPEND_MK)) # --------------------------------------

PREFER.hrp2_14?=	robotpkg

SYSTEM_SEARCH.hrp2_14=\
	include/hrp2_14/hrp2_14.h

DEPEND_USE+=		hrp2_14

DEPEND_ABI.hrp2_14?=	hrp2_14>=1.7.5
DEPEND_DIR.hrp2_14?=	../../robots/hrp2-14

endif # HRP2_14_DEPEND_MK --------------------------------------------

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
