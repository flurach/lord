#include "type.hh"

Type::Type(PrimType pt)
	: pt(pt)
{
}

size_t Type::size()
{
	if (pt != PT_TYPE)
		return PrimType_size[pt];

	size_t s = 0;
	for (auto f : field_types)
		s += f.size();

	return s;
}
