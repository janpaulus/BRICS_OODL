# robotpkg depend.mk for:	brics/boost-log
# Created:			Jan Paulus on 24 Aug 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
BOOST_LOG_DEPEND_MK:= ${BOOST_LOG_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		boost-log
endif

ifeq (+,$(BOOST_LOG_DEPEND_MK))
PREFER.boost-log?=	robotpkg

DEPEND_USE+=		boost-log

DEPEND_ABI.boost-log?=	boost-log>=0.8.11
DEPEND_DIR.boost-log?=	../../brics/boost-log

SYSTEM_SEARCH.boost-log=\
#	include/sicklms-1.0/SickLMS.hh
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
