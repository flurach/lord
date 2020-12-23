#ifndef LORD_LC_VISITORS_LITERALS_H
#define LORD_LC_VISITORS_LITERALS_H

/* abstract */
#include "base.h"

/* constructor */
Visitor *LiteralsVisitor_new(CompState *state);

/* methods */
void LiteralsVisitor_MOD(Visitor *self, Node *node);
void LiteralsVisitor_FN(Visitor *self, Node *node);
void LiteralsVisitor_CALL(Visitor *self, Node *node);
void LiteralsVisitor_STR(Visitor *self, Node *node);
void LiteralsVisitor_SEMI(Visitor *self, Node *node);

#endif
