#include "lc.hh"

StructVisitor::StructVisitor(Module *m)
	: Visitor(m)
{
}

void StructVisitor::visit_STRUCT(Node *n)
{
	auto s = new Type(TK_STRUCT, n->at(0)->val);
	s = m->typemgr.make(s);
	m->structs[n->at(0)->val] = s;
}
