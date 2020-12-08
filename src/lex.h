#ifndef LORD_LEX_H
#define LORD_LEX_H

#include <ctype.h>
#include "node.h"

struct Lex {
	char *it;
	enum Token type;
	char val[256];
};

enum Token lex_next(struct Lex *lex);
enum Token lex_peek(struct Lex *lex);
void lex_print(struct Lex *lex);
struct Node *lex_node(struct Lex *lex);

#endif
