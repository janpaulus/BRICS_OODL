# robotpkg sydep for:		ruby.mk
# Created:			Michael Reckhaus 11.11.2010

DEPEND_DEPTH:=   ${DEPEND_DEPTH}+
RUBY_DEPEND_MK:= ${RUBY_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=ruby
endif

ifeq (+,$(RUBY_DEPEND_MK)) 

PREFER.ruby?=	system
DEPEND_USE+=		ruby
DEPEND_ABI.ruby?=	ruby>=1.8

SYSTEM_SEARCH.ruby=	\
	/usr/bin/ruby

SYSTEM_PKG.Linux-ubuntu.ruby=ruby

endif 

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
