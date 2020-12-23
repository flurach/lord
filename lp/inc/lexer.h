#ifndef LORD_LP_LEX_H
#define LORD_LP_LEX_H

#include <ctype.h>
#include "node.h"

/* lexer class */
typedef struct {
	char *src;
	size_t i;

	Range range;
	Token token;
	char *val;
} Lexer;

/* constructor & destructor */
Lexer *Lexer_new(char *src);
void Lexer_free(Lexer *self);

/* methods */
char Lexer_curr(Lexer *self);
char Lexer_char(Lexer *self);
Token Lexer_next(Lexer *self);
Token Lexer_peek(Lexer *self);

/* debug */
void Lexer_print(Lexer *self);

#endif
