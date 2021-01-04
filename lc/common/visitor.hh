#ifndef LORD_LC_COMMON_VISITOR_HH
#define LORD_LC_COMMON_VISITOR_HH

#include "node.hh"
struct CompState;
typedef struct CompState CompState;

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
