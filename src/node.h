#ifndef LORD_NODE_H
#define LORD_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

/* node class */
struct Node {
	enum Token type;
	char *val;

	size_t ns_len, ns_cap;
	struct Node **ns;
};

/* constructor & destructor */
struct Node *new_node(enum Token type, char *val);
void free_node(struct Node *self);

/* methods */
void node_push(struct Node *self, struct Node *child);
struct Node *node_pop(struct Node *self);

/* debugging */
void node_print(struct Node *self);

#endif
