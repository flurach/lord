#include "parser.h"
#include "lex.h"
#include "node.h"

struct Node *parse(struct Lex *lex)
{
	return parse_fdef(lex);
}

struct Node *parse_fdef(struct Lex *lex)
{
	struct Node *sym, *eq, *fcall;

	if ((sym = parse_SYM(lex)) == NULL)
		return NULL;

	if ((eq = parse_EQ(lex)) == NULL)
		return sym;
	node_push(eq, sym);

	if ((fcall = parse_fcall(lex)) == NULL)
		return eq;
	node_push(eq, fcall);

	return eq;
}

struct Node *parse_fcall(struct Lex *lex)
{
	struct Node *sym, *arg;

	if ((sym = parse_SYM(lex)) == NULL)
		return NULL;

	if ((arg = parse_STR(lex)) == NULL)
		return sym;
	node_push(sym, arg);

	return sym;
}

#define X(token)\
struct Node *parse_##token(struct Lex *lex)\
{\
	if (lex_peek(lex) != T_##token)\
		return NULL;\
	lex_next(lex);\
	return lex_node(lex);\
}
	LORD_TOKENS
#undef X
