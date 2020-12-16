#include "comp_state.h"

#define LORD_COMPSTATE_DEFAULT_LS_CAP 50

/*!
 * Constructor
 */
CompState *CompState_new()
{
	CompState *self = malloc(sizeof(CompState));
	*self = (CompState){
		.ls_len = 0,
		.ls_cap = LORD_COMPSTATE_DEFAULT_LS_CAP,
		.ls = calloc(LORD_COMPSTATE_DEFAULT_LS_CAP, sizeof(Lit*))
	};
	return self;
}

void CompState_free(CompState *self)
{
	size_t i;
	for (i = 0; i < self->ls_len; i++)
		Lit_free(self->ls[i]);
	free(self->ls);
	free(self);
}

int CompState_addlit(CompState *self, Lit *l)
{
	if (self->ls_len > self->ls_cap / 2) {
		self->ls_cap *= 2;
		self->ls = realloc(self->ls, self->ls_cap * sizeof(Lit*));
	}

	int i;
	for (i = 0; i < self->ls_len; i++) {
		if (Lit_cmp(self->ls[i], l)) {
			Lit_free(l);
			return i;
		}
	}

	self->ls[self->ls_len++] = l;
	return self->ls_len - 1;
}
