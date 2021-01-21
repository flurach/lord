#ifndef LORD_LC_COMMON_FNMGR_HH
#define LORD_LC_COMMON_FNMGR_HH

struct Fn {
	/* known data */
	Node *ref;

	/* collected data */
	Range defined_at;
	std::string name;
	Scope scope;

	Fn(Node *ref);
	void print();
};

struct FnMgr {
	std::vector<Fn*> fns;

	~FnMgr();

	void add(Fn *f);
	void print();
};

#endif
