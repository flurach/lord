#include "lc.hh"

Scope::Scope()
{
	ascend();
}

Node *Scope::make(Node sym, Node *type)
{
	if (syms.size() == 0)
		return NULL;

	syms.back()[sym] = type;
	return type;
}

Node *Scope::get(Node sym)
{
	if (syms.size() == 0)
		return NULL;

	auto it = syms.rbegin();
	while (it != syms.rend()) {
		if (it->at(sym))
			return it->at(sym);
	}

	return NULL;
}

void Scope::ascend()
{
	std::map<Node, Node*> table;
	syms.push_back(table);
}

void Scope::descend()
{
	if (syms.size())
		syms.pop_back();
}
