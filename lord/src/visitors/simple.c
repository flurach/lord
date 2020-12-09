#include "visitors/simple.h"

Visitor *SimpleVisitor_new()
{
	Visitor *self = Visitor_new();

	self->callbacks[T_MOD]  = SimpleVisitor_MOD;
	self->callbacks[T_EXT]  = SimpleVisitor_EXT;
	self->callbacks[T_FN]   = SimpleVisitor_FN;
	self->callbacks[T_CALL] = SimpleVisitor_CALL;

	return self;
}

void SimpleVisitor_MOD(Visitor *self, Node *node)
{
	size_t i;
	for (i = 0; i < node->ns_len; i++)
		Visitor_visit(self, node->ns[i]);
}

void SimpleVisitor_EXT(Visitor *self, Node *node)
{
	printf("  extern %s\n", node->ns[0]->val);
}

void SimpleVisitor_FN(Visitor *self, Node *node)
{
	printf("%s:\n", node->ns[0]->val);
	Visitor_visit(self, node->ns[2]);
}

void SimpleVisitor_CALL(Visitor *self, Node *node)
{
	printf("  LOAD_STR '%s'\n", node->ns[1]->val);
	printf("  CALL %s\n", node->ns[0]->val);
}
