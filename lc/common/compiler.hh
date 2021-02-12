#ifndef LORD_LC_COMMON_COMPILER_HH
#define LORD_LC_COMMON_COMPILER_HH

struct Compiler {
	std::vector<Module> mods;

	Module *load_mod(std::string fpath, std::string name = "__main__");

	void print();
};

#endif
