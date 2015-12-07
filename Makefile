CC=g++
CXXFLAGS=-std=c++11 -pthread $(DEBUG_FLAGS) -Wall `pkg-config --cflags gtk+-3.0`
LDFLAGS=-std=c++11 -pthread -export-dynamic `pkg-config --libs gtk+-3.0`
SOURCES=src/*.cc
OBJECTS=src/init.o src/utility.o src/debug.o src/mutation.o src/thread.o src/main.o
EXECUTABLE=Genetic.out

Genetic.out: $(OBJECTS)
	g++ -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

-include dependencies

.PHONY: depend clean cleanall

depend:
	g++ -MM $(SOURCES) > dependencies

clean:
	rm -f $(OBJECTS)

cleanall:
	rm -f $(EXECUTABLE) $(OBJECTS)
