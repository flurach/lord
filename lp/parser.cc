#include "lp.hh"

Node *parse(Lexer *lexer)
{
	Node *module = parse_many(lexer, parse_stmt);
	module->token = T_MODULE;
	return module;
}

Node *parse_stmt(Lexer *lexer)
{
	return parse_either(lexer, {
		parse_for,
		parse_if,
		parse_fdef,
		parse_type,
		parse_bind,
		parse_ret,
		parse_logic,
		parse_PASS,
		parse_EOL
	});
}

Node *parse_for(Lexer *lexer)
{
	Node *_for, *forcond, *fbody;

	if ((_for = parse_FOR(lexer)) == NULL)
		return NULL;

	if ((forcond = parse_forcond(lexer)) == NULL)
		return _for;
	_for->push(forcond);

	if ((fbody = parse_fbody(lexer)) == NULL)
		return _for;
	_for->push(fbody);

	return _for;
}

Node *parse_forcond(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_SYM, parse_IN, parse_range }))
		return n;
	return parse_sepby(lexer, parse_forlogic, parse_SEMI);
}

Node *parse_forlogic(Lexer *lexer)
{
	auto either = {
		parse_bind,
		parse_logic
	};

	return parse_either(lexer, either);
}

Node *parse_type(Lexer *lexer)
{
	Node *type, *sym, *eq, *fbody;

	if ((type = parse_TYPE(lexer)) == NULL)
		return NULL;

	if ((sym = parse_SYM(lexer)) == NULL)
		return type;
	type->push(sym);

	if ((eq = parse_EQ(lexer)) == NULL)
		return type;
	type->push(eq);

	if ((fbody = parse_fbody(lexer)) == NULL)
		return type;
	type->push(fbody);

	return type;
}

Node *parse_if(Lexer *lexer)
{
	Node *_if, *logic, *fbody, *_else;

	if ((_if = parse_IF(lexer)) == NULL)
		return NULL;

	if ((logic = parse_logic(lexer)) == NULL)
		return _if;
	_if->push(logic);

	if ((fbody = parse_fbody(lexer)) == NULL)
		return _if;
	_if->push(fbody);

	if ((_else = parse_else(lexer)) == NULL)
		return _if;
	_if->push(_else);

	return _if;
}

Node *parse_else(Lexer *lexer)
{
	Node *_else, *_if_or_fbody;

	if ((_else = parse_ELSE(lexer)) == NULL)
		return NULL;

	auto parsers = {
		parse_if,
		parse_fbody
	};

	if ((_if_or_fbody = parse_either(lexer, parsers)) == NULL)
		return _else;
	_else->push(_if_or_fbody);

	return _else;
}

Node *parse_ret(Lexer *lexer)
{
	Node *ret, *logic;

	if ((ret = parse_RET(lexer)) == NULL)
		return NULL;

	if ((logic = parse_logic(lexer)) != NULL)
		ret->push(logic);

	return ret;
}

Node *parse_logic(Lexer *lexer)
{
	Node *eqcmp, *and_or_orr, *logic;

	if ((eqcmp = parse_eqcmp(lexer)) == NULL)
		return NULL;

	auto parsers = {
		parse_AND,
		parse_ORR
	};
	if ((and_or_orr = parse_either(lexer, parsers)) == NULL)
		return eqcmp;
	and_or_orr->push(eqcmp);

	if ((logic = parse_logic(lexer)) == NULL)
		return and_or_orr;
	and_or_orr->push(logic);

	return and_or_orr;
}

Node *parse_eqcmp(Lexer *lexer)
{
	Node *difcmp, *eeq_or_neq, *eqcmp;

	if ((difcmp = parse_difcmp(lexer)) == NULL)
		return NULL;

	auto parsers = {
		parse_EEQ,
		parse_NEQ
	};
	if ((eeq_or_neq = parse_either(lexer, parsers)) == NULL)
		return difcmp;
	eeq_or_neq->push(difcmp);

	if ((eqcmp = parse_eqcmp(lexer)) == NULL)
		return eeq_or_neq;
	eeq_or_neq->push(eqcmp);

	return eeq_or_neq;
}

