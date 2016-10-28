TARGET	= main.bin
INCLUDES = -I/usr/local/include/eigen3 -I/usr/local/include/oscpack -IwiringPi
LDFLAGS = -lwiringPi -loscpack -lpthread
NOMAKEDIR = .git%
OBJDIR = objs

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wconversion

CPPS = $(shell find * -name "*.cpp")
SRCS = $(filter-out $(NOMAKEDIR), $(CPPS))
DIRS = $(dir $(SRCS))
BINDERS = $(addprefix $(OBJDIR)/, $(DIRS))

OBJS = $(addprefix $(OBJDIR)/, $(patsubst %.cpp, %.o, $(SRCS)))
DEPS = $(OBJS:.o=.d)
TILS = $(patsubst %.cpp, %.cpp~, $(SRCS))

.SUFFIXES : .o .cpp
.PHONY: clean

ifeq "$(strip $OBJDIR)" ""
	OBJDIR = .
endif

ifeq "$(strip $DIRS)" ""
	OBJDIR = .
endif

all: $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	-echo $@ | sed -E 's@(.*/).*@\1@' | xargs mkdir -p
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -rf $(TARGET) $(TILS) $(OBJDIR)

-include $(DEPS)

run:
	./main.bin `uname -n | cut -c 7`
