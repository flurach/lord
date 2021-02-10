#include "lc.hh"

Type *node2type(Module *m, Node *n)
{
	if (m->structs[n->val])
		return m->structs[n->val];

	return m->typemgr.make_atomic(n->val);
}
