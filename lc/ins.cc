#include "lc.hh"

InsOp::InsOp(InsOpType type, std::string payload, int size)
	: type(type), payload(payload), size(size)
{
}

void InsOp::print()
{
	switch (type)
	{
	case IOT_STR:
		std::cout << ".L";
		break;

	case IOT_LIT:
		std::cout << "$";
		break;

	case IOT_REG:
		std::cout << ":";
		break;
	}

	std::cout << payload << "(" << size << ")";
}

Ins::Ins(InsType type, std::vector<InsOp> ops)
	: type(type), ops(ops)
{
}

void Ins::print()
{
	std::cout << InsType_str[type];
	for (auto& op : ops) {
		std::cout << " ";
		op.print();
	}
	std::cout << std::endl;
}
