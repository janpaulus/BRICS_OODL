# robotpkg depend.mk for:	manipulation/genManip-genom
# Created:			Xavier Broquere on Tue, 20 Apr 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
GENMANIPGENOM_DEPEND_MK:=	${GENMANIPGENOM_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		genManip-genom
endif

ifeq (+,$(GENMANIPGENOM_DEPEND_MK))
PREFER.genManip-genom?=	robotpkg

DEPEND_USE+=		genManip-genom

DEPEND_ABI.genManip-genom?=	genManip-genom>=0.2
DEPEND_DIR.genManip-genom?=	../../manipulation/genManip-genom

SYSTEM_SEARCH.genManip-genom=\
	include/genManip/genManipStruct.h		\
	lib/pkgconfig/genManip.pc
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
