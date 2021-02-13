#include "lp.hh"

std::optional<Node> parse(Lexer *lexer)
{
	if (auto modul = parse_many(lexer, parse_stmt)) {
		modul->token = T_MODULE;
		return modul;
	}
	return std::nullopt;
}

std::optional<Node> parse_stmt(Lexer *lexer)
{
	return parse_either(lexer, {
		parse_import,
		parse_for,
		parse_if,
		parse_fn,
		parse_ret,
		parse_bind,
		parse_pipe,
		parse_PASS,
		parse_ERR,
		parse_EOL
	});
}

std::optional<Node> parse_import(Lexer *lexer)
{
	std::optional<Node> import;

	if (auto parsed = parse_IMPORT(lexer))
		import = parsed;
	else
		return {};

	if (auto sym = parse_SYM(lexer))
		import->push(*sym);

	return import;
}

std::optional<Node> parse_for(Lexer *lexer)
{
	std::optional<Node> _for;

	if (auto parsed = parse_FOR(lexer))
		_for = parsed;
	else
		return std::nullopt;

	if (auto forcond = parse_forcond(lexer))
		_for->push(*forcond);
	else
		return _for;

	if (auto fbody = parse_fbody(lexer))
		_for->push(*fbody);

	return _for;
}

std::optional<Node> parse_forcond(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_SYM, parse_IN, parse_range })) {
		n->binarify();
		return n;
	}
	return parse_sepby(lexer, parse_forstmt, parse_SEMI);
}

std::optional<Node> parse_forstmt(Lexer *lexer)
{
	return parse_either(lexer, { parse_bind, parse_pipe });
}

std::optional<Node> parse_if(Lexer *lexer)
{
	std::optional<Node> _if;

	if (auto parsed = parse_IF(lexer))
		_if = parsed;
	else
		return {};

	if (auto pipe = parse_pipe(lexer))
		_if->push(*pipe);
	else
		return _if;

	if (auto fbody = parse_fbody(lexer))
		_if->push(*fbody);
	else
		return _if;

	if (auto _else = parse_else(lexer))
		_if->push(*_else);

	return _if;
}

std::optional<Node> parse_else(Lexer *lexer)
{
	std::optional<Node> _else;

	if (auto parsed = parse_ELSE(lexer))
		_else = parsed;
	else
		return {};

	auto parsers = { parse_if, parse_fbody };
	if (auto _if_or_fbody = parse_either(lexer, parsers))
		_else->push(*_if_or_fbody);

	return _else;
}

std::optional<Node> parse_fn(Lexer *lexer)
{
	std::optional<Node> fn;

	if (auto parsed = parse_FN(lexer))
		fn = parsed;
	else
		return std::nullopt;

	if (auto dot = parse_dot(lexer))
		fn->push(*dot);
	else
		return fn;

	auto args = parse_many(lexer, parse_SYM);
	args->token = T_ARGS;
	fn->push(*args);

	if (auto eq = parse_EQ(lexer))
		{}
	else
		return fn;

	if (auto fbody = parse_fbody(lexer))
		fn->push(*fbody);
	else
		return fn;

	return fn;
}

std::optional<Node> parse_fbody(Lexer *lexer)
{
	if (auto pipe = parse_pipe(lexer))
		return pipe;

	if (auto indent = parse_INDENT(lexer)) {}
	else { return std::nullopt; }

	auto stmts = parse_many(lexer, parse_stmt);
	stmts->token = T_INDENT;

	parse_DEDENT(lexer);
	return stmts;
}

std::optional<Node> parse_ret(Lexer *lexer)
{
	std::optional<Node> ret;

	if (auto parsed = parse_RET(lexer))
		ret = parsed;
	else
		return {};

	if (auto pipe = parse_pipe(lexer))
		ret->push(*pipe);

	return ret;
}

std::optional<Node> parse_bind(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_typedsym, parse_bindop, parse_pipe })) {
		n->binarify();
		return n;
	}

	return {};
}

