# $LAAS: package.mk 2009/10/27 18:22:06 mallet $
#
# Copyright (c) 2006-2007,2009 LAAS/CNRS
# All rights reserved.
#
# Redistribution and use  in source  and binary  forms,  with or without
# modification, are permitted provided that the following conditions are
# met:
#
#   1. Redistributions of  source  code must retain the  above copyright
#      notice, this list of conditions and the following disclaimer.
#   2. Redistributions in binary form must reproduce the above copyright
#      notice,  this list of  conditions and the following disclaimer in
#      the  documentation  and/or  other   materials provided  with  the
#      distribution.
#
# THIS  SOFTWARE IS PROVIDED BY  THE  COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND  ANY  EXPRESS OR IMPLIED  WARRANTIES,  INCLUDING,  BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES  OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR  PURPOSE ARE DISCLAIMED. IN  NO EVENT SHALL THE COPYRIGHT
# HOLDERS OR      CONTRIBUTORS  BE LIABLE FOR   ANY    DIRECT, INDIRECT,
# INCIDENTAL,  SPECIAL,  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR
# TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
# USE   OF THIS SOFTWARE, EVEN   IF ADVISED OF   THE POSSIBILITY OF SUCH
# DAMAGE.
#
# From $NetBSD: package.mk,v 1.18 2006/10/09 12:25:44 joerg Exp $
#
#                                      Anthony Mallet on Mon Dec  4 2006
#


# --- package (PUBLIC) -----------------------------------------------
#
# package is a public target to generate a binary package.
#
ifneq (,$(filter replace,${MAKECMDGOALS}))
_PACKAGE_TARGETS+=	replace
else
_PACKAGE_TARGETS+=	install
endif
_PACKAGE_TARGETS+=	acquire-package-lock
_PACKAGE_TARGETS+=	${_COOKIE.package}
_PACKAGE_TARGETS+=	release-package-lock

.PHONY: package
ifeq (yes,$(call exists,${_COOKIE.package}))
  package:;
else
  $(call require, ${ROBOTPKG_DIR}/mk/internal/barrier.mk)
  $(call require, ${ROBOTPKG_DIR}/mk/install/install-vars.mk)

  package: $(call barrier, depends, ${_PACKAGE_TARGETS})
endif

.PHONY: acquire-package-lock release-package-lock
acquire-package-lock: acquire-lock
release-package-lock: release-lock

ifeq (yes,$(call exists,${_COOKIE.package}))
  ${_COOKIE.package}:;
else
  $(call require, ${ROBOTPKG_DIR}/mk/pkg/pkg-vars.mk)
  ${_COOKIE.package}: real-package;
endif


# --- real-package (PRIVATE) -----------------------------------------
#
# real-package is a helper target onto which one can hook all of the
# targets that do the actual packaging of the built objects.
#
_REAL_PACKAGE_TARGETS+=	package-message
_REAL_PACKAGE_TARGETS+=	pkg-check-installed
_REAL_PACKAGE_TARGETS+=	pkg-create
_REAL_PACKAGE_TARGETS+=	package-cookie
_REAL_PACKAGE_TARGETS+=	package-warnings

.PHONY: real-package
real-package: ${_REAL_PACKAGE_TARGETS}

.PHONY: package-message
package-message:
	@${PHASE_MSG} "Building binary package for ${PKGNAME}"


# --- package-cookie (PRIVATE) ---------------------------------------
#
# package-cookie creates the "package" cookie file
#
.PHONY: package-cookie
package-cookie:
	${_PKG_SILENT}${_PKG_DEBUG}${TEST} ! -f ${_COOKIE.package} || ${FALSE}
	${_PKG_SILENT}${_PKG_DEBUG}${MKDIR} $(dir ${_COOKIE.package})
	${_PKG_SILENT}${_PKG_DEBUG}${ECHO} ${PKGNAME} > ${_COOKIE.package}


# Displays warnings about the binary package.
.PHONY: package-warnings
package-warnings:
ifdef NO_PUBLIC_BIN
	@${WARNING_MSG} "${PKGNAME} may not be publicly available:"
	@${WARNING_MSG} $(call quote,${NO_PUBLIC_BIN})
endif
