#ifndef LORD_VISITORS_SIMPLE_H
#define LORD_VISITORS_SIMPLE_H

/* abstract */
#include "base.h"

/* constructor */
Visitor *SimpleVisitor_new(CompState *state);

/* methods */
void SimpleVisitor_compile_literals(Visitor *self);
void SimpleVisitor_MOD(Visitor *self, Node *node);
void SimpleVisitor_EXT(Visitor *self, Node *node);
void SimpleVisitor_FN(Visitor *self, Node *node);
void SimpleVisitor_CALL(Visitor *self, Node *node);
void SimpleVisitor_SEMI(Visitor *self, Node *node);

#endif
