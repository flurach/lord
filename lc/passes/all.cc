#include "lc.hh"

bool pipe_all_passes(Module& m)
{
	if (SyntacticVisitor(m, m.ast) == false)
		return false;

	DesugarVisitor(m, m.ast);
	FnVisitor(m, m.ast);
	InferVisitor(m, m.ast);
	RegAllocVisitor(m, m.ast);
	GenVisitor(m, m.ast);

	return true;
}
