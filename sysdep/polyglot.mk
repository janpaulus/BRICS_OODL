# robotpkg sydep for:		polyglot.mk
# Created:			Michael Reckhaus 11.11.2010
# TODO: search path contains version numbers from ruby!. Can this be avoided via regular expressions?

DEPEND_DEPTH:=   ${DEPEND_DEPTH}+ 
POLYGLOT_DEPEND_MK:= ${POLYGLOT_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=polyglot
endif

ifeq (+,$(POLYGLOT_DEPEND_MK)) 

PREFER.polyglot?=	system
DEPEND_USE+=		polyglot
DEPEND_ABI.polyglot?=	polyglot>=0.3.1

SYSTEM_SEARCH.polyglot=	\
	/.gem/ruby/1.8/gems/polyglot-0.3.1/lib/polyglot.rb 

SYSTEM_PKG.Linux-ubuntu.polyglot= polyglot (use gem install polyglot)

include ../sysdep/ruby.mk
include ../sysdep/rubygems.mk

endif 

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
