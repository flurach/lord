#include "lc.hh"

void pipe_all_passes(Module& m)
{
	DesugarVisitor(m, m.ast);
	RegAllocVisitor(m, m.ast);
	GenVisitor(m, m.ast);
}
