#ifndef LORD_LC_INS_HH
#define LORD_LC_INS_HH

namespace Ins {

	// memory places
	struct Register {
		size_t index;
		size_t size;
	};

	struct Literal {
		int value;
	};

	struct LabelRef {
		std::string value;
	};

	using Mem = std::variant<Register, Literal, LabelRef>;


	// instructions
	struct Label {
		std::string name;
	};

	struct Add {
		Mem left;
		Mem right;
		Mem into;
	};

	struct Sub {
		Mem left;
		Mem right;
		Mem into;
	};

	struct Mul {
		Mem left;
		Mem right;
		Mem into;
	};

	struct Div {
		Mem left;
		Mem right;
		Mem into;
	};

	struct Mov {
		Mem from;
		Mem to;
	};

	struct Ret {};

	using Ins = std::variant<
		Label,
		Add,
		Sub,
		Mul,
		Div,
		Mov,
		Ret
	>;

}

std::ostream& operator<<(std::ostream& stream, const Ins::Register& self);
std::ostream& operator<<(std::ostream& stream, const Ins::Literal& self);
std::ostream& operator<<(std::ostream& stream, const Ins::LabelRef& self);
std::ostream& operator<<(std::ostream& stream, const Ins::Mem& self);

std::ostream& operator<<(std::ostream& stream, const Ins::Label& self);
std::ostream& operator<<(std::ostream& stream, const Ins::Add& self);
std::ostream& operator<<(std::ostream& stream, const Ins::Sub& self);
std::ostream& operator<<(std::ostream& stream, const Ins::Mul& self);
std::ostream& operator<<(std::ostream& stream, const Ins::Div& self);
std::ostream& operator<<(std::ostream& stream, const Ins::Mov& self);
std::ostream& operator<<(std::ostream& stream, const Ins::Ret& self);
std::ostream& operator<<(std::ostream& stream, const Ins::Ins& self);

#endif
