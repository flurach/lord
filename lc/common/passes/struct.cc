#include "lc.hh"

StructVisitor::StructVisitor(Module *m)
	: Visitor(m)
{
}

void StructVisitor::visit_STRUCT(Node *n)
{
	m->structmgr.add(new Struct(n));
}
