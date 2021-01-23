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
	visit_fnargs(n->ns[1]);
	visit(n->ns[3]);
}

void MethodBodyVisitor::visit_fnargs(Node *n)
{
	for (auto nn : n->ns)
		nn->id = f->symgr.add(nn->val);

	if (n->ns.size() > 0)
		f->symgr.types[n->ns[0]->id] = Type(s);
}

void MethodBodyVisitor::visit_EQ(Node *n)
{
	n->ns[0]->id = f->symgr.add(n->ns[0]->val);
}

void MethodBodyVisitor::visit_SYM(Node *n)
{
	n->id = f->symgr.get(n->val);
}
