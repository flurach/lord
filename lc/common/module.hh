#ifndef LORD_LC_COMMON_MODULE_HH
#define LORD_LC_COMMON_MODULE_HH

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
	void print();
};

#endif
