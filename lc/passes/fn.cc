#include "lc.hh"

void FnVisitorPre(Module& m, Node& n, Fn *f = NULL)
{
	switch (n.token)
	{

	case T_FN: {
		if (m.fns.find(n.val) == m.fns.end())
			m.fns[n.val] = Fn();
		f = &m.fns[n.val];

		// collect arguments
		FnVisitorPre(m, n[0], f);

		// collect locals
		FnVisitorPre(m, n[1], f);

		break;
	}

	case T_TYPEDEC: {
		if (m.fns.find(n[0].val) == m.fns.end())
			m.fns[n[0].val] = Fn();
		m.fns[n[0].val].type = n[1];
		break;
	}

	case T_ARGS: {
		for (auto& arg : n)
			f->args[arg.val] = Node(arg.range, T_NONE);
		break;
	}

	// TODO: collect locals here
	// case T_LET: {
	// 	break;
	// }

	default: {
		for (auto& child : n)
			FnVisitorPre(m, child, f);
		break;
	}

	}
}

void FnVisitor(Module& m, Node& n)
{
	// firstly, collect functions
	FnVisitorPre(m, n);

	// then if a function has type declaration,
	// copy them over to args, change return type etc.change return type etc.
	for (auto& pair : m.fns) {
		if (pair.second.type.token != T_ARROW)
			continue;

		// copy over args
		size_t arg_idx = 0;
		for (auto& arg_pair : pair.second.args)
			arg_pair.second = pair.second.type[arg_idx++];

		// change return type
		pair.second.type = pair.second.type[pair.second.type.size() - 1];
	}
}
