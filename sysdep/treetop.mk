# robotpkg sydep for:		treetop.mk
# Created:			Michael Reckhaus 11.11.2010

DEPEND_DEPTH:=   ${DEPEND_DEPTH}+ 
TREETOP_DEPEND_MK:= ${TREETOP_DEPEND_MK}+

TREETOP_VERSION = 1.4.9

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=treetop
endif

ifeq (+,$(TREETOP_DEPEND_MK)) 

PREFER.treetop?=	system
DEPEND_USE+=		treetop
DEPEND_ABI.treetop?=	treetop>=${TREETOP_VERSION}

SYSTEM_SEARCH.treetop=\
	.gem/ruby/${RUBY_VERSION}/gems/treetop-${TREETOP_VERSION}/lib/treetop.rb 

SYSTEM_PKG.Linux-ubuntu.treetop=treetop (use "gem install treetop -v ${TREETOP_VERSION}")

include ../sysdep/ruby.mk
include ../sysdep/rubygems.mk

endif 

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
