CC=g++
CXXFLAGS=-std=c++11 -Wall `pkg-config --cflags gtk+-3.0`
LDFLAGS=-std=c++11 -export-dynamic `pkg-config --libs gtk+-3.0`
SOURCES=src/*.cc
OBJECTS=src/utility.o src/debug.o src/mutation.o src/main.o src/draw.o src/GUI.o
EXECUTABLE=Genetic.out

Genetic.out: $(OBJECTS)
	g++ -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

.PHONY: depend clean cleanall

clean:
	rm -f $(OBJECTS)

cleanall:
	rm -f $(EXECUTABLE) $(OBJECTS)

compress:
	tar -cvf Genetic.tar.xz $(SOURCES) Makefile Doxyfile src/*.h
