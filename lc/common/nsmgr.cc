#include "lc.hh"

int NsMgr::newsym(std::string s)
{
	std::string mangled = ns + s;

	for (size_t i = 0; i < syms.size(); i++) {
		if (syms[i] == mangled)
			return i;
	}

	syms.push_back(mangled);
	return syms.size() - 1;
}

int NsMgr::getsym(std::string s)
{
	for (size_t i = 0; i < syms.size(); i++) {
		if (syms[i] == s)
			return i;
	}
	return -1;
}

void NsMgr::ascend(std::string s)
{
	ns += s + '#';
}

void NsMgr::descend()
{
	if (ns.back() == '#') {
		ns.pop_back();
		while (ns.size() && ns.back() != '#')
			ns.pop_back();
		if (ns.size())
			ns.pop_back();
	}
}

void NsMgr::print()
{
	for (size_t i = 0; i < syms.size(); i++)
		std::cout << i << " '" << syms[i] << "'" << std::endl;
}
