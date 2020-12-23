#include "visitors/base.h"

Visitor *Visitor_new(CompState *state)
{
	Visitor *self = malloc(sizeof(Visitor));
	memset(self, 0, sizeof(Visitor));
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
