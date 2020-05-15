CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-pthread
SOURCES=main.cpp Connection.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=FTPServer


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@


clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
