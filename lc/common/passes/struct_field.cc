#include "lc.hh"

StructFieldVisitor::StructFieldVisitor(Module *m)
	: Visitor(m)
{
}

void StructFieldVisitor::visit_TYPE(Node *n)
{
	auto s = m->structmgr.get(n->ns[0]->val);

	for (auto nn : n->ns[2]->ns) {
		if (nn->token == T_COLN)
			s->addField(Field(
				nn->ns[0]->range,
				nn->ns[0]->val,
				node2type(m, nn->ns[1])
			));
	}
}
