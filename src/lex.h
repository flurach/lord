#ifndef LORD_LEX_H
#define LORD_LEX_H

#include <ctype.h>
#include "node.h"

/* lexer class */
struct Lex {
	char *src;
	size_t i;

	struct Range range;
	enum Token type;
	char *val;
};

/* constructor & destructor */
struct Lex *new_lex(char *src);
void free_lex(struct Lex *self);

/* methods */
char lex_curr(struct Lex *self);
char lex_char(struct Lex *self);
enum Token lex_next(struct Lex *self);
enum Token lex_peek(struct Lex *self);
struct Node *lex_node(struct Lex *self);

/* debug */
void lex_print(struct Lex *self);

#endif
