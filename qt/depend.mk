# robotpkg depend.mk for:	brics/qt
# Created:			Michael Reckhaus on 07 Oct 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
QT_DEPEND_MK:= ${QT_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		qt
endif

ifeq (+,$(QT_DEPEND_MK))
PREFER.qt?=	system

DEPEND_USE+=		qt

DEPEND_ABI.qt?=	qt>=4.6.2
DEPEND_DIR.qt?=	../../brics/qt

SYSTEM_SEARCH.qt=\
   'include/qt4/Qt/qcoreevent.h' \
	'share/qt4/lib/libQtCore.{a,so,dylib}'
endif

SYSTEM_PKG.Linux.qt=libqt4-dev

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
