# A makefile that canbe used for a generic C++ project in which there is
# a single executable named project3, which depends on all source code files.
# To build or update the executable, or any files that require rebuilding,
# type
#     make
# To remove object files only, type
#     make clean
# To remove object files and the executable, type 
#     make cleanall
#
# Written by Stewart Weiss for CSci 335, Spring 2018, Project 3

CXX       := /usr/bin/g++
CXXFLAGS  += -Wall -g -lm
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
PROG = project3


all: $(PROG) 

.PHONY: clean  cleanall
clean:
	rm -f $(OBJS) 

cleanall:
	rm -f $(OBJS) $(PROG) 

$(PROG): $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) command.o

.cpp:
	$(CXX) -c $@.cpp  $(CXXFLAGS)
