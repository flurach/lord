#include "lc.hh"

StructVisitor::StructVisitor(Module *m)
	: Visitor(m)
{
}

void StructVisitor::visit_STRUCT(Node *n)
{
	auto s = new Struct(n);
	m->structmgr.add(s);
	m->typemgr.make_struct(s);
}
