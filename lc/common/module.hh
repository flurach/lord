#ifndef LORD_LC_COMMON_MODULE_HH
#define LORD_LC_COMMON_MODULE_HH

#include <map>
#include "type.hh"
#include "nsmgr.hh"
#include "structmgr.hh"

struct Module {
	/* general info */
	std::string name;

	/* internal info */
	NsMgr ns = NsMgr();
	StructMgr structmgr = StructMgr();

	Module(std::string name = "");

	void print();
};

#endif
