#include "node.h"

void free_node(struct Node *node)
{
	if (node == NULL)
		return;
	free_node(node->ns[0]);
	free_node(node->ns[1]);
	free(node);
}

void node_print(struct Node *node)
{
	static int indent = 0;

	if (node == NULL)
		return;

	int x = 0;
	while (x++ < indent)
		putchar('\t');

	printf("%d '%s'\n", node->type, node->val);
	indent++;
	node_print(node->ns[0]);
	node_print(node->ns[1]);
	indent--;
}
