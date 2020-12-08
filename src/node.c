#include "node.h"

#define DEFAULT_NS_CAP 50

struct Node *new_node(enum Token type, char *val)
{
	struct Node *self = malloc(sizeof(struct Node));
	*self = (struct Node){
		.type = type,
		.val = val,

		.ns_len = 0,
		.ns_cap = DEFAULT_NS_CAP,
		.ns = calloc(DEFAULT_NS_CAP, sizeof(struct Node*))
	};
	return self;
}

void free_node(struct Node *self)
{
	if (self == NULL)
		return;

	for (size_t i = 0; i < self->ns_len; i++)
		free_node(self->ns[i]);

	free(self->ns);
	free(self->val);
	free(self);
}

void node_push(struct Node *self, struct Node *child)
{
	if (self->ns_len > self->ns_cap / 2) {
		self->ns_cap *= 2;
		self->ns = realloc(self->ns, self->ns_cap * sizeof(struct Node*));
	}

	self->ns[self->ns_len++] = child;
}

struct Node *node_pop(struct Node *self)
{
	if (self->ns_len > 0)
		return self->ns[--self->ns_len];
	return NULL;
}

void node_print(struct Node *self)
{
	static int indent = 0;

	int x = 0;
	while (x++ < indent)
		putchar('\t');

	printf("%d '%s'\n", self->type, self->val);

	indent++;
	for (size_t i = 0; i < self->ns_len; i++)
		node_print(self->ns[i]);
	indent--;
}
