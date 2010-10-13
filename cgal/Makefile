# robotpkg Makefile for:	brics/cgal
# Created:			Jan Paulus on 12 Oct 2010

CGAL_LIBRARY_VERSION=	3.4
DISTNAME=		        CGAL-${CGAL_LIBRARY_VERSION}
PKGNAME=		        cgal-${CGAL_LIBRARY_VERSION}
CATEGORIES=			graphics
#FETCH_METHOD= 			custom
MASTER_SITES=       http://gforge.inria.fr/frs/download.php/15692/
#http://gforge.inria.fr/frs/download.php/15692/CGAL-3.4.tar.gz

do-fetch:
	${RUN}cd ${DISTDIR} && wget -nc http://gforge.inria.fr/frs/download.php/15692/CGAL-${CGAL_LIBRARY_VERSION}.tar.gz 

MAINTAINER=		  	INRIA
HOMEPAGE=		  	https://gforge.inria.fr/projects/cgal
COMMENT=		  	CGAL, the Computational Geometry Algorithms Library
LICENSE=		  	gnu-lgpl-v3

USE_LANGUAGES=			c c++


include ../../mk/sysdep/cmake.mk
include ../../mk/robotpkg.mk

