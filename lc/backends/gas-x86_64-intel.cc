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
		if (auto s = std::get_if<Ins::Register>(&m))
			return regs.find(s->size)->second[s->index];
		else if (auto s = std::get_if<Ins::Literal>(&m))
			return std::to_string(s->value);
		else if (auto s = std::get_if<Ins::LabelRef>(&m))
			return s->value;
		return "";
	}

	std::string transpile(std::vector<Ins::Ins> ins)
	{
		std::string gen =
			".global main\n"
			".section .text\n"
			".intel_syntax noprefix\n\n"
		;

		for (auto& i : ins) {
			if (auto s = std::get_if<Ins::Label>(&i))
				gen += s->name + ":\n";
			else if (auto s = std::get_if<Ins::Add>(&i))
				gen += "\tadd " + mem(s->left) + ", " + mem(s->right) + "\n";
			else if (auto s = std::get_if<Ins::Sub>(&i))
				gen += "\tsub " + mem(s->left) + ", " + mem(s->right) + "\n";
			else if (auto s = std::get_if<Ins::Mul>(&i))
				gen += "\timul " + mem(s->left) + ", " + mem(s->right) + "\n";
			else if (auto s = std::get_if<Ins::Div>(&i)) {
				auto reg = mem(Ins::Register { .index = 0, .size = 8 });
				gen +=
					"\tpush " + reg + "\n" +
					"\tmov " + reg + ", " + mem(s->left) + "\n" +
					"\tcqo\n" + // TODO: fix this, this is size dependent
					"\tidiv " + mem(s->right) + "\n" +
					"\tmov " + mem(s->left) + ", " + reg + "\n" +
					"\tpop " + reg + "\n";
			}
			else if (auto s = std::get_if<Ins::Mov>(&i))
				gen += "\tmov " + mem(s->to) + ", " + mem(s->from) + "\n";
			else if (auto s = std::get_if<Ins::Ret>(&i))
				gen += "\tret\n";
		}

		return gen;
	}

}
