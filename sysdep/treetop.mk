# robotpkg sydep for:		treetop.mk
# Created:			Michael Reckhaus 11.11.2010

# TODO: search path contains version numbers from ruby!. Can this be avoided via regular expressions?



DEPEND_DEPTH:=   ${DEPEND_DEPTH}+ 
TREETOP_DEPEND_MK:= ${TREETOP_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=treetop
endif

ifeq (+,$(TREETOP_DEPEND_MK)) 

PREFER.treetop?=	system
DEPEND_USE+=		treetop
DEPEND_ABI.treetop?=	treetop>=1.4.8

_vregex:=^(\d+\.)?(\d+\.)?(\*|\d+)

SYSTEM_SEARCH.treetop=\
	/.gem/ruby/1.8/gems/treetop-1.4.8/lib/treetop.rb 

SYSTEM_PKG.Linux-ubuntu.treetop=treetop (use gem install treetop)

include ../sysdep/ruby.mk
include ../sysdep/rubygems.mk

endif 

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
