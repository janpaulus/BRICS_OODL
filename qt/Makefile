# robotpkg Makefile for:	brics/qt
# Created:			Michael Reckhaus on 07 Oct 2010

QT_LIBRARY_VERSION=	4.7.0
EXTRACT_SUFX?=		        .tar.gz
DISTNAME=		        qt-everywhere-opensource-src-${QT_LIBRARY_VERSION}
PKGNAME=		        qt-everywhere-opensource-src-${QT_LIBRARY_VERSION}
CATEGORIES=			graphics
MASTER_SITES=        	     	http://get.qt.nokia.com/qt/source/


MAINTAINER=		  	Nokia
HOMEPAGE=		  	http://get.qt.nokia.com/qt/source/
COMMENT=		  	QT Library
LICENSE=		  	gnu-lgpl-v3

GNU_CONFIGURE=			yes

CONFIGURE_ARGS+= --prefix=${PREFIX} 
#CONFIGURE_ARGS+= -opensource 
#CONFIGURE_ARGS+= -no-glib  

USE_LANGUAGES=			c c++

include ../../mk/robotpkg.mk



