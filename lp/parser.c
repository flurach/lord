#include "parser.h"

Node *parse(Lexer *lexer)
{
	return parse_many(lexer, parse_stmt);
}

Node *parse_stmt(Lexer *lexer)
{
	Node *(*parsers[])(Lexer*) = {
		parse_for,
		parse_if,
		parse_fdef,
		parse_bind,
		parse_logic,
		parse_PASS,
	};

	return parse_either(
		lexer,
		sizeof(parsers) / sizeof(parsers[0]),
		parsers
	);
}

Node *parse_for(Lexer *lexer)
{
	Node *_for, *forcond, *fbody;

	if ((_for = parse_FOR(lexer)) == NULL)
		return NULL;

	if ((forcond = parse_forcond(lexer)) == NULL)
		return _for;
	Node_push(_for, forcond);

	if ((fbody = parse_fbody(lexer)) == NULL)
		return _for;
	Node_push(_for, fbody);

	return _for;
}

/* INCOMPLETE */
Node *parse_forcond(Lexer *lexer)
{
	return NULL;
}

Node *parse_type(Lexer *lexer)
{
	Node *type, *sym, *eq, *fbody;

	if ((type = parse_TYPE(lexer)) == NULL)
		return NULL;

	if ((sym = parse_SYM(lexer)) == NULL)
		return type;
	Node_push(type, sym);

	if ((eq = parse_EQ(lexer)) == NULL)
		return type;
	Node_push(type, eq);

	if ((fbody = parse_fbody(lexer)) == NULL)
		return type;
	Node_push(type, fbody);

	return type;
}

Node *parse_if(Lexer *lexer)
{
	Node *_if, *logic, *fbody, *_else;

	if ((_if = parse_IF(lexer)) == NULL)
		return NULL;

	if ((logic = parse_logic(lexer)) == NULL)
		return _if;
	Node_push(_if, logic);

	if ((_else = parse_else(lexer)) == NULL)
		return _if;
	Node_push(_if, _else);

	return _if;
}

Node *parse_else(Lexer *lexer)
{
	Node *_else, *_if_or_fbody;

	if ((_else = parse_ELSE(lexer)) == NULL)
		return NULL;

	Node *(*parsers[])(Lexer*) = {
		parse_if,
		parse_fbody
	};

	if ((_if_or_fbody = parse_either(lexer, 2, parsers)) == NULL)
		return _else;
	Node_push(_else, _if_or_fbody);

	return _else;
}

Node *parse_logic(Lexer *lexer)
{
	Node *eqcmp, *and_or_orr, *logic;

	Node *(*parsers[])(Lexer*) = {
		parse_AND,
		parse_ORR
	};

	if ((eqcmp = parse_eqcmp(lexer)) == NULL)
		return NULL;

	if ((and_or_orr = parse_either(lexer, 2, parsers)) == NULL)
		return eqcmp;
	Node_push(and_or_orr, eqcmp);

	if ((logic = parse_logic(lexer)) == NULL)
		return and_or_orr;
	Node_push(and_or_orr, logic);

	return and_or_orr;
}

Node *parse_eqcmp(Lexer *lexer)
{
	Node *difcmp, *eeq_or_neq, *eqcmp;

	Node *(*parsers[])(Lexer*) = {
		parse_EEQ,
		parse_NEQ
	};

	if ((difcmp = parse_difcmp(lexer)) == NULL)
		return NULL;

	if ((eeq_or_neq = parse_either(lexer, 2, parsers)) == NULL)
		return difcmp;
	Node_push(eeq_or_neq, difcmp);

	if ((eqcmp = parse_eqcmp(lexer)) == NULL)
		return eeq_or_neq;
	Node_push(eeq_or_neq, eqcmp);

	return eeq_or_neq;
}

Node *parse_difcmp(Lexer *lexer)
{
	Node *expr, *cmp, *difcmp;

	Node *(*parsers[])(Lexer*) = {
		parse_LSS,
		parse_GTR,
		parse_LEQ,
		parse_GEQ
	};

	if ((expr = parse_expr(lexer)) == NULL)
		return NULL;

	if ((cmp = parse_either(lexer, 2, parsers)) == NULL)
		return expr;
	Node_push(cmp, expr);

	if ((difcmp = parse_difcmp(lexer)) == NULL)
		return cmp;
	Node_push(cmp, difcmp);

	return cmp;
}

