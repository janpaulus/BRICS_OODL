DEPEND_DEPTH:=   ${DEPEND_DEPTH}+ 
POLYGLOT_VERSION=0.3.1

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=polyglot
endif

ifeq (+,$(POLYGLOT_DEPEND_MK)) 

PREFER.polyglot?=	system
DEPEND_USE+=		polyglot
DEPEND_ABI.polyglot?=	polyglot>=$(POLYGLOT_VERSION)

SYSTEM_SEARCH.polyglot=	\
	bin/polyglot$(POLYGLOT_VERSION) \

SYSTEM_PKG.Linux-ubuntu.polyglot= polyglot (use gem install polyglot)

include ../sysdep/ruby.mk
include ../sysdep/rubygems.mk

endif 

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
