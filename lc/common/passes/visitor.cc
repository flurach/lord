#include "visitor.hh"

Visitor::Visitor(Module *mod)
	: mod(mod)
{
}

void Visitor::visit(Node *n)
{
	switch (n->token) {
		#define X(token)\
			case T_##token:\
				visit_##token(n);\
				break;
			LORD_LP_TOKENS
		#undef X
	}
}

void pipe_visitors(Node *n, std::vector<Visitor*> visitors)
{
	for (auto v : visitors) {
		v->visit(n);
		delete v;
	}
}
