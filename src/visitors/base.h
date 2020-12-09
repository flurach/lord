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
Visitor *Visitor_new(void *payload);
void Visitor_free(Visitor *self, void (*payload_freer)(void *));

/* methods */
void Visitor_visit(Visitor *self, Node *node);

#endif
