#include "lc.hh"

StructFieldVisitor::StructFieldVisitor(Module *m)
	: Visitor(m)
{
}

void StructFieldVisitor::visit_STRUCT(Node *n)
{
	s = new Type(TK_STRUCT, n->at(0)->val);
	s = m->typemgr.make(s);

	for (auto f : *n->at(2)) {
		if (f->token != T_COLN)
			return;
		visit_coln(f);
	}
}

void StructFieldVisitor::visit_coln(Node *n)
{
	(*s)[n->at(0)->val] = node2type(m, n->at(1));
}
