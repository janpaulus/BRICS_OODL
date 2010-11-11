# robotpkg depend.mk for:	brics/treetop
# Created:			Michael Reckhaus on 08 Nov 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
TREETOP_DEPEND_MK:= ${TREETOP_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		treetop
endif

ifeq (+,$(TREETOP_DEPEND_MK))
PREFER.treetop?=	system

DEPEND_USE+=		treetop

DEPEND_ABI.treetop?=	treetop>=1.4.2
DEPEND_DIR.treetop?=	../../brics/treetop


SYSTEM_SEARCH.treetop=\
	${HOME}/.gem/ruby/1.8/gems/treetop-1.4.2/bin/tt \
	/var/lib/gems/1.8/bin/tt
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
