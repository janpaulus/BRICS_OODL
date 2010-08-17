# $LAAS: bison.mk 2008/11/02 00:57:01 tho $
#
# Copyright (c) 2008 LAAS/CNRS
# All rights reserved.
#
# Redistribution and use  in source  and binary  forms,  with or without
# modification, are permitted provided that the following conditions are
# met:
#
#   1. Redistributions of  source  code must retain the  above copyright
#      notice and this list of conditions.
#   2. Redistributions in binary form must reproduce the above copyright
#      notice and  this list of  conditions in the  documentation and/or
#      other materials provided with the distribution.
#
#                                      Anthony Mallet on Fri Oct 24 2008
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
BISON_DEPEND_MK:=	${BISON_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		bison
endif

ifeq (+,$(BISON_DEPEND_MK)) # ----------------------------------------

_YACC?=			bison -y
CONFIGURE_ENV+=		YACC=$(call quote,${_YACC})

PREFER.bison?=		system
DEPEND_USE+=		bison
DEPEND_ABI.bison?=	bison
DEPEND_METHOD.bison+=	build
SYSTEM_SEARCH.bison=	'bin/$(firstword ${_YACC})'

# bison/lex selection
PKG_SUPPORTED_OPTIONS+=	yacc
PKG_OPTION_DESCR.yacc=	Use yacc in place of bison
PKG_OPTION_SET.yacc=	_YACC:=	yacc
PKG_OPTION_UNSET.yacc=	_YACC:=	bison -y

endif # BISON_DEPEND_MK ----------------------------------------------

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
