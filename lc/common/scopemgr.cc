#include "lc.hh"

void Scope::setType(std::string sym, Type type)
{
	types[sym] = type;
}

void Scope::incMut(std::string sym)
{
	muts[sym] += 1;
}

void Scope::print()
{
	for (auto p : muts) {
		putchar('\t');
		std::cout << p.first << "(" << p.second << ")" << std::endl;
	}
}
