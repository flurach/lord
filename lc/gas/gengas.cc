#include "lc.hh"

const std::vector<std::string> regs = {
	"rax",
	"rbx",
	"rcx"
};

GenGasVisitor::GenGasVisitor(Module& m)
	: Visitor(m)
{
}

void GenGasVisitor::visit_MODULE(Node& n)
{
	for (auto& thing : n)
		visit(thing);

	for (size_t id = 0; id < strmgr.size(); id++) {
		strs += ".S" + std::to_string(id) + ":\n";
		strs += "\t.string \"" + strmgr[id] + "\"\n";
	}

	buf = strs + buf;
}

void GenGasVisitor::visit_FN(Node& n)
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

void GenGasVisitor::visit_RET(Node& n)
{
	// eval what to return
	visit(n[0]);

	// return
	buf += "\tpopq %rbp\n";
	buf += "\tret\n";
}

void GenGasVisitor::visit_CALL(Node& n)
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

void GenGasVisitor::visit_ADD(Node& n)
{
	visit(n[0]);
	buf += "\tpushq %rax\n";
	visit(n[1]);
	buf += "\tpopq %rbx\n";
	buf += "\taddq %rbx, %rax\n";
}

void GenGasVisitor::visit_SUB(Node& n)
{
	visit(n[0]);
	buf += "\tpushq %rax\n";
	visit(n[1]);
	buf += "\tpopq %rbx\n";
	buf += "\tsubq %rbx, %rax\n";
}

void GenGasVisitor::visit_SYM(Node& n)
{
	auto pair = f->get_local(n.val);
	buf += "\tmovq -" + std::to_string(pair.first + pair.second) + "(%rbp), %rax\n";
}

void GenGasVisitor::visit_INT(Node& n)
{
	buf += "\tmovq $" + n.val + ", %rax\n";
}

void GenGasVisitor::visit_STR(Node& n)
{
	auto id = strmgr.make(n.val);
	buf += "\tleaq .S" + std::to_string(id) + "(%rip), %rdi\n";
}
