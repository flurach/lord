#include "lc.hh"

InferVisitor::InferVisitor(Module& m)
	: Visitor(m)
{
}

void InferVisitor::visit_EQ(Node& n)
{
	if (n[0][1].token != T_NONE)
		return;

	n[0][1] = n[1].toType();
}
