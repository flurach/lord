#ifndef LORD_LC_COMMON_TYPE_HH
#define LORD_LC_COMMON_TYPE_HH

#include <string>
#include <vector>

#define LORC_LC_COMMON_PRIMTYPES\
	\
	X(I8, 8)\
	X(I16, 16)\
	X(I32, 32)\
	X(I64, 64)\
	\
	X(U8, 8)\
	X(U16, 16)\
	X(U32, 32)\
	X(U64, 64)\
	\
	X(F32, 32)\
	X(F64, 64)\
	\
	X(PTR, 8)\
	X(TYPE, 0)\
	\
	X(LAST, 0)

enum PrimType {
	#define X(pt, sz) PT_##pt,
		LORC_LC_COMMON_PRIMTYPES
	#undef X
};

static const size_t PrimType_size[] = {
	#define X(pt, sz) sz,
		LORC_LC_COMMON_PRIMTYPES
	#undef X
};

static const char *PrimType_str[] = {
	#define X(pt, sz) #pt,
		LORC_LC_COMMON_PRIMTYPES
	#undef X
};

struct Type {
	PrimType pt;

	/* for custom types */
	std::vector<std::string> field_names = {};
	std::vector<Type> field_types = {};

	/* constructor */
	Type(PrimType pt = PT_I64);

	/* methods */
	size_t size();
};

#endif
