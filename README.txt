                              A guide to robotpkg

                    Anthony Mallet - anthony.mallet@laas.fr
                       Copyright 2006-2009 (C) LAAS/CNRS

                                 June 28, 2010

Contents

1  Introduction
    1.1  What is robotpkg?
    1.2  Why robotpkg?
    1.3  Supported platforms
    1.4  Overview
    1.5  Terminology
    1.6  Roles involved in robotpkg
    1.7  Typography
2  The robotpkg user's guide
    2.1  Where to get robotpkg and how to keep it up-to-date
        2.1.1  Getting the binary bootstrap kit
        2.1.2  Getting robotpkg for source compilation
        2.1.3  Keeping robotpkg up-to-date
    2.2  Bootstrapping robotpkg
        2.2.1  Bootstrapping via the binary kit
        2.2.2  Bootstrapping from source
    2.3  Using robotpkg
        2.3.1  Building packages from source
        2.3.2  Installing binary packages
        2.3.3  Removing packages
        2.3.4  Getting information about installed packages
        2.3.5  Other administrative functions
    2.4  Configuring robotpkg
        2.4.1  Selecting build options
        2.4.2  General configuration variables
        2.4.3  Variables affecting the build process
        2.4.4  Additional flags to the compiler
3  The robotpkg developer's guide
4  The robotpkg infrastructure internals

1
Introduction

1.1  What is robotpkg?

The robotics research community has always been developing a lot of software,
in order to illustrate theoretical concepts and validate algorithms on board
real robots. A great amount of this software was made freely available to the
community, especially for Unix-based systems, and is usually available in form
of the source code. Therefore, before such software can be used, it needs to be
configured to the local system, compiled and installed. This is exactly what
The Robotics Packages Collection (robotpkg) does. robotpkg also has some basic
commands to handle binary packages, so that not every user has to build the
packages for himself, which is a time-costly, cumbersome and error-prone task.
The robotpkg project was initiated in the Laboratory for Analysis and
Architecture of Systems (CNRS/LAAS), France. The motivation was, on the one
hand, to ease the software maintenance tasks for the robots that are used
there. On the other hand, roboticists at CNRS/LAAS have always fostered an
open-source development model for the software they were developing. In order
to help people working with the laboratory to get the LAAS software running
outside the laboratory, a package management system was necessary.
Although robotpkg was an innovative project in the robotics community (it
started in 2006), a lot of general-purpose software packages management systems
were readily available at this time for a great variety of Unix-based systems.
The main requirements that we wanted robotpkg to fullfill were listed and the
best existing package management system was chosen as a starting point. The
biggest requirement was the capacity of the system to adapt to the nature of
the robotic software, being available mostly in form of source code only (no
binary packages), with unfrequent stable releases. robotpkg had thus to deal
mostly with source code and automate the compilation of the packages. The
system chosen as a starting point was The NetBSD Packages Collection (pkgsrc).
robotpkg can be considered as a fork of this project and it is still very
similar to pkgsrc in many points, although some simplifications were made in
order to provide a tool geared toward people that are not computer scientists
but roboticists.
Due to its origins, robotpkg provides many packages developed at LAAS. It is
however not limited to such packages and contains, in fact, quite some other
software useful to roboticists. Of course, robotpkg is not meant to be a
general purpose packaging system (although there would be no technical
restriction to this) and will never contain widely available packages that can
be found on any modern Unix distribution. Yet, robotpkg currently contains
roughly one hundred and fifty packages, including:

  * architecture/genom - The LAAS Generator of Robotic Components
  * architecture/openhrp - The Open Architecture Humanoid Robotics Platform
    from AIST, Japan
  * architecture/openrtm - The robotic distributed middleware from AIST, Japan
  * architecture/yarp - The "other", yet famous, robot platform
  * ...just to name a few.

1.2  Why robotpkg?

robotpkg provides the following key features:

  * Easy building of software from source as well as the creation and
    installation of binary packages. The source and latest patches are
    retrieved from a master download site, checksum verified, then built on
    your system.
  * All packages are installed in a consistent directory tree, including
    binaries, libraries, man pages and other documentation.
  * Package dependencies, including when performing package updates, are
    handled automatically.
  * The installation prefix, acceptable software licenses and build-time
    options for a large number of packages are all set in a simple, central
    configuration file.
  * The entire framework source (not including the package distribution files
    themselves) is freely available under a BSD license, so you may extend and
    adapt robotpkg to your needs, like robotpkg was adapted from pkgsrc.

1.3  Supported platforms

