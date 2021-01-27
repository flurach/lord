#include "lc.hh"

DesugarVisitor::DesugarVisitor(Module *m)
	: Visitor(m)
{
}

void DesugarVisitor::visit_FN(Node *n)
{
	auto last = n->at(3)->pop();
	auto ret = new Node(last->range, T_RET, "ret");
	ret->push(last);
	n->at(3)->push(ret);
}
