# robotpkg Makefile for:	brics/rubygems
# Created:			Michael Reckhaus on 07 Oct 2010

RUBYGEMS_LIBRARY_VERSION=	1.3.7
EXTRACT_SUFX?=		        .tgz
DISTNAME=		        rubygems-${RUBYGEMS_LIBRARY_VERSION}
PKGNAME=		        rubygems-${RUBYGEMS_LIBRARY_VERSION}
CATEGORIES=			pakage management
MASTER_SITES=        	     	http://production.cf.rubygems.org/rubygems/


MAINTAINER=		  	Gemcutter
HOMEPAGE=		  	http://production.cf.rubygems.org/rubygems/
COMMENT=		  	ruby pakage management
LICENSE=		  	mit	

NO_BUILD=			yes
#GNU_CONFIGURE=			yes

do-install:
	cd ${WRKSRC} && ruby1.8 setup.rb --prefix=${PREFIX}

include ../sysdep/ruby.mk
include ../../mk/robotpkg.mk

