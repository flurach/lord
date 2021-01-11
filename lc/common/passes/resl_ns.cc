#include "lc.hh"

ReslNsVisitor::ReslNsVisitor(Module *m)
	: Visitor(m)
{
}

void ReslNsVisitor::visit_FN(Node *n)
{
	m->nsmgr.ascend(n->ns[0]->val);
	visit_args(n->ns[1]);
	visit(n->ns[3]);
	m->nsmgr.descend();
}

void ReslNsVisitor::visit_args(Node *n)
{
	for (auto nn : n->ns)
		nn->id = m->nsmgr.newsym(nn->val);
}

void ReslNsVisitor::visit_STRUCT(Node *n)
{
	(void)n;
}

void ReslNsVisitor::visit_EQ(Node *n)
{
	if (n->ns[0]->token == T_SYM)
		n->ns[0]->id = m->nsmgr.newsym(n->ns[0]->val);
	else
		visit(n->ns[0]);
	visit(n->ns[1]);
}

void ReslNsVisitor::visit_SYM(Node *n)
{
	n->id = m->nsmgr.getsym(n->val);
}

void ReslNsVisitor::visit_COLN(Node *n)
{
	n->ns[0]->id = m->nsmgr.newsym(n->ns[0]->val);
	visit(n->ns[1]);
}
