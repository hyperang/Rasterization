# core
#  |  geometry.h
#  |  transformation.h
#  |  color.h
#  |  ppm.h
#  |  frame.h
#  |  object.h
# cameras
#  |  camera.h
#  |  orthocamera.h
# test
#  |----objload
#  |		|  objload.cpp
#  |		|  objload.h
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
obj = objload.o

# $(TARGET) : $(OBJS)
#	$(CXX) $^ -o $@

#$(OBJS):%.o : %.cpp
#	$(CXX) $(CFLAGS) $< -o $@

$(exe):$(obj)
	$(CXX) -o $(exe) $(obj)

$(obj):objload.cpp
	$(CXX) -c objload.cpp

clean:
	$(DEL) *.exe *.o *.ppm
