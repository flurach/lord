#include "lc.hh"

Node *InferVisitor(Module& m, Node& n, Fn *f)
{
	switch (n.token)
	{

	case T_FN: {
		f = &m.fns[n.val];
		// TODO: visit arguments

		auto ret = InferVisitor(m, n[1], f);
		if (ret)
			f->type = *ret;
		return ret;
	}

	case T_ADD:
	case T_SUB:
	case T_MUL:
	case T_DIV:
	case T_DDIV: {
		auto ret = InferVisitor(m, n[0], f);
		InferVisitor(m, n[1], f);
		return ret;
	}

	case T_INT: {
		return new Node(Range {0, 0}, T_INT, "Int");
	}

	default: {
		for (auto& child : n)
			InferVisitor(m, child, f);
		break;
	}

	}

	return NULL;
}
