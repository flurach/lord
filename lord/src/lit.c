#include "lit.h"

Lit *Lit_new(char *val)
{
	Lit *self = malloc(sizeof(Lit));
	self->val = val;
	return self;
}

void Lit_free(Lit *self)
{
	free(self->val);
	free(self);
}

bool Lit_cmp(Lit *self, Lit *l)
{
	return strcmp(self->val, l->val) == 0;
}
