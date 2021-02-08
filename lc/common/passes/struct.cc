#include "lc.hh"

StructVisitor::StructVisitor(Module *m)
	: Visitor(m)
{
}

void StructVisitor::visit_STRUCT(Node *n)
{
	auto s = new Struct(n);
	m->typemgr.make(new TypeStruct(m, s));
	m->structmgr.add(s);
}
