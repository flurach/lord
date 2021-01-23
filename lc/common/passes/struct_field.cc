#include "lc.hh"

StructFieldVisitor::StructFieldVisitor(Module *m)
	: Visitor(m)
{
}

void StructFieldVisitor::visit_MODULE(Node *n)
{
	(void)n;

	for (auto ss : m->structmgr.structs) {
		s = ss;
		visit(s->ref);
	}
}

void StructFieldVisitor::visit_COLN(Node *n)
{
	s->addField(Field(
		n->ns[0]->range,
		n->ns[0]->val,
		Type(n->ns[1])
	));
}
