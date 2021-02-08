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

void Symgr::print(size_t j)
{
	for (size_t i = 0; i < syms.size(); i++) {
		size_t x = 0;
		while (x++ < j)
			putchar('\t');

		std::cout << syms[i];
		if (auto t = types[i]) {
			std::cout
				<< ": "
				<< t->as_str();
		}
		std::cout << std::endl;
	}
}
