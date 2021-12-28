# core
#  |  geometry.h
#  |  transformation.h
#  |  color.h
#  |  ppm.h
#  |  frame.h
# test
#  |----linedraw
#  |		|  linedraw.cpp
#  |		|  linedraw.h
#  |		|  makefile

CROSS =  
CC = $(CROSS)gcc
CXX = $(CROSS)g++
DEBUG = 
CFLAGS = $(DEBUG) -Wall -c
RM = rm -rf
DEL = del

# SRCS = $(wildcard ./*.cpp)
# OBJS = $(patsubst %.cpp, %.o, $(SRCS))

# VERSION = 1.0.0.0
# TARGET = test.$(VERSION)

exe = test
obj = linedraw.o

# $(TARGET) : $(OBJS)
#	$(CXX) $^ -o $@

#$(OBJS):%.o : %.cpp
#	$(CXX) $(CFLAGS) $< -o $@

$(exe):$(obj)
	$(CXX) -o $(exe) $(obj)

$(obj):linedraw.cpp
	$(CXX) -c linedraw.cpp

clean:
	$(DEL) *.exe *.o *.ppm
