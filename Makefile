#-*- mode:makefile-gmake; -*-
ROOT = $(shell pwd)
TARGET = csgtool

INCLUDE += -I$(ROOT)/src
SOURCES = $(wildcard $(ROOT)/src/*.c)

OBJS = $(patsubst %.c,%.o,$(SOURCES))
CPPFLAGS = $(OPTCPPFLAGS)
LIBS = -lm -lcsg $(OPTLIBS)
CFLAGS = -g -std=c99 $(INCLUDE) -Wall -Werror $(OPTFLAGS)

ifeq ($(shell uname),Darwin)
LIB_TARGET = libcsg.dylib
else
LIB_TARGET = libcsg.so
endif

.DEFAULT_GOAL = all
all: $(TARGET)

clean:
	make -C tests clean
	rm -rf $(OBJS) $(TARGET) $(TARGET).o $(TARGET).new $(LIB_TARGET)

test:
	@make -C tests clean test

.PHONY: all clean test

$(TARGET): $(TARGET).o $(LIB_TARGET)
	$(CC) $(CFLAGS) $< -L. $(LIBS) -o $@.new
	mv $@.new $@

$(LIB_TARGET): $(OBJS)
	$(CC) -shared $(OBJS) -lm -o $(LIB_TARGET)

%.o: %.c
	$(CC) -fPIC $(CFLAGS) -o $@ -c $^
