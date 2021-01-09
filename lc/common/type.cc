#include "lc.hh"

Type::Type(PrimType pt, std::string name, Type *sub)
	: pt(pt), name(name), sub(sub)
{
}

Type::~Type()
{
	if (sub)
		delete sub;
}
