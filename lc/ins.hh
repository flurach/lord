#ifndef LORD_LC_INS_HH
#define LORD_LC_INS_HH

// the four constructs below simply represent this:
// ins ($|:|.L)num(size) ($|:|.L)num(size)

#define LORD_LC_INS_INSOPTYPES\
	X(STR)\
	X(LIT)\
	X(REG)

enum InsOpType {
	#define X(op) IOT_##op,
		LORD_LC_INS_INSOPTYPES
	#undef X
};

static const char *InsOpType_str[] = {
	#define X(op) #op,
		LORD_LC_INS_INSOPTYPES
	#undef X
};

struct InsOp {
	InsOpType type;
	std::string payload;
	int size; // in bytes

	InsOp(InsOpType type, std::string payload = "", int size = 0);
	void print();
};

#define LORD_LC_INS_INSTYPES\
	X(LABEL)\
	X(RET)\
	\
	X(MOV)\
	X(PUSH)\
	X(POP)

enum InsType {
	#define X(op) IT_##op,
		LORD_LC_INS_INSTYPES
	#undef X
};

static const char *InsType_str[] = {
	#define X(op) #op,
		LORD_LC_INS_INSTYPES
	#undef X
};

struct Ins {
	InsType type;
	std::vector<InsOp> ops;

	Ins(InsType type, std::vector<InsOp> ops = {});
	void print();
};

#endif