Node *parse_difcmp(Lexer *lexer)
{
	Node *expr, *cmp, *difcmp;

	if ((expr = parse_expr(lexer)) == NULL)
		return NULL;

	auto parsers = {
		parse_LSS,
		parse_GTR,
		parse_LEQ,
		parse_GEQ
	};
	if ((cmp = parse_either(lexer, parsers)) == NULL)
		return expr;
	cmp->push(expr);

	if ((difcmp = parse_difcmp(lexer)) == NULL)
		return cmp;
	cmp->push(difcmp);

	return cmp;
}

Node *parse_fdef(Lexer *lexer)
{
	Node *fn, *dot, *args, *eq, *fbody;

	if ((fn = parse_FN(lexer)) == NULL)
		return NULL;

	if ((dot = parse_dot(lexer)) == NULL)
		return NULL;
	fn->push(dot);

	args = parse_many(lexer, parse_SYM);
	args->token = T_ARGS;
	fn->push(args);

	if ((eq = parse_EQ(lexer)) == NULL)
		return fn;
	fn->push(eq);

	if ((fbody = parse_fbody(lexer)) == NULL)
		return fbody;
	fn->push(fbody);

	return fn;
}

Node *parse_fbody(Lexer *lexer)
{
	Node *indent, *stmts, *dedent;

	if (auto expr = parse_expr(lexer))
		return expr;

	if ((indent = parse_INDENT(lexer)) == NULL)
		return NULL;
	delete indent;

	stmts = parse_many(lexer, parse_stmt);

	if ((dedent = parse_DEDENT(lexer)) != NULL)
		delete dedent;

	return stmts;
}

Node *parse_bind(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_typedsym, parse_bindsym, parse_logic })) {
		n->binarify();
		return n;
	}

	if (auto n = parse_typedsym(lexer))
		return n;

	if (auto n = parse_seq(lexer, { parse_SYM, parse_bindsym, parse_logic })) {
		n->binarify();
		return n;
	}

	return NULL;
}

Node *parse_bindsym(Lexer *lexer)
{
	return parse_either(lexer, {
		parse_EQ,
		parse_AEQ,
		parse_SEQ,
		parse_MEQ,
		parse_DEQ,
		parse_DDEQ,
		parse_MOQ,
	});
}

Node *parse_typedsym(Lexer *lexer)
{
	Node *n = parse_seq(lexer, {
		parse_dot,
		parse_COLN,
		parse_typeanno
	});

	if (n == NULL)
		return NULL;

	n->binarify();
	return n;
}

Node *parse_typeanno(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_LBRC, parse_dot, parse_RBRC })) {
		n->token = T_TYPEANNO;
		return n;
	}

	if (auto n = parse_seq(lexer, { parse_dot, parse_LBRC, parse_logic, parse_RBRC })) {
		n->token = T_TYPEANNO;
		return n;
	}

	return parse_dot(lexer);
}

Node *parse_expr(Lexer *lexer)
{
	Node *term, *op;

	if ((term = parse_term(lexer)) == NULL)
		return NULL;

	while (true) {
		if ((op = parse_either(lexer, { parse_ADD, parse_SUB })) == NULL)
			break;
		op->push(term);
		term = op;

		if ((op = parse_term(lexer)) == NULL)
			break;
		term->push(op);
	}

	return term;
}

Node *parse_term(Lexer *lexer)
{
	Node *fact, *op;

	if ((fact = parse_fact(lexer)) == NULL)
		return NULL;

	while (true) {
		if ((op = parse_either(lexer, { parse_MUL, parse_DIV, parse_DDIV, parse_MOD })) == NULL)
			break;
		op->push(fact);
		fact = op;

		if ((op = parse_fact(lexer)) == NULL)
			break;
		fact->push(op);
	}

	return fact;
}

Node *parse_fact(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_LPAR, parse_logic, parse_RPAR, }))
		return n;
	return parse_cast(lexer);
}

Node *parse_cast(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_not, parse_AS, parse_typeanno })) {
		n->token = T_CAST;
		return n;
	}
	return parse_not(lexer);
}

Node *parse_not(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_NOT, parse_lit }))
		return n;
	return parse_lit(lexer);
}

