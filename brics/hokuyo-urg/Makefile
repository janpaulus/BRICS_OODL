# robotpkg Makefile for:	brics/hokuyo_urg_library
# Created:			Michael Reckhaus on 24 Aug 2010

HOKUYO_URG_LIBRARY_VERSION=	0.8.11
EXTRACT_SUFX?=		.zip
DISTNAME=		urg-${HOKUYO_URG_LIBRARY_VERSION}
PKGNAME=		hokuyo_urg_library-${HOKUYO_URG_LIBRARY_VERSION}
CATEGORIES=		hardware
#MASTER_SITES=		http://downloads.sourceforge.net/project/sicktoolbox/sicktoolbox/${SICK_LIDAR_TOOLBOX_VERSION}/
MASTER_SITES=http://www.hokuyo-aut.jp/02sensor/07scanner/download/urg_programs_en/
#MASTER_REPOSITORY= 	svn https://sicktoolbox.svn.sourceforge.net/svnroot/sicktoolbox
#http://downloads.sourceforge.net/project/sicktoolbox/sicktoolbox/1.0.1/sicktoolbox-1.0.1.tar.gz

MAINTAINER=		Satofumi KAMIMURA
HOMEPAGE=		http://www.hokuyo-aut.jp/02sensor/07scanner/download/urg_programs_en/
COMMENT=		Hokuyo URG library 
LICENSE=		gnu-lgpl-v3

USE_LANGUAGES=		c c++

GNU_CONFIGURE=		yes

#WRKSRC=			${WRKDIR}/sick-lidar-toolbox-${SICK_LIDAR_TOOLBOX_VERSION}


include ../SDL.mk
include ../SDL_net.mk
include ../../mk/robotpkg.mk

