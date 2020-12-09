#include "visitors/simple.h"

Visitor *SimpleVisitor_new()
{
	Visitor *self = Visitor_new(NULL);

	self->callbacks[T_FN]   = SimpleVisitor_FN;
	self->callbacks[T_CALL] = SimpleVisitor_CALL;

	return self;
}

void SimpleVisitor_FN(Visitor *self, Node *node)
{
	printf("%s:\n", node->val);
	Visitor_visit(self, node->ns[2]);
}

void SimpleVisitor_CALL(Visitor *self, Node *node)
{
	printf("  LOAD_STR '%s'\n", node->ns[1]->val);
	printf("  CALL %s\n", node->ns[0]->val);
}
