#include "lc.hh"

void FnVisitor(Module& m, Node& n, Fn *f)
{
	switch (n.token)
	{

	case T_FN: {
		m.fns[n.val] = Fn();
		f = &m.fns[n.val];

		// collect arguments
		FnVisitor(m, n[0], f);

		break;
	}

	case T_ARGS: {
		for (auto& arg : n)
			f->args[arg.val] = Node(arg.range, T_NONE);
		break;
	}

	default: {
		for (auto& child : n)
			FnVisitor(m, child, f);
		break;
	}

	}
}
