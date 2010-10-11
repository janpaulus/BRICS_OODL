# robotpkg depend.mk for:	brics/qt
# Created:			Michael Reckhaus on 07 Oct 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
QT_DEPEND_MK:= ${QT_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		qt
endif

ifeq (+,$(QT_DEPEND_MK))
PREFER.qt?=	robotpkg

DEPEND_USE+=		qt

DEPEND_ABI.qt?=	qt>=4.7.0
DEPEND_DIR.qt?=	../../brics/qt

SYSTEM_SEARCH.qt=\
   #include/xercesc/parsers/XercesDOMParser.hpp
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