std::optional<Node> parse_typedsym(Lexer *lexer)
{
	std::optional<Node> n = parse_seq(lexer, {
		parse_dot,
		parse_COLN,
		parse_typeanno
	});

	if (n)
		n->binarify();
	else
		return parse_dot(lexer);

	return n;
}

std::optional<Node> parse_bindop(Lexer *lexer)
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

std::optional<Node> parse_typeanno(Lexer *lexer)
{
	if (auto parsed = parse_seq(lexer, { parse_LBRC, parse_typeanno, parse_RBRC })) {
		parsed->pop();
		auto typeanno = parsed->pop();
		auto lbrc = parsed->pop();

		auto arr = Node(lbrc.range, T_ARR);
		arr.push(typeanno);
		return arr;
	}

	return parse_dot(lexer);
}

std::optional<Node> parse_pipe(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_logic, parse_PIPE, parse_pipe })) {
		n->binarify();
		return n;
	}

	return parse_logic(lexer);
}

std::optional<Node> parse_logic(Lexer *lexer)
{
	std::optional<Node> logic;

	if (auto parsed = parse_eqcmp(lexer))
		logic = parsed;
	else
		return {};

	if (auto and_or_orr = parse_either(lexer, { parse_AND, parse_ORR })) {
		and_or_orr->push(*logic);
		logic = and_or_orr;
	} else {
		return logic;
	}

	if (auto l = parse_logic(lexer))
		logic->push(*l);

	return logic;
}

std::optional<Node> parse_eqcmp(Lexer *lexer)
{
	std::optional<Node> eqcmp;

	if (auto difcmp = parse_difcmp(lexer))
		eqcmp = difcmp;
	else
		return {};

	if (auto eeq_or_neq = parse_either(lexer, { parse_EEQ, parse_NEQ })) {
		eeq_or_neq->push(*eqcmp);
		eqcmp = eeq_or_neq;
	} else {
		return eqcmp;
	}

	if (auto e = parse_eqcmp(lexer))
		eqcmp->push(*e);

	return eqcmp;
}

std::optional<Node> parse_difcmp(Lexer *lexer)
{
	std::optional<Node> difcmp;

	if (auto expr = parse_expr(lexer))
		difcmp = expr;
	else
		return {};

	auto parsers = {
		parse_LSS,
		parse_GTR,
		parse_LEQ,
		parse_GEQ
	};
	if (auto cmp = parse_either(lexer, parsers)) {
		cmp->push(*difcmp);
		difcmp = cmp;
	} else {
		return difcmp;
	}

	if (auto d = parse_difcmp(lexer))
		difcmp->push(*d);

	return difcmp;
}

std::optional<Node> parse_expr(Lexer *lexer)
{
	std::optional<Node> expr;

	if (auto term = parse_term(lexer))
		expr = term;
	else
		return {};

	while (auto op = parse_either(lexer, { parse_ADD, parse_SUB })) {
		op->push(*expr);
		expr = op;

		if (auto term = parse_term(lexer))
			expr->push(*term);
		else
			break;
	}

	return expr;
}

std::optional<Node> parse_term(Lexer *lexer)
{
	std::optional<Node> term;

	if (auto fact = parse_fact(lexer))
		term = fact;
	else
		return {};

	while (auto op = parse_either(lexer, { parse_MUL, parse_DIV, parse_DDIV, parse_MOD })) {
		op->push(*term);
		term = op;

		if (auto fact = parse_fact(lexer))
			term->push(*fact);
		else
			break;
	}

	return term;
}

std::optional<Node> parse_fact(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_LPAR, parse_pipe, parse_RPAR, })) {
		n->pop();
		auto pipe = n->pop();
		n->pop();
		return pipe;
	}
	return parse_cast(lexer);
}

std::optional<Node> parse_cast(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_neg, parse_AS, parse_typeanno })) {
		n->binarify();
		return n;
	}
	return parse_neg(lexer);
}