Node *parse_lit(Lexer *lexer)
{
	return parse_either(lexer, {
		parse_call,
		parse_arg
	});
}

Node *parse_range(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_num, parse_TO, parse_num })) {
		n->binarify();
		return n;
	}
	return NULL;
}

Node *parse_num(Lexer *lexer)
{
	Node *sub, *int_or_flt;
	auto parsers = { parse_INT, parse_FLT };

	Lexer backup = *lexer;
	if ((sub = parse_SUB(lexer)) == NULL)
		return parse_either(lexer, parsers);

	if ((int_or_flt = parse_either(lexer, parsers)) == NULL) {
		*lexer = backup;
		return NULL;
	}

	sub->push(int_or_flt);
	return sub;
}

Node *parse_ptr(Lexer *lexer)
{
	Node *result = parse_seq(lexer, {
		parse_LBRC,
		parse_logic,
		parse_RBRC,
	});
	if (result == NULL)
		return NULL;

	result->token = T_PTR_ACCESS;
	return result;
}

Node *parse_arr(Lexer *lexer)
{
	Node *lcrl, *items, *rcrl;

	if ((lcrl = parse_LCRL(lexer)) == NULL)
		return NULL;
	Node *arr = new Node(lcrl->range, T_ARR);
	arr->push(lcrl);

	items = parse_sepby(lexer, parse_logic, parse_COMA);
	arr->push(items);

	if ((rcrl = parse_RCRL(lexer)) != NULL)
		arr->push(rcrl);

	return arr;
}

Node *parse_call(Lexer *lexer)
{
	Node *dot, *args;

	if ((dot = parse_dot(lexer)) == NULL)
		return NULL;
	Node *call = new Node(dot->range, T_CALL);
	call->push(dot);

	args = parse_many(lexer, parse_arg);
	args->token = T_ARGS;
	call->push(args);

	return call;
}

Node *parse_arg(Lexer *lexer)
{
	auto res = parse_seq(lexer, {
		parse_LPAR,
		parse_logic,
		parse_RPAR
	});
	if (res != NULL) {
		res->token = T_EXPR;
		return res;
	}

	return parse_either(lexer, {
		parse_range,
		parse_num,
		parse_STR,
		parse_CHR,
		parse_ptr,
		parse_arr,
		parse_dot,
	});
}

Node *parse_dot(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_SYM, parse_DOT, parse_dot })) {
		n->binarify();
		return n;
	}

	return parse_SYM(lexer);
}

Node *parse_many(Lexer *lexer, Node *(*parser)(Lexer*))
{
	Node *stmts = new Node((Range){0, 0}, T_STMTS);

	Node *result = NULL;
	while ((result = parser(lexer)) != NULL)
		stmts->push(result);

	return stmts;
}

Node *parse_sepby(Lexer *lexer, Node *(*parser)(Lexer*), Node *(*delim)(Lexer*))
{
	Node *stmts = new Node((Range){0, 0}, T_STMTS);

	Node *result = NULL;
	while ((result = parser(lexer)) != NULL) {
		stmts->push(result);
		if ((result = delim(lexer)) == NULL)
			break;
		stmts->push(result);
	}

	return stmts;
}

Node *parse_either(Lexer *lexer, std::vector<Node *(*)(Lexer*)> parsers)
{
	for (auto p : parsers) {
		Node *result = NULL;
		if ((result = p(lexer)) != NULL)
			return result;
	}
	return NULL;
}

Node *parse_seq(Lexer *lexer, std::vector<Node *(*)(Lexer*)> parsers)
{
	Node *seq = new Node((Range){0, 0}, T_STMTS);
	Lexer backup = *lexer;

	for (auto p : parsers) {
		Node *result = p(lexer);
		if (result == NULL) {
			*lexer = backup;
			delete seq;
			return NULL;
		}
		seq->push(result);
	}

	return seq;
}

#define X(t)\
Node *parse_##t(Lexer *lexer)\
{\
	if (lexer->peek() != T_##t)\
		return NULL;\
	lexer->next();\
	return new Node(lexer->range, lexer->token, lexer->val);\
}
	LORD_LP_TOKENS
#undef X
