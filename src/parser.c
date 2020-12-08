#include "parser.h"


struct Node *parse(struct Lex *lex)
{
	return parse_fdef(lex);
}

struct Node *parse_fdef(struct Lex *lex)
{
	struct Node *sym, *eq, *fcall;

	if (lex_peek(lex) != T_SYM)
		return NULL;

	lex_next(lex);
	sym = lex_node(lex);

	if (lex_peek(lex) != T_EQ)
		return sym;
	lex_next(lex);
	eq = lex_node(lex);
	node_push(eq, sym);

	if ((fcall = parse_fcall(lex)) == NULL)
		return eq;
	node_push(eq, fcall);

	eq->ns[1] = fcall;
	return eq;
}

struct Node *parse_fcall(struct Lex *lex)
{
	struct Node *sym, *arg;

	if (lex_peek(lex) != T_SYM)
		return NULL;

	lex_next(lex);
	sym = lex_node(lex);

	if (lex_peek(lex) != T_STR)
		return sym;
	lex_next(lex);
	arg = lex_node(lex);

	node_push(sym, arg);
	return sym;
}
