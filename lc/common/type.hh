#ifndef LORD_LC_COMMON_TYPES_TYPE_HH
#define LORD_LC_COMMON_TYPES_TYPE_HH

#define LORD_LC_COMMON_TYPES_TYPE_TYPEKINDS\
	X(ATOMIC)\
	X(ARR)\
	X(STRUCT)\
	X(FN)\
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

struct Type {

	// an optional reference
	Node *ref = NULL;

	// what kind of type this thing is
	TypeKind kind;

	// atomic types
	std::string name;

	// ADTs & functions
	std::vector<Type*> subtypes;

	// structs
	std::map<std::string, Type*> fields;

	// constructor
	Type(Node *ref, TypeKind kind, std::string name);

	// check equality
	bool equals(Type *t);

	// debug
	void print(size_t i = 0);

};

#endif
