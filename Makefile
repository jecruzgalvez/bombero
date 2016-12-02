bombero: main.cpp csprite.cpp csprite.h 
	g++  -g main.cpp  csprite.cpp `sdl-config --libs --cflags` -lSDL_mixer