Node *parse_fdef(Lexer *lexer)
{
	Node *fn, *sym, *args, *eq, *fbody;

	if ((fn = parse_FN(lexer)) == NULL)
		return NULL;

	if ((sym = parse_SYM(lexer)) == NULL)
		return NULL;
	Node_push(fn, sym);

	Node_push(fn, parse_many(lexer, parse_SYM));

	if ((eq = parse_EQ(lexer)) == NULL)
		return fn;
	Node_push(fn, eq);

	if ((fbody = parse_fbody(lexer)) == NULL)
		return fbody;
	Node_push(fn, fbody);

	return fn;
}

Node *parse_fbody(Lexer *lexer)
{
	Node *indent, *stmts, *dedent;
	Node *expr;

	if ((expr = parse_expr(lexer)) != NULL)
		return expr;

	if ((indent = parse_INDENT(lexer)) == NULL)
		return NULL;

	stmts = parse_many(lexer, parse_stmt);

	if ((dedent = parse_DEDENT(lexer)) == NULL)
		return stmts;
	Node_push(stmts, dedent);

	return stmts;
}

Node *parse_bind(Lexer *lexer)
{
	Node *typedsym, *op, *logic;

	Lexer backup = *lexer;
	if ((typedsym = parse_typedsym(lexer)) == NULL)
		return NULL;

	Node *(*ops[])(Lexer*) = {
		parse_EQ,
		parse_AEQ,
		parse_SEQ,
		parse_MEQ,
		parse_DEQ,
		parse_MOQ
	};

	if ((op = parse_either(lexer, 6, ops)) == NULL)
		return typedsym;
	Node_push(op, typedsym);

	if ((logic = parse_logic(lexer)) == NULL)
		return op;
	Node_push(op, logic);

	return op;
}

/* INCOMPLETE */
Node *parse_typedsym(Lexer *lexer)
{
	return NULL;
}

/* INCOMPLETE */
Node *parse_typeanno(Lexer *lexer)
{
	return NULL;
}

Node *parse_expr(Lexer *lexer)
{
	Node *term, *op, *expr;

	if ((term = parse_term(lexer)) == NULL)
		return NULL;

	Node *(*ops[])(Lexer*) = {
		parse_ADD,
		parse_SUB
	};
	if ((op = parse_either(lexer, 2, ops)) == NULL)
		return term;
	Node_push(op, term);

	if ((expr = parse_expr(lexer)) != NULL)
		Node_push(op, expr);

	return op;
}

Node *parse_term(Lexer *lexer)
{
	Node *fact, *op, *term;

	if ((fact = parse_fact(lexer)) == NULL)
		return NULL;

	Node *(*ops[])(Lexer*) = {
		parse_MUL,
		parse_DIV,
		parse_MOD
	};
	if ((op = parse_either(lexer, 3, ops)) == NULL)
		return fact;
	Node_push(op, fact);

	if ((term = parse_expr(lexer)) != NULL)
		Node_push(op, term);

	return op;
}

Node *parse_fact(Lexer *lexer)
{
	Node *(*ops[])(Lexer*) = {
		parse_LPAR,
		parse_logic,
		parse_RPAR,
	};

	Node *result;
	if ((result = parse_seq(lexer, 3, ops)) != NULL)
		return result;

	return parse_cast(lexer);
}

Node *parse_cast(Lexer *lexer)
{
	Node *(*seq[])(Lexer*) = {
		parse_not,
		parse_AS,
		parse_typeanno
	};

	Node *result;
	if ((result = parse_seq(lexer, 3, seq)) != NULL)
		return result;

	return parse_not(lexer);
}

Node *parse_not(Lexer *lexer)
{
	Node *(*seq[])(Lexer*) = {
		parse_NOT,
		parse_lit
	};

	Node *result;
	if ((result = parse_seq(lexer, 2, seq)) != NULL)
		return result;

	return parse_lit(lexer);
}

Node *parse_lit(Lexer *lexer)
{
	Node *(*either[])(Lexer*) = {
		parse_call,
		parse_arg
	};
	return parse_either(lexer, 2, either);
}

