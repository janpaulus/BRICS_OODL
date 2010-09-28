# robotpkg Makefile for:	hardware/oodl-sick-lms2xx
# Created:			Jan Paulus on 17 Aug 2010
#

OODL_SICK_LMS2xx_VERSION=	0.01
DISTNAME=		oodl-sick-lms2xx-${OODL_SICK_LMS2xx_VERSION}
PKGNAME=		oodl-sick-lms2xx-${OODL_SICK_LMS2xx_VERSION}
CATEGORIES=		hardware
MASTER_SITES=		http://brics.inf.h-brs.de/
MASTER_REPOSITORY= 	git git://github.com/janpaulus/BRICS_OODL.git

MAINTAINER=		jan.paulus@h-brs.de
HOMEPAGE=		http://www.best-of-robotics.org
COMMENT=		Sick LMS 2xx part of the BRICS Object Oriented Device Layer
LICENSE=		gnu-gpl-v3

USE_LANGUAGES=		c c++

CMAKE_ARGS+=		-DSELECTED_DRIVER=sick-lms-2xx
CMAKE_ARGS+=		-DSICK_TOOLBOX_PATH=${PREFIX.sicktoolbox}


include ../../devel/boost-headers/depend.mk
include ../../devel/boost-libs/depend.mk
include ../../brics/sicktoolbox/depend.mk
include ../../mk/sysdep/cmake.mk
#include ../../mk/sysdep/doxygen.mk
include ../../mk/robotpkg.mk
