#include "lc.hh"

void unif(std::vector<Constraint>& constraints)
{
	for (auto& c : constraints) {
		if (c.lhop->token != T_NONE || !is_complete_type(*c.rhop))
			continue;
		*c.lhop = *c.rhop;
		unif(constraints);
	}
}

bool is_complete_type(Node& t)
{
	if (t.token == T_NONE)
		return false;

	for (auto& child : t) {
		if (!is_complete_type(child))
			return false;
	}

	return true;
}
