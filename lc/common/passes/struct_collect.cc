#include "struct_collect.hh"

StructCollectVisitor::StructCollectVisitor(Compiler *c)
	: Visitor(c)
{
}

void StructCollectVisitor::visit_TYPE(Node *n)
{
	n->id = c->structns.newsym(n->ns[0]->val);
}
