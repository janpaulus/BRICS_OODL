#
# Copyright (c) 2007-2008 LAAS/CNRS                        --  Wed May 30 2007
# Copyright (c) 1999, 2000 Hubert Feyrer <hubertf@NetBSD.org>
# All rights reserved.
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
#   3. All  advertising  materials  mentioning  features or  use  of this
#      software must display  the following acknowledgement: This product
#      includes  software  developed  by  Hubert  Feyrer  for  the NetBSD
#      Project.
#
# This project includes software developed by Hubert Feyrer for the
# NetBSD project. It is derived from the 'pkgsrc' project
# (http://www.pkgsrc.org).
#
# From $NetBSD: bsd.bulk-pkg.mk,v 1.139 2007/04/15 22:14:44 rillig Exp $
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

##
## For this to work, put
##   DEPENDS_TARGET=	bulk-install
##   BATCH=		yes
## into your /etc/mk.conf, then cd /usr/pkgsrc; make bulk-package
##
## bulk-install will only compile pkgs if necessary, and install binary
##	pkgs if possible/available.
## bulk-package will build binary packages, and remove them (together with
##	any depending packages) immediately after that, leaving only the
##	binary package back. Broken packages are marked (``.broken'').
##

LS?=	ls
TEE?=	tee
WC?=	wc
TO_HTML?=	${SED} -e 's,&,\&amp;,g' -e 's,<,\&lt;,g' -e 's,>,\&gt;,g'

# This variable is set to 'yes' by the robotpkg/mk/bulk/build script.  It enables
# the use of several cache files (DEPENDSTREEFILE, DEPENDSFILE, SUPPORTSFILE,
# and INDEXFILE) for speeding up the processing of dependencies.  If we're not
# actively in the middle of a bulk build, however, we don't know that these files
# exist or are up to date and they take quite a while to rebuild.  So unless
# they're known to exist and be up to date, don't use them.
USE_BULK_CACHE?=	no

# If set to 'yes', avoids inflating the 'breaks' column of the final report
# by not counting dependent packages that are broken all by themselves.
# If set to 'no', may speed up building on some platforms where fork() is slow.
# (Only takes effect if USE_BULK_CACHE=yes.)
USE_BULK_BROKEN_CHECK?=	yes

# This variable may be set to 'no' to avoid automatic rebuilding of dependent
# packages based solely on timestamps of the package's pkgsrc files and/or
# its dependency binary packages.  This will cause rebuilding only when the
# full version number of the package changes (e.g., via PKGREVISION bump).
USE_BULK_TIMESTAMPS?=	yes

# Shall we remove any packages which are installed, but not required
# to build this package
PRECLEAN?=		yes

# Sometimes it's useful to not only keep the build logs from broken
# packages, but also the ones from packages that worked.
# This feature is still experimental.
KEEP_BUILDLOGS?=	no

# If OBJHOSTNAME is set, use first component of hostname in cache and log files
# If OBJMACHINE is set, use ${MACHINE_ARCH} in the cache and log files
ifdef OBJHOSTNAME
 ifndef _HOSTNAME
_HOSTNAME!=		${UNAME} -n
 endif
BULK_ID?=		.$(firstword $(subst ., ,${_HOSTNAME}))
else
 ifdef OBJMACHINE
BULK_ID?=		.${MACHINE_ARCH}
 else
BULK_ID?=
 endif
endif

#
# Package-specific files
#

# If the package has been built successfully, and if KEEP_BUILDLOGS is
# set to "yes", the build log is saved in this file.
BUILD_SUCCEEDED_FILE?=	.build_succeeded${BULK_ID}

# This file exists to mark a package as broken
BROKENFILE?=		.broken${BULK_ID}.html

# When this file exists for a package, it has been marked as not to be
# available on this platform.
NOT_AVAILABLE_FILE?=	.bulk-not_available

# This file is the work log for a broken package
BROKENWRKLOG?=		.broken${BULK_ID}.work.txt

