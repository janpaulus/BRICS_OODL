DEPEND_DEPTH:=		${DEPEND_DEPTH}+
OPENSCENEGRAPH_DEPEND_MK:=	${OPENSCENEGRAPH_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		openscenegraph
endif

ifeq (+,$(OPENSCENEGRAPH_DEPEND_MK)) # -------------------------------------

PREFER.openscenegraph?=	system
DEPEND_USE+=		openscenegraph
DEPEND_ABI.openscenegraph?=	openscenegraph>=2.8.1

SYSTEM_SEARCH.openscenegraph=	\
	'include/osg/AlphaFunc' \
	'lib/libosg.{a,so,dylib}'

SYSTEM_PKG.Linux.openscenegraph=libopenscenegraph-dev


endif # OPENSCENEGRAPH_DEPEND_MK -------------------------------------------

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
