#ifndef LORD_LC_MODULE_HH
#define LORD_LC_MODULE_HH

struct Module {
	std::string name;
	std::string src = "";
	Node ast;

	std::vector<Ins::Ins> ins;
};

std::optional<Module> load_module(std::string fpath);

#endif
