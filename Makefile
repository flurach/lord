# config
CC = clang++
CSTD= -std=c++20
CFLAGS = -Wall -Wextra -Werror
INCS = -I lp -I lc -I cli
LIBS = `pkg-config --libs readline`
LINKS = -Lbin -llp $(LIBS)
DBG = -g


# commands
CMD := $(CC) $(CSTD) $(CFLAGS) $(INCS)
BIN = $(CMD) $(LINKS) -o
LIB = $(CMD) -shared -o
OBJ = $(CMD) -fPIC -c


# release
ifneq (release,$(firstword $(MAKECMDGOALS)))
	CMD := $(CMD) $(DBG)
endif


# interface
all: dirs bin/lord
	@echo "=== Build (debug) Successful ==="

.PHONY: clean
clean:
	rm -rf bin


# modules
dirs:
	@mkdir -p bin/obj/lc bin/obj/lp bin/obj/cli

bin/lord: bin/liblp.so
	@echo "=== Building CLI ==="
	$(BIN) bin/lord cli/cli.cc

bin/liblc.so:
	@echo "=== Building Compiler ==="
	$(LIB) bin/lc.so lc/*.o

bin/liblp.so: lp/lp.hh bin/obj/lp/parser.o bin/obj/lp/node.o bin/obj/lp/lexer.o bin/obj/lp/helpers.o
	@echo "=== Building Parser ==="
	$(LIB) bin/liblp.so bin/obj/lp/*.o


# objects
bin/obj/lp/parser.o: lp/parser.hh lp/parser.cc
	$(OBJ) lp/parser.cc -o bin/obj/lp/parser.o

bin/obj/lp/node.o: lp/node.hh lp/node.cc
	$(OBJ) lp/node.cc -o bin/obj/lp/node.o

bin/obj/lp/lexer.o: lp/lexer.hh lp/lexer.cc
	$(OBJ) lp/lexer.cc -o bin/obj/lp/lexer.o

bin/obj/lp/helpers.o: lp/helpers.hh lp/helpers.cc
	$(OBJ) lp/helpers.cc -o bin/obj/lp/helpers.o
