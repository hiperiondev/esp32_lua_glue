# makefile for Lua compiler

LUA= ../components/lua401

INCS= -I.. -I$(LUA)/include -I$(LUA)/src
OBJS= dump.o luac.o opt.o print.o stubs.o
SRCS= dump.c luac.c opt.c print.c stubs.c luac.h print.h

T= $(BIN)/luac

all: $T

$T: $(OBJS)
	gcc -o $@ $(OBJS) -L$(LIB) -I$(LUA)/include -I$(LUA)/src

clean:
	rm -f $(OBJS) $T

co:
	co -q -f -M $(SRCS)

klean:	clean
	rm -f $(SRCS)
