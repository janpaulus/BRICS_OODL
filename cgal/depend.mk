# robotpkg depend.mk for:	brics/cgal
# Created:			Jan Paulus on 13 Oct 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
CGAL_DEPEND_MK:= ${CGAL_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		cgal
endif

ifeq (+,$(CGAL_DEPEND_MK))
PREFER.cgal?=	robotpkg

DEPEND_USE+=		cgal

DEPEND_ABI.cgal?=	cgal>=3.4
DEPEND_DIR.cgal?=	../../brics/cgal

SYSTEM_SEARCH.cgal=\
  lib/libCGAL.so\
  include/CGAL/AABB_tree/AABB_node.h
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
