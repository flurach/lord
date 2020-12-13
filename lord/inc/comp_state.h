#ifndef LORD_COMP_STATE_H
#define LORD_COMP_STATE_H

#include "lit.h"

/* compiler state class */
typedef struct {

	/* literals */
	size_t ls_len, ls_cap;
	Lit **ls;

} CompState;

/* constructor & destructor */
CompState *CompState_new();
void CompState_free(CompState *self);

/* methods */
int CompState_addlit(CompState *self, Lit *l);

#endif
