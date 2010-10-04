# robotpkg Makefile for:	brics/zeromq
# Created:			Azamat BRSU on 17 Aug 2010
#

ZEROMQ_VERSION=	2.0.9
DISTNAME=		zeromq-${ZEROMQ_VERSION}
PKGNAME=		zeromq-${ZEROMQ_VERSION}
CATEGORIES=		middleware
MASTER_SITES=   http://www.zeromq.org/local--files/area:download/



MAINTAINER=		iMatix Corp.
HOMEPAGE=		http://www.zeromq.org/
COMMENT=		small and fast socket communication library
LICENSE=		gnu-lgpl-v3

USE_LANGUAGES=		c c++
#PREFIX= /home/azamat/documents/euprojects/brics/development/BRICSWP2/Software/brocre_pkg_mng/


GNU_CONFIGURE=		yes
CONFIGURE_ARGS+= --prefix=${PREFIX} --with-pgm

include ../../mk/robotpkg.mk
