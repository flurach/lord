#include "lc.hh"

DesugarVisitor::DesugarVisitor(Module& m)
	: Visitor(m)
{
}

void DesugarVisitor::visit_FN(Node& n)
{
	// return type
	if (n[0].token == T_SYM) {
		auto t = Node(n[0].range, T_COLN);
		t.push(n[0]);
		t.push(Node(n[0].range, T_NONE));
		n[0] = t;
	}

	// argument types
	for (auto& a : n[1]) {
		if (a.token != T_SYM)
			return;

		auto t = Node(n[0].range, T_COLN);
		t.push(a);
		t.push(Node(n[0].range, T_NONE));
		a = t;
	}

	// exceptions for the main function
	if (m.name == "__main__" && n[0][0].val == "main") {
		// return type
		n[0][1] = Node(n[0][1].range, T_SYM, "i64");

		// args
		if (n[1].size() >= 1) {
			auto t = Node(n[1][0].range, T_ARR);
			t.push(Node(t.range, T_SYM, "str"));
			n[1][0][1] = t;
		}
	}

	// body
	if (n[2].token != T_INDENT) {
		auto body = Node(n[2].range, T_INDENT);
		body.push(n[2]);
		n[2] = body;
	}

	// visit body
	visit(n[2]);
}

void DesugarVisitor::visit_INDENT(Node& n)
{
	if (n.size() == 0)
		return;

	auto back = n.pop();
	auto ret = Node(back.range, T_RET, "return");
	ret.push(back);
	n.push(ret);
}

void DesugarVisitor::visit_EQ(Node& n)
{
	if (n[0].token != T_SYM)
		return;

	auto t = Node(n[0].range, T_COLN);
	t.push(n[0]);
	t.push(Node(n[0].range, T_NONE));
	n[0] = t;
}

void DesugarVisitor::visit_PIPE(Node& n)
{
	auto right = n.pop();
	auto left = n.pop();
	right[1].push(left);
	n = right;
}
