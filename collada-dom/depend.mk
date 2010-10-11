# robotpkg depend.mk for:	brics/collada-dom
# Created:			Michael Reckhaus on 07 Oct 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
COLLADA-DOM_DEPEND_MK:= ${COLLADA-DOM_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		collada-dom
endif

ifeq (+,$(COLLADA-DOM_DEPEND_MK))
PREFER.collada-dom?=	robotpkg

DEPEND_USE+=		collada-dom

DEPEND_ABI.collada-dom?=	collada-dom>=2.2
DEPEND_DIR.collada-dom?=	../../brics/collada-dom

SYSTEM_SEARCH.collada-dom=\
   #include/xercesc/parsers/XercesDOMParser.hpp
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
