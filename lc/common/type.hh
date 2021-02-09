#ifndef LORD_LC_COMMON_TYPES_TYPE_HH
#define LORD_LC_COMMON_TYPES_TYPE_HH

#define LORD_LC_COMMON_TYPES_TYPE_TYPEKINDS\
	X(ATOMIC)\
	X(ARR)\
	X(STRUCT)\
	\
	X(LAST)

enum TypeKind {
	#define X(tk) TK_##tk,
		LORD_LC_COMMON_TYPES_TYPE_TYPEKINDS
	#undef X
};

static const char *TypeKind_str[] = {
	#define X(tk) #tk,
		LORD_LC_COMMON_TYPES_TYPE_TYPEKINDS
	#undef X
};

struct Module;
struct Struct;

struct Type {
	TypeKind kind;
	std::string name = "";
	std::vector<Type*> subtypes = {};

	Type(TypeKind kind, std::string name, std::vector<Type*> subtypes = {});
	bool equals(Type *t);
	void print();
};

#endif
