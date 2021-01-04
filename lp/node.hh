#ifndef LORD_LP_NODE_H
#define LORD_LP_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "common.h"

/* node class */
typedef struct Node Node;
struct Node {
	int id;
	Range range;
	Token token;
	char *val;

	size_t ns_len, ns_cap;
	Node **ns;
};

/* constructor & destructor */
Node *Node_new(Range range, Token token, char *val);
void Node_free(Node *self);
void Node_dryfree(Node *self);

/* methods */
void Node_push(Node *self, Node *child);
Node *Node_pop(Node *self);
Node *Node_binarify(Node *self);

/* debugging */
void Node_print(Node *self);

#endif
