CC=g++
CFLAGS=-c -Wall  -pthread -std=c++0x
LDFLAGS= -lwiringPi
SOURCES=skynet.cpp wireless.cpp nrf24l01.c nrf24l01_interface.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=skynet_2.0
LIBS = -lwiringPi


all: $(SOURCES) $(EXECUTABLE) 
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $< -o  $@