#include "lc.hh"

FnNameVisitor::FnNameVisitor(Module *m)
	: Visitor(m)
{
}

void FnNameVisitor::visit_FN(Node *n)
{
	if (n->ns[0]->token == T_DOT)
		visit_method(n);
	else
		visit_fdef(n);
}

void FnNameVisitor::visit_method(Node *n)
{
	auto struct_name = n->ns[0]->ns[0]->val;
	auto s = m->structmgr.get(struct_name);
	if (s != NULL)
		s->addMethod(new Fn(n));
}


void FnNameVisitor::visit_fdef(Node *n)
{
	m->fnmgr.add(new Fn(n));
}
