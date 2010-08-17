#!/usr/bin/env awk -f
#
# Copyright (c) 2006,2009 LAAS/CNRS
# Copyright (c) 1994-2006 The NetBSD Foundation, Inc.
# All rights reserved.
#
# This code is derived from software contributed to The NetBSD Foundation
# by Johnny C. Lam. It is derived from the 'pkgsrc' project
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
#   3. All advertising materials mentioning   features or use of this
#      software must display the following acknowledgement:
#        This product includes software developed by the NetBSD
#        Foundation, Inc. and its contributors.
#   4. Neither the  name  of The NetBSD Foundation  nor the names  of its
#      contributors  may be  used to endorse or promote  products derived
#      from this software without specific prior written permission.
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
# From $NetBSD: depends.mk,v 1.14 2006/10/09 08:57:39 joerg Exp $
#
#                                       Anthony Mallet on Thu Dec  7 2006
#

######################################################################
#
# NAME
#	reduce-depends.awk -- reduce a list of dependencies
#
# SYNOPSIS
#	reduce-depends.awk "depends_list"
#
# DESCRIPTION
#	reduce-depends.awk removes some extraneous dependencies from the
#	dependency list.  The dependency list should be passed as a single
#	argument, and the output will be a list of the reduced dependencies,
#	echo one on a new line.
#
######################################################################

BEGIN {
	CAT = ENVIRON["CAT"] ? ENVIRON["CAT"] : "cat"
	PKG_ADMIN = ENVIRON["PKG_ADMIN"] ? ENVIRON["PKG_ADMIN"] : "robotpkg_admin"
	PWD_CMD = ENVIRON["PWD_CMD"] ? ENVIRON["PWD_CMD"] : "pwd"
	TEST = ENVIRON["TEST"] ? ENVIRON["TEST"] : "test"

	PROGNAME = "reduce-depends.awk"
	ERRCAT = CAT " 1>&2"

	# Gather all dependencies into the depends array.  Index 0 of the
	# depends[pkgpath] array is the number of patterns associated with
	# that pkgpath.
	#
	args = ARGV[1]
	ARGC = split(args, ARGV); ARGC++
	for (i = 1; i < ARGC; i++) {
		pattern = ARGV[i];	sub(":.*", "", pattern)
		dir = ARGV[i];		sub(".*:", "", dir)
		cmd = TEST " -d " dir
		if (system(cmd) == 0) {
			cmd = "cd " dir " && " PWD_CMD
			while (cmd | getline pkgpath)
				if (!(pkgpath in pkgsrcdirs)) {
					pkgpaths[P++] = pkgpath
					pkgsrcdirs[pkgpath] = dir
				}
				depends[pkgpath, 0]++;
				depends[pkgpath, depends[pkgpath, 0]] = pattern
			close(cmd)
		} else {
			print "ERROR: [" PROGNAME "] " dir " does not exist." | ERRCAT
			exit 1
		}
	}

	# Reduce dependencies to the strictest set of dependencies it
	# can derive from all of depends[...].  It only understands
	# dependencies of the form foo>=1.0, and leaves the other
	# dependencies undisturbed.
	#
	# The algorithm takes dependencies of the form foo>=1.0 and
	# converts them to foo-1.0.  It then compares this pkg name against
	# each dependency to see if it satisfies them all.  The key fact
	# is the the strictest dependency, when converted to a pkg name,
	# will satisfy every dependency.
	#
	for (p = 0; p < P; p++) {
		pkgpath = pkgpaths[p]
		D = depends[pkgpath, 0];
		for (d = 1; d <= D; d++) {
			dep = depends[pkgpath, d]
			if (dep ~ /[{]/ || \
			    dep ~ />=[0-9]+<[0-9]+/ || \
			    dep !~ />=[0-9]+/)
			{
				reduced[N++] = dep ":" pkgsrcdirs[pkgpath]
				continue
			}
			ge_depends[dep] = dep
		}
		match_all = 1
		for (dep in ge_depends) {
			dep2pkg = dep; sub(">=", "-", dep2pkg)
			match_all = 1
			for (pattern in ge_depends) {
 				cmd = PKG_ADMIN " pmatch '" pattern "' '" dep2pkg "'"
				if (system(cmd) != 0) {
					match_all = 0
					break
				}
			}
			if (match_all == 0) continue
			reduced[N++] = dep ":" pkgsrcdirs[pkgpath]
			break
		}
		#
		# If there are conflicting dependencies, then just pass them
		# through and let the rest of the pkgsrc machinery handle it.
		#
		if (match_all == 0) {
			for (d = 1; d <= D; d++) {
				dep = depends[pkgpath, d]
				reduced[N++] = dep ":" pkgsrcdirs[pkgpath]
			}
		}
		for (dep in ge_depends)
			delete ge_depends[dep]
	}

	# Output reduced dependencies.
	for (n = 0; n < N; n++)
		print reduced[n];
}
