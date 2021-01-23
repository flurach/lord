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

struct Module;
struct Struct;

struct Type {
	TypeKind kind = TK_UNKNOWN;
	Struct *structptr = NULL;

	Type();
	Type(Struct *structptr);
	Type(Module *m, Node *ref);

	void print();
};

#endif
