# core
#  |  geometry.h
#  |  transformation.h
#  |  color.h
#  |  ppm.h
#  |  object.h
#  |  deepmap.h
#  |  frame.h
#  |  tga.h
# cameras
#  |  camera.h
#  |  orthocamera.h
# shaders
#  |  shader.h
#  |  blinnphong.h
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
obj = shader.o

# $(TARGET) : $(OBJS)
#	$(CXX) $^ -o $@

#$(OBJS):%.o : %.cpp
#	$(CXX) $(CFLAGS) $< -o $@

$(exe):$(obj)
	$(CXX) -o $(exe) $(obj)

$(obj):shader.cpp
	$(CXX) -c shader.cpp

clean:
	$(DEL) *.exe *.o *.ppm
