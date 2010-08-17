#
# Variable definitions for the Solaris operating system.

ECHO_N?=	printf		# ksh builtin

PKGLOCALEDIR?=	share
EXTRACT_USING=	${PAX}

_USE_RPATH=		yes	# add rpath to LDFLAGS

# Standard commands
$(call setdefault, TRUE,	:)
$(call setdefault, FALSE,	false)
$(call setdefault, TEST,	test)
$(call setdefault, ECHO,	echo)
$(call setdefault, SH,		/bin/sh)
$(call setdefault, CAT,		/bin/cat)
$(call setdefault, SETENV,	/usr/bin/env)
$(call setdefault, EXPR,	/bin/expr)
$(call setdefault, CMP,		/usr/bin/cmp)
$(call setdefault, LS,		/bin/ls)
$(call setdefault, WC,		/usr/bin/wc)
$(call setdefault, TOUCH,	/usr/bin/touch)
$(call setdefault, CHOWN,	/usr/sbin/chown)
$(call setdefault, CHMOD,	/bin/chmod)
$(call setdefault, CP,		/bin/cp)
$(call setdefault, LN,		/bin/ln)
$(call setdefault, MV,		/bin/mv)
$(call setdefault, RM,		/bin/rm)
$(call setdefault, RMDIR,	/bin/rmdir)
$(call setdefault, MKDIR,	/bin/mkdir -p)
$(call setdefault, DATE,	/bin/date)
$(call setdefault, ID,		/usr/bin/id)
$(call setdefault, GREP,	/usr/bin/grep)
$(call setdefault, EGREP,	/usr/bin/egrep)
$(call setdefault, FIND,	/usr/bin/find)
$(call setdefault, SED,		/usr/bin/gsed)
$(call setdefault, SORT,	/usr/bin/sort)
$(call setdefault, TSORT,	/usr/bin/tsort)
$(call setdefault, AWK,		/usr/bin/nawk)
$(call setdefault, BASENAME,	/usr/bin/basename)
$(call setdefault, XARGS,	/usr/bin/xargs)
$(call setdefault, TPUT,	/usr/bin/tput)
$(call setdefault, PAGER,	/usr/bin/less)

FILE_CMD?=		file

GZCAT?=			gzcat
BZCAT?=			bzcat

TOOLS_INSTALL=		${ROBOTPKG_DIR}/mk/internal/install-sh
TOOLS_ECHO=		echo
TOOLS_CAT=		cat
TOOLS_TEST=		test
TOOLS_GREP=		grep
TOOLS_SORT=		sort
DEF_UMASK?=		0022

TPUT_BOLD?=		bold
TPUT_RMBOLD?=		sgr0
