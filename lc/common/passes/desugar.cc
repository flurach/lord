#include "lc.hh"

DesugarVisitor::DesugarVisitor(Module *m)
	: Visitor(m)
{
}

void DesugarVisitor::visit_FN(Node *n)
{
	auto last = n->at(3)->pop();
	visit(last);

	auto ret = new Node(last->range, T_RET, "ret");
	ret->push(last);

	n->at(3)->push(ret);
}

void DesugarVisitor::visit_PIPE(Node *n)
{
	auto left = n->at(0);
	auto right = n->at(1);
	right->at(1)->push(left);
	*n = *right;
}
