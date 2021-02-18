#include "lc.hh"

PostInferVisitor::PostInferVisitor(Module& m)
	: Visitor(m)
{
}

void PostInferVisitor::visit_MODULE(Node& n)
{
	(void)n;
	// TODO implement this
}
