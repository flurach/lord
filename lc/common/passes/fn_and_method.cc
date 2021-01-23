#include "lc.hh"

FnAndMethodVisitor::FnAndMethodVisitor(Module *m)
	: Visitor(m)
{
}

void FnAndMethodVisitor::visit_FN(Node *n)
{
	if (n->ns[0]->token == T_DOT)
		visit_method(n);
	else
		visit_fdef(n);
}

void FnAndMethodVisitor::visit_method(Node *n)
{
	auto struct_name = n->ns[0]->ns[0]->val;
	auto s = m->structmgr.get(struct_name);
	if (s != NULL)
		s->addMethod(new Fn(n));
}


void FnAndMethodVisitor::visit_fdef(Node *n)
{
	m->fnmgr.add(new Fn(n));
}
