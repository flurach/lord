#ifndef LORD_VISITORS_BASE_H
#define LORD_VISITORS_BASE_H

#include "../node.h"

/* visitor class */
typedef struct Visitor Visitor;
struct Visitor {
	void *payload;
	void (*callbacks[T_LAST])(Visitor*, Node*);
};

/* constructor & destructor */
Visitor *Visitor_new();
void Visitor_free(Visitor *self);

/* methods */
void Visitor_visit(Visitor *self, Node *node);

#endif