robotpkg consists of a source distribution. After retrieving the required
source, you can be up and running with robotpkg in just minutes!
robotpkg does not have much requirements by itself and it can work on a wide
variety of systems as long as they provide a GNU-make utility, a working
C-compiler and a small, reasonably standard subset of Unix commands (like sed,
awk, find, grep ...). However, individual packages might have their specific
requirements. The following platforms have been reported to be supported
reasonably well:
                        +-----------------------------+
                        |Platform|      Version       |
                        |--------+--------------------|
                        |--------+--------------------|
                        | Fedora |       5 - 12       |
                        |--------+--------------------|
                        | Ubuntu |    7.10 - 9.04     |
                        |--------+--------------------|
                        | Debian |        5.03        |
                        |--------+--------------------|
                        | CentOS |         5          |
                        |--------+--------------------|
                        | NetBSD |       4 - 5        |
                        |--------+--------------------|
                        | Darwin |Preliminary support |
                        +-----------------------------+

1.4  Overview

This document is divided into three parts. The first one describes how one can
use one of the packages in the Robotics Package Collection, either by
installing a precompiled binary package, or by building one's own copy using
robotpkg. The second part explains how to prepare a package so it can be easily
built by other users without knowing about the package's building details. The
third part is intended for those who want to understand how robotpkg is
implemented.

1.5  Terminology

Here is a description of all the terminology used within this document.

Package
    A set of files and building instructions that describe what's necessary to
    build a certain piece of software using robotpkg. Packages are
    traditionally stored under /opt/robotpkg.
robotpkg
    This is the The Robotics Package Collection. It handles building
    (compiling), installing, and removing of packages.
Distfile
    This term describes the file or files that are provided by the author of
    the piece of software to distribute his work. All the changes necessary to
    build are reflected in the corresponding package. Usually the distfile is
    in the form of a compressed tar-archive, but other types are possible, too.
    Distfiles are usually stored below /opt/robotpkg/distfiles.
Precompiled/binary package
    A set of binaries built with robotpkg from a distfile and stuffed together
    in a single .tgz file so it can be installed on machines of the same
    machine architecture without the need to recompile. Packages are usually
    generated in /opt/robotpkg/packages.
    Sometimes, this is referred to by the term "package" too, especially in the
    context of precompiled packages.
Program
    The piece of software to be installed which will be constructed from all
    the files in the distfile by the actions defined in the corresponding
    package.

1.6  Roles involved in robotpkg

robotpkg users
    The robotpkg users are people who use the packages provided by robotpkg.
    Typically they are student working in robotics. The usage of the software
    that is inside the packages is not covered by the robotpkg guide.
    There are two kinds of robotpkg users: Some only want to install pre-built
    binary packages. Others build the robotpkg packages from source, either for
    installing them directly or for building binary packages themselves. For
    robotpkg users, Part 2 should provide all necessary documentation.
package maintainers
    A package maintainer creates packages as described in Part 3.
infrastructure developers
    These people are involved in all those files that live in the mk/ directory
    and below. Only these people should need to read through Part 4, though
    others might be curious, too.

1.7  Typography

When giving examples for commands, shell prompts are used to show if the
command should/can be issued as root, or if "normal" user privileges are
sufficient. We use a # for root's shell prompt, and a % for users' shell
prompt, assuming they use the C-shell or tcsh.

2
The robotpkg user's guide

Basically, there are two ways of using robotpkg. The first is to only install
the package tools and to use binary packages that someone else has prepared.
The second way is to install the programs from source. Then you are able to
build your own packages, and you can still use binary packages from someone
else. Sections in this document will detail both approaches where appropriate.

2.1  Where to get robotpkg and how to keep it up-to-date

Before you download and extract the files, you need to decide where you want to
extract them and where you want robotpkg to install packages. By defaut, the /
opt/openrobots directory is used. In the rest of this document, the
installation path is called the prefix.
robotpkg will never require administration privileges by itself. We thus
recommend that you do not install or run robotpkg as the root user. If
something ever goes really wrong, it might go less wrong if it is not running
as root. If you want to install to the default location /opt/openrobots, we
recommend that you create this directory owned by a regular user.
Creating or using /opt/openrobots typically requires administration ( a.k.a.
"root") privileges. If you don't have such privileges (or if you want to
install to a different location), you have to unpack the sources and install
the binary packages in another prefix. If you don't have any special
administration rights on the target machine, a safe bet is to choose the $HOME/
openrobots location, as the $HOME directory will always be writable by
yourself.
Any prefix will work, but please note that you should choose an installation
path which is dedicated to robotpkg packages and not shared with other programs
(e.g., we do not recommend to use a prefix of /usr). Also, you should not try
to add any of your own files or directories (such as src/) below the prefix
tree. This will prevent possible conflicts between programs and other files
installed by the package system and whatever else may have been installed
there.
Finally, the installation path shall not contain white-space or other
characters that are interpreted specially by the shell and some other programs:
use only letters, digits, underscores and dashes.
The rest of this document will assume that you are using /opt/openrobots as the
prefix. You should adapt this path to whatever prefix you choosed.

