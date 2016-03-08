CXXFLAGS = -std=c++11 -Wall -Wextra -Wconversion -I /usr/include/eigen3/
LDFLAGS = -lwiringPi 
CXX = g++
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
MAIN_OUT = test_motor.bin
.SUFFIXES: .cpp .o

.PHONY: all
all: $(MAIN_OUT)

$(MAIN_OUT): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

.PHONY:clean
clean:
	-rm $(MAIN_OUT) $(OBJS)

