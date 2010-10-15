DEPEND_DEPTH:=		${DEPEND_DEPTH}+
CPPUNIT_DEPEND_MK:=	${CPPUNIT_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		cppunit
endif

ifeq (+,$(CPPUNIT_DEPEND_MK)) # -------------------------------------

PREFER.cppunit?=	system
DEPEND_USE+=		cppunit
DEPEND_ABI.cppunit?=	cppunit>=1.12.1

SYSTEM_SEARCH.cppunit=	\
	'include/cppunit/Asserter.h' \
	'lib/libcppunit.{a,so,dylib}'

SYSTEM_PKG.Linux.cppunit=libcppunit-dev


endif # CPPUNIT_DEPEND_MK -------------------------------------------

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
