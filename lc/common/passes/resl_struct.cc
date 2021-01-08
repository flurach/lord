#include "resl_struct.hh"

ReslStructVisitor::ReslStructVisitor(Module *mod)
	: Visitor(mod)
{
}

void ReslStructVisitor::visit_TYPE(Node *n)
{
	mod->structmgr.addStruct(Struct(n->ns[0]->range, n->ns[0]->val));

	for (auto c : n->ns[2]->ns) {
		if (c->token == T_COLN)
			mod->structmgr.addField(Field(c->ns[0]->range, c->ns[0]->val, Type()));
	}
}
