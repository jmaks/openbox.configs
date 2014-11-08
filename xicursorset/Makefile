CFLAGS := -ansi -Wall -pedantic
CFLAGS += -ggdb
CFLAGS += $(shell pkg-config --cflags x11 xi xcursor)

LDLIBS := $(shell pkg-config --libs x11 xi xcursor)

all: xicursorset

clean:
	rm -f xicursorset *.o
