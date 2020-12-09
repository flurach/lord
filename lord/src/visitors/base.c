#include "visitors/base.h"

Visitor *Visitor_new(void *payload)
{
	Visitor *self = malloc(sizeof(Visitor));
	memset(self, 0, sizeof(Visitor));
	self->payload = payload;
	return self;
}


void Visitor_free(Visitor *self, void (*payload_freer)(void *))
{
	if (payload_freer != NULL)
		payload_freer(self->payload);
	free(self);
}

void Visitor_visit(Visitor *self, Node *node)
{
	if (self->callbacks[node->type] != NULL)
		self->callbacks[node->type](self, node);
}
