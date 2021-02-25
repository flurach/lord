#include "lc.hh"

void GenVisitor(Module& m, Node& n)
{
	switch (n.token) {

	case T_FN: {
		m.ins.push_back(Ins::Label { .name = n.val });

		// visit body
		GenVisitor(m, n[1]);
		break;
	}

	case T_ADD: {
		GenVisitor(m, n[0]);
		GenVisitor(m, n[1]);
		m.ins.push_back(Ins::Add {
			.left = Ins::Register { .index = n[0].reg_index, .size = n[0].reg_size },
			.right = Ins::Register { .index = n[1].reg_index, .size = n[1].reg_size },
			.into = Ins::Register { .index = n.reg_index, .size = n.reg_size }
		});
		break;
	}

	case T_SUB: {
		GenVisitor(m, n[0]);
		GenVisitor(m, n[1]);
		m.ins.push_back(Ins::Sub {
			.left = Ins::Register { .index = n[0].reg_index, .size = n[0].reg_size },
			.right = Ins::Register { .index = n[1].reg_index, .size = n[1].reg_size },
			.into = Ins::Register { .index = n.reg_index, .size = n.reg_size }
		});
		break;
	}

	case T_MUL: {
		GenVisitor(m, n[0]);
		GenVisitor(m, n[1]);
		m.ins.push_back(Ins::Mul {
			.left = Ins::Register { .index = n[0].reg_index, .size = n[0].reg_size },
			.right = Ins::Register { .index = n[1].reg_index, .size = n[1].reg_size },
			.into = Ins::Register { .index = n.reg_index, .size = n.reg_size }
		});
		break;
	}

	case T_DIV: {
		GenVisitor(m, n[0]);
		GenVisitor(m, n[1]);
		m.ins.push_back(Ins::Div {
			.left = Ins::Register { .index = n[0].reg_index, .size = n[0].reg_size },
			.right = Ins::Register { .index = n[1].reg_index, .size = n[1].reg_size },
			.into = Ins::Register { .index = n.reg_index, .size = n.reg_size }
		});
		break;
	}

	case T_RET:
	case T_IMP_RET: {
		GenVisitor(m, n[0]);
		m.ins.push_back(Ins::Ret {
			.value = Ins::Register { .index = n[0].reg_index, .size = n[0].reg_size },
		});
		break;
	}

	case T_INT: {
		m.ins.push_back(Ins::Mov {
			.from = Ins::Literal { .value = std::stoi(n.val) },
			.to = Ins::Register { .index = n.reg_index, .size = n.reg_size }
		});
		break;
	}

	default: {
		for (auto& child : n)
			GenVisitor(m, child);
		break;
	}

	}
}
