# robotpkg depend.mk for:	brics/soqt
# Created:			Michael Reckhaus on 07 Oct 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
SOQT_DEPEND_MK:= ${SOQT_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		soqt
endif

ifeq (+,$(SOQT_DEPEND_MK))
PREFER.soqt?=	robotpkg

DEPEND_USE+=		soqt

DEPEND_ABI.soqt?=	soqt>=1.5.0
DEPEND_DIR.soqt?=	../../brics/soqt

SYSTEM_SEARCH.soqt=\
	'lib/libSoQt.{a,so,dylib}'\
	'bin/soqt-config'
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
