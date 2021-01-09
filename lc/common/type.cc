#include "lc.hh"

Type::Type(PrimType pt, std::string name, Type *sub)
	: pt(pt), name(name), sub(sub)
{
}

Type::~Type()
{
}

void Type::print()
{
	if (pt == PT_UNKNOWN) {
		std::cout << "{}";
	} else if (pt == PT_BUILTIN) {
		std::cout << name;
	} else if (pt == PT_STRUCT) {
		std::cout << name << " {}";
	} else if (pt == PT_PTR) {
		std::cout << "[";
		sub->print();
		std::cout << "]";
	} else if (pt == PT_ARR) {
		sub->print();
		std::cout << "[" << name << "]";
	}
}
