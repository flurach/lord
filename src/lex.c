#include "lex.h"

struct Lex *new_lex(char *src)
{
	struct Lex *self = malloc(sizeof(struct Lex));
	*self = (struct Lex){
		.src = src,
		.i = 0,

		.range = {0, 0},
		.type = T_EOF,
		.val = strdup(src)
	};
	self->val[0] = '\0';
	return self;
}

void free_lex(struct Lex *self)
{
	free(self->val);
	free(self->src);
	free(self);
}

char lex_curr(struct Lex *self)
{
	return self->src[self->i];
}

char lex_char(struct Lex *self)
{
	if (self->src[self->i] != '\0')
		return self->src[self->i++];
	return '\0';
}

enum Token lex_next(struct Lex *self)
{
	char *vi = self->val;

	/* skip whitespace */
	while (isspace(lex_curr(self)))
		lex_char(self);

	self->range.begin = self->i;

	/* comments */
	if (lex_curr(self) == '#') {
		while (lex_curr(self) != '\n' && lex_curr(self) != '\0')
			lex_char(self);
		return lex_next(self);
	}

	/* symbols */
	else if (isalpha(lex_curr(self))) {
		self->type = T_SYM;
		while (isalpha(lex_curr(self)))
			*vi++ = lex_char(self);
	}

	/* strings */
	else if (lex_curr(self) == '\'' || lex_curr(self) == '\"') {
		self->type = T_STR;
		const char pair = lex_char(self);
		while (lex_curr(self) != pair && lex_curr(self) != '\0')
			*vi++ = lex_char(self);
		lex_char(self);
	}

	/* operators */
	else if (lex_curr(self) == '=') {
		self->type = T_EQ;
		*vi++ = lex_char(self);
	}

	/* end of file */
	else if (lex_curr(self) == '\0') {
		self->type = T_EOF;
	}

	self->range.end = self->i;
	*vi = '\0';
	return self->type;
}

enum Token lex_peek(struct Lex *self)
{
	size_t i = self->i;
	enum Token type = lex_next(self);
	self->i = i;
	return type;
}

void lex_print(struct Lex *self)
{
	printf(
		"%s '%s' %lu..%lu\n",
		Token_str[self->type],
		self->val,
		self->range.begin,
		self->range.end
	);
}

struct Node *lex_node(struct Lex *self)
{
	return new_node(self->range, self->type, strdup(self->val));
}
