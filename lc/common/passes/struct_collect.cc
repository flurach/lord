#include "lc.hh"

StructCollectVisitor::StructCollectVisitor(Module *m)
	: Visitor(m)
{
}

void StructCollectVisitor::visit_TYPE(Node *n)
{
	n->id = c->structns.newsym(n->ns[0]->val);
}
