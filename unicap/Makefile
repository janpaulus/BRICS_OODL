# robotpkg Makefile for:	brics/libunicap
# Created:			Azamat BRSU on 17 Aug 2010
#

UNICAP_VERSION=	0.9.11
DISTNAME=		libunicap-${UNICAP_VERSION}
PKGNAME=		libunicap-${UNICAP_VERSION}
CATEGORIES=		hardware
MASTER_SITES=		http://unicap-imaging.org/downloads/



MAINTAINER=		Arne Caspari
HOMEPAGE=		http://unicap-imaging.org/
COMMENT=		Unified API to linux cameras (ieee1394, UVC, V4L2)
LICENSE=		gnu-gpl-v2

USE_LANGUAGES=		c 

GNU_CONFIGURE=		yes
CONFIGURE_ARGS+= --prefix=${PREFIX} --disable-euvccam

include ../../mk/robotpkg.mk
