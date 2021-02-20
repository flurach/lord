#include "lc.hh"

GenVisitor::GenVisitor(Module& m)
	: Visitor(m)
{
}

void GenVisitor::visit_FN(Node& n)
{
	auto fname = n[0][0].val;
	f = &m.fns[fname];

	// create function
	m.ins.push_back(Ins(IT_LABEL, {
		InsOp(IOT_LIT, n[0][0].val),                  // function name
		InsOp(IOT_LIT, "frame-size", f->frame_size()) // space for local vars
	}));

	// TODO: load arguments from regs to stack

	// TODO: then
	visit(/* body */ n[2]);
}