2.1.1  Getting the binary bootstrap kit

At the moment, the binary bootstrap kit is not available. Please get the
robotpkg sources as described in the next section.

2.1.2  Getting robotpkg for source compilation

robotpkg sources are distributed via the git software content management
system. git will probably be readily available on your system but if you don't
have it installed or if you are unsure about it, contact your local system
administrator.
There are two download methods: the anonymous one and the authenticated one:

  * Anonymous download is the recommended method if you don't intend to work on
    the robotpkg infrastructure itself, nor commit any changes or packages
    additions back to the robotpkg main repository. Furthermore, the
    possibility to send contributions via patches is still open.
    As your regular user, simply run in a shell:

    % cd /opt/openrobots
    % git clone http://softs.laas.fr/git/robots/robotpkg.git


  * Authenticated download requires a valid login on the main robotpkg
    repository, and will give you full commit access to this repository. Simply
    run the following:

    % cd /opt/openrobots
    % git clone ssh://softs.laas.fr/git/robots/robotpkg


2.1.3  Keeping robotpkg up-to-date

robotpkg is a living thing: updates to the packages are made perdiodicaly,
problems are fixed, enhancements are developed... If you downloaded the
robotpkg sources via git, you should keep it up-to-date so that you get the
most recent packages descriptions. This is done by running git pull in the
robotpkg source directory:

% cd /opt/openrobots/robotpkg
% git pull


When you update robotpkg, the git program will only touch those files that are
registered in the git repository. That means that any packages that you created
on your own will stay unmodified. If you change files that are managed by git,
later updates will try to merge your changes with those that have been done by
others. See the git-pull manual for details.
If you want to be informed of package additions and other updates, a public
mailing list is available for your reading pleasure. Go to https://
sympa.laas.fr/sympa/info/robotpkg for more information and subscription.

2.2  Bootstrapping robotpkg

Once you have downloaded the robotpkg sources or the binary bootstrap kit as
described in Section 2.1, a minimal set of the administrative package
management utilities must be installed on your system before you can use
robotpkg. This is called the "bootstrap phase" and should be done only once,
the very first time you download robotpkg.

2.2.1  Bootstrapping via the binary kit

At the moment, the binary bootstrap kit is not available. Please bootstrap
robotpkg as described in the next section.

2.2.2  Bootstrapping from source

You will need a working C compiler and the GNU-make utility version 3.81 or
later. If you have extracted the robotpkg archive into the standard /opt/
openrobots/robotpkg location, installing the bootstrap kit from source should
then be as simple as:

% cd /opt/openrobots/robotpkg/bootstrap
% ./bootstrap


This will install various utilities into /opt/openrobots/sbin.
Should you prefer another installation path, you could use the --prefix option
to change the default installation prefix. For instance, configuring robotpkg
to install programs into the openrobots directory in your home directory can be
done like this:

% cd robotpkg/bootstrap
% ./bootstrap --prefix=${HOME}/openrobots


After the bootstrap script has run, a message indicating the success should be
displayed. If you choosed a non-standard installation path, read this message
carefuly, as it contains instructions that you have to follow in order to setup
your shell environment correctly. These instructions are described in the next
section.

Configuring your environment

If you configured robotpkg, during the bootstrap phase, to install to some
other location than /opt/openrobots, you have to setup manually your shell
environment so that it contains a few variables holding the installation path.
Assuming you invoked bootstrap with -prefix=/path/to/openrobots, you have two
options that are compatible with each other:

  * Add the directory /path/to/openrobots/sbin to your PATH variable. robotpkg
    will then be able to find its administrative tools automatically and from
    that recover other configuration information. This is the preferred method.
  * Create the environment variable ROBOTPKG_BASE and set its value to /path/to
    /openrobots. robotpkg will look for this variable first, so it takes
    precedence over the first method. This is the method you have to choose if
    you have configured several instances of robotpkg in your system. This is
    ony useful in some circumstances and is not normally needed.

If you don't know how to setup environment variables permanently in your
system, please refer to your shell's manual or contact your local system
administrator.

