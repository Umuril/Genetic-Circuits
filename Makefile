CC=g++
CXXFLAGS=-std=c++11 -pthread -Wall
LDFLAGS=-std=c++11 -pthread
SOURCES=src/*.cc
OBJECTS=src/init.o src/utility.o src/debug.o src/mutation.o src/thread.o src/main.o
EXECUTABLE=Genetic.out

Genetic.out: $(OBJECTS)
	g++ $(CXXFLAGS) -o Genetic.out $(OBJECTS)

.PHONY: build depend clean cleanall

clean:
	rm -f $(OBJECTS)

cleanall:
	rm -f $(EXECUTABLE) $(OBJECTS)
