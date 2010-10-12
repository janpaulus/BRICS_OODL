DEPEND_DEPTH:=		${DEPEND_DEPTH}+
QT_DEPEND_MK:=	${QT_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		qt
endif

ifeq (+,$(QT_DEPEND_MK)) # -------------------------------------

PREFER.qt?=	system
DEPEND_USE+=		qt
DEPEND_ABI.qt?=	qt>=4.6.2

SYSTEM_SEARCH.qt=	\
	'include/qt4/Qt/qcoreevent.h' \
	'share/qt4/lib/libQtCore.{a,so,dylib}'

SYSTEM_PKG.Linux.qt=libqt4-dev


endif # QT_DEPEND_MK -------------------------------------------

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
