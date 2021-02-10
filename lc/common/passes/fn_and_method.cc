#include "lc.hh"

FnAndMethodVisitor::FnAndMethodVisitor(Module *m)
	: Visitor(m)
{
}

void FnAndMethodVisitor::visit_FN(Node *n)
{
	if (n->at(0)->token == T_DOT)
		visit_method(n);
	else
		visit_fdef(n);
}

void FnAndMethodVisitor::visit_method(Node *n)
{
	auto struct_name = n->at(0)->at(0)->val;
	auto method_name = n->at(0)->at(1)->val;

	auto s = m->structs[struct_name];
	s->fields[method_name] = m->typemgr.make_fn(n, struct_name + "::" + method_name);
}

void FnAndMethodVisitor::visit_fdef(Node *n)
{
	auto fn_name = n->at(0)->val;
	m->fns[fn_name] = m->typemgr.make_fn(n, fn_name);
}
