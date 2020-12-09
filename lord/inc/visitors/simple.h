#ifndef LORD_VISITORS_SIMPLE_H
#define LORD_VISITORS_SIMPLE_H

/* abstract */
#include "base.h"

/* constructor */
Visitor *SimpleVisitor_new();

/* methods */
void SimpleVisitor_MOD(Visitor *self, Node *node);
void SimpleVisitor_EXT(Visitor *self, Node *node);
void SimpleVisitor_FN(Visitor *self, Node *node);
void SimpleVisitor_CALL(Visitor *self, Node *node);

#endif
