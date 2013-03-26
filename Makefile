CCFLAGS = -g -pg

default: aurua
all: aurua

aurua: main.o ship.o
	g++ ${CCFLAGS_MAKE_TEXTURES} main.cpp ship.cpp global.cpp -o aurua \
		glut32.lib -lopengl32 -lglu32

clean:
	touch aurua
	rm -rf aurua.exe *.o
