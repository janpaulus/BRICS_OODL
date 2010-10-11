# robotpkg Makefile for:	brics/collada-dom
# Created:			Michael Reckhaus on 07 Oct 2010

COLLADA-DOM_LIBRARY_VERSION=	2.2
EXTRACT_SUFX?=		        .zip
DISTNAME=		        ${COLLADA-DOM_LIBRARY_VERSION}
PKGNAME=		        collada-dom-${COLLADA-DOM_LIBRARY_VERSION}
CATEGORIES=			parser
MASTER_SITES=        	     	http://sourceforge.net/projects/collada-dom/files/Collada%20DOM%20


MAINTAINER=		  	Marcus Barnes
HOMEPAGE=		  	http://sourceforge.net/projects/collada-dom/files/
COMMENT=		  	COLLADA XML parser
LICENSE=		  	mit

USE_LANGUAGES=			c c++

GNU_CONFIGURE=			yes
CONFIGURE_ARGS+= --prefix=${PREFIX}


include ../../mk/robotpkg.mk

