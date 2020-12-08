#ifndef LORD_NODE_H
#define LORD_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

struct Node {
	enum Token type;
	char val[256];
	struct Node *ns[2];
};

void free_node(struct Node *node);
void node_print(struct Node *node);

#endif
