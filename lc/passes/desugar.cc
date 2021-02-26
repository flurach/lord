#include "lc.hh"

void DesugarVisitorInner(Module& m, Node& n, std::set<std::string> fns)
{
	switch (n.token)
	{

	// even symbols are calls in Lord
	// so desugar them to be symbol references
	// if they are not a function
	case T_CALL: {
		auto isnt_fn = fns.find(n[0].val) == fns.end();
		if (isnt_fn) {
			n = n[0];
		} else {
			DesugarVisitorInner(m, n[0], fns);
			DesugarVisitorInner(m, n[1], fns);
		}
		break;
	}

	default: {
		for (auto& child : n)
			DesugarVisitorInner(m, child, fns);
		break;
	}

	}
}

void DesugarVisitor(Module& m, Node& n)
{
	// first of all, collect all functions
	std::set<std::string> fns;
	for (auto& candidate : n) {
		if (candidate.token == T_FN)
			fns.insert(candidate.val);
	}

	// then visit
	DesugarVisitorInner(m, n, fns);
}
