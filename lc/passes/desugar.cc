#include "lc.hh"

DesugarVisitor::DesugarVisitor(Module& m)
	: Visitor(m)
{
}

void DesugarVisitor::visit_FN(Node& n)
{
	f = &m.fns[n.val];

	// body
	if (n[1].token != T_INDENT) {
		auto body = Node(n[1].range, T_INDENT);
		body.push(n[2]);
		n[1] = body;
	}

	// visit body
	visit(n[1]);
}

void DesugarVisitor::visit_INDENT(Node& n)
{
	if (n.size() == 0)
		return;

	if (n.back().token != T_RET) {
		auto back = n.pop();
		auto ret = Node(back.range, T_RET, "return");
		ret.push(back);
		n.push(ret);
	}

	for (auto& child : n)
		visit(child);
}

void DesugarVisitor::visit_EQ(Node& n)
{
	if (n[0].token == T_SYM)
		locals.insert(n[0].val);
	else if (n[0].token == T_COLN)
		locals.insert(n[0][0].val);

	visit(n[1]);
}

void DesugarVisitor::visit_CALL(Node& n)
{
	bool in_locals = (locals.find(n[0].val) != locals.end());
	bool has_no_args = n[1].size() == 0;

	if (in_locals && has_no_args)
		n = n[0];
	else
		visit(n[1]);
}

void DesugarVisitor::visit_PIPE(Node& n)
{
	auto right = n.pop();
	auto left = n.pop();
	right[1].push(left);
	n = right;
}
