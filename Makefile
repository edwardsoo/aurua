IDIR =./include
CC=g++
CFLAGS=-I$(IDIR)

ODIR =.
SDIR =./src

LIBS=-lGL -lGLU -lglut

_DEPS = Camera.h Global.h Header.h Ship.h ViewingMode.h Vec3.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


_OBJ = Camera.o main.o Ship.o Global.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< 

all: aurua

aurua: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ aurua

