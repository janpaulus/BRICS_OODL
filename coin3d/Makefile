# robotpkg Makefile for:	brics/coin-3d
# Created:			Michael Reckhaus on 07 Oct 2010

COIN-3D_LIBRARY_VERSION=	3.1.3
#EXTRACT_SUFX?=		        .tar.gz
DISTNAME=		        Coin-${COIN-3D_LIBRARY_VERSION}
PKGNAME=		        Coin-${COIN-3D_LIBRARY_VERSION}
CATEGORIES=			graphics
MASTER_SITES=        	     	http://ftp.coin3d.org/coin/src/all/


MAINTAINER=		  	Kongsberg SIM AS
HOMEPAGE=		  	http://ftp.coin3d.org/coin/src/all/
COMMENT=		  	Coin 3D Graphics Development Kit
LICENSE=		  	gnu-gpl-v2

USE_LANGUAGES=			c c++


GNU_CONFIGURE=			yes
CONFIGURE_ARGS+= --enable-debug=no 	#Does not compile in debug mode wich is standard option!

include ../../mk/robotpkg.mk

