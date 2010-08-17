# robotpkg depend.mk for:	image/libdc1394
# Created:			Anthony Mallet on Fri, 14 Mar 2008
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
LIBDC1394_DEPEND_MK:=	${LIBDC1394_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		libdc1394
endif

ifeq (+,$(LIBDC1394_DEPEND_MK)) # ------------------------------------------

PREFER.libdc1394?=	system

DEPEND_USE+=		libdc1394

DEPEND_ABI.libdc1394?=	libdc1394>=2.0.1
DEPEND_DIR.libdc1394?=	../../image/libdc1394

SYSTEM_PKG.Linux-fedora.libdc1394=libdc1394-devel
SYSTEM_PKG.Linux-ubuntu.libdc1394=libdc1394-dev
SYSTEM_PKG.Linux-debian.libdc1394=libdc1394-dev

SYSTEM_SEARCH.libdc1394=\
	include/dc1394/dc1394.h		\
	'lib/pkgconfig/libdc1394-2.pc:/Version/s/[^0-9.]//gp'

endif # LIBDC1394_DEPEND_MK ------------------------------------------------

include ../../mk/robotpkg.prefs.mk
ifeq (Linux,${OPSYS})
  include ../../image/libraw1394/depend.mk
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
