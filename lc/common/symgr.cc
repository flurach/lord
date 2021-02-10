#include "lc.hh"

int Symgr::add(std::string s)
{
	auto with_base = base_ns + s;
	for (size_t i = 0; i < syms.size(); i++) {
		if (syms[i] == with_base)
			return i;
	}

	syms.push_back(with_base);
	return syms.size() - 1;
}

int Symgr::get(std::string s)
{
	auto with_base = base_ns + s;
	for (size_t i = 0; i < syms.size(); i++) {
		if (syms[i] == with_base)
			return i;
	}
	return -1;
}

void Symgr::ascend(std::string ns)
{
	base_ns += ns;
	base_ns += "#";
}

void Symgr::descend()
{
	base_ns.pop_back();
	while (base_ns.length() >= 0 && base_ns[base_ns.length() - 1] != '#')
		base_ns.pop_back();
}

void Symgr::print(size_t j)
{
	for (size_t i = 0; i < syms.size(); i++) {
		size_t x = 0;
		while (x++ < j)
			putchar('\t');

		std::cout << syms[i];
		if (auto t = types[i]) {
			std::cout << ": ";
			t->print();
		}
		std::cout << std::endl;
	}
}
