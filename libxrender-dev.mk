DEPEND_DEPTH:=		${DEPEND_DEPTH}+
LIBXRENDER_DEV_DEPEND_MK:=	${LIBXRENDER_DEV_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		libxrender-dev
endif

ifeq (+,$(LIBXRENDER_DEV_DEPEND_MK)) # -------------------------------------

PREFER.libxrender-dev?=	system
DEPEND_USE+=		libxrender-dev
DEPEND_ABI.libxrender-dev?=	libxrender-dev>=1.2

SYSTEM_SEARCH.libxrender-dev=	\
	'include/X11/extensions/Xrender.h' \
	'lib/libXrender.{a,so,dylib}'

SYSTEM_PKG.Linux.libxrender-dev=libxrender-dev?


endif # LIBXRENDER_DEV_DEPEND_MK -------------------------------------------

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
