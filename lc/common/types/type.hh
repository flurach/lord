#ifndef LORD_LC_COMMON_TYPES_TYPE_HH
#define LORD_LC_COMMON_TYPES_TYPE_HH

#define LORD_LC_COMMON_TYPES_TYPE_TYPEKINDS\
	X(UNKNOWN)\
	X(BUILTIN)\
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

class Type {
public:
	TypeKind kind = TK_UNKNOWN;
	std::vector<Type*> subtypes = {};

public:
	virtual ~Type() {}

	virtual size_t byte_size() { return 0; }
	virtual std::string as_str() { return "[unknown]"; }
};

#endif
