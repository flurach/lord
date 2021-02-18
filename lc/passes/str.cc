#include "lc.hh"

StrVisitor::StrVisitor(Module& m)
	: Visitor(m)
{
}

void StrVisitor::visit_STR(Node& n)
{
	// make string
	m.strs.insert(n.val);

	// find index
	size_t idx = 0;
	for (auto& str : m.strs) {
		if (str == n.val)
			break;
		idx++;
	}

	// refactor
	n.token = T_STRREF;
	n.val = std::to_string(idx);
}
