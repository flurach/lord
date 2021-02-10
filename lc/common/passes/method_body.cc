#include "lc.hh"

MethodBodyVisitor::MethodBodyVisitor(Module *m)
	: FnBodyVisitor(m)
{
}

void MethodBodyVisitor::visit_MODULE(Node *n)
{
	(void)n;

	// FIXME
	// for (auto ss : m->structmgr.structs) {
	// 	s = ss;
	// 	for (auto ff : s->fnmgr.fns) {
	// 		f = ff;
	// 		visit(f->ref);
	// 	}
	// }
}

void MethodBodyVisitor::visit_fnargs(Node *n)
{
	for (auto nn : *n)
		nn->id = f->symgr.add(nn->val);

	// FIXME
	// if (n->size() > 0) {
	// 	auto t = m->typemgr.make_struct(s);
	// 	std::cout << "BE GONE THOT: " << t << std::endl;
	// 	f->symgr.types[n->at(0)->id] = t;
	// }
}
