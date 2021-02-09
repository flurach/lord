#include "lc.hh"

Type *TypeMgr::make_atomic(std::string name)
{
	Type *t = new Type(TK_ATOMIC, name);

	for (auto tt : types) {
		if (t->equals(tt)) {
			delete t;
			return tt;
		}
	}

	types.push_back(t);
	return t;
}

Type *TypeMgr::make_arr(Type *t)
{
	Type *a = new Type(TK_ARR, "", {t});

	for (auto tt : types) {
		if (a->equals(tt)) {
			delete a;
			return tt;
		}
	}

	types.push_back(a);
	return a;
}

Type *TypeMgr::make_struct(Struct *s)
{
	Type *t = new Type(TK_STRUCT, s->name);

	for (auto field : s->fields)
		t->subtypes.push_back(field.type);

	for (auto tt : types) {
		if (t->equals(tt)) {
			delete t;
			return tt;
		}
	}

	types.push_back(t);
	return t;
}
