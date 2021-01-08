#ifndef LORD_LC_COMMON_COMPILER_HH
#define LORD_LC_COMMON_COMPILER_HH

#include "parser.hh"
#include "type.hh"
#include "nsmgr.hh"
#include "structmgr.hh"

struct Compiler {
	/* parser info */
	std::string src = "";
	Node *ast = NULL;

	/* compiler info */
	NsMgr structns = NsMgr();
	StructMgr structmgr = StructMgr();
	NsMgr symns = NsMgr();

	/* constructor & destructor */
	Compiler();
	~Compiler();

	/* methods */
	bool load_file(std::string fpath);

	/* debugging */
	void print();
};

#endif
