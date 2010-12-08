# robotpkg sydep for:		polyglot.mk
# Created:			Michael Reckhaus 11.11.2010

DEPEND_DEPTH:=   ${DEPEND_DEPTH}+ 
POLYGLOT_DEPEND_MK:= ${POLYGLOT_DEPEND_MK}+

POLYGLOT_VERSION = 0.3.1

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=polyglot
endif

ifeq (+,$(POLYGLOT_DEPEND_MK)) 

PREFER.polyglot?=	system
DEPEND_USE+=		polyglot
DEPEND_ABI.polyglot?=	polyglot>=${POLYGLOT_VERSION}

SYSTEM_SEARCH.polyglot=	\
	/.gem/ruby/${RUBY_VERSION}/gems/polyglot-${POLYGLOT_VERSION}/lib/polyglot.rb 

SYSTEM_PKG.Linux-ubuntu.polyglot= polyglot (use "gem install polyglot -v ${POLYGLOT_VERSION}")

include ../sysdep/ruby.mk
include ../sysdep/rubygems.mk

endif 

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
