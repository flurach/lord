#include "visitors/simple.h"

Visitor *SimpleVisitor_new(CompState *state)
{
	Visitor *self = Visitor_new(state);

	self->callbacks[T_MOD]  = SimpleVisitor_MOD;
	self->callbacks[T_EXT]  = SimpleVisitor_EXT;
	self->callbacks[T_FN]   = SimpleVisitor_FN;
	self->callbacks[T_CALL] = SimpleVisitor_CALL;

	return self;
}

void SimpleVisitor_compile_literals(Visitor *self)
{
	puts("  .section .rodata");

	size_t i;
	for (i = 0; i < self->state->ls_len; i++) {
		printf(".l%d:\n", i);
		printf("  .string \"%s\"\n", self->state->ls[i]->val);
	}

	puts("  .text");
	puts("  .globl main");
}

void SimpleVisitor_MOD(Visitor *self, Node *node)
{
	SimpleVisitor_compile_literals(self);

	size_t i;
	for (i = 0; i < node->ns_len; i++)
		Visitor_visit(self, node->ns[i]);
}

void SimpleVisitor_EXT(Visitor *self, Node *node)
{
	printf("  .extern %s\n", node->ns[0]->val);
}

void SimpleVisitor_FN(Visitor *self, Node *node)
{
	printf("%s:\n", node->ns[0]->val);
	printf("  pushq %%rbp\n");
	printf("  movq %%rsp, %%rbp\n");
	Visitor_visit(self, node->ns[2]);
	printf("  movl $0, %%eax\n");
	printf("  popq %%rbp\n");
	printf("  ret\n");
}

void SimpleVisitor_CALL(Visitor *self, Node *node)
{
	printf("  leaq .l%d(%%rip), %%rdi\n", node->ns[1]->id);
	printf("  call %s@PLT\n", node->ns[0]->val);
}
