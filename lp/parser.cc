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
		parse_import,
		parse_for,
		parse_if,
		parse_fdef,
		parse_struct,
		parse_ret,
		parse_bind,
		parse_pipe,
		parse_PASS,
		parse_ERR,
		parse_EOL
	});
}

Node *parse_import(Lexer *lexer)
{
	Node *imp, *sym;

	if ((imp = parse_IMPORT(lexer)) == NULL)
		return NULL;

	if ((sym = parse_SYM(lexer)) != NULL)
		imp->push(sym);

	return imp;
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
		parse_pipe
	};

	return parse_either(lexer, either);
}

Node *parse_struct(Lexer *lexer)
{
	Node *type, *sym, *eq, *fbody;

	if ((type = parse_STRUCT(lexer)) == NULL)
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
	Node *_if, *pipe, *fbody, *_else;

	if ((_if = parse_IF(lexer)) == NULL)
		return NULL;

	if ((pipe = parse_pipe(lexer)) == NULL)
		return _if;
	_if->push(pipe);

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
	Node *ret, *pipe;

	if ((ret = parse_RET(lexer)) == NULL)
		return NULL;

	if ((pipe = parse_pipe(lexer)) != NULL)
		ret->push(pipe);

	return ret;
}

Node *parse_pipe(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_logic, parse_PIPE, parse_pipe })) {
		n->binarify();
		return n;
	}

	return parse_logic(lexer);
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

	if (auto pipe = parse_pipe(lexer))
		return pipe;

	if ((indent = parse_INDENT(lexer)) == NULL)
		return NULL;
	delete indent;

	stmts = parse_many(lexer, parse_stmt);
	stmts->token = T_INDENT;

	if ((dedent = parse_DEDENT(lexer)) != NULL)
		delete dedent;

	return stmts;
}

Node *parse_bind(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_typedsym, parse_bindsym, parse_pipe })) {
		n->binarify();
		return n;
	}

	if (auto n = parse_typedsym(lexer))
		return n;

	if (auto n = parse_seq(lexer, { parse_SYM, parse_bindsym, parse_pipe })) {
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
	Node *ptr_or_dot;

	if ((ptr_or_dot = parse_either(lexer, { parse_deref, parse_dot })) == NULL)
		return NULL;

	while (auto ptr = parse_deref(lexer)) {
		auto arr = new Node(ptr_or_dot->range, T_TYPEANNO, "");
		arr->push(ptr_or_dot);
		arr->push(ptr);
		ptr_or_dot = arr;
	}

	return ptr_or_dot;
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
	if (auto n = parse_seq(lexer, { parse_LPAR, parse_pipe, parse_RPAR, }))
		return n;
	return parse_cast(lexer);
}

Node *parse_cast(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_neg, parse_AS, parse_typeanno })) {
		n->token = T_CAST;
		return n;
	}
	return parse_neg(lexer);
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
		parse_structinit,
		parse_call,
		parse_arg
	});
}

Node *parse_structinit(Lexer *lexer)
{
	auto n = parse_seq(lexer, {
		parse_dot,
		parse_LCRL,
		parse_structbody,
		parse_RCRL
	});

	if (n != NULL)
		n->token = T_STRUCTINIT;

	return n;
}

Node *parse_structbody(Lexer *lexer)
{
	return parse_sepby(lexer, parse_structfield, parse_COMA);
}

Node *parse_structfield(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_SYM, parse_COLN, parse_pipe })) {
		n->binarify();
		return n;
	}
	return NULL;
}

Node *parse_range(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_INT, parse_TO, parse_INT })) {
		n->binarify();
		return n;
	}
	return NULL;
}

Node *parse_neg(Lexer *lexer)
{
	Node *sub, *_not;
	Lexer backup = *lexer;

	if ((sub = parse_SUB(lexer)) == NULL)
		return parse_not(lexer);

	if ((_not = parse_not(lexer)) == NULL ) {
		*lexer = backup;
		return NULL;
	}

	sub->push(_not);
	return _not;
}

Node *parse_deref(Lexer *lexer)
{
	Node *result = parse_seq(lexer, {
		parse_LBRC,
		parse_logic,
		parse_RBRC,
	});
	if (result == NULL)
		return NULL;

	result->token = T_DEREF;
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
		parse_pipe,
		parse_RPAR
	});
	if (res != NULL) {
		res->token = T_EXPR;
		return res;
	}

	return parse_either(lexer, {
		parse_range,
		parse_INT,
		parse_FLT,
		parse_STR,
		parse_CHR,
		parse_deref,
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