# This file is human-created to force a package to show up as broken
# (it is never cleaned by the bulk build, and contains the broken reason)
FORCEBROKENFILE?=	.forcebroken

# This file is where the log of the build goes
BUILDLOG?=		.make${BULK_ID}

#
# Top level databases and log files
#

# This is the directory in which all temporary files and log files from the
# bulk build are kept.
# It defaults to ${ROBOTPKG_DIR}, but may be better suited to another directory
# if pkgsrc is on a remote (e.g., nfs) filesystem.
BULKFILESDIR?=		${ROBOTPKG_DIR}

# This is a top level file which lists the entire pkgsrc depends tree in the
# format:
# foo/bar devel/libfoo
# meaning 'foo/bar' is requied to build 'devel/libfoo'
# this is in the format needed by tsort(1)
DEPENDSTREEFILE?=	${BULKFILESDIR}/.dependstree${BULK_ID}

# This is a top level file which lists the entire pkgsrc depends tree in the
# format:
# foo/bar depends on: devel/libfoo devel/libbar devel/baz .....
# ie, to build foo/bar we need devel/libfoo devel/libbar devel/baz ... installed
DEPENDSFILE?=		${BULKFILESDIR}/.depends${BULK_ID}

# This is a top level file which lists the entire pkgsrc depends tree in the
# format:
# devel/libfoo is depended upon by: foo/bar graphics/gtkfoo ...
# ie, to build foo/bar we need devel/libfoo to be installed.
#     to build graphics/gtkfoo we need devel/libfoo to be installed
SUPPORTSFILE?=		${BULKFILESDIR}/.supports${BULK_ID}

# This is a top level file which cross-references each package name and pkg
# directory in the format:
# devel/libfoo libfoo-1.3
INDEXFILE?=		${BULKFILESDIR}/.index${BULK_ID}

# File containing a list of all the packages in the correct order for a bulk
# build.  The correct order is one where packages that are required by others
# are built before the packages which require them.
ORDERFILE?=		${BULKFILESDIR}/.order${BULK_ID}

# File which is used as a timestamp for when the build started.  This is used
# eventually for looking for leftover files (files not properly deinstalled)
STARTFILE?=		${BULKFILESDIR}/.start${BULK_ID}

# This top level file saves the bulk build ID. As it most often has a time
# stamp, it is only generated once and later retrieved from this file.
BULK_BUILD_ID_FILE?=	${BULKFILESDIR}/.bulk_build_id${BULK_ID}

# File created and used by lintpkgsrc(8) to cache package metadata for
# pruning and bulk-upload exclusions.
LINTPKGSRC_DB?=		${BULKFILESDIR}/.lintpkgsrc.db${BULK_ID}

# File which is used as a database for bulk builds in which SPECIFIC_PKGS is
# defined.  This database is used to hold all the dependency and index
# information for the specific packages as well as their dependencies.  In a
# SPECIFIC_PKGS bulk build, this file is created and then used to create the
# INDEXFILE and DEPENDSTREEFILE.
BULK_DBFILE?=		${BULKFILESDIR}/.bulk_db${BULK_ID}

# A list of pkgs which we should _never_ delete during a build.  The primary
# use is for pkgtools and also for digest.
BULK_PREREQ+=		pkgtools/pkg_install
BULK_PREREQ+=		pkgtools/digest
BULK_PREREQ+=		pkgtools/pax
BULK_PREREQ+=		pkgtools/tnftp

# Commands for printing informational messages from the bulk build.
# BULK_MSG_CONT is used for continuing a message started with BULK_MSG
BULK_MSG?=		${ECHO_MSG} "BULK>"
BULK_MSG_CONT?=		${ECHO_MSG} "     "

#
# Private variables
#

# If this is "yes", the working directory will not be cleaned after building
# the package. It can also be set to "pack-if-failed" to save a .tar.gz
# file of the working directory in BULKFILESDIR instead of keeping the files,
# but only if the package failed to build.
_PRESERVE_WRKDIR?=	no

