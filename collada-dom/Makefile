# robotpkg Makefile for:	brics/collada-dom
# Created:			Michael Reckhaus on 07 Oct 2010

COLLADA-DOM_LIBRARY_VERSION=	2.2
EXTRACT_SUFX?=		        .zip
DISTNAME=		        Collada%20DOM%20${COLLADA-DOM_LIBRARY_VERSION}
PKGNAME=		        collada-dom-${COLLADA-DOM_LIBRARY_VERSION}
CATEGORIES=			parser
MASTER_SITES=        	     	http://downloads.sourceforge.net/project/collada-dom/Collada%20DOM/Collada%20DOM%20${COLLADA-DOM_LIBRARY_VERSION}/
#http://downloads.sourceforge.net/project/collada-dom/Collada%20DOM/Collada%20DOM%202.2/Collada%20DOM%202.2.zip


MAINTAINER=		  	Marcus Barnes
HOMEPAGE=		  	http://sourceforge.net/projects/collada-dom/files/
COMMENT=		  	COLLADA XML parser
LICENSE=		  	mit

WRKSRC = 	${WRKDIR}/collada-dom

#BUILD_MAKE_FLAGS+= os=linux
#BUILD_MAKE_FLAGS+= project=minizip 

USE_LANGUAGES=			c c++

#pre-build:
#	${SED} -e 's,@PREFIX@,${PREFIX},' \
#		< ${FILESDIR}/Makefile.in > ${WRKSRC}/Makefile
#	${SED} -e 's,@PREFIX@,${PREFIX},' \
#	       -e 's,@PACKAGE_VERSION@,${VERSION},' \
#		< ${FILESDIR}/primitiveShapes-libs.pc.in \
#		> ${WRKSRC}/primitiveShapes-libs.pc


post-extract:
	${RUN}cd ${WRKSRC} &&					\
	cp ${FILESDIR}/Makefile.linux Makefile

pre-configure:
	${RUN}cd ${WRKSRC} && cd dom && cd include && cd 1.4 && cd dom && \
	cp domasset.h domAsset.h


do-install:
	${RUN}cp ${WRKSRC}/dom/build/linux-1.4/libcollada14dom.a ${PREFIX}/lib/.
	${RUN}cp ${WRKSRC}/dom/build/linux-1.4/libcollada14dom.so ${PREFIX}/lib/.
	${RUN}cp ${WRKSRC}/dom/build/linux-1.4/libcollada14dom.so.2 ${PREFIX}/lib/.
	${RUN}cp ${WRKSRC}/dom/build/linux-1.4/libcollada14dom.so.2.1 ${PREFIX}/lib/.
	${RUN}cp ${WRKSRC}/dom/build/linux-1.4/libminizip.a ${PREFIX}/lib/.
	${RUN}cp ${WRKSRC}/dom/build/linux-1.4/libminizip.so ${PREFIX}/lib/.
	${RUN}cp ${WRKSRC}/dom/build/linux-1.4/libminizip.so.1 ${PREFIX}/lib/.
	${RUN}cp ${WRKSRC}/dom/build/linux-1.4/libminizip.so.1.2.3 ${PREFIX}/lib/.
	${RUN}mkdir -p ${PREFIX}/include/collada-dom/
	${RUN}cd ${WRKSRC}/dom/include && cp -r * ${PREFIX}/include/collada-dom/


	#${RUN}cd ${WRKSRC}/dom/include/1.4 && cp *.h ${PREFIX}/include/collada-dom/1.4/
	#${RUN}cd ${WRKSRC}/dom/include/1.5 && cp *.h ${PREFIX}/include/collada-dom/1.5/
	#${RUN}cd ${WRKSRC}/dom/include/dae && cp *.h ${PREFIX}/include/collada-dom/dae/
	#${RUN}cd ${WRKSRC}/dom/include/modules && cp *.h ${PREFIX}/include/collada-dom/modules/


	#${RUN}mkdir -p ${PREFIX}/include/collada-dom/1.4/
	#${RUN}mkdir -p ${PREFIX}/include/collada-dom/1.5/
	#${RUN}mkdir -p ${PREFIX}/include/collada-dom/dae/
	#${RUN}mkdir -p ${PREFIX}/include/collada-dom/modules/





#GNU_CONFIGURE=			yes
#CONFIGURE_ARGS+= --prefix=${PREFIX}


#include ../../mk/sysdep/autoconf.mk
#include ../../mk/sysdep/automake.mk
include ../../mk/robotpkg.mk

