# $LAAS: gcc.mk 2009/12/06 15:17:50 tho $
#
# Copyright (c) 2006,2008-2009 LAAS/CNRS
# All rights reserved.
#
# This project includes software developed by the NetBSD Foundation, Inc.
# and its contributors. It is derived from the 'pkgsrc' project
# (http://www.pkgsrc.org).
#
# Redistribution  and  use in source   and binary forms,  with or without
# modification, are permitted provided that  the following conditions are
# met:
#
#   1. Redistributions  of  source code must  retain  the above copyright
#      notice, this list of conditions and the following disclaimer.
#   2. Redistributions in binary form must  reproduce the above copyright
#      notice,  this list of  conditions and  the following disclaimer in
#      the  documentation   and/or  other  materials   provided with  the
#      distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
# ANY  EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES   OF MERCHANTABILITY AND  FITNESS  FOR  A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO  EVENT SHALL THE AUTHOR OR  CONTRIBUTORS
# BE LIABLE FOR ANY DIRECT, INDIRECT,  INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING,  BUT  NOT LIMITED TO, PROCUREMENT  OF
# SUBSTITUTE  GOODS OR SERVICES;  LOSS   OF  USE,  DATA, OR PROFITS;   OR
# BUSINESS  INTERRUPTION) HOWEVER CAUSED AND  ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE  USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# From $NetBSD: gcc.mk,v 1.86 2006/12/02 22:32:59 jschauma Exp $
#
#					Anthony Mallet on Wed Dec  6 2006
#

# Select required compilers based on COMPILER_TARGET and USE_LANGUAGES.
#
ifeq (i386-mingw32,${COMPILER_TARGET})
  ifneq (,$(filter c c++,${USE_LANGUAGES}))
    include ${ROBOTPKG_DIR}/cross/i386-mingw32/depend.mk
  endif
else
  ifneq (,$(filter c,${USE_LANGUAGES}))
    include ${ROBOTPKG_DIR}/mk/sysdep/gcc-c.mk

    ifneq (,$(filter c99,${USE_LANGUAGES}))
      ROBOTPKG_CC+=	-std=c99
    endif
  endif

  ifneq (,$(filter c++,${USE_LANGUAGES}))
    include ${ROBOTPKG_DIR}/mk/sysdep/gcc-c++.mk

    ifneq (,$(filter c++0x,${USE_LANGUAGES}))
      ROBOTPKG_CXX+=	-std=c++0x
    endif
  endif

  ifneq (,$(filter fortran,${USE_LANGUAGES}))
    include ${ROBOTPKG_DIR}/mk/sysdep/gcc-fortran.mk
  endif
endif


# Include gcc common definitions
#
$(call require, ${ROBOTPKG_DIR}/mk/compiler/gcc-common.mk)
