CC=g++
CFLAGS=-c -Wall -g
MYSSQLC=$(shell mysql_config --cflags)
LIBS = $(shell mysql_config --libs)
LDFLAGS=-pthread 
SOURCES=main.cpp Connection.cpp database.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=FTPServer


all:     
	$(SOURCES)  $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(MYSSQLC) $(LIBS)  $(OBJECTS) -o $@


clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

start:
	sudo ./FTPServer
