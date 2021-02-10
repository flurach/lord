#include "lc.hh"

Type *node2type(Module *m, Node *n)
{
	return m->typemgr.make(new Type(TK_ATOMIC, n->val));
}
