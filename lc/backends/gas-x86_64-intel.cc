#include "lc.hh"

namespace GasX86_64_Intel {

	// registers
	static const std::map<size_t, std::vector<const char*>> regs = {
		// 64 bit
		std::make_pair(8, std::vector<const char*>({ "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" })),

		// 32 bit
		std::make_pair(4, std::vector<const char*>({ "eax", "ebx", "ecx", "edx", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" })),

		// 16 bit
		std::make_pair(2, std::vector<const char*>({ "ax", "bx", "cx", "dx", "si", "di", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w" })),

		// 8 bit
		std::make_pair(1, std::vector<const char*>({ "al", "bl", "cl", "dl", "sil", "dil", "r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b" })),
	};

	std::string mem(Ins::Mem m)
	{
		switch (m.type) {
		case Ins::MT_REG:
			return regs.find(m.size)->second[m.index];

		case Ins::MT_LIT:
			return std::to_string(m.value);

		case Ins::MT_LABEL:
			return m.name;
		}
	}

	std::string transpile(std::vector<Ins::Ins> ins)
	{
		std::string gen =
			".global main\n"
			".section .text\n"
			".intel_syntax noprefix\n\n"
		;

		for (auto& i : ins) {
			switch (i.type) {
			case Ins::IT_LABEL:
				gen += i.name + ":\n";
				break;

			case Ins::IT_ADD:
				gen += "\tadd " + mem(i.ops[0]) + ", " + mem(i.ops[1]) + "\n";
				break;

			case Ins::IT_SUB:
				gen += "\tsub " + mem(i.ops[0]) + ", " + mem(i.ops[1]) + "\n";
				break;

			case Ins::IT_MUL:
				gen += "\timul " + mem(i.ops[0]) + ", " + mem(i.ops[1]) + "\n";
				break;

			case Ins::IT_DIV: {
				auto reg = mem(Ins::Mem { .type = Ins::MT_REG, .index = 0, .size = 8 });
				gen +=
					"\tpush " + reg + "\n" +
					"\tmov " + reg + ", " + mem(i.ops[0]) + "\n" +
					"\tcqo\n" + // TODO: fix this, this is size dependent
					"\tidiv " + mem(i.ops[1]) + "\n" +
					"\tmov " + mem(i.ops[0]) + ", " + reg + "\n" +
					"\tpop " + reg + "\n";
				break;
			}

			case Ins::IT_MOV:
				gen += "\tmov " + mem(i.ops[1]) + ", " + mem(i.ops[0]) + "\n";
				break;

			case Ins::IT_RET:
				gen += "\tret\n";
				break;
			}
		}

		return gen;
	}

}
