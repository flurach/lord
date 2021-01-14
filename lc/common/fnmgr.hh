#ifndef LORD_LC_COMMON_FNMGR_HH
#define LORD_LC_COMMON_FNMGR_HH

struct Fn {
	/* known data */
	Range defined_at;

	/* collected data */
	std::string name = "";
	// std::vector<Field> fields; // ARGUMENTS

	Fn(Range r, std::string n);

	void print();
};

struct FnMgr {
	std::vector<Fn> fns;
	void add(Fn f);
	void print();
};

#endif
