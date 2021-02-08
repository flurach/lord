#include "lc.hh"

Type *node2type(Module *m, Node *n)
{
	if (n->token == T_SYM && n->val == "i64") {
		return m->typemgr.make(new TypeI64());
	}

	return m->typemgr.make(new Type());
}
