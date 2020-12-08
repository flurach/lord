#include "parser.h"

Node *parse(Lexer *lexer)
{
	return parse_fdef(lexer);
}

Node *parse_fdef(Lexer *lexer)
{
	Node *sym, *eq, *fcall;

	if ((sym = parse_SYM(lexer)) == NULL)
		return NULL;

	if ((eq = parse_EQ(lexer)) == NULL)
		return sym;
	Node_push(eq, sym);

	if ((fcall = parse_fcall(lexer)) == NULL)
		return eq;
	Node_push(eq, fcall);

	return eq;
}

Node *parse_fcall(Lexer *lexer)
{
	Node *sym, *arg;

	if ((sym = parse_SYM(lexer)) == NULL)
		return NULL;

	if ((arg = parse_STR(lexer)) == NULL)
		return sym;
	Node_push(sym, arg);

	return sym;
}

#define X(token)\
Node *parse_##token(Lexer *lexer)\
{\
	if (Lexer_peek(lexer) != T_##token)\
		return NULL;\
	Lexer_next(lexer);\
	return Node_new(lexer->range, lexer->type, strdup(lexer->val));\
}
	LORD_TOKENS
#undef X
