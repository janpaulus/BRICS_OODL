# robotpkg sydep for:		rubygems.mk
# Created:			Michael Reckhaus 11.11.2010

DEPEND_DEPTH:=   ${DEPEND_DEPTH}+
RUBYGEMS_DEPEND_MK:= ${RUBYGEMS_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=rubygems
endif

ifeq (+,$(RUBYGEMS_DEPEND_MK)) 

PREFER.rubygems?=	system
DEPEND_USE+=		rubygems
DEPEND_ABI.rubygems?=	rubygems>=1.8

SYSTEM_SEARCH.rubygems=		\
	/bin/gem

SYSTEM_PKG.Linux.rubygems=rubygems

include ../sysdep/ruby.mk

endif 

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
