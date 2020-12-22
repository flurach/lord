#ifndef LORD_LIT_H
#define LORD_LIT_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* literal class */
typedef struct {
	char *val;
} Lit;

/* constructor & destructor */
Lit *Lit_new(char *val);
void Lit_free(Lit *self);

/* methods */
bool Lit_cmp(Lit *self, Lit *l);

#endif