The bootstrap script usage

The bootstrap script will by default install the package administrative tools
in /opt/openrobots/sbin, use gcc as the C compiler and make as the GNU-make
program. This behaviour can be fine-tuned by using the following options:

--prefix <path>
    will select the prefix location where programs will be installed in.
--sysconfdir <path>
    defaults to <prefix>/etc. This is the path to the robotpkg configuration
    file. Other packages configuration files (if any) will also be stored in
    this directory.
--pkgdbdir <path>
    defaults to <prefix>/var/db/pkg. This is the path to the package database
    directory where robotpkg will do its internal bookkeeping.
--compiler <program>
    defaults to gcc. Use this option if you want to use a different C compiler.
--make <program>
    defaults to make. Use this option if you want to use a different make
    program. This program should be compatible with GNU-make.
--help
    displays the bootstrap usage. The comprehensive list of recognized options
    will be displayed.

2.3  Using robotpkg

After obtaining robotpkg , the robotpkg directory now contains a set of
packages, organized into categories. You can browse the online index of
packages, or run make index from the robotpkg directory to build local
index.html files for all packages, viewable with any web browser such as lynx
or firefox.

2.3.1  Building packages from source

The first step for building a package is downloading the distfiles (i.e. the
unmodified source). If they have not yet been downloaded, robotpkg will fetch
them automatically and place them in the robotpkg/distfiles directory.
Once the software has been downloaded, any patches will be applied and the
package will be compiled for you. This may take some time depending on your
computer, and how many other packages the software depends on and their compile
time.
For example, type the following commands at the shell prompt to build the
robotpkg documentation package:

% cd /opt/openrobots/robotpkg
% cd doc/robotpkg
% make


The next stage is to actually install the newly compiled package onto your
system. While you are still in the directory for whatever package you are
installing, you can do this by entering:

% make install


Installing the package on your system does not require you to be root (except
for a few specific packages). However, if you bootstraped with a prefix for
which you don't have writing permissions, robotpkg has a just-in-time-sudo
feature, which allows you to become root for the actual installation step.
That's it, the software should now be installed under the prefix of the
packages tree - /opt/openrobots by default - and setup for use.
You can now enter:

% make clean


to remove the compiled files in the work directory, as you shouldn't need them
any more. If other packages were also added to your system (dependencies) to
allow your program to compile, you can also tidy these up with the command:

% make clean-depends


Since the three tasks of building, installing and cleaning correspond to the
typical usage of robotpkg , a helper target doing all these tasks exists and is
called update. Thus, to intall a package with a single command, you can simply
run:

% make update


In addition, make update will also recompile all the installed packages that
were depending on the package that you are updating. This can be quite time
consuming if you are updating a low-level package. Also, note that all packages
that depend on the package you are updating will be deinstalled first and
unavailable in your system until all packages are recompiled and reinstalled.
Occasionally, people want to "look under the covers" to see what is going on
when a package is building or being installed. This may be for debugging
purposes, or out of simple curiosity. A number of utility values have been
added to help with this.

 1. If you invoke the make command with PKG_DEBUG_LEVEL=1, then a huge amount
    of information will be displayed. For example,

    % make patch PKG_DEBUG_LEVEL=1


    will show all the commands that are invoked, up to and including the
    "patch" stage. Using PKG_DEBUG_LEVEL=2 will give you even more details.
 2. If you want to know the value of a certain make definition, then the
    VARNAME variable should be used, in conjunction with the show-var target.
    e.g. to show the expansion of the make variable LOCALBASE:

    % make show-var VARNAME=LOCALBASE


2.3.2  Installing binary packages

At the moment, installing binary packages is not documented.

2.3.3  Removing packages

To deinstall a package, it does not matter whether it was installed from source
code or from a binary package. The robotpkg_delete command does not know it
anyway. To delete a package, you can just run robotpkg_delete <package-name>.
The package name can be given with or without version number. Wildcards can
also be used to deinstall a set of packages, for example *genom* all packages
whose name contain the word genom. Be sure to include them in quotes, so that
the shell does not expand them before robotpkg_delete sees them.
The -r option is very powerful: it removes all the packages that require the
package in question and then removes the package itself. For example:

% robotpkg_delete -r genom


will remove genom and all the packages that used it; this allows upgrading the
genom package.

2.3.4  Getting information about installed packages

The robotpkg_info shows information about installed packages or binary package
files.

2.3.5  Other administrative functions

The robotpkg_admin executes various administrative functions on the package
system.

