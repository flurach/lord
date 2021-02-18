#ifndef LORD_LC_COMPILER_HH
#define LORD_LC_COMPILER_HH

struct Compiler {
	// backend to compile into
	// by default it generates GAS x86_64 for now
	std::string backend = "gas-x86_64";

	// modules imported
	// this ensures no re-imports
	std::vector<Module> mods;

	// modules use this to import other modules,
	// this method is meant to be parallel,
	// but is sequential for the moment.
	Module *load_mod(std::string fpath, std::string name = "__main__");

	// this tells each module to generate assembly
	// depending on the backend specified above.
	// returns them concatinated afterwards.
	std::string compile();

	// this prints out the gathered data from modules.
	// rather effectful, but this function is of great help.
	void analyze();
};

#endif
