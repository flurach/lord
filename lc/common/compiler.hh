#ifndef LORD_LC_COMMON_COMPILER_HH
#define LORD_LC_COMMON_COMPILER_HH

struct Compiler {
	std::vector<Module*> mods = {};

	~Compiler();

	Module *load_main(std::string fpath);
	Module *load_mod(std::string fpath);
	void print();
};

#endif