# create an escaped version of PKGPATH.  We do this because
# in several places we want to be able to use something like
# foo/bar.baz++ in a regular expression but have it be interpreted
# literally.  So, turn it into foo\/bar\.baz\+\+
_ESCPKGPATH=		$(call quote,$(subst /,\/,$(subst +,\+,$(subst .,\.,${PKGPATH}))))

# The directory where package-specific log files are saved.
_BULK_PKGLOGDIR=	${BULKFILESDIR}/${PKGPATH}

# Package-specific log files.
_BROKENFILE=		${_BULK_PKGLOGDIR}/${BROKENFILE}
_BROKENWRKLOG=		${_BULK_PKGLOGDIR}/${BROKENWRKLOG}
_BUILDLOG=		${_BULK_PKGLOGDIR}/${BUILDLOG}
_FORCEBROKENFILE=	${_BULK_PKGLOGDIR}/${FORCEBROKENFILE}
_BUILD_SUCCEEDED_FILE=	${_BULK_PKGLOGDIR}/${BUILD_SUCCEEDED_FILE}

# Only create directories if ${ROBOTPKG_DIR} != ${BULKFILESDIR}
ifneq (${ROBOTPKG_DIR},${BULKFILESDIR})
_BULK_MKDIR=		${MKDIR}
else
_BULK_MKDIR=		${DO_NADA}
endif

#
# Sanity checks
#

# Allow FORCEBROKENFILE files to be created in either ROBOTPKG_DIR or BULKFILESDIR.
ifeq (yes,$(call exists,${FORCEBROKENFILE}))
PKG_FAIL_REASON+=	"${PKGNAME} is marked as broken by the bulk build administrator: `cat ${FORCEBROKENFILE}`"
else
 ifeq (yes,$(call exists,${_FORCEBROKENFILE}))
PKG_FAIL_REASON+=	"${PKGNAME} is marked as broken by the bulk build administrator: `cat ${_FORCEBROKENFILE}`"
 endif
endif

#
# Make targets
#

# build the cache files used as part of a full bulk build
# Note:  we have to install the BULK_PREREQ packages _before_
# extracting the depends tree because some packages like
# xpkgwedge only become DEPENDS if it is installed
.PHONY: bulk-cache
bulk-cache:
	@${BULK_MSG} "Installing BULK_PREREQ packages"
	for __prereq in ${BULK_PREREQ}; do \
		cd ${ROBOTPKG_DIR}/$${__prereq} && ${RECURSIVE_MAKE} bulk-install; \
	done
	${RM} -f ${BULK_DBFILE}
	${TOUCH} ${BULK_DBFILE}
ifndef SPECIFIC_PKGS
	@${ECHO} "This file is unused for a full pkgsrc bulk build" >> ${BULK_DBFILE}
	@${ECHO} "It is only used for a SPECIFIC_PKGS bulk build" >> ${BULK_DBFILE}
	@${BULK_MSG} "Building complete pkgsrc dependency tree (this may take a while)."
	cd ${ROBOTPKG_DIR} && \
		${SETENV} MAKE=${MAKE} ${SH} mk/bulk/printdepends \
			${BROKENFILE} ${BULKFILESDIR} > ${DEPENDSTREEFILE}
	@${BULK_MSG} "Generating package name <=> package directory cross reference file"
	@${BULK_MSG_CONT} "(this may take a while)."
	cd ${ROBOTPKG_DIR} && \
		${SETENV} MAKE=${MAKE} ${SH} mk/bulk/printindex \
			${NOT_AVAILABLE_FILE} ${BULKFILESDIR} > ${INDEXFILE}
