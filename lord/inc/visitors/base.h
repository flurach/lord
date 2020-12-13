#ifndef LORD_VISITORS_BASE_H
#define LORD_VISITORS_BASE_H

#include "../node.h"
#include "comp_state.h"

/* visitor class */
typedef struct Visitor Visitor;
struct Visitor {
	CompState *state;
	void (*callbacks[T_LAST])(Visitor*, Node*);
};

/* constructor & destructor */
Visitor *Visitor_new(CompState *state);
void Visitor_free(Visitor *self);

/* methods */
void Visitor_visit(Visitor *self, Node *node);

#endif
