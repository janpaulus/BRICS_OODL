# robotpkg Makefile for:	hardware/sicktoolbox
# Created:			Jan Paulus on 17 Aug 2010
#

SICK_LIDAR_TOOLBOX_VERSION=	1.0.1
DISTNAME=		sicktoolbox-${SICK_LIDAR_TOOLBOX_VERSION}
PKGNAME=		sicktoolbox-${SICK_LIDAR_TOOLBOX_VERSION}
CATEGORIES=		hardware
MASTER_SITES=		http://downloads.sourceforge.net/project/sicktoolbox/sicktoolbox/${SICK_LIDAR_TOOLBOX_VERSION}/
MASTER_REPOSITORY= 	svn https://sicktoolbox.svn.sourceforge.net/svnroot/sicktoolbox
#http://downloads.sourceforge.net/project/sicktoolbox/sicktoolbox/1.0.1/sicktoolbox-1.0.1.tar.gz

MAINTAINER=		Jason Derenick
HOMEPAGE=		https://sicktoolbox.svn.sourceforge.net/
COMMENT=		The Sick LIDAR Matlab/C++ Toolbox 
LICENSE=		modified-bsd

USE_LANGUAGES=		c c++

GNU_CONFIGURE=		yes


#WRKSRC=			${WRKDIR}/sick-lidar-toolbox-${SICK_LIDAR_TOOLBOX_VERSION}

include ../../mk/robotpkg.mk
