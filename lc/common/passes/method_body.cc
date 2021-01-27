#include "lc.hh"

MethodBodyVisitor::MethodBodyVisitor(Module *m)
	: Visitor(m)
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

void MethodBodyVisitor::visit_FN(Node *n)
{
	visit_fnargs(n->at(1));
	visit(n->at(1));
}

void MethodBodyVisitor::visit_fnargs(Node *n)
{
	for (auto nn : *n)
		nn->id = f->symgr.add(nn->val);

	if (n->size() > 0)
		f->symgr.types[n->at(0)->id] = Type(s);
}

void MethodBodyVisitor::visit_EQ(Node *n)
{
	n->at(0)->id = f->symgr.add(n->at(0)->val);
}

void MethodBodyVisitor::visit_SYM(Node *n)
{
	n->id = f->symgr.get(n->val);
}
