#include "lexer.h"

Lexer *Lexer_new(char *src)
{
	Lexer *self = malloc(sizeof(Lexer));
	*self = (Lexer){
		.src = src,
		.i = 0,

		.range = {0, 0},
		.type = T_EOF,
		.val = strdup(src)
	};
	self->val[0] = '\0';
	return self;
}

void Lexer_free(Lexer *self)
{
	free(self->val);
	free(self->src);
	free(self);
}

char Lexer_curr(Lexer *self)
{
	return self->src[self->i];
}

char Lexer_char(Lexer *self)
{
	if (self->src[self->i] != '\0')
		return self->src[self->i++];
	return '\0';
}

Token Lexer_next(Lexer *self)
{
	char *vi = self->val;

	/* skip whitespace */
	while (isspace(Lexer_curr(self)))
		Lexer_char(self);

	self->range.begin = self->i;

	/* comments */
	if (Lexer_curr(self) == '#') {
		while (Lexer_curr(self) != '\n' && Lexer_curr(self) != '\0')
			Lexer_char(self);
		return Lexer_next(self);
	}

	/* symbols */
	else if (isalpha(Lexer_curr(self))) {
		while (isalpha(Lexer_curr(self)))
			*vi++ = Lexer_char(self);
		*vi = '\0';

		if (strcmp(self->val, "fn") == 0)
			self->type = T_FN;
		else
			self->type = T_SYM;
	}

	/* strings */
	else if (Lexer_curr(self) == '\'' || Lexer_curr(self) == '\"') {
		self->type = T_STR;
		const char pair = Lexer_char(self);
		while (Lexer_curr(self) != pair && Lexer_curr(self) != '\0')
			*vi++ = Lexer_char(self);
		Lexer_char(self);
	}

	/* operators */
	else if (Lexer_curr(self) == '=') {
		self->type = T_EQ;
		*vi++ = Lexer_char(self);
	}

	/* end of file */
	else if (Lexer_curr(self) == '\0') {
		self->type = T_EOF;
	}

	self->range.end = self->i;
	*vi = '\0';
	return self->type;
}

Token Lexer_peek(Lexer *self)
{
	size_t i = self->i;
	Token type = Lexer_next(self);
	self->i = i;
	return type;
}

void Lexer_print(Lexer *self)
{
	printf(
		"%s '%s' %lu..%lu\n",
		Token_str[self->type],
		self->val,
		self->range.begin,
		self->range.end
	);
}
