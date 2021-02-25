#include "lc.hh"

void DesugarVisitor(Module& m, Node& n)
{
	switch (n.token)
	{

	// if function bodies are not T_INDENT
	// their bodies should be wrapped in a T_IMP_RET (implicit return)
	case T_FN: {
		if (n[1].token != T_INDENT) {
			auto ret = Node(n[1].range, T_IMP_RET);
			ret.push(n[1]);
			n[1] = ret;
		}

		DesugarVisitor(m, n[1]);
		break;
	}

	default: {
		for (auto& child : n)
			DesugarVisitor(m, child);
		break;
	}

	}
}
