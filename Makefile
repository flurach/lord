# colors
GREEN = \033[1;32m
YELLOW = \033[1;33m
NOCOLOR = \033[0m


# config
CC = clang++
CSTD= -std=c++20
CFLAGS = -Wall -Wextra -Werror
INCS = -I lp -I lc -I cli
LIBS = `pkg-config --libs readline`
LINKS = -Lbin -llp -llc $(LIBS)
OPT = -O3
DBG = -g


# commands
CMD := $(CC) $(CSTD) $(CFLAGS) $(INCS)
ifeq (release,$(firstword $(MAKECMDGOALS)))
	CMD := $(CMD) $(OPT)
else
	CMD := $(CMD) $(DBG)
endif
BIN = $(CMD) $(LINKS) -o
LIB = $(CMD) -shared -o
OBJ = $(CMD) -fPIC -c


# interface
.PHONY: debug release clean
debug: debug_title dirs lp lc cli;
release: release_title dirs lp lc cli;
clean:
	@rm -rf bin
	@echo "Cleaned!"


# modules
.PHONY: cli lc lp
cli: cli_title bin/lord;
lc: lc_title bin/liblc.so;
lp: lp_title bin/liblp.so;


# titles
.PHONY: dirs debug_title release_title cli_title lc_title lp_title
dirs:
	@find cli lc lp -type d -exec bash -c "mkdir -p bin/obj/{}" \;
debug_title:
	@echo -e "$(GREEN)=== Build (debug) ===$(NOCOLOR)"
release_title:
	@echo -e "$(GREEN)=== Build (release) ===$(NOCOLOR)"
cli_title:
	@echo -e "$(YELLOW)=== Building CLI ===$(NOCOLOR)"
lc_title:
	@echo -e "$(YELLOW)=== Building Compiler ===$(NOCOLOR)"
lp_title:
	@echo -e "$(YELLOW)=== Building Parser ===$(NOCOLOR)"


# bins & libs
bin/lord: cli/cli.cc
	$(BIN) bin/lord cli/cli.cc

bin/liblc.so: lc/lc.hh\
              bin/obj/lc/common/node2x.o\
              bin/obj/lc/common/passes/struct_field.o\
              bin/obj/lc/common/passes/struct_name.o\
              bin/obj/lc/common/passes/resl_ns.o\
              bin/obj/lc/common/passes/visitor.o\
              bin/obj/lc/common/compiler.o\
              bin/obj/lc/common/module.o\
              bin/obj/lc/common/nsmgr.o\
              bin/obj/lc/common/structmgr.o\
              bin/obj/lc/common/type.o
	$(LIB) bin/liblc.so `find bin/obj/lc -type f -name '**.o'`

bin/liblp.so: lp/lp.hh lp/token.hh\
              bin/obj/lp/parser.o\
	      bin/obj/lp/node.o\
              bin/obj/lp/lexer.o\
	      bin/obj/lp/helpers.o
	$(LIB) bin/liblp.so bin/obj/lp/*.o


# objects
bin/obj/lc/common/passes/struct_field.o: lc/common/passes/struct_field.hh lc/common/passes/struct_field.cc
	$(OBJ) lc/common/passes/struct_field.cc -o bin/obj/lc/common/passes/struct_field.o

bin/obj/lc/common/passes/struct_name.o: lc/common/passes/struct_name.hh lc/common/passes/struct_name.cc
	$(OBJ) lc/common/passes/struct_name.cc -o bin/obj/lc/common/passes/struct_name.o

bin/obj/lc/common/passes/resl_ns.o: lc/common/passes/resl_ns.hh lc/common/passes/resl_ns.cc
	$(OBJ) lc/common/passes/resl_ns.cc -o bin/obj/lc/common/passes/resl_ns.o

bin/obj/lc/common/passes/visitor.o: lc/common/passes/visitor.hh lc/common/passes/visitor.cc
	$(OBJ) lc/common/passes/visitor.cc -o bin/obj/lc/common/passes/visitor.o

bin/obj/lc/common/node2x.o: lc/common/node2x.hh lc/common/node2x.cc
	$(OBJ) lc/common/node2x.cc -o bin/obj/lc/common/node2x.o

bin/obj/lc/common/compiler.o: lc/common/compiler.hh lc/common/compiler.cc
	$(OBJ) lc/common/compiler.cc -o bin/obj/lc/common/compiler.o

bin/obj/lc/common/module.o: lc/common/module.hh lc/common/module.cc
	$(OBJ) lc/common/module.cc -o bin/obj/lc/common/module.o

bin/obj/lc/common/nsmgr.o: lc/common/nsmgr.hh lc/common/nsmgr.cc
	$(OBJ) lc/common/nsmgr.cc -o bin/obj/lc/common/nsmgr.o

bin/obj/lc/common/structmgr.o: lc/common/structmgr.hh lc/common/structmgr.cc
	$(OBJ) lc/common/structmgr.cc -o bin/obj/lc/common/structmgr.o

bin/obj/lc/common/type.o: lc/common/type.hh lc/common/type.cc
	$(OBJ) lc/common/type.cc -o bin/obj/lc/common/type.o

bin/obj/lp/parser.o: lp/parser.hh lp/parser.cc
	$(OBJ) lp/parser.cc -o bin/obj/lp/parser.o

bin/obj/lp/node.o: lp/node.hh lp/node.cc
	$(OBJ) lp/node.cc -o bin/obj/lp/node.o

bin/obj/lp/lexer.o: lp/lexer.hh lp/lexer.cc
	$(OBJ) lp/lexer.cc -o bin/obj/lp/lexer.o

bin/obj/lp/helpers.o: lp/helpers.hh lp/helpers.cc
	$(OBJ) lp/helpers.cc -o bin/obj/lp/helpers.o
