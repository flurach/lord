#include "lc.hh"

StructNameVisitor::StructNameVisitor(Module *m)
	: Visitor(m)
{
}

void StructNameVisitor::visit_STRUCT(Node *n)
{
	m->structmgr.add(new Struct(n));
}
