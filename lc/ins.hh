#ifndef LORD_LC_INS_HH
#define LORD_LC_INS_HH

namespace Ins {

	// memory places
	enum MemType {
		MT_REG,
		MT_LABEL,
		MT_LIT,
		MT_STACK,
	};

	struct Mem {
		MemType type;
		size_t index;
		size_t size;
		int value;
		std::string name;
	};


	// instructions
	enum InsType {
		IT_LABEL,
		IT_ARG,
		IT_ADD,
		IT_SUB,
		IT_MUL,
		IT_DIV,
		IT_MOD,
		IT_MOV,
		IT_CALL,
		IT_RET,
	};

	struct Ins {
		InsType type;
		std::string name;
		size_t frame_size;
		std::vector<Mem> ops;
	};

}

std::ostream& operator<<(std::ostream& stream, const Ins::Mem& self);
std::ostream& operator<<(std::ostream& stream, const Ins::Ins& self);

#endif
