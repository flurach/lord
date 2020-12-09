#include "node.h"
#include "token.h"

#define DEFAULT_NS_CAP 50

Node *Node_new(Range range, Token type, char *val)
{
	Node *self = malloc(sizeof(Node));
	*self = (Node){
		.range = range,
		.type = type,
		.val = val,

		.ns_len = 0,
		.ns_cap = DEFAULT_NS_CAP,
		.ns = calloc(DEFAULT_NS_CAP, sizeof(Node*))
	};
	return self;
}

void Node_free(Node *self)
{
	if (self == NULL)
		return;

	for (size_t i = 0; i < self->ns_len; i++)
		Node_free(self->ns[i]);

	free(self->ns);
	free(self->val);
	free(self);
}

void Node_push(Node *self, Node *child)
{
	if (self->ns_len > self->ns_cap / 2) {
		self->ns_cap *= 2;
		self->ns = realloc(self->ns, self->ns_cap * sizeof(Node*));
	}

	self->ns[self->ns_len++] = child;
}

Node *Node_pop(Node *self)
{
	if (self->ns_len > 0)
		return self->ns[--self->ns_len];
	return NULL;
}

void Node_print(Node *self)
{
	static int indent = 0;

	int x = 0;
	while (x++ < indent)
		putchar('\t');

	printf(
		"%s '%s' %lu..%lu\n",
		Token_str[self->type],
		self->val,
		self->range.begin,
		self->range.end
	);

	indent++;
	for (size_t i = 0; i < self->ns_len; i++)
		Node_print(self->ns[i]);
	indent--;
}
