# robotpkg depend.mk for:	brics/xerces-c
# Created:			Michael Reckhaus on 07 Oct 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
XERCES-C_DEPEND_MK:= ${XERCES-C_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		xerces-c
endif

ifeq (+,$(XERCES-C_DEPEND_MK))
PREFER.xerces-c?=	robotpkg

DEPEND_USE+=		xerces-c

DEPEND_ABI.xerces-c?=	xerces-c>=3.1.1
DEPEND_DIR.xerces-c?=	../../brics/xerces-c

SYSTEM_SEARCH.xerces-c=\
   include/xercesc/parsers/XercesDOMParser.hpp
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
