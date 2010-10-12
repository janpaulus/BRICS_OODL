# robotpkg Makefile for:	brics/qt
# Created:			Michael Reckhaus on 07 Oct 2010

QT_LIBRARY_VERSION=	4.7.0
DISTNAME=		        qt-everywhere-opensource-src-${QT_LIBRARY_VERSION}
PKGNAME=		        qt-${QT_LIBRARY_VERSION}
CATEGORIES=			graphics
MASTER_SITES=        	     	http://get.qt.nokia.com/qt/source/


MAINTAINER=		  	Nokia
HOMEPAGE=		  	http://get.qt.nokia.com/qt/source/
COMMENT=		  	QT Library
LICENSE=		  	gnu-lgpl-v3


# uses gnu configure but the prefix "--infodir=" "--mandir=" which are auto-set by robotpkg do not work
do-configure:
	 ${RUN}cd ${WRKSRC} && ./configure --prefix=${PREFIX} 

#-opensource --confirm-license=yes

USE_LANGUAGES=			c c++

include ../../mk/robotpkg.mk



