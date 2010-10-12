# robotpkg Makefile for:	hardware/oodl-sick-s300
# Created:			Jan Paulus on 17 Aug 2010
#

OODL_SICK_S300_VERSION=	0.01
DISTNAME=		oodl-sick-s300-${OODL_SICK_S300_VERSION}
PKGNAME=		oodl-sick-s300-${OODL_SICK_S300_VERSION}
CATEGORIES=		hardware
MASTER_SITES=		http://brics.inf.h-brs.de/
MASTER_REPOSITORY= 	git git://github.com/janpaulus/BRICS_OODL.git

MAINTAINER=		jan.paulus@h-brs.de
HOMEPAGE=		http://www.best-of-robotics.org
COMMENT=		Sick S300 part of the BRICS Object Oriented Device Layer
LICENSE=		gnu-gpl-v3

USE_LANGUAGES=		c c++

CMAKE_ARGS+=		-DSELECTED_DRIVER=sick-s300
CMAKE_ARGS+=		-DBOOST_LOG_PATH=${PREFIX.boost-log}



include ../../devel/boost-headers/depend.mk
include ../../devel/boost-libs/depend.mk
include ../../devel/boost-log/depend.mk
include ../../mk/sysdep/cmake.mk
#include ../../mk/sysdep/doxygen.mk
include ../../mk/robotpkg.mk
