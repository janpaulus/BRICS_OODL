Every Package is in one folder. To create a new package create a folder in one of the topic folders e.g. architecture, archivers, audio...
A package is composed of five text files:
xxxxxx

depend.mk
The depend.mk file will be included by other packages to resolve the dependency.

DESCR
The DESCR file contains a description of the package.

distinfo:
The distinfo file contains checksum of the package archive, to verify the archive after a download.
To create a SHA1 checksum type:
sha1sum <filename>

For the RMD160 checksum type:
openssl rmd160 <filename>

Makefile
SICK_TOOLBOX_VERSION=    1.0.1
DISTNAME=        sicktoolbox-${SICK_TOOLBOX_VERSION}
PKGNAME=        sicktoolbox-${SICK_TOOLBOX_VERSION}
CATEGORIES=        hardware
MASTER_SITES=        http://downloads.sourceforge.net/project/sicktoolbox/sicktoolbox/${SICK_TOOLBOX_VERSION}/
MASTER_REPOSITORY=     svn https://sicktoolbox.svn.sourceforge.net/svnroot/sicktoolbox

MAINTAINER=        Jason Derenick
HOMEPAGE=        https://sicktoolbox.svn.sourceforge.net/
COMMENT=        The Sick LIDAR Matlab/C++ Toolbox
LICENSE=        modified-bsd

USE_LANGUAGES=        c c++

GNU_CONFIGURE=        yes

include ../../mk/robotpkg.mk

PLIST




