#include "lc.hh"

TypeArr::TypeArr(Type *subtype)
{
	subtypes.push_back(subtype);
}

std::string TypeArr::as_str()
{
	return subtypes[0]->as_str() + "[]";
}
