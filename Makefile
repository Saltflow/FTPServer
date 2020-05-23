CC=g++
CFLAGS= -Wall -g
MYSSQLC=$(shell mysql_config --cflags)
LIBS=$(shell mysql_config --libs)
LDFLAGS=-pthread 
SOURCES=main.cpp Connection.cpp database.cpp libftp.cpp fileserve.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=FTPServer


all:     
	$(SOURCES)  $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJECTS) -o $@


clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

start:
	sudo ./FTPServer

tp:
	$(CC) $(SOURCES) $(LDFLAGS) $(CFLAGS) $(MYSQLC) $(LIBS)  -o $(EXECUTABLE)
