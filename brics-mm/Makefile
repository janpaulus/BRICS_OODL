# robotpkg Makefile for:	brics/brics-mm
# Created:			Jan Paulus on 12 Oct 2010
#

BRICS_MM_VERSION=	0.00
DISTNAME=		brics-mm-${BRICS_MM_VERSION}
PKGNAME=		brics-mm-${BRICS_MM_VERSION}
CATEGORIES=		path
MASTER_SITES=		http://brics.inf.h-brs.de/
MASTER_REPOSITORY= 	svn https://svn.best-of-robotics.org/brics/BROCRE/BRICS_MM/trunk

MAINTAINER=		nowak@gps-stuttgart.de
HOMEPAGE=		http://www.best-of-robotics.org
COMMENT=		BRICS_MM is the BRICS library for mobile manipulation.
LICENSE=		2-clause-bsd

USE_LANGUAGES=		c c++

#CMAKE_ARGS+=		-DSELECTED_DRIVER=hokuyo-urg
#CMAKE_ARGS+=		-DHOKUYO_URG_PATH=${PREFIX.hokuyo-urg}
#CMAKE_ARGS+=		-DBOOST_LOG_PATH=${PREFIX.boost-log}


include ../../mk/sysdep/xerces-c.mk
#include ../../brics/collada-dom/depend.mk
include ../../brics/sysdep/qt.mk
include ../../brics/coin3d/depend.mk
include ../../mk/sysdep/libsoqt.mk
include ../../devel/boost-headers/depend.mk
include ../../devel/boost-libs/depend.mk
include ../../mk/sysdep/cmake.mk
#include ../../mk/sysdep/doxygen.mk
include ../../mk/robotpkg.mk
