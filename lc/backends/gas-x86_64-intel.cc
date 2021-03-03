#include "lc.hh"
#include <utility>

namespace GasX86_64_Intel {

	// registers
	static const std::map<size_t, std::vector<const char*>> arg_regs = {
		// 64 bit
		std::make_pair(8, std::vector<const char*>{ "rdi", "rsi", "rdx", "rcx", "r8" }),

		// 32 bit
		std::make_pair(4, std::vector<const char*>{ "edi", "esi", "edx", "ecx", "r8d" }),
	};

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

	// mov operators
	static const std::map<size_t, const char*> movops = {
		std::make_pair(8, "cqo"),
		std::make_pair(4, "cdq"),
		std::make_pair(2, "cdq"),
		std::make_pair(1, "cdq"),
	};

	// division operators
	static const std::map<size_t, const char*> divops = {
		std::make_pair(8, "cqo"),
		std::make_pair(4, "cdq"),
		std::make_pair(2, "cdq"),
		std::make_pair(1, "cqo"),
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

		case Ins::MT_STACK:
			return "[%rsp - " + std::to_string(m.index) + "]";
		}
	}

	std::string transpile_single(Ins::Ins i)
	{
		std::string gen = "";

		switch (i.type) {
		case Ins::IT_LABEL:
			gen += i.name + ":\n";
			break;

		case Ins::IT_ARG: {
			auto& m = i.ops[0];
			gen += "\tmov " + mem(i.ops[1]) + ", " + arg_regs.find(m.size)->second[m.index] + "\n";
			break;
		}

		case Ins::IT_CALL:
			gen += "\tcall" + i.name + "\n";
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

		// TODO: refactor this
		case Ins::IT_DIV: {
			auto temp = mem(Ins::Mem { .type = Ins::MT_REG, .index = 0, .size = 8 });
			auto reg = mem(Ins::Mem { .type = Ins::MT_REG, .index = 0, .size = i.ops[0].size });
			auto mem0 = mem(i.ops[0]);
			auto is_eq = (reg != mem0);
			if (is_eq) {
				gen += "\tpush " + temp + "\n";
				gen += "\tmov " + reg + ", " + mem0 + "\n";
			}
			gen += std::string("\t") + divops.find(i.ops[0].size)->second + "\n";
			gen += "\tidiv " + mem(i.ops[1]) + "\n";
			if (is_eq) {
				gen += "\tmov " + mem0 + ", " + reg + "\n";
				gen += "\tpop " + temp + "\n";
			}
			break;
		}

		// TODO: refactor this
		case Ins::IT_MOD: {
			auto temp = mem(Ins::Mem { .type = Ins::MT_REG, .index = 0, .size = 8 });
			auto reg = mem(Ins::Mem { .type = Ins::MT_REG, .index = 0, .size = i.ops[0].size });
			auto mem0 = mem(i.ops[0]);
			auto is_eq = (reg != mem0);
			if (is_eq) {
				gen += "\tpush " + temp + "\n";
				gen += "\tmov " + reg + ", " + mem0 + "\n";
			}
			gen += std::string("\t") + divops.find(i.ops[0].size)->second + "\n";
			gen += "\tidiv " + mem(i.ops[1]) + "\n";

			auto remainder = mem(Ins::Mem { .type = Ins::MT_REG, .index = 3, .size = i.ops[0].size });
			gen += "\tmov " + mem0 + ", " + remainder + "\n";

			if (is_eq)
				gen += "\tpop " + temp + "\n";
			break;
		}

		case Ins::IT_MOV:
			gen += "\tmov " + mem(i.ops[1]) + ", " + mem(i.ops[0]) + "\n";
			break;

		case Ins::IT_RET:
			gen += "\tret\n";
			break;
		}

		return gen;
	}

	std::string transpile(std::vector<Ins::Ins> ins)
	{
		std::string gen =
			".global main\n"
			".section .text\n"
			".intel_syntax noprefix\n\n"
		;

		for (auto& i : ins)
			gen += transpile_single(i);

		return gen;
	}

}
