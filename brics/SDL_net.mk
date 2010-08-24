DEPEND_DEPTH:=		${DEPEND_DEPTH}+
SDL_NET_DEPEND_MK:=	${SDL_NET_DEPEND_MK}+

ifeq (+,$(DEPEND_DEPTH))
DEPEND_PKG+=		SDL_NET
endif

ifeq (+,$(SDL_NET_DEPEND_MK)) # -------------------------------------

PREFER.sdl?=	system
DEPEND_USE+=		sdl_net
DEPEND_ABI.sdl_net?=	sdl_net>=1.2

SYSTEM_SEARCH.sdl_net=	\
	'bin/sdl:/SDL/{s/[^.0-9]//gp;q;}:% --version'

SYSTEM_PKG.Linux.sdl_net=libsdl-net1.2-dev

export SDL_NET=	${PREFIX.sdl_net}/bin/sdl_net

endif # SDL_NET_DEPEND_MK -------------------------------------------

DEPEND_DEPTH:=		${DEPEND_DEPTH:+=}
