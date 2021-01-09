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

	std::cout << Token_str[n->token] << std::endl;

	if (n->token == T_SYM) {
		if (std::find(builtin.begin(), builtin.end(), n->val))
			return Type(PT_BUILTIN, n->val);

		if (auto s = m->structmgr.get(n->val))
			return Type(PT_STRUCT,  s->name);
	} else if (n->token == T_TYPEANNO) {
		if (n->ns[0]->token == T_LBRC) {
			auto p = new Type();
			*p = node2type(m, n->ns[1]);
			p->print();
			return Type(PT_PTR, "", p);
		}
	}

	return Type();
}
