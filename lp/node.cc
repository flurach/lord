#include "node.h"
#include "token.h"

#define DEFAULT_NS_CAP 50

Node *Node_new(Range range, Token token, char *val)
{
	Node *self = malloc(sizeof(Node));
	*self = (Node){
		.id = 0,
		.range = range,
		.token = token,
		.val = val,

		.ns_len = 0,
		.ns_cap = DEFAULT_NS_CAP,
		.ns = calloc(DEFAULT_NS_CAP, sizeof(Node*))
	};
	return self;
}

void Node_free(Node *self)
{
	size_t i;
	for (i = 0; i < self->ns_len; i++)
		Node_free(self->ns[i]);

	Node_dryfree(self);
}

void Node_dryfree(Node *self)
{
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

Node *Node_binarify(Node *self)
{
	Node *tmp = self->ns[1];

	Node_push(tmp, self->ns[0]);
	Node_push(tmp, self->ns[2]);
	Node_dryfree(self);

	return tmp;
}

void Node_print(Node *self)
{
	static size_t indent = 0;

	size_t i = 0;
	while (i++ < indent)
		putchar('\t');

	printf(
		"%s '%s' %lu..%lu\n",
		Token_str[self->token],
		self->val,
		self->range.begin,
		self->range.end
	);

	indent++;
	for (i = 0; i < self->ns_len; i++)
		Node_print(self->ns[i]);
	indent--;
}