2.4  Configuring robotpkg

The whole robotpkg system is configured via a single, centralized file, called
robotpkg.conf and placed in the /opt/openrobots/etc directory by default. This
location might be redefined during the bootstrap phase, see Section 2.2. During
the bootstrap, an initial configuration file is created with the settings you
provided to bootstrap.
The format of the configuration file is that of the usual GNU style Makefiles.
The whole robotpkg configuration is done by setting variables in this file.
Note that you can define all kinds of variables, and no special error checking
(for example for spelling mistakes) takes place, so you have to try it out to
see if it works.

2.4.1  Selecting build options

Some packages have build time options, usually to select between different
dependencies, enable optional support for big dependencies or enable
experimental features.
To see which options, if any, a package supports, and which options are
mutually exclusive, run make show-options, for example:

Any of the following general options may be selected:
    debug   Produce debugging information for binary programs
    doc     Compile documentation material
    lex     Use lex in place of flex
    tcl     Enable support for TCL clients
    yacc    Use yacc in place of bison

These options are enabled by default:
    doc tcl

These options are currently enabled:
    doc tcl


The following variables can be defined in robotpkg.conf to select which options
to enable for a package:

  * PKG_DEFAULT_OPTIONS, which can be used to select or disable options for all
    packages that support them,
  * PKG_OPTIONS.<pkgbase>, which can be used to select or disable options
    specifically for package pkgbase. Options listed in these variables are
    selected, options preceded by - are disabled.

A few examples:

PKG_DEFAULT_OPTIONS=    debug
PKG_OPTIONS.genom=      doc -tcl


It is important to note that options that were specifically suggested by the
package maintainer must be explicitely removed if you do not wish to include
the option. If you are unsure you can view the current state with make
show-options.
The following settings are consulted in the order given, and the last setting
that selects or disables an option is used:

 1. the default options as suggested by the package maintainer,
 2. PKG_DEFAULT_OPTIONS,
 3. PKG_OPTIONS.<pkgbase>

For groups of mutually exclusive options, the last option selected is used, all
others are automatically disabled. If an option of the group is explicitly
disabled, the previously selected option, if any, is used. It is an error if no
option from a required group of options is selected, and building the package
will fail.

2.4.2  General configuration variables

In this section, you can find some variables that apply to all robotpkg
packages.

ACCEPTABLE_LICENSES
    List of acceptable licenses. Whenever you try to build a package whose
    license is not in this list, you will get an error message that includes
    instructions on how to change this variable.
DISTDIR
    Where to store the downloaded copies of the original source distributions
    used for building robotpkg packages. The default is $ROBOTPKG_DIR/
    distfiles.
PACKAGES
    The top level directory for the binary packages. The default is
    $ROBOTPKG_DIR/packages.
MASTER_SITE_BACKUP
    List of backup locations for distribution files if not found locally or in
    $MASTER_SITES. The default is
    http://softs.laas.fr/openrobots/robotpkg/distfiles/.
PKG_DEBUG_LEVEL
    The level of debugging output which is displayed whilst making and
    installing the package. The default value for this is 0, which will not
    display the commands as they are executed (normal, default, quiet
    operation); the value 1 will display all shell commands before their
    invocation, and the value 2 will display both the shell commands before
    their invocation, and their actual execution progress with set -x.

2.4.3  Variables affecting the build process

WRKOBJDIR
    The top level directory where, if defined, the separate working directories
    will get created. This is useful for building packages on a different
    filesystem than the robotpkg sources.
DEPENDS_TARGET
    By default, dependencies are only installed, and no binary package is
    created for them. You can set this variable to package to automatically
    create binary packages after installing dependencies.
LOCALBASE
    Where packages will be installed. The default value is /opt/openrobots. Do
    not mix binary packages with different values of LOCALBASEs!

2.4.4  Additional flags to the compiler

If you wish to set compiler variables such as CFLAGS, CXXFLAGS, FFLAGS ...
please make sure to use the += operator instead of the = operator:

CFLAGS+= -your -flags


Using CFLAGS= (i.e. without the "+") may lead to problems with packages that
need to add their own flags.
If you want to pass flags to the linker, both in the configure step and the
build step, you can do this in two ways. Either set LDFLAGS or LIBS. The
difference between the two is that LIBS will be appended to the command line,
while LDFLAGS come earlier. LDFLAGS is pre-loaded with rpath settings for
machines that support it. As with CFLAGS you should use the += operator:

LDFLAGS+= -your -linkerflags


3
The robotpkg developer's guide

4
The robotpkg infrastructure internals

