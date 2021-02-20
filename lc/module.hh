#ifndef LORD_LC_MODULE_HH
#define LORD_LC_MODULE_HH

struct Module {
	/* parsed data */
	std::string name;
	std::string src = "";
	Node ast;

	/* analysed data */
	std::map<std::string, Fn> fns;

	/* compiled output */
	std::vector<Ins> ins;

	/* methods */
	bool load_file(std::string fpath);
	void print_analysed();
};

#endif
