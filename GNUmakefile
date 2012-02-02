CFLAGS := -O0 -Wall -g
CXXFLAGS := $(CFLAGS)

PROGRAMS := $(subst .c,,$(wildcard *.c)) $(subst .cc,,$(wildcard *.cc))

.PHONY: all clean
all: $(PROGRAMS)
clean:
	rm -f $(PROGRAMS)
