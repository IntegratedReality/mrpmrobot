TARGET	= main
INCLUDES = /usr/include/eigen3 /usr/include/oscpack
LDFLAGS = -lwiringPi 
NOMAKEDIR = .git%
BJDIR = objs

GCC = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wconversion

CPPS = $(shell find * -name "*.cpp")
SRCS = $(filter-out $(NOMAKEDIR), $(CPPS))
DIRS = $(dir $(SRCS))
BINDERS = $(addprefix $(OBJDIR)/, $(DIRS))

OBJS = $(addprefix $(OBJDIR)/. $patsubst %,.cpp, %.o, $(SRCS))
DEPS = $(OBJS:.o=.d)
TILS = $(patsubst %.cpp, %.cpp~, $(SRCS))

ifeq "$(strip $OBJDIR))" ""
	OBJDIR = .
endif

ifeq "$(strip $DIRS))" ""
	OBJDIR = .
endif

all: $(ONJS) $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	$(GCC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	$(GCC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	@rm -rf $(TARGET) $(TILS) $(OBJDIR)

-include $(DEPS)

