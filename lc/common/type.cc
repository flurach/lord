#include "type.hh"

Type::Type(PrimType pt = PT_TYPE, std::string name = "i64", Type *sub = NULL)
	: pt(pt), name(name), sub(sub)
{
}

Type::~Type()
{
	if (sub)
		delete sub;
}
