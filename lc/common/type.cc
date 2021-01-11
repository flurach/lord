#include "lc.hh"

Type::~Type()
{
	if (sub)
		delete sub;
}

void Type::print()
{
	if (tk == TK_UNKNOWN) {
		std::cout << "{}";
	} else if (tk == TK_STRUCT) {
		std::cout << "struct " << TypeKind_str[tk] << " {}";
	} else if (tk == TK_PTR) {
		std::cout << "[";
		if (sub) sub->print();
		std::cout << "]";
	} else if (tk == TK_ARR) {
		if (sub) sub->print();
		std::cout << "[" << TypeKind_str[tk] << "]";
	} else {
		std::cout << TypeKind_str[tk];
	}
}
