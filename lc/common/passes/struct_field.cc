#include "lc.hh"

StructFieldVisitor::StructFieldVisitor(Module *m)
	: Visitor(m)
{
}

void StructFieldVisitor::visit_STRUCT(Node *n)
{
	if (!m->structs[n->at(0)->val])
		return;
	s = m->structs[n->at(0)->val];

	for (auto f : *n->at(2)) {
		if (f->token != T_COLN)
			continue;
		visit_coln(f);
	}
}

void StructFieldVisitor::visit_coln(Node *n)
{
	s->fields[n->at(0)->val] = node2type(m, n->at(1));
}
