# core
#  |  geometry.h
#  |  color.h
#  |  ppm.h
#  |  frame.h
#  |  tga.h
# test
#  |----shader
#  |		|  shader.cpp
#  |		|  shader.h
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
obj = main.o

# $(TARGET) : $(OBJS)
#	$(CXX) $^ -o $@

#$(OBJS):%.o : %.cpp
#	$(CXX) $(CFLAGS) $< -o $@

$(exe):$(obj)
	$(CXX) -o $(exe) $(obj)

$(obj):main.cpp
	$(CXX) -c main.cpp

clean:
	$(DEL) *.exe *.o *.ppm
