#ifndef LORD_LC_MODULE_HH
#define LORD_LC_MODULE_HH

struct Constraint {
	Range range;
	Node *lhop;
	Node *rhop;

	Constraint(Range range, Node *lhop, Node *rhop);
};

struct Module {
	/* parsed data */
	std::string name;
	std::string src = "";
	Node ast;

	/* analysed data */
	std::map<std::string, Fn> fns;
	std::vector<Constraint> constraints;
	std::vector<Node*> left_over_types;

	/* compiled output */
	std::vector<Ins> ins;

	/* methods */
	~Module();
	bool load_file(std::string fpath);
	void print_analysed();
};

#endif
