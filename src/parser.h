#ifndef LORD_PARSER_H
#define LORD_PARSER_H

#include "lex.h"

struct Node *parse(struct Lex *lex);

struct Node *parse_fdef(struct Lex *lex);
struct Node *parse_fcall(struct Lex *lex);

#define X(token) struct Node *parse_##token(struct Lex *lex);
	LORD_TOKENS
#undef X

#endif
