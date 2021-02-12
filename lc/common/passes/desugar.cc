#include "lc.hh"

DesugarVisitor::DesugarVisitor(Module& m)
	: Visitor(m)
{
}

void DesugarVisitor::visit_PIPE(Node& n)
{
	auto right = n.pop();
	auto left = n.pop();
	right[1].push(left);
	n = right;
}
