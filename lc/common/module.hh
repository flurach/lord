#ifndef LORD_LC_COMMON_MODULE_HH
#define LORD_LC_COMMON_MODULE_HH

#include "parser.hh"
#include "passes/all.hh"
#include "nsmgr.hh"
#include "structmgr.hh"

struct Compiler;

struct Module {
	Compiler *c = NULL;

	std::string name = "";
	std::string src = "";
	Node *ast = NULL;

	StructMgr structmgr = StructMgr();
	NsMgr nsmgr = NsMgr();

	Module(Compiler *c);
	bool load_file(std::string fpath);
};

#endif
