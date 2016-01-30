CXXFLAGS = -std=c++11 -Wall -Wextra -Wconversion
LDFLAGS = -lm -lwiringPi 
CXX = g++-4.8
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
MAIN_OUT = osctest.bin
.SUFFIXES: .cpp .o

INCLUDEDIR = /usr/lib
LIBNAME = liboscpack
LIBSONAME = $(LIBNAME).so
LIBFILENAME = $(LIBSONAME).1.0.2

.PHONY: all
all: $(MAIN_OUT)

$(MAIN_OUT): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

.PHONY:clean
clean:
	-rm $(MAIN_OUT) $(OBJS)

