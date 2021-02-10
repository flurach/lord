#include "lc.hh"

Type::Type(TypeKind kind, std::string name)
	: kind(kind), name(name)
{
}

bool Type::equals(Type *t)
{
	if (kind != t->kind)
		return false;

	if (name != t->name)
		return false;

	if (size() != t->size())
		return false;

	if (!std::equal(begin(), end(), t->begin()))
		return false;

	return true;
}

void Type::print(size_t i)
{
	size_t x = 0;
	while (x++ < i)
		putchar('\t');

	if (kind == TK_ATOMIC) {
		std::cout << name;
	} else if (kind == TK_ARR) {
		(*this)["subtype"]->print();
		std::cout << "[]";
	} else if (kind == TK_STRUCT) {
		std::cout << name << std::endl;
		for (auto pair : *this) {
			x = 0;
			while (x++ < i + 1)
				putchar('\t');
			std::cout << pair.first << ": ";
			pair.second->print();
			std::cout << std::endl;
		}
	}
}
