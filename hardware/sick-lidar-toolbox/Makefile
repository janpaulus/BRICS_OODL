# robotpkg Makefile for:	hardware/sick-lidar-toolbox
# Created:			Jan Paulus on 17 Aug 2010
#

SICK_LIDAR_TOOLBOX_VERSION=	1.0.1
DISTNAME=		sick-lidar-toolbox-${SICK_LIDAR_TOOLBOX_VERSION}
PKGNAME=		sick-lidar-toolbox-${SICK_LIDAR_TOOLBOX_VERSION}
CATEGORIES=		hardware
#MASTER_SITES=		https://sicktoolbox.svn.sourceforge.net/
MASTER_REPOSITORY= 	svn https://sicktoolbox.svn.sourceforge.net/svnroot/sicktoolbox



MAINTAINER=		Jason Derenick
HOMEPAGE=		https://sicktoolbox.svn.sourceforge.net/
COMMENT=		The Sick LIDAR Matlab/C++ Toolbox 
LICENSE=		original-bsd

USE_LANGUAGES=		c++

WRKSRC=			${WRKDIR}/sick-lidar-toolbox-${SICK_LIDAR_TOOLBOX_VERSION}

#include ../../mk/sysdep/doxygen.mk
include ../../mk/robotpkg.mk
