#include "lc.hh"

Type node2type(Module *m, Node *n)
{
	auto builtin = {
		"i8",
		"i16",
		"i32",
		"i64",
		"u8",
		"u16",
		"u32",
		"u64",
		"f32",
		"f64"
	};

	if (n->ns.size() == 0) {
		if (std::find(builtin.begin(), builtin.end(), n->val))
			return Type(PT_BUILTIN, n->val);

		if (auto s = m->structmgr.get(n->val))
			return Type(PT_STRUCT,  s->name);
	}

	else if (n->ns.size() == 2) {
		auto p = new Type();
		*p = node2type(m, n->ns[0]);

		auto arr = Type(PT_ARR, "", p);
		for (auto nn : n->ns[1]->ns)
			arr.size += stoi(nn->ns[1]->val);

		return arr;
	}

	else if (n->ns.size() == 3) {
		auto p = new Type();
		*p = node2type(m, n->ns[1]->ns[0]);
		return Type(PT_PTR, "", p);
	}

	return Type();
}
