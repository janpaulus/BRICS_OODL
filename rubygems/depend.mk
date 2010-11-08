# robotpkg depend.mk for:	brics/rubygems
# Created:			Michael Reckhaus on 08 Nov 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
RUBYGEMS_DEPEND_MK:= ${RUBYGEMS_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		rubygems
endif

ifeq (+,$(RUBYGEMS_DEPEND_MK))
PREFER.rubygems?=	robotpkg

DEPEND_USE+=		rubygems

DEPEND_ABI.rubygems?=	rubygems>=1.3.7
DEPEND_DIR.rubygems?=	../../brics/rubygems

endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
