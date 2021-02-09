#include "lc.hh"

Type::Type(TypeKind kind, std::string name, std::vector<Type*> subtypes)
	: kind(kind), name(name), subtypes(subtypes)
{
}

bool Type::equals(Type *t)
{
	if (kind != t->kind)
		return false;

	if (name != t->name)
		return false;

	if (subtypes.size() != t->subtypes.size())
		return false;

	for (size_t i = 0; i < subtypes.size(); i++) {
		if (!subtypes[i]->equals(t->subtypes[i]))
			return false;
	}

	return true;
}

void Type::print()
{
	if (kind == TK_ATOMIC || kind == TK_STRUCT) {
		std::cout << name;
	} else if (kind == TK_ARR) {
		subtypes[0]->print();
		std::cout << "[]";
	}
}