else
	@${BULK_MSG} "Extracting database for SPECIFIC_PKGS subset of pkgsrc"
	@${BULK_MSG_CONT} "along with their dependencies"
	@for __tmp__ in ${SUBDIR} ${BULK_PREREQ}; do \
	if [ ! -d ${ROBOTPKG_DIR}/$${__tmp__} ]; then \
		${BULK_MSG} "WARN: Skipping nonexisting directory $${__tmp__}"; \
		${ECHO} " 0 $${__tmp__} 0" >> ${BULKFILESDIR}/${BROKENFILE}; \
	else \
		cd ${ROBOTPKG_DIR}/$${__tmp__} && \
			${SETENV} MAKE=${MAKE} AWK=${AWK} EXPR=${EXPR} \
			${SH} ../../mk/internal/mkdatabase -a -f ${BULK_DBFILE}; \
	fi; \
	done
	@${BULK_MSG} "Extracting dependency tree file"
	${AWK} '/^(build_)?depends/ {pkgs[$$2] = 1; cat=$$2; sub(/\/.*/, "", cat); \
		for(i=3; i<=NF; i=i+1){ \
			listed[$$2] = 1; \
			sub(/[^:]*:\.\.\/\.\.\//, "", $$i); \
			sub(/[^:]*:\.\./, cat , $$i); \
			print $$i " " $$2; \
		}} END{ \
		for(pkg in pkgs) {if( pkg in listed ) {} else{ print pkg " " pkg;}} \
		}' \
		${BULK_DBFILE} | ${SORT} -u > ${DEPENDSTREEFILE}
	@${BULK_MSG} "Extracting package name <=> package directory cross reference file"
	${AWK} '/^index/ {print $$2 " " $$3 " "}' ${BULK_DBFILE} > ${INDEXFILE}
endif
	@${BULK_MSG} "Sorting build order."
	cd ${BULKFILESDIR} && ${TSORT} ${DEPENDSTREEFILE} > ${ORDERFILE}
	@${BULK_MSG} "Generating up and down dependency files."
	${PERL} ${ROBOTPKG_DIR}/mk/bulk/tflat \
		${SUPPORTSFILE} ${DEPENDSFILE} < ${DEPENDSTREEFILE}

# note explicit pathname on "perl" above, so that we do NOT auto-set
# USE_TOOLS=perl (which may be undesirable for package building)

# remove the bulk cache files
.PHONY: clean-bulk-cache
clean-bulk-cache:
	${RM} -f ${BULK_DBFILE} \
		${DEPENDSTREEFILE} \
		${DEPENDSFILE} \
		${SUPPORTSFILE} \
		${INDEXFILE} \
		${ORDERFILE}


ifndef ROBOTPKGTOP

# check if the $REF file is uptodate, i.e. is newer than any of
# the pkg files; prints "1" if upto date, "0" if not.
.PHONY: bulk-check-uptodate
bulk-check-uptodate:
	@uptodate=1; \
	if [ -f "${REF}" ]; then \
		if [ "$(notdir ${REF})" != "$(notdir ${PKGFILE})" ]; then \
			${BULK_MSG} 1>&2 "${REF} is out of date (new version ${PKGNAME}); rebuilding..."; \
			uptodate=0; \
		elif [ "${USE_BULK_TIMESTAMPS}" = "yes" ]; then \
			${SHCOMMENT} "Check files of this package"; \
			newfiles="`${FIND} . \( -name ${WRKDIR_BASENAME} -prune \) -o \( -type f -newer "${REF}" ! \( -name README.html -o -name DESCR -o -name COMMENT -o -name '.*' \) \) -print || ${TRUE}`"; \
			nnewfiles="`echo $$newfiles | ${WC} -w`"; \
			if [ "$$nnewfiles" -gt 0 ]; then \
				${BULK_MSG} 1>&2 "Package ${PKGNAME} ($$newfiles) modified since last 'make package' re-packaging..."; \
				uptodate=0; \
			else \
				${BULK_MSG} 1>&2 "${REF} is up to date."; \
			fi; \
		else \
			${BULK_MSG} 1>&2 "${REF} is up to date."; \
		fi; \
	else \
		${BULK_MSG} 1>&2 "Package ${PKGNAME} not built yet, packaging..."; \
		uptodate=0; \
	fi; \
	if [ "$$uptodate" = "1" ]; then \
		${SHCOMMENT} "Check required binary packages"; \
		($(foreach d,${DEPENDS},${ECHO} $(call quote,$(firstword $(subst :, ,${d})));) ${TRUE}) | \
		(while read dep; do \
			${SHCOMMENT} "check against the binary pkg that pkg_add would pick, too:"; \
			${SHCOMMENT} "(Only one should be returned here, really...)"; \
			pkg=`${PKG_ADMIN} lsbest "${PACKAGES}/All/$$dep"`; \
			if [ -z "$$pkg" ]; then \
				${BULK_MSG} 1>&2 "Required binary package $$dep does not exist, rebuilding..."; \
				exit 1; \
			elif [ "${USE_BULK_TIMESTAMPS}" = "yes" ] && [ -n "`${FIND} $$pkg -prune -newer ${REF} -print`" ]; then \
				${BULK_MSG} 1>&2 "Required binary package $$dep (`basename $$pkg`) is newer, rebuilding..."; \
				exit 1; \
			else \
				${BULK_MSG} 1>&2 "Required binary package $$dep (`basename $$pkg`) is usable."; \
			fi; \
		done) || uptodate=0; \
	fi; \
	${ECHO} $$uptodate

