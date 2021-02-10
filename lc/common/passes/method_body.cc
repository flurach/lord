#include "lc.hh"

MethodBodyVisitor::MethodBodyVisitor(Module *m)
	: FnBodyVisitor(m)
{
}

void MethodBodyVisitor::visit_MODULE(Node *n)
{
	(void)n;

	for (auto pair : m->structs) {
		s = pair.second;
		if (s == NULL)
			continue;
		for (auto pair : s->fields) {
			if (pair.second->kind != TK_FN)
				continue;
			f = pair.second;
			visit(f->ref);
		}
	}
}

void MethodBodyVisitor::visit_fnargs(Node *n)
{
	for (auto nn : *n)
		nn->id = m->symgr.add(nn->val);

	if (n->size() > 0)
		m->symgr.types[n->at(0)->id] = s;
}
