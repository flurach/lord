#ifndef LORD_LC_COMMON_TYPE_HH
#define LORD_LC_COMMON_TYPE_HH

#include <string>
#include <vector>

#define LORC_LC_COMMON_PRIMTYPES\
	\
	X(I8)\
	X(I16)\
	X(I32)\
	X(I64)\
	\
	X(U8)\
	X(U16)\
	X(U32)\
	X(U64)\
	\
	X(F32)\
	X(F64)\
	\
	X(PTR)\
	X(TYPE)\
	\
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

	/* for custom types */
	std::vector<std::string> field_names = {};
	std::vector<Type> field_types = {};

	/* constructor */
	Type(PrimType pt = PT_I64);
};

#endif
