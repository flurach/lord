#include "parser.h"

Node *parse(Lexer *lexer)
{
	Node *module = Node_new((Range){0, 0}, T_MOD, NULL);

	while (1) {
		Node *result = NULL;
		if ((result = parse_ext(lexer)) != NULL)
			Node_push(module, result);
		else if ((result = parse_fdef(lexer)) != NULL)
			Node_push(module, result);
		else
			break;
	}

	return module;
}

Node *parse_ext(Lexer *lexer)
{
	Node *ext, *sym;

	if ((ext = parse_EXT(lexer)) == NULL)
		return NULL;

	if ((sym = parse_SYM(lexer)) == NULL)
		return ext;

	Node_push(ext, sym);
	return ext;
}

Node *parse_fdef(Lexer *lexer)
{
	Node *fn, *sym, *eq, *semibind;

	if ((fn = parse_FN(lexer)) == NULL)
		return NULL;

	if ((sym = parse_SYM(lexer)) == NULL)
		return fn;
	Node_push(fn, sym);

	if ((eq = parse_EQ(lexer)) == NULL)
		return fn;
	Node_push(fn, eq);

	if ((semibind = parse_semibind(lexer)) == NULL)
		return fn;
	Node_push(fn, semibind);

	return fn;
}

Node *parse_call(Lexer *lexer)
{
	Node *call, *sym, *arg;

	if ((sym = parse_SYM(lexer)) == NULL)
		return NULL;

	if ((arg = parse_STR(lexer)) == NULL)
		return sym;

	call = Node_new(sym->range, T_CALL, NULL);
	Node_push(call, sym);
	Node_push(call, arg);

	return call;
}

Node *parse_semibind(Lexer *lexer)
{
	Node *lcall, *semi, *semibind;

	if ((lcall = parse_call(lexer)) == NULL)
		return NULL;

	if ((semi = parse_SEMI(lexer)) == NULL)
		return lcall;
	Node_push(semi, lcall);

	if ((semibind = parse_semibind(lexer)) == NULL)
		return semi;
	Node_push(semi, semibind);

	return semi;
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
