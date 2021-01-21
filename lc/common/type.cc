#include "lc.hh"

Type::Type()
{
}

Type::Type(Node *ref)
{
	if (ref->token == T_SYM) {
		if (ref->val == "i64")
			kind = TK_i64;
		else
			kind = TK_STRUCT;
		name = ref->val;
	}
}

void Type::print()
{
	std::cout << TypeKind_str[kind] << "(" << name << ")" << std::endl;
}
