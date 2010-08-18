# robotpkg Makefile for:	hardware/brics-oodl
# Created:			Jan Paulus on 17 Aug 2010
#

BRICS_OODL_VERSION=		0.01
DISTNAME=		brics-oodl-${BRICS_OODL_VERSION}
PKGNAME=		brics-oodl-${BRICS_OODL_VERSION}
CATEGORIES=		hardware
MASTER_SITES=		http://brics.inf.h-brs.de/
MASTER_REPOSITORY= 	git ssh://github.com/janpaulus/BRICS_OODL.git



MAINTAINER=		jan.paulus@h-brs.de
HOMEPAGE=		http://www.best-of-robotics.org
COMMENT=		BRICS Object Oriented Device Layer
LICENSE=		original-bsd

USE_LANGUAGES=		c c++

#CMAKE_ARGS+=	-DBOOST_INCLUDEDIR=${PREFIX.boost-headers}/include

WRKSRC=			${WRKDIR}/brics-oodl-${BRICS_OODL_VERSION}

include ../../devel/boost-headers/depend.mk
include ../../devel/boost-libs/depend.mk
#include ../../hardware/serial/depend.mk
include ../../hardware/sicktoolbox/depend.mk
include ../../mk/sysdep/cmake.mk
#include ../../mk/sysdep/doxygen.mk
include ../../mk/robotpkg.mk