std::optional<Node> parse_not(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_NOT, parse_neg })) {
		auto neg = n->pop();
		auto _not = n->pop();
		_not.push(neg);
		return _not;
	}
	return parse_lit(lexer);
}

std::optional<Node> parse_neg(Lexer *lexer)
{
	std::optional<Node> neg;
	Lexer backup = *lexer;

	if (auto sub = parse_SUB(lexer))
		neg = sub;
	else
		return parse_atom(lexer);

	if (auto atom = parse_atom(lexer)) {
		neg->push(*atom);
	} else {
		*lexer = backup;
		return {};
	}

	return neg;
}

std::optional<Node> parse_atom(Lexer *lexer)
{
	return parse_either(lexer, {
		parse_call,
		parse_lit
	});
}

std::optional<Node> parse_call(Lexer *lexer)
{
	std::optional<Node> call;

	if (auto dot = parse_dot(lexer))
		call = dot;
	else
		return {};

	auto c = Node(call->range, T_CALL);
	c.push(*call);
	*call = c;

	auto args = parse_many(lexer, parse_arg);
	args->token = T_ARGS;
	call->push(*args);

	return call;
}

std::optional<Node> parse_arg(Lexer *lexer)
{
	auto res = parse_seq(lexer, {
		parse_LPAR,
		parse_pipe,
		parse_RPAR
	});

	if (res) {
		res->pop();
		auto expr = res->pop();
		res->pop();
		return expr;
	}

	return parse_lit(lexer);
}

std::optional<Node> parse_lit(Lexer *lexer)
{
	return parse_either(lexer, {
		parse_arr,
		parse_range,
		parse_INT,
		parse_FLT,
		parse_STR,
		parse_CHR,
		parse_dot,
	});
}

std::optional<Node> parse_arr(Lexer *lexer)
{
	if (auto lcrl = parse_LBRC(lexer)) {}
	else return {};

	auto arr = parse_sepby(lexer, parse_logic, parse_COMA);
	arr->token = T_ARR;

	parse_RBRC(lexer);
	return arr;
}

std::optional<Node> parse_range(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_INT, parse_TO, parse_INT })) {
		n->binarify();
		return n;
	}
	return std::nullopt;
}

std::optional<Node> parse_dot(Lexer *lexer)
{
	if (auto n = parse_seq(lexer, { parse_SYM, parse_DOT, parse_dot })) {
		n->binarify();
		return n;
	}

	return parse_SYM(lexer);
}

std::optional<Node> parse_many(Lexer *lexer, Parser p)
{
	Node stmts = Node((Range){0, 0}, T_STMTS);

	while (auto result = p(lexer))
		stmts.push(*result);

	return std::optional<Node>{stmts};
}

std::optional<Node> parse_sepby(Lexer *lexer, Parser p, Parser delim)
{
	Node stmts = Node((Range){0, 0}, T_STMTS);

	while (auto result = p(lexer)) {
		stmts.push(*result);
		if (auto result = delim(lexer)) {}
		else break;
	}

	return stmts;
}

std::optional<Node> parse_either(Lexer *lexer, std::vector<Parser> ps)
{
	for (auto p : ps) {
		if (auto result = p(lexer))
			return result;
	}
	return std::nullopt;
}

std::optional<Node> parse_seq(Lexer *lexer, std::vector<Parser> ps)
{
	Node seq = Node((Range){0, 0}, T_STMTS);
	Lexer backup = *lexer;

	for (auto p : ps) {
		if (auto result = p(lexer)) {
			seq.push(*result);
		} else {
			*lexer = backup;
			return std::nullopt;
		}
	}

	return seq;
}

#define X(t)\
std::optional<Node> parse_##t(Lexer *lexer)\
{\
	if (lexer->peek() != T_##t)\
		return std::nullopt;\
	lexer->next();\
	return std::optional<Node>{Node(lexer->range, lexer->token, lexer->val)};\
}
	LORD_LP_TOKENS
#undef X
