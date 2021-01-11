#include "lc.hh"

Type::~Type()
{
	if (sub)
		delete sub;
}

void Type::print()
{
	if (tk == PT_UNKNOWN) {
		std::cout << "{}";
	} else if (tk == PT_STRUCT) {
		std::cout << "struct " << name << " {}";
	} else if (tk == PT_PTR) {
		std::cout << "[";
		if (sub) sub->print();
		std::cout << "]";
	} else if (tk == PT_ARR) {
		if (sub) sub->print();
		std::cout << "[" << name << "]";
	}

	else if (tk)
}
