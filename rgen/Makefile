# robotpkg Makefile for:	brics/rgen
# Created:			Michael Reckhaus on 05 Nov 2010

RGEN_LIBRARY_VERSION=	0.5.0
EXTRACT_SUFX?=		        .zip
DISTNAME=		        rgen-${RGEN_LIBRARY_VERSION}
PKGNAME=		        rgen-${RGEN_LIBRARY_VERSION}
CATEGORIES=			development
MASTER_SITES=        	     	http://rubyforge.org/frs/download.php/58283/


MAINTAINER=		  	The Apache Software Foundation
HOMEPAGE=		  	http://rubyforge.org/frs/download.php/58283/
COMMENT=		  	rgen - ruby mdsd tool
LICENSE=		  	mit

#GNU_CONFIGURE=			no
NO_BUILD=			yes

do-install:
	cd ${WRKSRC} && cd .. && cp -r rgen-${RGEN_LIBRARY_VERSION} ${PREFIX}/bin

include ../../mk/robotpkg.mk

