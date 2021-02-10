#include "lc.hh"

StructVisitor::StructVisitor(Module *m)
	: Visitor(m)
{
}

void StructVisitor::visit_STRUCT(Node *n)
{
	auto t = m->typemgr.make_struct(n, n->at(0)->val);
	m->structs[t->name] = t;
}
