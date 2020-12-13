#include "visitors/literals.h"

Visitor *LiteralsVisitor_new(CompState *state)
{
	Visitor *self = Visitor_new(state);

	self->callbacks[T_MOD]  = LiteralsVisitor_MOD;
	self->callbacks[T_FN]   = LiteralsVisitor_FN;
	self->callbacks[T_CALL] = LiteralsVisitor_CALL;
	self->callbacks[T_STR]  = LiteralsVisitor_STR;

	return self;
}

void LiteralsVisitor_MOD(Visitor *self, Node *node)
{
	size_t i;
	for (i = 0; i < node->ns_len; i++)
		Visitor_visit(self, node->ns[i]);
}

void LiteralsVisitor_FN(Visitor *self, Node *node)
{
	Visitor_visit(self, node->ns[2]);
}

void LiteralsVisitor_CALL(Visitor *self, Node *node)
{
	Visitor_visit(self, node->ns[1]);
}

void LiteralsVisitor_STR(Visitor *self, Node *node)
{
	node->id = CompState_addlit(
		self->state,
		Lit_new(strdup(node->val))
	);
}
