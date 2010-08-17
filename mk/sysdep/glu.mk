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
#                                             Anthony Mallet on Tue Dec 15 2009
#
DEPEND_DEPTH:=		${DEPEND_DEPTH}+
GLU_DEPEND_MK:=		${GLU_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		glu
endif

ifeq (+,$(GLU_DEPEND_MK)) # ------------------------------------------------

PREFER.glu?=		system

DEPEND_USE+=		glu

DEPEND_ABI.glu?=	glu>=7

SYSTEM_SEARCH.glu=	\
	'include/GL/glu.h'						\
	'lib/libGLU.*'

SYSTEM_PKG.Linux-fedora.glu=	mesa-libGLU-devel
SYSTEM_PKG.Linux-ubuntu.glu=	libglu1-mesa-dev
SYSTEM_PKG.Linux-debian.glu=	libglu1-mesa-dev
SYSTEM_PKG.NetBSD.glu=		pkgsrc/graphics/glu

endif # GLU_DEPEND_MK ------------------------------------------------------

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
