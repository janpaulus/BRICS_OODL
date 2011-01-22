# robotpkg depend.mk for:	brics/netcdf
# Created:			nico.hochgeschwender(at)h-brs.de on 28 Oct. 2010


DEPEND_DEPTH:=		${DEPEND_DEPTH}+
NETCDF_DEPEND_MK:= ${NETCDF_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		netcdf
endif

ifeq (+,$(NETCDF_DEPEND_MK))
PREFER.netcdf?=	system

DEPEND_USE+=		netcdf

DEPEND_ABI.netcdf?=	netcdf>=3.6.3
DEPEND_DIR.netcdf?=	../../brics/netcdf

SYSTEM_SEARCH.netcdf=\
	'include/netcdf.h'\
	'lib/libnetcdf.{a,so,dylib}'
endif

SYSTEM_PKG.Linux.netcdf=libnetcdf-dev

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
