CC=g++
CFLAGS=-c -Wall
LDFLAGS= -lwiringPi
SOURCES=wireless.cpp nrf24l01.c nrf24l01_interface.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=wireless
LIBS = -lwiringPi


all: $(SOURCES) $(EXECUTABLE) 
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $< -o  $@