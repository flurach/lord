#include "lc.hh"

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
