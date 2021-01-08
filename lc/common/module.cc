#include "module.hh"

Module::Module(std::string name)
	: name(name)
{
}

void Module::print()
{
	std::cout << "NAMES:" << std::endl;
	ns.print();

	std::cout << "STRUCTS:" << std::endl;
	structmgr.print();
}
