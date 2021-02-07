#include "lc.hh"

MethodBodyVisitor::MethodBodyVisitor(Module *m)
	: FnBodyVisitor(m)
{
}

void MethodBodyVisitor::visit_MODULE(Node *n)
{
	(void)n;

	for (auto ss : m->structmgr.structs) {
		s = ss;
		for (auto ff : s->fnmgr.fns) {
			f = ff;
			visit(f->ref);
		}
	}
}

void MethodBodyVisitor::visit_fnargs(Node *n)
{
	for (auto nn : *n)
		nn->id = f->symgr.add(nn->val);

	if (n->size() > 0)
		f->symgr.types[n->at(0)->id] = Type(s);
}
