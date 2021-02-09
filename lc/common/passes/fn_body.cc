#include "lc.hh"

FnBodyVisitor::FnBodyVisitor(Module *m)
	: Visitor(m)
{
}

void FnBodyVisitor::visit_MODULE(Node *n)
{
	(void)n;

	for (auto ff : m->fnmgr.fns) {
		f = ff;
		visit(ff->ref);
	}
}

void FnBodyVisitor::visit_FN(Node *n)
{
	auto fnargs = n->at(1);
	auto fnbody = n->at(3);

	/* main function exception */
	if (m->name == "__main__" && n->at(0)->val == "main") {
		auto _args = fnargs->at(0);
		_args->id = f->symgr.add(_args->val);

		auto t = m->typemgr.make_arr(m->typemgr.make_atomic("str"));
		f->symgr.types[_args->id] = t;
	}

	visit_fnargs(fnargs);
	visit(fnbody);
}

void FnBodyVisitor::visit_fnargs(Node *n)
{
	for (auto nn : *n)
		nn->id = f->symgr.add(nn->val);
}

void FnBodyVisitor::visit_EQ(Node *n)
{
	n->at(0)->id = f->symgr.add(n->at(0)->val);
	visit(n->at(0));
	visit(n->at(1));
}

void FnBodyVisitor::visit_SYM(Node *n)
{
	n->id = f->symgr.get(n->val);
}
