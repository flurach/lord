#ifndef LORD_LC_COMMON_TYPE_HH
#define LORD_LC_COMMON_TYPE_HH

#define LORC_LC_COMMON_TYPEKINDS\
	X(UNKNOWN)\
	X(i8)\
	X(i16)\
	X(i32)\
	X(i64)\
	X(u8)\
	X(u16)\
	X(u32)\
	X(u64)\
	X(f32)\
	X(f64)\
	X(STRUCT)\
	X(ARR)\
	X(PTR)\
	X(FNPTR)\
	X(LAST)

enum TypeKind {
	#define X(tk) TK_##tk,
		LORC_LC_COMMON_TYPEKINDS
	#undef X
};

static const char *TypeKind_str[] = {
	#define X(tk) #tk,
		LORC_LC_COMMON_TYPEKINDS
	#undef X
};

struct Type {
	TypeKind tk;
	Type *sub;

	~Type();

	void print();
};

#endif