Node *parse_range(Lexer *lexer)
{
	Node *lnum, *to, *rnum;

	if ((lnum = parse_num(lexer)) == NULL)
		return NULL;

	if ((to = parse_TO(lexer)) == NULL)
		return lnum;
	Node_push(to, lnum);

	if ((rnum = parse_num(lexer)) == NULL)
		return to;
	Node_push(to, rnum);

	return to;
}

Node *parse_num(Lexer *lexer)
{
	Node *sub, *int_or_flt;
	Node *(*parsers[])(Lexer*) = {parse_INT, parse_FLT};

	Lexer backup = *lexer;
	if ((sub = parse_SUB(lexer)) == NULL)
		return parse_either(lexer, 2, parsers);

	if ((int_or_flt = parse_either(lexer, 2, parsers)) == NULL) {
		*lexer = backup;
		return NULL;
	}

	Node_push(sub, int_or_flt);
	return sub;
}

Node *parse_ptr(Lexer *lexer)
{
	Node *(*seq[])(Lexer*) = {
		parse_LBRC,
		parse_logic,
		parse_RBRC,
	};
	return parse_seq(lexer, 3, seq);
}

Node *parse_arr(Lexer *lexer)
{
	Node *lcrl, *items, *rcrl;

	if ((lcrl = parse_LCRL(lexer)) == NULL)
		return NULL;
	Node_free(lcrl);

	items = parse_sepby(lexer, parse_logic, parse_COMA);

	if ((rcrl = parse_RCRL(lexer)) != NULL)
		Node_free(lcrl);

	items->token = T_ARR;
	return items;
}

Node *parse_call(Lexer *lexer)
{
	Node *dot, *args;

	if ((dot = parse_dot(lexer)) == NULL)
		return NULL;

	args = parse_many(lexer, parse_arg);
	Node_push(dot, args);

	return args;
}

Node *parse_arg(Lexer *lexer)
{
	Node *res;
	Node *(*seq[])(Lexer*) = { parse_LPAR, parse_logic, parse_RPAR };
	if ((res = parse_seq(lexer, 3, seq)) != NULL)
		return res;

	Node *(*either[])(Lexer*) = {
		parse_range,
		parse_num,
		parse_STR,
		parse_CHR,
		parse_ptr,
		parse_arr,
		parse_SYM,
	};
	return parse_either(lexer, sizeof(either)/sizeof(either[0]), either);
}

Node *parse_dot(Lexer *lexer)
{
	Node *sym, *dot, *dotop;

	if ((sym = parse_SYM(lexer)) == NULL)
		return NULL;

	if ((dot = parse_DOT(lexer)) == NULL)
		return sym;
	Node_push(dot, sym);

	if ((dotop = parse_dot(lexer)) == NULL)
		return dot;
	Node_push(dot, dotop);

	return dot;
}

Node *parse_many(Lexer *lexer, Node *(*parser)(Lexer*))
{
	Node *stmts = Node_new((Range){0, 0}, T_STMTS, NULL);

	Node *result = NULL;
	while ((result = parser(lexer)) != NULL)
		Node_push(stmts, result);

	return stmts;
}

Node *parse_sepby(Lexer *lexer, Node *(*parser)(Lexer*), Node *(*delim)(Lexer*))
{
	Node *stmts = Node_new((Range){0, 0}, T_STMTS, NULL);

	Node *result = NULL;
	while ((result = parser(lexer)) != NULL) {
		Node_push(stmts, result);
		if ((result = delim(lexer)) == NULL)
			break;
		Node_push(stmts, result);
	}

	return stmts;
}

Node *parse_either(Lexer *lexer, size_t count, Node *(*parsers[])(Lexer*))
{
	Node *result = NULL;
	size_t i;

	for (i = 0; i < count; i++) {
		if ((result = parsers[i](lexer)) != NULL)
			return result;
	}

	return NULL;
}

Node *parse_seq(Lexer *lexer, size_t count, Node *(*parsers[])(Lexer*))
{
	Node *seq = Node_new((Range){0, 0}, T_STMTS, NULL);
	size_t i;

	Lexer backup = *lexer;
	for (i = 0; i < count; i++) {
		Node *result = parsers[i](lexer);
		if (result == NULL) {
			*lexer = backup;
			Node_free(seq);
			return NULL;
		}
		Node_push(seq, result);
	}

	return seq;
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
