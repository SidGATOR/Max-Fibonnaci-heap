#!/bin/bash

CXX:= g++


#compilation flags
ifeq ($(DEBUG),1)
CXXFLAGS += -g
else
CXXFLAGS += -O2
endif

CFLAGS:= -Wall -c -g -std=gnu++0x  $(DEBUG)

#Objects
OBJS:=  maxHASHfib.o 
MAIN:= hashtagcounter.o

#Target
TARGET:= hashtagcounter

#Make it all
all:= hashtagcounter

#Building Executables
$(TARGET) : $(OBJS) $(MAIN) 
	$(CXX) $(OBJS) $(MAIN) -o $(TARGET)

# maxHASHfib.o
maxHASHfib.o : maxHASHfib.cpp maxHASHfib.h hashtagcounter.h
	$(CXX) $(CFLAGS) maxHASHfib.cpp

# hashtagcounter.o
hashtagcounter.o : hashtagcounter.cpp maxHASHfib.h hashtagcounter.h
	$(CXX) $(CFLAGS) hashtagcounter.cpp

#Clean
clean:
	rm -f *.o finalO.txt $(TARGET)
