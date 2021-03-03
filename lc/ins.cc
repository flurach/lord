#include "ins.hh"
#include "lc.hh"

std::ostream& operator<<(std::ostream& stream, const Ins::Mem& self)
{
	switch (self.type) {
        case Ins::MT_LIT:
		return stream << "$" << self.value;

        case Ins::MT_REG:
		return stream
			<< "%r" << self.index
			<< "(" << self.size << ")";

        case Ins::MT_LABEL:
		return stream << "." << self.value;

	case Ins::MT_STACK:
		return stream << "(%sp -" << self.index << ")";
        }
}

std::ostream& operator<<(std::ostream& stream, const Ins::Ins& self)
{
	switch (self.type) {
	case Ins::IT_LABEL:
		return stream
			<< "Label { "
			<< "name = " << '"' << self.name << "\" "
			<< "frame_size = " << self.frame_size
			<< " }";

	case Ins::IT_ARG:
		return stream
			<< "Arg { "
			<< "from = " << self.ops[0] << ", "
			<< "to = " << self.ops[1]
			<< " }";

	case Ins::IT_ADD:
		return stream
			<< "Add { "
			<< "left = " << self.ops[0] << ", "
			<< "right = " << self.ops[1] << ", "
			<< "into = " << self.ops[2]
			<< " }";

	case Ins::IT_SUB:
		return stream
			<< "Sub { "
			<< "left = " << self.ops[0] << ", "
			<< "right = " << self.ops[1] << ", "
			<< "into = " << self.ops[2]
			<< " }";

	case Ins::IT_MUL:
		return stream
			<< "Mul { "
			<< "left = " << self.ops[0] << ", "
			<< "right = " << self.ops[1] << ", "
			<< "into = " << self.ops[2]
			<< " }";

	case Ins::IT_DIV:
		return stream
			<< "Div { "
			<< "left = " << self.ops[0] << ", "
			<< "right = " << self.ops[1] << ", "
			<< "into = " << self.ops[2]
			<< " }";

	case Ins::IT_MOD:
		return stream
			<< "Mod { "
			<< "left = " << self.ops[0] << ", "
			<< "right = " << self.ops[1] << ", "
			<< "into = " << self.ops[2]
			<< " }";

	case Ins::IT_MOV:
		return stream
			<< "Mov { "
			<< "from = " << self.ops[0] << ", "
			<< "to = " << self.ops[1]
			<< " }";

	case Ins::IT_CALL:
		return stream
			<< "Call { "
			<< "fn = " << self.name
			<< " }";

	case Ins::IT_RET:
		return stream
			<< "Ret { "
			<< "value = " << self.ops[0]
			<< " } ";

	}
}
