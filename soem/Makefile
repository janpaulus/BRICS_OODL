# robotpkg Makefile for:	brics/soem
# Created: Jan Paulus on 27 Oct 2010
#

SOEM_VERSION=	1.2.4
EXTRACT_SUFX?= .tar.bz2
DISTNAME=		SOEM${SOEM_VERSION}
PKGNAME=		soem-${SOEM_VERSION}
CATEGORIES=		hardware
MASTER_SITES=		http://download.berlios.de/soem/

MAINTAINER=		Arthur Ketels
HOMEPAGE=		http://soem.berlios.de/
COMMENT=		SOEM is an EtherCAT (Ethernet for Control Automation Technology) master library written in c.
LICENSE=		gnu-gpl-v2

USE_LANGUAGES=		c c++

pre-configure:
	${RUN}cd ${WRKSRC} &&					\
	cp ${FILESDIR}/CMakeLists.txt CMakeLists.txt


include ../../mk/sysdep/cmake.mk
include ../../mk/robotpkg.mk
