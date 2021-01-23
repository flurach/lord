#include "lc.hh"

int Symgr::add(std::string s)
{
	for (size_t i = 0; i < syms.size(); i++) {
		if (syms[i] == s)
			return i;
	}

	syms.push_back(s);
	return syms.size() - 1;
}

int Symgr::get(std::string s)
{
	for (size_t i = 0; i < syms.size(); i++) {
		if (syms[i] == s)
			return i;
	}
	return -1;
}

void Symgr::print(size_t i)
{
	for (auto s : syms) {
		size_t x = 0;
		while (x++ < i)
			putchar('\t');
		std::cout << '\t' << s << std::endl;
	}
}
