#include "lc.hh"

Fn::Fn(Range r, std::string n)
	: defined_at(r), name(n)
{
}

void Fn::print()
{
	std::cout << name << ": void" << std::endl;
}

void FnMgr::add(Fn f)
{
	fns.push_back(f);
}

void FnMgr::print()
{
	for (auto fn : fns)
		fn.print();
}
