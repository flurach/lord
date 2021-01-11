#include "lc.hh"

StructNameVisitor::StructNameVisitor(Module *m)
	: Visitor(m)
{
}

void StructNameVisitor::visit_STRUCT(Node *n)
{
	auto s = new Struct(n->ns[0]->range, n->ns[0]->val);
	m->structmgr.add(s);
}
