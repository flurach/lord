#ifndef LORD_LC_COMMON_NS_HH
#define LORD_LC_COMMON_NS_HH

#include "node.hh"

struct NsMgr {
	std::string ns = "";
	std::vector<std::string> syms = {};

	int newsym(std::string s);
	int getsym(std::string s);

	void ascend(std::string s);
	void decend();

	void print();
};

#endif
