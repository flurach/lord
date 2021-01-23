#ifndef LORD_LC_COMMON_FNMGR_HH
#define LORD_LC_COMMON_FNMGR_HH

struct Fn {
	/* known data */
	Node *ref;

	/* collected data */
	Range defined_at;
	std::string name;
	Symgr symgr;

	Fn(Node *ref);
	void print(size_t i = 0);
};

struct FnMgr {
	std::vector<Fn*> fns;

	~FnMgr();

	void add(Fn *f);
	void print(size_t i = 0);
};

#endif
