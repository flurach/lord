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
	std::cout << "method: " << n->ns[0]->ns[0]->val << "." << n->ns[0]->ns[1]->val << std::endl;
}


void FnNameVisitor::visit_fdef(Node *n)
{
	m->fnmgr.add(Fn(n->range, n->ns[0]->val));
}
