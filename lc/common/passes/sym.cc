#include "lc.hh"

SymVisitor::SymVisitor(Module *m)
	: Visitor(m)
{
}

void SymVisitor::visit_MODULE(Node *n)
{
	(void)n;

	// visit methods
	for (auto pair : m->structs) {
		auto s = pair.second;

		if (s == NULL)
			continue;

		for (auto pair : s->fields) {
			auto f = pair.second;

			if (f == NULL)
				continue;
			if (f->kind != TK_FN)
				continue;

			symgr = Symgr();
			visit(f->ref);
		}
	}

	// visit functions
	for (auto pair : m->fns) {
		symgr = Symgr();
		visit(pair.second->ref);
	}
}

void SymVisitor::visit_FN(Node *n)
{
	visit(n->at(1));
	visit(n->at(3));
}

void SymVisitor::visit_ARGS(Node *n)
{
	for (auto a : *n)
		visit_lval(a);
}

void SymVisitor::visit_EQ(Node *n)
{
	visit(n->at(1));
	visit_lval(n->at(0));
}

void SymVisitor::visit_lval(Node *n)
{
	if (n->token == T_COLN)
		n->at(0)->id = symgr.add(n->at(0)->val);
	else
		n->id = symgr.add(n->val);
}

void SymVisitor::visit_SYM(Node *n)
{
	n->id = symgr.get(n->val);
}
