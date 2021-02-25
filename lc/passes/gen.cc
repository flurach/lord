#include "lc.hh"

void GenVisitor(Module& m, Node& n)
{
	switch (n.token) {

	case T_FN: {
		m.ins.push_back({ .type = Ins::IT_LABEL, .name = n.val });

		// visit body
		GenVisitor(m, n[1]);
		break;
	}

	case T_ADD: {
		GenVisitor(m, n[0]);
		GenVisitor(m, n[1]);
		m.ins.push_back({ .type = Ins::IT_ADD, .ops = {
			{ .type = Ins::MT_REG, .index = n[0].reg_index, .size = n[0].reg_size },
			{ .type = Ins::MT_REG, .index = n[1].reg_index, .size = n[1].reg_size },
			{ .type = Ins::MT_REG, .index = n.reg_index, .size = n.reg_size },
		}});
		break;
	}

	case T_SUB: {
		GenVisitor(m, n[0]);
		GenVisitor(m, n[1]);
		m.ins.push_back({ .type = Ins::IT_SUB, .ops = {
			{ .type = Ins::MT_REG, .index = n[0].reg_index, .size = n[0].reg_size },
			{ .type = Ins::MT_REG, .index = n[1].reg_index, .size = n[1].reg_size },
			{ .type = Ins::MT_REG, .index = n.reg_index, .size = n.reg_size },
		}});
		break;
	}

	case T_MUL: {
		GenVisitor(m, n[0]);
		GenVisitor(m, n[1]);
		m.ins.push_back({ .type = Ins::IT_MUL, .ops = {
			{ .type = Ins::MT_REG, .index = n[0].reg_index, .size = n[0].reg_size },
			{ .type = Ins::MT_REG, .index = n[1].reg_index, .size = n[1].reg_size },
			{ .type = Ins::MT_REG, .index = n.reg_index, .size = n.reg_size },
		}});
		break;
	}

	case T_DIV:
	case T_DDIV: {
		GenVisitor(m, n[0]);
		GenVisitor(m, n[1]);
		m.ins.push_back({ .type = Ins::IT_DIV, .ops = {
			{ .type = Ins::MT_REG, .index = n[0].reg_index, .size = n[0].reg_size },
			{ .type = Ins::MT_REG, .index = n[1].reg_index, .size = n[1].reg_size },
			{ .type = Ins::MT_REG, .index = n.reg_index, .size = n.reg_size },
		}});
		break;
	}

	case T_RET:
	case T_IMP_RET: {
		GenVisitor(m, n[0]);
		m.ins.push_back({ .type = Ins::IT_RET, .ops = {
			{ .type = Ins::MT_REG, .index = n[0].reg_index, .size = n[0].reg_size },
		}});
		break;
	}

	case T_INT: {
		m.ins.push_back({ .type = Ins::IT_MOV, .ops = {
			{ .type = Ins::MT_LIT, .value = std::stoi(n.val) },
			{ .type = Ins::MT_REG, .index = n.reg_index, .size = n.reg_size },
		}});
		break;
	}

	default: {
		for (auto& child : n)
			GenVisitor(m, child);
		break;
	}

	}
}
