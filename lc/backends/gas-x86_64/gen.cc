#include "lc.hh"

std::vector<std::string> regs = {
	"rax",
	"rbx",
	"rcx"
};

GenGasX86_64::GenGasX86_64(Module& m)
	: Visitor(m)
{
}

void GenGasX86_64::visit_MODULE(Node& n)
{
	// compile strings
	buf += "\t.section .rodata\n";
	size_t idx = 0;
	for (auto& s : m.strs) {
		buf += ".S" + std::to_string(idx) + ":\n";
		buf += "\t.string \"" + s + "\"\n";
		idx++;
	}

	// compile instructions
	buf += "\t.text\n";
	buf += "\t.extern puts\n";
	buf += "\t.globl main\n";
	for (auto& thing : n)
		visit(thing);
}

void GenGasX86_64::visit_FN(Node& n)
{
	// store ref
	f = &m.fns[n[0][0].val];

	// create label
	buf += n[0][0].val + ":\n";

	// create stack frame
	buf += "\tpushq %rbp\n";
	buf += "\tmovq %rsp, %rbp\n";

	// visit body
	visit(n[2]);

	// if last op is not return, return yourself
	if (n[2].size()) {
		if (n[2].back().token != T_RET) {
			buf += "\tpopq %rbp\n";
			buf += "\tret\n";
		}
	}
}

void GenGasX86_64::visit_RET(Node& n)
{
	// eval what to return
	visit(n[0]);

	// return
	buf += "\tpopq %rbp\n";
	buf += "\tret\n";
}

void GenGasX86_64::visit_CALL(Node& n)
{
	// load arguments to stack
	size_t arg = 0;
	for (auto& ref : f->args) {
		auto pair = f->get_local(ref.first);
		buf += "\tmovq %" + regs[arg] + ", ";
		buf += "-" + std::to_string(pair.first + pair.second) + "(%rbp)\n";
		arg++;
	}
	// eval arguments
	visit(n[1]);

	// call function
	buf += "\tcall " + n[0].val;
	if (m.fns[n[0].val].plt)
		buf +="@PLT";
	buf += '\n';
}

void GenGasX86_64::visit_ADD(Node& n)
{
	visit(n[0]);
	buf += "\tpushq %rax\n";
	visit(n[1]);
	buf += "\tpopq %rbx\n";
	buf += "\taddq %rbx, %rax\n";
}

void GenGasX86_64::visit_SUB(Node& n)
{
	visit(n[0]);
	buf += "\tpushq %rax\n";
	visit(n[1]);
	buf += "\tpopq %rbx\n";
	buf += "\tsubq %rbx, %rax\n";
}

void GenGasX86_64::visit_SYM(Node& n)
{
	auto pair = f->get_local(n.val);
	buf += "\tmovq -" + std::to_string(pair.first + pair.second) + "(%rbp), %rax\n";
}

void GenGasX86_64::visit_INT(Node& n)
{
	buf += "\tmovq $" + n.val + ", %rax\n";
}

void GenGasX86_64::visit_STRREF(Node& n)
{
	buf += "\tleaq .S" + n.val + "(%rip), %rdi\n";
}
