CCFLAGS = -g -pg

default: aurua
all: aurua

aurua:
	g++ ${CCFLAGS_MAKE_TEXTURES} main.cpp ship.cpp global.cpp -o bin/aurua.exe \
		glut32.lib -lopengl32 -lglu32

clean:
	rm -rf bin/*
