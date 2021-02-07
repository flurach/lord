#include "lc.hh"

DesugarVisitor::DesugarVisitor(Module *m)
	: Visitor(m)
{
}

void DesugarVisitor::visit_FN(Node *n)
{
	auto fbody = n->at(3);
	visit(fbody);

	if (fbody->back()->token == T_COLN
	 || fbody->back()->token == T_EQ
	 || fbody->back()->token == T_IF) {
		auto ret = new Node(fbody->back()->range, T_RET, "ret");
		fbody->push(ret);
		return;
	}

	auto last = fbody->pop();
	auto ret = new Node(last->range, T_RET, "ret");
	ret->push(last);
	fbody->push(ret);
}

void DesugarVisitor::visit_PIPE(Node *n)
{
	auto left = n->at(0);
	auto right = n->at(1);
	right->at(1)->push(left);
	*n = *right;
}
