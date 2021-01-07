#include "resl_type.hh"

ReslTypeVisitor::ReslTypeVisitor(CompState *state)
	: Visitor(state)
{
}

void ReslTypeVisitor::visit_TYPE(Node *n)
{
	std::cout << n->ns[0]->val << std::endl;
}
