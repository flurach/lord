#ifndef LORD_LC_COMMON_MODULE_HH
#define LORD_LC_COMMON_MODULE_HH

struct Compiler;

struct Module {
	Compiler *c = NULL;

	/* parsed data */
	std::string name;
	std::string src = "";
	Node ast;

	/* constructor */
	Module(Compiler *c, std::string name = "");

	/* methods */
	bool load_file(std::string fpath);

	/* debugging */
	void print();
};

#endif
