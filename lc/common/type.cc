#include "lc.hh"

const auto builtin = {
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

Type::Type()
{
}

Type::Type(Node *ref)
{
	if (ref->token == T_SYM) {
		auto i = std::find(builtin.begin(), builtin.end(), ref->val);
		if (i != builtin.end())
			kind = (TypeKind)(builtin.end() - i + 1);
		else
			kind = TK_STRUCT;
		name = ref->val;
	}
}

void Type::print()
{
	std::cout << kind << " : " << name << std::endl;
}
