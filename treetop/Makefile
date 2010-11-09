# robotpkg Makefile for:	brics/treetop
# Created:			Michael Reckhaus on 11 Nov 2010

TREETOP_LIBRARY_VERSION=	1.4.2
EXTRACT_SUFX?=		        .gem
DISTNAME=		        treetop-${TREETOP_LIBRARY_VERSION}
PKGNAME=		        treetop-${TREETOP_LIBRARY_VERSION}
CATEGORIES=			DSL
MASTER_SITES=        	     	http://rubyforge.org/frs/download.php/63483/


MAINTAINER=		  	Brian Takita
HOMEPAGE=		  	http://rubyforge.org/frs/download.php/63483/
COMMENT=		  	ruby pakage management
LICENSE=		  	mit	

NO_BUILD=			yes
#GNU_CONFIGURE=			no

do-extract:
	mkdir ${WRKSRC} && ${CP} -Rp ${DISTDIR}/treetop-${TREETOP_LIBRARY_VERSION}.gem ${WRKSRC}/treetop-${TREETOP_LIBRARY_VERSION}.gem

do-install:
	gem${RUBYGEMS_VERSION} install ${WRKSRC}/treetop-${TREETOP_LIBRARY_VERSION}.gem

include ../sysdep/ruby.mk
include ../sysdep/rubygems.mk
include ../../mk/robotpkg.mk

