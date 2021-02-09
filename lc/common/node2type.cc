#include "lc.hh"

Type *node2type(Module *m, Node *n)
{
	if (n->token == T_SYM) {

		// check all structs
		for (auto s : m->structmgr.structs) {
			if (s->name == n->val)
				return m->typemgr.make_struct(s);
		}

	}

	return m->typemgr.make_atomic(n->val);
}
