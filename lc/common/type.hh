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

class Type : public std::map<std::string, Type*> {
public:
	TypeKind kind;
	std::string name;

	Type(TypeKind kind, std::string name = "");
	bool equals(Type *t);
	void print(size_t i = 0);
};

#endif
