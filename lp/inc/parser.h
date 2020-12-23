#ifndef LORD_LP_PARSER_H
#define LORD_LP_PARSER_H

#include "lexer.h"

Node *parse(Lexer *lexer);

Node *parse_ext(Lexer *lexer);
Node *parse_fdef(Lexer *lexer);
Node *parse_call(Lexer *lexer);
Node *parse_semibind(Lexer *lexer);

#define X(token) Node *parse_##token(Lexer *lexer);
	LORD_TOKENS
#undef X

#endif
