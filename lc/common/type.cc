#include "lc.hh"

Type::Type(Node *ref, TypeKind kind, std::string name)
	: ref(ref), kind(kind), name(name)
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

	if (!std::equal(subtypes.begin(), subtypes.end(), t->subtypes.begin()))
		return false;

	if (fields.size() != t->fields.size())
		return false;

	if (!std::equal(fields.begin(), fields.end(), t->fields.begin()))
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
		subtypes[0]->print();
		std::cout << "[]";
	} else if (kind == TK_STRUCT) {
		std::cout << name << std::endl;
		for (auto pair : fields) {
			x = 0;
			while (x++ < i + 1)
				putchar('\t');

			std::cout << pair.first << ": ";
			if (pair.second->kind == TK_STRUCT)
				std::cout << pair.second->name;
			else
				pair.second->print();
			std::cout << std::endl;
		}
	} else if (kind == TK_FN) {
		size_t arg_count = 0;
		for (auto arg : subtypes) {
			arg->print();
			arg_count++;
			if (arg_count != subtypes.size())
				std::cout << " -> ";
		}
		if (arg_count == 0)
			std::cout << "()";
	}
}
