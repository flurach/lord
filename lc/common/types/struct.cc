#include "lc.hh"

TypeStruct::TypeStruct(Module *m, Struct *s)
	: m(m), s(s)
{
}

size_t TypeStruct::byte_size()
{
	size_t sum = 0;
	for (auto f : s->fields)
		sum += f.type->byte_size();
	return sum;
}

std::string TypeStruct::as_str()
{
	return s->name;
}
