#include "lc.hh"

SymNameVisitor::SymNameVisitor(Module *m)
	: Visitor(m)
{
}

void SymNameVisitor::visit_MODULE(Node *n)
{
	(void)n;
	for (auto ff : m->fnmgr.fns) {
		f = ff;
		visit(ff->ref->ns[3]);
	}
}

void SymNameVisitor::visit_EQ(Node *n)
{
	f->scope.incMut(n->ns[0]->val);
}
