DEPEND_DEPTH:=   ${DEPEND_DEPTH}+
RUBY_DEPEND_MK:= ${RUBY_DEPEND_MK}+

RUBY_VERSION=1.8

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=ruby
endif

ifeq (+,$(RUBY_DEPEND_MK)) 

PREFER.ruby?=	system
DEPEND_USE+=		ruby
DEPEND_ABI.ruby?=	ruby>=$(RUBY_VERSION)

SYSTEM_SEARCH.ruby=	\
	bin/ruby$(RUBY_VERSION) \
	lib/ruby/$(RUBY_VERSION)/rubyunit.rb

SYSTEM_PKG.Linux.ruby=ruby$(RUBY_VERSION)

endif 

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
