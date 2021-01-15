#include "lc.hh"

StructFieldVisitor::StructFieldVisitor(Module *m)
	: Visitor(m)
{
}

void StructFieldVisitor::visit_STRUCT(Node *n)
{
	auto struct_name = n->ns[0]->val;
	auto fields = n->ns[2]->ns;

	auto s = m->structmgr.get(struct_name);

	for (auto f : fields) {
		if (f->token == T_COLN)
			s->addField(Field(
				f->ns[0]->range,
				f->ns[0]->val,
				Type(f->ns[1])
			));
	}
}
