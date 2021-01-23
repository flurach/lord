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

void Fn::print(size_t i)
{
	size_t x = 0;
	while (x++ < i)
		putchar('\t');
	std::cout << name << ": ()" << std::endl;
	symgr.print(i + 1);
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

void FnMgr::print(size_t i)
{
	size_t x = 0;
	while (x++ < i)
		putchar('\t');
	for (auto fn : fns)
		fn->print(i + 1);
}
