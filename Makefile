# colors
GREEN = \033[1;32m
NOCOLOR = \033[0m


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
.PHONY: all clean
all: ld_path dirs lp cli
	@echo -e "$(GREEN)=== Build (debug) Successful ===$(NOCOLOR)"
clean:
	@rm -rf bin
	@echo "Cleaned!"


# modules
.PHONY: cli lc lp
cli: cli_title bin/lord;
lc: lc_title bin/liblc.so;
lp: lp_title bin/liblp.so;


# titles
.PHONY: ld_path dirs cli_title lc_title lp_title
ld_path: export LD_LIBRARY_PATH=bin ;
dirs:
	@mkdir -p bin/obj/lc bin/obj/lp bin/obj/cli
cli_title:
	@echo -e "$(GREEN)=== Building CLI ===$(NOCOLOR)"
lc_title:
	@echo -e "$(GREEN)=== Building Compiler ===$(NOCOLOR)"
lp_title:
	@echo -e "$(GREEN)=== Building Parser ===$(NOCOLOR)"


# bins & libs
bin/lord:
	$(BIN) bin/lord cli/cli.cc

bin/liblc.so:
	$(LIB) bin/lc.so lc/*.o

bin/liblp.so: lp/lp.hh lp/token.hh\
              bin/obj/lp/parser.o bin/obj/lp/node.o\
              bin/obj/lp/lexer.o bin/obj/lp/helpers.o
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
