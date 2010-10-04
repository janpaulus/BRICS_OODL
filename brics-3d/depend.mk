# robotpkg depend.mk for:	brics/libunicap
# Created:	 Azamat BRSU on 18 Aug 2010
#

DEPEND_DEPTH:=		${DEPEND_DEPTH}+
ZEROMQ_DEPEND_MK:= ${ZEROMQ_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		zeromq
endif

ifeq (+,$(ZEROMQ_DEPEND_MK))
PREFER.zeromq?=	robotpkg

DEPEND_USE+=		zeromq

DEPEND_ABI.zeromq?=	zeromq>=2.0.9
DEPEND_DIR.zeromq?=	../../brics/zeromq

SYSTEM_SEARCH.zeromq=\
	include/zmq.h
endif

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
