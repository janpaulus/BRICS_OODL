# robotpkg Makefile for:	brics/brics-3d
# Created:			Jan Paulus on 12 Oct 2010
#

BRICS_3D_VERSION=	0.00
DISTNAME=					brics-3d-${BRICS_3D_VERSION}
PKGNAME=		brics-3d-${BRICS_3D_VERSION}
CATEGORIES=		image
MASTER_SITES=		http://brics.inf.h-brs.de/
MASTER_REPOSITORY= 	svn https://svn.best-of-robotics.org/brics/BROCRE/BRICS_3D/trunk

MAINTAINER=		blumenthal@gps-stuttgart.de
HOMEPAGE=		http://www.best-of-robotics.org
CO3DENT=		BRICS 3D is the BRICS library for 3D perception and modeling.
LICENSE=		2-clause-bsd

USE_LANGUAGES=		c c++

CMAKE_ARGS+=		-DCGAL_DIR=${PREFIX.cgal}/lib/CGAL
#CMAKE_ARGS+=		-DXERCES_ROBOTPKG_DIR=${PREFIX.xerces-c}


include ../../image/opencv/depend.mk
include ../../devel/boost-headers/depend.mk
include ../../devel/boost-libs/depend.mk
include ../../brics/cgal/depend.mk
include ../../math/eigen2/depend.mk
include ../../brics/xerces-c/depend.mk
include ../sysdep/openscenegraph.mk
include ../sysdep/cppunit.mk
include ../../mk/sysdep/cmake.mk
#include ../../mk/sysdep/doxygen.mk
include ../../mk/robotpkg.mk
