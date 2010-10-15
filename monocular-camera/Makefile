# robotpkg Makefile for:	brics/zeromq
# Created:			Azamat BRSU on 17 Aug 2010
#

OODL_MONOCULAR_CAMERA_VERSION= 0.1
DISTNAME=		monocular-camera-${OODL_MONOCULAR_CAMERA_VERSION}
PKGNAME=		monocular-camera-${OODL_MONOCULAR_CAMERA_VERSION}
CATEGORIES=		hardware
MASTER_SITES=		http://brics.inf.h-brs.de/
MASTER_REPOSITORY= 	git git://github.com/janpaulus/BRICS_OODL.git

MAINTAINER=		azamat.shakhimardanov@h-brs.de
HOMEPAGE=		http://www.best-of-robotics.org
COMMENT=		Generic monocular camera API based on unicap. Works with ieee1394, DCAM, UVC, V4L1/2 compiliant cameras
LICENSE=		gnu-gpl-v3

USE_LANGUAGES=		c c++

CMAKE_ARGS+=		-DSELECTED_DRIVER=monocular-camera
CMAKE_ARGS+=		-DUNICAP_PATH=${PREFIX.unicap}

include ../../brics/unicap/depend.mk
include ../../mk/sysdep/cmake.mk
include ../../mk/robotpkg.mk
