#include "resl_ns.hh"

ReslNsVisitor::ReslNsVisitor(CompState *state)
	: Visitor(state)
{
}

void ReslNsVisitor::visit_ADD(Node *n)
{
	(void)n;
	std::cout << "ADD FOUND" << std::endl;
}
