#include "lc.hh"

Fn::Fn(Node *ref)
	: ref(ref)
{
	defined_at = ref->range;

	if (ref->ns[0]->token == T_DOT)
		name = ref->ns[0]->ns[1]->val;
	else
		name = ref->ns[0]->val;
}

void Fn::print()
{
	std::cout << name << ": ()" << std::endl;
	scope.print();
}

void FnMgr::add(Fn *f)
{
	fns.push_back(f);
}

FnMgr::~FnMgr()
{
	for (auto f : fns)
		delete f;
}

void FnMgr::print()
{
	for (auto fn : fns)
		fn->print();
}
