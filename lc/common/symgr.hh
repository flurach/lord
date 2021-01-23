#ifndef LORD_LC_COMMON_SYMGR_HH
#define LORD_LC_COMMON_SYMGR_HH

struct Symgr {
	std::vector<std::string> syms;
	std::map<int, Type> types;

	int add(std::string s);
	int get(std::string s);

	void print(size_t j = 0);
};

#endif
