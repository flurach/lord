#ifndef LORD_LC_COMMON_TYPE_H
#define LORD_LC_COMMON_TYPE_H

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

typedef enum {
	#define X(pt) PT_##pt,
		LORD_LC_COMMON_PRIMTYPES
	#undef
} PrimType;

static const char *PrimType_str[] = {
	#define X(pt) #pt,
		LORD_LC_COMMON_PRIMTYPES
	#undef
};

typedef struct {
	PrimType pt;

} Type;

#endif
