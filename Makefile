CC=g++
CFLAGS=-c -Wall -std=c++11 -pthread
LDFLAGS= -std=c++11 -pthread
SOURCES=main.cc init.cc debug.cc thread.cc utility.cc mutation.cc
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


