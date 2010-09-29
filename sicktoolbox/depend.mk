# robotpkg depend.mk for:	brics/sicktoolbox
# Created:			Jan Paulus on 18 Aug 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
SICKTOOLBOX_DEPEND_MK:= ${SICKTOOLBOX_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		sicktoolbox
endif

ifeq (+,$(SICKTOOLBOX_DEPEND_MK))
PREFER.sicktoolbox?=	robotpkg

DEPEND_USE+=		sicktoolbox

DEPEND_ABI.sicktoolbox?=	sicktoolbox>=1.0.1
DEPEND_DIR.sicktoolbox?=	../../brics/sicktoolbox

SYSTEM_SEARCH.sicktoolbox=\
	include/sicklms-1.0/SickLMS.hh
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
