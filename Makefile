# colors
GREEN = \033[1;32m
YELLOW = \033[1;33m
NOCOLOR = \033[0m


# config
CC = clang++
CSTD= -std=c++20
CFLAGS = -Wall -Wextra -Werror
INCS = -I lp -I lc -I cli
LIBS = -lreadline
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
              bin/obj/lc/py/pygen.o\
              bin/obj/lc/common/passes/method_body.o\
              bin/obj/lc/common/passes/fn_and_method.o\
              bin/obj/lc/common/passes/struct_field.o\
              bin/obj/lc/common/passes/struct.o\
              bin/obj/lc/common/passes/desugar.o\
              bin/obj/lc/common/passes/visitor.o\
              bin/obj/lc/common/compiler.o\
              bin/obj/lc/common/module.o\
              bin/obj/lc/common/structmgr.o\
              bin/obj/lc/common/fnmgr.o\
              bin/obj/lc/common/symgr.o\
              bin/obj/lc/common/type.o
	$(LIB) bin/liblc.so `find bin/obj/lc -type f -name '**.o'`

bin/liblp.so: lp/lp.hh lp/token.hh\
              bin/obj/lp/parser.o\
	      bin/obj/lp/node.o\
              bin/obj/lp/lexer.o
	$(LIB) bin/liblp.so bin/obj/lp/*.o


# objects
bin/obj/lc/py/pygen.o: lc/py/pygen.hh lc/py/pygen.cc
	$(OBJ) lc/py/pygen.cc -o bin/obj/lc/py/pygen.o

bin/obj/lc/common/passes/method_body.o: lc/common/passes/method_body.hh lc/common/passes/method_body.cc
	$(OBJ) lc/common/passes/method_body.cc -o bin/obj/lc/common/passes/method_body.o

bin/obj/lc/common/passes/fn_and_method.o: lc/common/passes/fn_and_method.hh lc/common/passes/fn_and_method.cc
	$(OBJ) lc/common/passes/fn_and_method.cc -o bin/obj/lc/common/passes/fn_and_method.o

bin/obj/lc/common/passes/struct_field.o: lc/common/passes/struct_field.hh lc/common/passes/struct_field.cc
	$(OBJ) lc/common/passes/struct_field.cc -o bin/obj/lc/common/passes/struct_field.o

bin/obj/lc/common/passes/struct.o: lc/common/passes/struct.hh lc/common/passes/struct.cc
	$(OBJ) lc/common/passes/struct.cc -o bin/obj/lc/common/passes/struct.o

bin/obj/lc/common/passes/desugar.o: lc/common/passes/desugar.hh lc/common/passes/desugar.cc
	$(OBJ) lc/common/passes/desugar.cc -o bin/obj/lc/common/passes/desugar.o

bin/obj/lc/common/passes/visitor.o: lc/common/passes/visitor.hh lc/common/passes/visitor.cc
	$(OBJ) lc/common/passes/visitor.cc -o bin/obj/lc/common/passes/visitor.o

bin/obj/lc/common/compiler.o: lc/common/compiler.hh lc/common/compiler.cc
	$(OBJ) lc/common/compiler.cc -o bin/obj/lc/common/compiler.o

bin/obj/lc/common/module.o: lc/common/module.hh lc/common/module.cc
	$(OBJ) lc/common/module.cc -o bin/obj/lc/common/module.o

bin/obj/lc/common/structmgr.o: lc/common/structmgr.hh lc/common/structmgr.cc
	$(OBJ) lc/common/structmgr.cc -o bin/obj/lc/common/structmgr.o

bin/obj/lc/common/fnmgr.o: lc/common/fnmgr.hh lc/common/fnmgr.cc
	$(OBJ) lc/common/fnmgr.cc -o bin/obj/lc/common/fnmgr.o

bin/obj/lc/common/symgr.o: lc/common/symgr.hh lc/common/symgr.cc
	$(OBJ) lc/common/symgr.cc -o bin/obj/lc/common/symgr.o

bin/obj/lc/common/type.o: lc/common/type.hh lc/common/type.cc
	$(OBJ) lc/common/type.cc -o bin/obj/lc/common/type.o

bin/obj/lp/parser.o: lp/parser.hh lp/parser.cc
	$(OBJ) lp/parser.cc -o bin/obj/lp/parser.o

bin/obj/lp/node.o: lp/node.hh lp/node.cc
	$(OBJ) lp/node.cc -o bin/obj/lp/node.o

bin/obj/lp/lexer.o: lp/lexer.hh lp/lexer.cc
	$(OBJ) lp/lexer.cc -o bin/obj/lp/lexer.o
