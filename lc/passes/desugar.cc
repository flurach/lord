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

	m.fns[n[0][0].val] = Fn();
	f = &m.fns[n[0][0].val];

	// argument types
	auto& args = n[1];
	for (size_t i = 0; i < args.size(); i++) {
		auto arg_token = args[i].token;

		if (arg_token == T_SYM) {
			auto sym = args[i];
			auto none = Node(sym.range, T_NONE);

			auto t = Node(none.range, T_COLN);
			t.push(sym);
			t.push(none);

			args[i] = t;
		}

		// TODO pass type size
		f->make_arg(args[i][0].val, 8);
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
	if (n[0].token != T_COLN) {
		auto t = Node(n[0].range, T_COLN);
		t.push(n[0]);
		t.push(Node(n[0].range, T_NONE));
		n[0] = t;
	}

	f->make_local(n[0][0].val, 8);
}

void DesugarVisitor::visit_CALL(Node& n)
{
	bool in_locals = (f->locals.find(n[0].val) != f->locals.end());
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