# rebuild binpkg if any of the pkg files is newer than the binary archive
# set DO to ":" to not actually do anything (debugging, ...)
.PHONY: bulk-package
bulk-package:
	@${_BULK_MKDIR} ${_BULK_PKGLOGDIR}
	@if [ -f ${_BROKENFILE} ]; then \
		${BULK_MSG} "Package ${PKGNAME} is already marked as broken."; \
		exit 1; \
	fi
	${RUN} \
	{ ${ECHO} "###"; \
	  ${ECHO} "### `${DATE}`"; \
	  ${ECHO} "### robotpkg build log for ${PKGNAME}"; \
	  ${ECHO} "###"; \
	  ${ECHO} ""; \
	} >> ${_BUILDLOG}
	${RUN} set +e; \
	uptodate=`${RECURSIVE_MAKE} ${MAKEFLAGS} bulk-check-uptodate REF=${PKGFILE}` ; \
	if [ $$uptodate = 1 ]; then \
		{ ${BULK_MSG} "Nothing to be done for ${PKGNAME}." ; \
		} 2>&1 | ${TEE} -a ${_BUILDLOG}; \
	else \
		( if ${PKG_INFO} -qe $(call quote,${PKGWILDCARD}); then \
			${BULK_MSG} "Removing outdated (installed) package ${PKGNAME} first." ; \
			${DO} ${PKG_DELETE} -r $(call quote,${PKGWILDCARD}) ;\
		fi ; \
		if [ -f ${PKGFILE} ]; then \
			${BULK_MSG} "Removing old binary package ${PKGFILE}." ; \
			${DO}       ${RM} -f ${PKGFILE} ; \
			for cat in ${CATEGORIES}; do \
				${DO} ${RM} -f ${PACKAGES}/$$cat/${PKGNAME}${PKG_SUFX}; \
			done ;\
		fi; \
		${BULK_MSG} "Bulk building ${PKGNAME}" ; \
		${DO} ${RECURSIVE_MAKE} clean;\
		if [ "${PRECLEAN}" = "yes" ]; then \
			${BULK_MSG} "Currently installed packages:"; \
			${PKG_INFO} -e "*" | ${SED} -e "s,^,* ,"; \
			${PHASE_MSG} "Removing installed packages which are not needed to build ${PKGNAME}" ; \
			if [ "${USE_BULK_CACHE}" = "yes" ]; then \
				for pkgname in `${PKG_INFO} -e \\*`; do \
					: "The package may have been deinstalled in between."; \
					${PKG_INFO} -qe "$$pkgname" || continue; \
					pkgdir=`${PKG_INFO} -Q PKGPATH "$$pkgname"`; \
					[ "$$pkgdir" ] || { ${FAIL_MSG} "Empty PKGPATH for $$pkgname"; continue; }; \
					required=`${AWK} '$$1 == "${PKGPATH}" { for (i = 4; i <= NF; i++) { if ($$i == "'"$$pkgdir"'") { print $$i; } } }' ${DEPENDSFILE}`; \
					if true; then \
						if [ "$$required" ]; then \
							${STEP_MSG} "Keeping dependency $$pkgname." ;\
						else \
							case "${BULK_PREREQ}" in \
								*$$pkgdir* ) \
									${STEP_MSG} "Keeping BULK_PREREQ $$pkgname ($$pkgdir)" ;\
									;; \
								* ) \
									${STEP_MSG} "Deinstalling $$pkgname"; \
									${DO}       ${PKG_DELETE} -r $$pkgname || ${TRUE}; \
									;; \
							esac ; \
						fi ;\
					fi ;\
				done; \
			else \
				${STEP_MSG} "Deinstalling all packages"; \
				${DO} ${PKG_DELETE} -r "*" || ${TRUE}; \
			fi ;\
		fi ;\
		if [ "${USE_BULK_CACHE}" = "yes" ]; then \
			${SHCOMMENT} "Install required depends via binarypkgs XXX" ; \
			${BULK_MSG} "Installing dependencies for ${PKGNAME}." ;\
			for pkgdir in `${SED} -n -e "/^${_ESCPKGPATH} / s;^[^:]*:;;p" ${DEPENDSFILE}` ${BULK_PREREQ} ; do \
				pkgname=`${AWK} '$$1 == "'"$$pkgdir"'" { print $$2; }' ${INDEXFILE}`; \
				if [ -z "$$pkgname" ]; then ${BULK_MSG} "WARNING: could not find package name for directory $$pkgdir"; continue ; fi ;\
				if [ -f "${BULKFILESDIR}/$$pkgdir/${NOT_AVAILABLE_FILE}" ]; then \
					${ECHO} "The dependency $$pkgname ($$pkgdir) is not available." >> ${BULKFILESDIR}/${PKGPATH}/${NOT_AVAILABLE_FILE}; \
					exit 1; \
				fi; \
				pkgfile=${PACKAGES}/All/$${pkgname}${PKG_SUFX} ;\
				if ${PKG_INFO} -qe $$pkgname ; then \
					${BULK_MSG} "Dependency $$pkgname is already installed" ; \
				else \
					if [ -f $$pkgfile ]; then \
						${BULK_MSG} "Installing $$pkgfile"; \
						${DO} ${PKG_ADD} ${PKG_ARGS_ADD} $$pkgfile || ${WARNING_MSG} "could not add $$pkgfile." ; \
					else \
						${BULK_MSG} "warning: $$pkgfile does not exist.  It will be rebuilt." ;\
					fi ;\
				fi ;\
			done ;\
		fi ;\
		if [ -f ${_INTERACTIVE_COOKIE} ]; then \
			${BULK_MSG} "Removing old marker for INTERACTIVE_STAGE..." ; \
			${ECHO_MSG} ${RM} -f ${_INTERACTIVE_COOKIE} ; \
			${DO}       ${RM} -f ${_INTERACTIVE_COOKIE} ; \
		fi ;\
		${ECHO_MSG} ${MAKE} package '(${PKGNAME})' 2>&1 ; \
		${DO} ${RECURSIVE_MAKE} package; \
		${ECHO} "";						\
		) 2>&1 | ${TEE} -a ${_BUILDLOG} ; \
		if [ -f ${PKGFILE} ]; then \
			case ${KEEP_BUILDLOGS} in			\
			yes)	${MV} ${_BUILDLOG} ${_BUILD_SUCCEEDED_FILE}; \
				;;					\
			no)	${RM} ${_BUILDLOG};			\
				;;					\
			esac;						\
		else \
			{ ${ECHO} "<html>";				\
			  ${ECHO} "<head><title>pkgsrc build log for ${PKGNAME}</title></head>"; \
			  ${ECHO} "";					\
			  ${ECHO} "<body>";				\
			  ${ECHO} "<pre>";				\
			  ${TO_HTML} < ${_BUILDLOG};			\
			  ${ECHO} "</pre>";				\
			} > ${_BROKENFILE};				\
			${RM} -f ${_BUILDLOG};				\
			( \
			if [ -f ${_BROKENWRKLOG} ]; then \
				${ECHO} "<p>"; \
				${ECHO} "Please view the <a href=\"../../${PKGPATH}/${BROKENWRKLOG}\">work log for ${PKGNAME}</a>"; \
				${ECHO} "</p>"; \
			fi >> ${_BROKENFILE}; \
			${ECHO} "<pre>" >> ${_BROKENFILE}; \
			${BULK_MSG} "${PKGNAME} was marked as broken:" ; \
			${LS} -la ${_BROKENFILE} ; \
			${ECHO_MSG} ${MAKE} deinstall ; \
			${DO}       ${RECURSIVE_MAKE} deinstall ; \
			${ECHO} "</pre>" >> ${_BROKENFILE}; \
			nbrokenby=0;\
			if [ "${USE_BULK_CACHE}" = "yes" ]; then \
				${BULK_MSG} "Marking all packages which depend upon ${PKGNAME} as broken:"; \
				tmp=`${SED} -n -e "/^${_ESCPKGPATH} / s;^[^:]*:[ ]*;;p" ${SUPPORTSFILE}` ; \
				if test -n "$$tmp" ; then \
					${ECHO} "<ul>"; \
					for pkgdir in $$tmp ; do \
						pkg_brokendir=${BULKFILESDIR}/"$$pkgdir"; \
						pkg_brokenfile="$$pkg_brokendir"/${BROKENFILE}; \
						pkgname=`${AWK} '$$1 == "'"$$pkgdir"'" { print $$2; }' ${INDEXFILE}`; \
						case $$pkgname in \
						"")	pkgname="unknown"; \
							${BULK_MSG} "WARNING: unknown pkgname in $$pkgdir.";; \
						esac; \
						${ECHO} "<li>$$pkgname ($$pkgdir)</li>";\
						pkgerr='-1'; pkgignore=''; pkgskip=''; \
						if [ "${USE_BULK_BROKEN_CHECK}" = 'yes' ]; then \
							pkgignore=`(cd ${ROBOTPKG_DIR}/$$pkgdir && ${RECURSIVE_MAKE} show-var VARNAME=PKG_FAIL_REASON)`; \
							pkgskip=`(cd ${ROBOTPKG_DIR}/$$pkgdir && ${RECURSIVE_MAKE} show-var VARNAME=PKG_SKIP_REASON)`; \
						fi; \
						if [ ! -z "$${pkgignore}$${pkgskip}" -a ! -f "$${pkg_brokenfile}" ]; then \
							{ ${BULK_MSG} "$$pkgname ($$pkgdir) may not be packaged because:"; \
							  ${BULK_MSG} "$$pkgignore"; \
							  ${BULK_MSG} "$$pkgskip"; \
							} >> "$${pkg_brokenfile}"; \
							if [ "${USE_BULK_BROKEN_CHECK}" != 'yes' ] || [ -z "`(cd ${ROBOTPKG_DIR}/$$pkgdir && ${RECURSIVE_MAKE} show-var VARNAME=BROKEN)`" ]; then \
								pkgerr="0"; \
							else \
								pkgerr="1"; \
							fi; \
						fi; \
						${_BULK_MKDIR} "$${pkg_brokendir}"; \
						{ ${ECHO} "$$pkgname ($$pkgdir) is broken because it depends upon ${PKGNAME} (${PKGPATH}) which is broken."; \
						  ${ECHO} "Please view the <a href=\"../../${PKGPATH}/${BROKENFILE}\">build log for ${PKGNAME}</a>.<br />"; \
						} >> "$${pkg_brokenfile}"; \
						nbrokenby=`expr $$nbrokenby + 1`;\
						if ${GREP} -q " $$pkgdir/${BROKENFILE}" ${BULKFILESDIR}/${BROKENFILE} ; then :; \
						else \
							${ECHO} " $$pkgerr $$pkgdir/${BROKENFILE} 0 " >> ${BULKFILESDIR}/${BROKENFILE} ;\
						fi ;\
					done ;\
					${ECHO} "</ul>"; \
				fi ;\
			fi ;\
			nerrors=`${GREP} -c '^\*\*\* Error code' ${_BROKENFILE} || true`; \
			if [ -f ${_INTERACTIVE_COOKIE} ]; then \
				nerrors="0"; \
			fi; \
			${ECHO} " $$nerrors ${PKGPATH}/${BROKENFILE} $$nbrokenby " >> ${BULKFILESDIR}/${BROKENFILE} \
			) 2>&1 | ${TEE} -a ${_BROKENFILE}; \
		fi ; \
		if [ ${_PRESERVE_WRKDIR} = "pack-if-failed" ] && [ ! -f ${PKGFILE} ]; then \
			${BULK_MSG} "Making an archive from the working directory."; \
			(cd ${WRKDIR}					\
			&& ${PAX} -wz -f ${_BULK_PKGLOGDIR}/wrkdir.tar.gz . \
			) || ${TRUE};					\
		fi;							\
		case ${_PRESERVE_WRKDIR} in				\
		yes|YES)	;;					\
		*)	${DO} ${RECURSIVE_MAKE} clean;;			\
		esac;							\
	fi
	@if [ ! -f ${PKGFILE} ]; then \
		${BULK_MSG} "Build for ${PKGNAME} was not successful, aborting." | ${TEE} -a ${_BROKENFILE} ; \
		${ECHO} "<pre>" >> ${_BROKENFILE};			\
		{ ${ECHO} "</pre>";					\
		  ${ECHO} "</body>";					\
		  ${ECHO} "</html>";					\
		} >> ${_BROKENFILE};					\
		exitcode=1;						\
	else \
		case ${KEEP_BUILDLOGS} in				\
		yes)	${TEST} ! -f ${_BUILDLOG}			\
			|| ${MV} ${_BUILDLOG} ${_BUILD_SUCCEEDED_FILE}; \
			;;						\
		no)	${RM} -f ${_BUILDLOG};				\
			;;						\
		esac;							\
		exitcode=0;						\
	fi;								\
	exit $$exitcode
