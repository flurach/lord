#include "lc.hh"

void RegAllocVisitor(Module& m, Node& n, size_t curr_reg)
{
	switch (n.token)
	{

	case T_ADD:
	case T_SUB:
	case T_MUL:
	case T_DIV:
	case T_DDIV: {
		RegAllocVisitor(m, n[0], curr_reg);
		RegAllocVisitor(m, n[1], curr_reg + 1);
		n.reg_index = curr_reg;
		n.reg_size = n[0].reg_size;
		break;
	}

	case T_RET:
	case T_IMP_RET: {
		RegAllocVisitor(m, n[0], curr_reg);
		n.reg_index = curr_reg;
		n.reg_size = n[0].reg_size;
		break;
	}

	case T_INT: {
		n.reg_index = curr_reg;
		n.reg_size = 8;
		break;
	}

	default: {
		for (auto& child : n)
			RegAllocVisitor(m, child, curr_reg);
		break;
	}

	}
}
