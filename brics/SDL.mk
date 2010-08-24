DEPEND_DEPTH:=		${DEPEND_DEPTH}+
SDL_DEPEND_MK:=	${SDL_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		SDL
endif

ifeq (+,$(SDL_DEPEND_MK)) # -------------------------------------

PREFER.sdl?=	system
DEPEND_USE+=		sdl
DEPEND_ABI.sdl?=	sdl>=1.2

SYSTEM_SEARCH.sdl=	\
	'bin/sdl:/SDL/{s/[^.0-9]//gp;q;}:% --version'

SYSTEM_PKG.Linux.sdl=libsdl1.2-dev

export SDL=	${PREFIX.sdl}/bin/sdl

endif # SDL_DEPEND_MK -------------------------------------------

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
