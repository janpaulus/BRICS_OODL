#
# Copyright (c) 2009 LAAS/CNRS
# All rights reserved.
#
# Permission to use, copy, modify, and distribute this software for any purpose
# with or without   fee is hereby granted, provided   that the above  copyright
# notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS  SOFTWARE INCLUDING ALL  IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS. IN NO EVENT SHALL THE AUTHOR  BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR  ANY DAMAGES WHATSOEVER RESULTING  FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION,   ARISING OUT OF OR IN    CONNECTION WITH THE USE   OR
# PERFORMANCE OF THIS SOFTWARE.
#
#                                             Anthony Mallet on Thu Mar 12 2009
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
READLINE_DEPEND_MK:=	${READLINE_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		readline
endif

ifeq (+,$(READLINE_DEPEND_MK)) # -------------------------------------------

PREFER.readline?=	system

DEPEND_USE+=		readline
DEPEND_ABI.readline?=	readline>=5

SYSTEM_PKG.Linux-fedora.readline=	"readline-devel"
SYSTEM_PKG.NetBSD.readline=		"pkgsrc/devel/readline"

SYSTEM_SEARCH.readline=\
	'include/readline/readline.h:				\
		/VERSION_MAJOR/{s/$$/./;h;};			\
		/VERSION_MINOR/{H;g;s/[^0-9.]//gp;q;}'		\
	'lib/libreadline.{a,so}'


endif # READLINE_DEPEND_MK -------------------------------------------------

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
