#ifndef LORD_LC_COMMON_COMPILER_HH
#define LORD_LC_COMMON_COMPILER_HH

#include "module.hh"

struct Compiler {
	std::vector<Module> mods = {};
	bool load_mod(std::string fpath);
};

#endif
