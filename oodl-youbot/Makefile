# robotpkg Makefile for:	hardware/oodl-youbot
# Created:			Jan Paulus on 17 Aug 2010
#

OODL_YOUBOT_VERSION=	0.2
DISTNAME=		oodl-youbot-${OODL_YOUBOT_VERSION}
PKGNAME=		oodl-youbot-${OODL_YOUBOT_VERSION}
CATEGORIES=		hardware
MASTER_SITES=		http://brics.inf.h-brs.de/
MASTER_REPOSITORY= 	git git://github.com/janpaulus/BRICS_OODL.git

MAINTAINER=		jan.paulus@h-brs.de
HOMEPAGE=		http://www.best-of-robotics.org
COMMENT=		YouBot part of the BRICS Object Oriented Device Layer
LICENSE=		gnu-gpl-v3

USE_LANGUAGES=		c c++

CMAKE_ARGS+=		-DSELECTED_DRIVER=youbot
CMAKE_ARGS+=		-DSOEM_PATH=${PREFIX.soem}
CMAKE_ARGS+=		-DRUDECONFIG_PATH=${PREFIX.rudeconfig}
CMAKE_ARGS+=		-DBOOST_LOG_PATH=${PREFIX.boost-log}


include ../../devel/boost-headers/depend.mk
include ../../devel/boost-libs/depend.mk
include ../../devel/boost-log/depend.mk
include ../../brics/soem/depend.mk
include ../../brics/rudeconfig/depend.mk
include ../../mk/sysdep/cmake.mk
#include ../../mk/sysdep/doxygen.mk
include ../../mk/robotpkg.mk
