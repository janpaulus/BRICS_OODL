# robotpkg depend.mk for:	archivers/bzip2
# Created:			Anthony Mallet on Sat, 19 Apr 2008
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
BZIP2_DEPEND_MK:=	${BZIP2_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		bzip2
endif

ifeq (+,$(BZIP2_DEPEND_MK))
PREFER.bzip2?=		system

SYSTEM_PKG.Linux-fedora.bzip2=	bzip2-devel
SYSTEM_PKG.Linux-ubuntu.bzip2=	libbz2-dev
SYSTEM_PKG.Linux-debian.bzip2=	bzip2 libbz2-dev

SYSTEM_SEARCH.bzip2=	\
	bin/bzip2	\
	include/bzlib.h	\
	lib/libbz2.*

  # pull-in the user preferences for bzip2 now
  include ../../mk/robotpkg.prefs.mk

  ifeq (inplace+robotpkg,$(strip $(BZIP2_STYLE)+$(PREFER.bzip2)))
  # This is the "inplace" version of bzip2 package, for bootstrap process
  #
BZIP2_FILESDIR=	${ROBOTPKG_DIR}/archivers/bzip2/dist
BZIP2_SRCDIR=	${WRKDIR}/bzip2

CPPFLAGS+=	-I${BZIP2_SRCDIR}
LDFLAGS+=	-L${BZIP2_SRCDIR}
LIBS+=		-lbz2

post-extract: bzip2-extract
bzip2-extract:
	${CP} -Rp ${BZIP2_FILESDIR} ${BZIP2_SRCDIR}

pre-configure: bzip2-build
bzip2-build:
	${RUN}								\
	cd ${BZIP2_SRCDIR} && 						\
	${SETENV} AWK="${AWK}" CC="${CC}" CFLAGS="${CFLAGS} ${CPPFLAGS}"\
		${MAKE_PROGRAM} libbz2.a
  else
  # This is the regular version of bzip2 package, for normal install
  #
DEPEND_USE+=		bzip2

DEPEND_ABI.bzip2?=	bzip2>=1.0.3
DEPEND_DIR.bzip2?=	../../archivers/bzip2

DEPEND_LIBS.bzip2+=	-lbz2
  endif
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
