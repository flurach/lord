#ifndef LORD_LC_COMMON_TYPE_HH
#define LORD_LC_COMMON_TYPE_HH

enum TypeKind {
	TK_UNKNOWN,
	TK_i8,
	TK_i16,
	TK_i32,
	TK_i64,
	TK_u8,
	TK_u16,
	TK_u32,
	TK_u64,
	TK_f32,
	TK_f64,
	TK_STRUCT
};

struct Type {
	TypeKind kind = TK_UNKNOWN;
	std::string name = "";

	Type();
	Type(Node *ref);

	void print();
};

#endif
