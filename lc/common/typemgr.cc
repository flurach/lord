#include "lc.hh"

TypeMgr::~TypeMgr()
{
	for (auto t : *this)
		delete t;
}

Type *TypeMgr::make(Type *t)
{
	for (auto tt : *this) {
		if (t->equals(tt)) {
			delete t;
			return tt;
		}
	}

	push_back(t);
	return t;
}

Type *TypeMgr::make_atomic(std::string name)
{
	return make(new Type(NULL, TK_ATOMIC, name));
}

Type *TypeMgr::make_arr(Type *t)
{
	auto a = new Type(NULL, TK_ARR, "");
	a->subtypes.push_back(t);
	return make(a);
}

Type *TypeMgr::make_struct(Node *ref, std::string name)
{
	return make(new Type(ref, TK_STRUCT, name));
}

Type *TypeMgr::make_fn(Node *ref, std::string name)
{
	return make(new Type(ref, TK_FN, name));
}
