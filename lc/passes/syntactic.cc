#ifndef LORD_LC_PASSES_SYNTACTIC_HH
#define LORD_LC_PASSES_SYNTACTIC_HH

// returns false if is invalid
bool SyntacticVisitor(Module &m, Node& n)
{
	switch (n.token)
	{

	case T_ADD:
	case T_SUB:
	case T_MUL:
	case T_DIV:
	case T_DDIV: {
		if (n.size() == 2)
			return SyntacticVisitor(m, n[0]) && SyntacticVisitor(m, n[1]);

		m.errs.push_back(Err {
			.type = E_FATAL,
			.rng = n.range,
			.msg = "Expected an rval after '" + n.val + "'"
		});
		SyntacticVisitor(m, n[0]);
		return false;
	}

	default: {
		bool ret = true;
		for (auto& child : n)
			ret = ret && SyntacticVisitor(m, child);
		return ret;
	}

	}
}

#endif
