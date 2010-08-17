# robotpkg depend.mk for:	pkgtools/pkg-config
# Created:			Anthony Mallet on Sun, 25 May 2008
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
PKG_CONFIG_DEPEND_MK:=	${PKG_CONFIG_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		pkg-config
endif

ifeq (+,$(PKG_CONFIG_DEPEND_MK)) # -----------------------------------

PREFER.pkg-config?=		system

SYSTEM_SEARCH.pkg-config=	'bin/pkg-config::% --version'

DEPEND_USE+=			pkg-config
DEPEND_METHOD.pkg-config+=	build
DEPEND_ABI.pkg-config?=		pkg-config>=0.22
DEPEND_DIR.pkg-config?=		../../pkgtools/pkg-config

SYSTEM_PKG.Linux-fedora.pkg-config=	pkgconfig
SYSTEM_PKG.NetBSD.pkg-config=		pkgsrc/devel/pkg-config


# Define the proper pkg-config in environment
#
export PKG_CONFIG=$(call quote,${PREFIX.pkg-config}/bin/pkg-config)


# Append our path in front of PKG_CONFIG_PATH
#
CONFIGURE_ENV+= PKG_CONFIG_PATH=$(call quote,$(call \
		prependpath,${PREFIX}/lib/pkgconfig,${PKG_CONFIG_PATH}))


# insert the compiler's "rpath" flag into pkg-config data files so that
# ``pkg-config --libs <module>'' will return the full set of compiler
# flags needed to find libraries at run-time. If this is not desirable,
# set PKG_CONFIG_OVERRIDE to an empty value before including this file.
#
# From $NetBSD: pkg-config-override.mk,v 1.3 2007/07/25 18:07:34 rillig Exp $
#
OVERRIDE_DIRDEPTH.pkg-config?=	${OVERRIDE_DIRDEPTH}
PKG_CONFIG_OVERRIDE_PATTERN?=	*.pc *.pc.in

ifndef PKG_CONFIG_OVERRIDE
  # pull-in preferences now, for OVERRIDE_DIRDEPTH
  include ../../mk/robotpkg.prefs.mk

  # build the default pattern list according to the selected depth.
  # the result is a list like *.pc */*.pc */*/.pc ...
  #
  $(eval PKG_CONFIG_OVERRIDE:= ${PKG_CONFIG_OVERRIDE_PATTERN}	\
    $(call substs,{ | },$$( , ),				\
    $(call iterate,${OVERRIDE_DIRDEPTH.pkg-config},{addprefix	\
	*/|${PKG_CONFIG_OVERRIDE_PATTERN})			\
    $(call iterate,${OVERRIDE_DIRDEPTH.pkg-config},}))		\
  )
endif

ifneq (,$(call isyes,${_USE_RPATH})) # when using rpath flags
  ifneq (,${PKG_CONFIG_OVERRIDE})    # and not disabled by a package
    SUBST_CLASSES+=		pkgconfig
    SUBST_STAGE.pkgconfig=	do-configure-pre-hook
    SUBST_MESSAGE.pkgconfig=	Adding run-time search paths to pkg-config files.
    SUBST_FILES.pkgconfig=	${PKG_CONFIG_OVERRIDE}
    SUBST_SED.pkgconfig=\
	'/^Libs:.*[ 	]/s|-L\([ 	]*[^ 	]*\)|${COMPILER_RPATH_FLAG}\1 -L\1|g'
  endif
endif

endif # PKG_CONFIG_DEPEND_MK -----------------------------------------

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
