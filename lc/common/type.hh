#ifndef LORD_LC_COMMON_TYPE_HH
#define LORD_LC_COMMON_TYPE_HH

#define LORC_LC_COMMON_PRIMTYPES\
	X(UNKNOWN)\
	X(BUILTIN)\
	X(STRUCT)\
	X(PTR)\
	X(ARR)\
	X(LAST)

enum PrimType {
	#define X(pt) PT_##pt,
		LORC_LC_COMMON_PRIMTYPES
	#undef X
};

static const char *PrimType_str[] = {
	#define X(pt) #pt,
		LORC_LC_COMMON_PRIMTYPES
	#undef X
};

struct Type {
	PrimType pt;
	std::string name;
	Type *sub;
	size_t size = 0;

	Type(PrimType pt = PT_UNKNOWN, std::string name = "", Type *sub = NULL);
	~Type();

	void print();
};

#endif
