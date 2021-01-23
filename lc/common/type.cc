#include "lc.hh"

Type::Type()
{
}

Type::Type(Struct *structptr)
	: kind(TK_STRUCT), structptr(structptr)
{
}

Type::Type(Module *m, Node *ref)
{
	if (ref->token == T_SYM) {

		/* primivites */
		if (ref->val == "i64")
			kind = TK_i64;

		/* for structs */
		for (auto s : m->structmgr.structs) {
			if (s->name == ref->val) {
				kind = TK_STRUCT;
				structptr = s;
				return;
			}
		}

	}
}

void Type::print()
{
	if (kind == TK_STRUCT)
		std::cout << "struct " << structptr->name << std::endl;
	else
		std::cout << TypeKind_str[kind] << std::endl;
}