ifneq (${BULKFILESDIR},${ROBOTPKG_DIR})
	${_PKG_SILENT}${_PKG_DEBUG}					\
	${RMDIR} ${_BULK_PKGLOGDIR} 2>/dev/null 1>&2 || ${TRUE}
endif

# Install pkg - if possible from binary pkg (i.e. available & up-to-date)
# else revert to the old recompiling.
# Don't rely upon pkg_add to snarf in depending pkgs as they may have
# been modified and need rebuilding.
.PHONY: bulk-install
bulk-install:
	@if [ `${RECURSIVE_MAKE} bulk-check-uptodate REF=${PKGFILE}` = 1 ]; then \
		if ${PKG_INFO} -qe ${PKGNAME} ; then :; \
		else \
			${DO} ${RECURSIVE_MAKE} install-depends ; \
			${BULK_MSG} ${PKG_ADD} ${PKG_ARGS_ADD} ${PKGFILE} ; \
			${DO} ${PKG_ADD} ${PKG_ARGS_ADD} ${PKGFILE} ; \
		fi ; \
	else \
		${ECHO_MSG} ${MAKE} bulk-package PRECLEAN=no; \
		${DO}       ${RECURSIVE_MAKE} bulk-package PRECLEAN=no; \
	fi

.PHONY: bulk-info
bulk-info:
	@${ECHO} pkgname ${PKGPATH} ${PKGNAME}
	@:; $(foreach d,${DEPENDS},${ECHO} ${PKGPATH} $(call quote,${d});)

endif # ROBOTPKGTOP
