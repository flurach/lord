#include "parser.h"

Node *parse(Lexer *lexer)
{
	return NULL;
}

Node *parse(Lexer *lexer)
{
	return NULL;
}

Node *parse_stmt(Lexer *lexer)
{
	return NULL;
}

Node *parse_for(Lexer *lexer)
{
	return NULL;
}

Node *parse_forcond(Lexer *lexer)
{
	return NULL;
}

Node *parse_type(Lexer *lexer)
{
	return NULL;
}

Node *parse_if(Lexer *lexer)
{
	return NULL;
}

Node *parse_else(Lexer *lexer)
{
	return NULL;
}

Node *parse_logic(Lexer *lexer)
{
	return NULL;
}

Node *parse_eqcmp(Lexer *lexer)
{
	return NULL;
}

Node *parse_difcmp(Lexer *lexer)
{
	return NULL;
}

Node *parse_fdef(Lexer *lexer)
{
	return NULL;
}

Node *parse_fbody(Lexer *lexer)
{
	return NULL;
}

Node *parse_bind(Lexer *lexer)
{
	return NULL;
}

Node *parse_typedsym(Lexer *lexer)
{
	return NULL;
}

Node *parse_typeanno(Lexer *lexer)
{
	return NULL;
}

Node *parse_call(Lexer *lexer)
{
	return NULL;
}

Node *parse_expr(Lexer *lexer)
{
	return NULL;
}

Node *parse_term(Lexer *lexer)
{
	return NULL;
}

Node *parse_fact(Lexer *lexer)
{
	return NULL;
}

Node *parse_cast(Lexer *lexer)
{
	return NULL;
}

Node *parse_lit(Lexer *lexer)
{
	return NULL;
}

Node *parse_init(Lexer *lexer)
{
	return NULL;
}

Node *parse_initbody(Lexer *lexer)
{
	return NULL;
}

Node *parse_dotop(Lexer *lexer)
{
	return NULL;
}

Node *parse_ptr(Lexer *lexer)
{
	return NULL;
}

Node *parse_num(Lexer *lexer)
{
	return NULL;
}

Node *parse_arr(Lexer *lexer)
{
	return NULL;
}

Node *parse_range(Lexer *lexer)
{
	return NULL;
}

Node *parse_many(Lexer *lexer, Node *(*parser)(Lexer*))
{
	return NULL;
}

Node *parse_sepby(Lexer *lexer, Node *(*parser)(Lexer*), Node *(*delim)(Lexer*))
{
	return NULL;
}

Node *parse_either(Lexer *lexer, size_t count, Node *(*parser)(Lexer*))
{
	return NULL;
}

#define X(t)\
Node *parse_##t(Lexer *lexer)\
{\
	if (Lexer_peek(lexer) != T_##t)\
		return NULL;\
	Lexer_next(lexer);\
	return Node_new(lexer->range, lexer->token, strdup(lexer->val));\
}
	LORD_LP_TOKENS
#undef X
