#ifndef LORD_LC_COMMON_COMP_STATE_HH
#define LORD_LC_COMMON_COMP_STATE_HH

#include <vector>
#include "type.hh"
#include "nsmgr.hh"

struct CompState {
	NsMgr ns;
	std::vector<Type*> types;

	void print();
};

#endif
