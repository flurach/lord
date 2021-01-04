#include "visitor.h"

Visitor *Visitor_new(CompState *state)
{
	Visitor *self = malloc(sizeof(Visitor));

	size_t i;
	for (i = 0; i < T_LAST; i++)
		self->callbacks[i] = Visitor_visit;

	self->state = state;
	return self;
}

void Visitor_free(Visitor *self)
{
	free(self);
}

void Visitor_visit(Visitor *self, Node *node)
{
	if (self->callbacks[node->token] != NULL)
		self->callbacks[node->token](self, node);
}
