#ifndef LORD_LC_COMMON_NSMGR_HH
#define LORD_LC_COMMON_NSMGR_HH

struct NsMgr {
	std::string ns = "";
	std::vector<std::string> syms = {};

	int newsym(std::string s);
	int getsym(std::string s);

	void ascend(std::string s);
	void descend();

	void print();
};

#endif
