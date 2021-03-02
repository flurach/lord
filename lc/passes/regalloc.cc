#include "lc.hh"

void RegAllocVisitorInner(Module& m, Node& n, size_t curr_reg, Fn *f)
{
	switch (n.token)
	{

	// skip these
	case T_TYPEDEC: {
		break;
	}

	case T_FN: {
		f = &m.fns[n.val];
		RegAllocVisitorInner(m, f->type, 0, f);

		int reg_acc = 0;
		for (auto& pair : m.fns[n.val].args)
			RegAllocVisitorInner(m, pair.second, reg_acc++, f);

		RegAllocVisitorInner(m, n[1], curr_reg, f);
		break;
	}

	case T_ARGS: {
		size_t reg_idx = 0;
		for (auto& arg : f->args)
			RegAllocVisitorInner(m, arg.second, reg_idx++, f);
		break;
	}

	case T_ADD:
	case T_SUB:
	case T_MUL:
	case T_DIV:
	case T_DDIV:
	case T_MOD: {
		RegAllocVisitorInner(m, n[0], curr_reg, f);
		RegAllocVisitorInner(m, n[1], curr_reg + 1, f);
		n.reg_index = curr_reg;
		n.reg_size = n[0].reg_size;
		break;
	}

	case T_SYM: {
		if (n.val == "Int") {
			n.token = T_INT;
			RegAllocVisitorInner(m, n, curr_reg, f);
			return;
		}

		RegAllocVisitorInner(m, f->args[n.val], curr_reg, f);
		n.reg_index = f->args[n.val].reg_index;
		n.reg_size = f->args[n.val].reg_size;
		break;
	}

	case T_INT: {
		n.reg_index = curr_reg;
		n.reg_size = 4;
		break;
	}

	default: {
		for (auto& child : n)
			RegAllocVisitorInner(m, child, curr_reg, f);
		break;
	}

	}
}

// wrapper
void RegAllocVisitor(Module& m, Node& n)
{
	RegAllocVisitorInner(m, n, 0, NULL);
}
