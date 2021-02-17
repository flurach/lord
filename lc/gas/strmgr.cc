#include "lc.hh"

size_t StrMgr::make(std::string s)
{
	for (size_t i = 0; i < size(); i++) {
		if (s == this->at(i))
			return i;
	}

	push_back(s);
	return size() - 1;
}
