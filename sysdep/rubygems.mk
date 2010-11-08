DEPEND_DEPTH:=   ${DEPEND_DEPTH}+
RUBYGEMS_DEPEND_MK:= ${RUBYGEMS_DEPEND_MK}+

RUBYGEMS_VERSION=1.8

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=rubygems
endif

ifeq (+,$(RUBYGEMS_DEPEND_MK)) 

PREFER.rubygems?=	system
DEPEND_USE+=		rubygems
DEPEND_ABI.rubygems?=	rubygems>=$(RUBYGEMS_VERSION)

SYSTEM_SEARCH.rubygems=	\
	/bin/gem1.8

SYSTEM_PKG.Linux.rubygems=rubygems$(RUBYGEMS_VERSION)

endif 

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
