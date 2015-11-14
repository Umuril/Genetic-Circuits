CC=g++
CXXFLAGS=-std=c++11 -pthread
LDFLAGS=-std=c++11 -pthread
SOURCES=*.cc
OBJECTS=init.o utility.o debug.o mutation.o thread.o main.o
EXECUTABLE=Genetic.out

Genetic.out: $(OBJECTS)
	g++ $(CXXFLAGS) -o Genetic.out $(OBJECTS)

-include dependencies

.PHONY: build depend clean cleanall

depend:
	g++ -MM $(CXXFLAGS) $(SOURCES) > dependencies

clean:
	rm -f $(OBJECTS)

cleanall:
	rm -f $(EXECUTABLE) $(OBJECTS)
