#ifndef LORD_LC_COMMON_SYMGR_HH
#define LORD_LC_COMMON_SYMGR_HH

struct Symgr {
	std::vector<std::string> syms;

	int add(std::string s);
	int get(std::string s);

	void print(size_t i = 0);
};

#endif
