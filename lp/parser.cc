#include "lp.hh"
#include "parser.hh"

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
		parse_fn,
		parse_ERR
	});
}

std::optional<Node> parse_import(Lexer *lexer)
{
	Node import;

	if (auto parsed = parse_IMPORT(lexer))
		import = *parsed;
	else
		return {};

	if (auto sym = parse_SYM(lexer))
		import.push(*sym);

	return import;
}

std::optional<Node> parse_fn(Lexer *lexer)
{
	Node fn;

	if (auto parsed = parse_SYM(lexer))
		fn = *parsed;
	else
		return {};
	fn.token = T_FN;

	auto args = *parse_many(lexer, parse_SYM);
	args.token = T_ARGS;
	fn.push(args);

	if (auto eq = parse_EQ(lexer)) {}
	else return fn;

	if (auto expr = parse_expr(lexer))
		fn.push(*expr);

	return fn;
}

std::optional<Node> parse_expr(Lexer *lexer)
{
	return parse_either(lexer, {
		parse_if,
		parse_let,
		parse_pipe
	});
}

std::optional<Node> parse_if(Lexer *lexer)
{
	std::optional<Node> _if;

	if (auto parsed = parse_IF(lexer))
		_if = parsed;
	else
		return {};

	if (auto parsed = parse_expr(lexer))
		_if->push(*parsed);
	else
		return _if;

	if (auto parsed = parse_THEN(lexer)) {}
	else return _if;

	if (auto parsed = parse_expr(lexer))
		_if->push(*parsed);
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

	auto parsers = { parse_if, parse_expr };
	if (auto parsed = parse_either(lexer, parsers))
		_else->push(*parsed);

	return _else;
}

std::optional<Node> parse_let(Lexer *lexer)
{
	Node let;

	if (auto parsed = parse_LET(lexer))
		let = *parsed;
	else
		return {};

	if (auto parsed = parse_SYM(lexer))
		let.push(*parsed);
	else
		return let;

	if (auto parsed = parse_EQ(lexer)) {}
	else return let;

	if (auto parsed = parse_expr(lexer))
		let.push(*parsed);
	else
		return let;

	if (auto parsed = parse_seq(lexer, { parse_IN, parse_expr }))
		let.push(parsed->at(1));

	return let;
}

std::optional<Node> parse_pipe(Lexer *lexer)
{
	Node pipe;

	if (auto parsed = parse_logic(lexer))
		pipe = *parsed;
	else
		return {};

	while (auto op = parse_PIPE(lexer)) {
		op->push(pipe);
		pipe = *op;

		if (auto parsed = parse_logic(lexer))
			pipe.push(*parsed);
		else
			break;
	}

	return pipe;
}

std::optional<Node> parse_logic(Lexer *lexer)
{
	Node logic;

	if (auto parsed = parse_eqcmp(lexer))
		logic = *parsed;
	else
		return {};

	while (auto op = parse_either(lexer, { parse_ADD, parse_ORR })) {
		op->push(logic);
		logic = *op;

		if (auto parsed = parse_eqcmp(lexer))
			logic.push(*parsed);
		else
			break;
	}

	return logic;
}

std::optional<Node> parse_eqcmp(Lexer *lexer)
{
	Node eqcmp;

	if (auto parsed = parse_difcmp(lexer))
		eqcmp = *parsed;
	else
		return {};

	while (auto op = parse_either(lexer, { parse_EEQ, parse_NEQ })) {
		op->push(eqcmp);
		eqcmp = *op;

		if (auto parsed = parse_difcmp(lexer))
			eqcmp.push(*parsed);
		else
			break;
	}

	return eqcmp;
}

std::optional<Node> parse_difcmp(Lexer *lexer)
{
	Node difcmp;

	if (auto parsed = parse_math(lexer))
		difcmp = *parsed;
	else
		return {};

	while (auto op = parse_either(lexer, { parse_LSS, parse_GTR, parse_LEQ, parse_GEQ })) {
		op->push(difcmp);
		difcmp = *op;

		if (auto parsed = parse_math(lexer))
			difcmp.push(*parsed);
		else
			break;
	}

	return difcmp;
}

std::optional<Node> parse_math(Lexer *lexer)
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
	return parse_not(lexer);
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
