#include "lc.hh"

void GenVisitorInner(Module& m, Node& n, Fn *f)
{
	switch (n.token) {

	// skip these
	case T_TYPEDEC: {
		break;
	}

	case T_FN: {
		f = &m.fns[n.val];

		// label
		// TODO: include locals here later
		size_t frame_size = 0;
		for (auto& arg : n[0])
			frame_size += arg.reg_size;
		m.ins.push_back({ .type = Ins::IT_LABEL, .name = n.val, .frame_size = frame_size });

		// args
		GenVisitorInner(m, n[0], f);

		// body
		GenVisitorInner(m, n[1], f);

		// return
		auto f = m.fns[n.val];
		m.ins.push_back({ .type = Ins::IT_RET, .ops = {
			{ .type = Ins::MT_REG, .index = f.type.reg_index, .size = f.type.reg_size },
		}});
		break;
	}

	case T_ARGS: {
		size_t idx = 0;
		for (auto& arg : n) {
			idx += arg.reg_size;
			m.ins.push_back({ .type = Ins::IT_ARG, .ops = {
				{ .type = Ins::MT_REG, .index = arg.reg_index, .size = arg.reg_size },
				{ .type = Ins::MT_STACK, .index = idx },
			}});
		}
		break;
	}

	case T_ADD: {
		GenVisitorInner(m, n[0], f);
		GenVisitorInner(m, n[1], f);
		m.ins.push_back({ .type = Ins::IT_ADD, .ops = {
			{ .type = Ins::MT_REG, .index = n[0].reg_index, .size = n[0].reg_size },
			{ .type = Ins::MT_REG, .index = n[1].reg_index, .size = n[1].reg_size },
			{ .type = Ins::MT_REG, .index = n.reg_index, .size = n.reg_size },
		}});
		break;
	}

	case T_SUB: {
		GenVisitorInner(m, n[0], f);
		GenVisitorInner(m, n[1], f);
		m.ins.push_back({ .type = Ins::IT_SUB, .ops = {
			{ .type = Ins::MT_REG, .index = n[0].reg_index, .size = n[0].reg_size },
			{ .type = Ins::MT_REG, .index = n[1].reg_index, .size = n[1].reg_size },
			{ .type = Ins::MT_REG, .index = n.reg_index, .size = n.reg_size },
		}});
		break;
	}

	case T_MUL: {
		GenVisitorInner(m, n[0], f);
		GenVisitorInner(m, n[1], f);
		m.ins.push_back({ .type = Ins::IT_MUL, .ops = {
			{ .type = Ins::MT_REG, .index = n[0].reg_index, .size = n[0].reg_size },
			{ .type = Ins::MT_REG, .index = n[1].reg_index, .size = n[1].reg_size },
			{ .type = Ins::MT_REG, .index = n.reg_index, .size = n.reg_size },
		}});
		break;
	}

	case T_DIV:
	case T_DDIV: {
		GenVisitorInner(m, n[0], f);
		GenVisitorInner(m, n[1], f);
		m.ins.push_back({ .type = Ins::IT_DIV, .ops = {
			{ .type = Ins::MT_REG, .index = n[0].reg_index, .size = n[0].reg_size },
			{ .type = Ins::MT_REG, .index = n[1].reg_index, .size = n[1].reg_size },
			{ .type = Ins::MT_REG, .index = n.reg_index, .size = n.reg_size },
		}});
		break;
	}

	case T_MOD: {
		GenVisitorInner(m, n[0], f);
		GenVisitorInner(m, n[1], f);
		m.ins.push_back({ .type = Ins::IT_MOD, .ops = {
			{ .type = Ins::MT_REG, .index = n[0].reg_index, .size = n[0].reg_size },
			{ .type = Ins::MT_REG, .index = n[1].reg_index, .size = n[1].reg_size },
			{ .type = Ins::MT_REG, .index = n.reg_index, .size = n.reg_size },
		}});
		break;
	}

	case T_SYM: {
		if (f->args.find(n.val) != f->args.end()) {
			size_t arg_idx = 0;
			for (auto& arg : f->args) {
				arg_idx += arg.second.reg_size;
				if (arg.first == n.val)
					break;
			}
			m.ins.push_back({ .type = Ins::IT_MOV, .ops = {
				{ .type = Ins::MT_STACK, .index = arg_idx },
				{ .type = Ins::MT_REG, .index = n.reg_index, .size = n.reg_size },
			}});
		}
		// TODO: add locals here later
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
			GenVisitorInner(m, child, f);
		break;
	}

	}
}

// wrapper
void GenVisitor(Module& m, Node& n)
{
	GenVisitorInner(m, n, NULL);
}
