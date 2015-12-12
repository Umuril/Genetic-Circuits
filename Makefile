CC=g++
CXXFLAGS=-std=c++11 -O2 -pthread $(DEBUG_FLAGS) -Wall `pkg-config --cflags gtk+-3.0`
LDFLAGS=-std=c++11 -pthread -export-dynamic `pkg-config --libs gtk+-3.0`
SOURCES=src/*.cc
OBJECTS=src/init.o src/utility.o src/debug.o src/mutation.o src/thread.o src/main.o src/draw.o
EXECUTABLE=Genetic.out

Genetic.out: $(OBJECTS)
	g++ -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

.PHONY: depend clean cleanall

clean:
	rm -f $(OBJECTS)

cleanall:
	rm -f $(EXECUTABLE) $(OBJECTS)
