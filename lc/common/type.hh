#ifndef LORD_LC_COMMON_TYPE_HH
#define LORD_LC_COMMON_TYPE_HH

#define LORD_LC_COMMON_TYPE_TYPEKINDS\
	X(UNKNOWN)\
	X(i64)\
	X(STRUCT)\
	\
	X(LAST)

enum TypeKind {
	#define X(tk) TK_##tk,
		LORD_LC_COMMON_TYPE_TYPEKINDS
	#undef X
};

static const char *TypeKind_str[] = {
	#define X(tk) #tk,
		LORD_LC_COMMON_TYPE_TYPEKINDS
	#undef X
};

struct Type {
	TypeKind kind = TK_UNKNOWN;
	std::string name = "";

	Type();
	Type(Node *ref);

	void print();
};

#endif
