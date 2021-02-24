#include "lc.hh"

void GenVisitor(Module& m, Node& n)
{
	switch (n.token) {

	case T_FN: {
		m.ins.push_back(Ins::Label {
			.name = n.val,
			.frame_size = 0
		});

		// visit body
		GenVisitor(m, n[1]);
		break;
	}

	case T_ADD: {
		GenVisitor(m, n[0]);
		GenVisitor(m, n[1]);
		m.ins.push_back(Ins::Add {
			.left = Ins::Register { .index = 0, .size = 8 },
			.right = Ins::Register { .index = 0, .size = 8 },
			.into = Ins::Register { .index = 0, .size = 8 }
		});
		break;
	}

	case T_SUB: {
		GenVisitor(m, n[0]);
		GenVisitor(m, n[1]);
		m.ins.push_back(Ins::Add {
			.left = Ins::Register { .index = 0, .size = 8 },
			.right = Ins::Register { .index = 0, .size = 8 },
			.into = Ins::Register { .index = 0, .size = 8 }
		});
		break;
	}

	case T_MUL: {
		GenVisitor(m, n[0]);
		GenVisitor(m, n[1]);
		m.ins.push_back(Ins::Add {
			.left = Ins::Register { .index = 0, .size = 8 },
			.right = Ins::Register { .index = 0, .size = 8 },
			.into = Ins::Register { .index = 0, .size = 8 }
		});
		break;
	}

	case T_DIV: {
		GenVisitor(m, n[0]);
		GenVisitor(m, n[1]);
		m.ins.push_back(Ins::Add {
			.left = Ins::Register { .index = 0, .size = 8 },
			.right = Ins::Register { .index = 0, .size = 8 },
			.into = Ins::Register { .index = 0, .size = 8 }
		});
		break;
	}

	case T_INT: {
		m.ins.push_back(Ins::Mov {
			.from = Ins::Literal { .value = std::stoi(n.val) },
			.to = Ins::Register { .index = 0, .size = 8 }
		});
		break;
	}

	default:
		for (auto& child : n)
			GenVisitor(m, child);
		break;

	}
}
