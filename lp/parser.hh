#ifndef LORD_LP_PARSER_HH
#define LORD_LP_PARSER_HH

/* interface */
std::optional<Node> parse(Lexer *lexer);

/* grammar */
std::optional<Node> parse_stmt(Lexer *lexer);

std::optional<Node> parse_import(Lexer *lexer);

std::optional<Node> parse_for(Lexer *lexer);
std::optional<Node> parse_forcond(Lexer *lexer);
std::optional<Node> parse_forstmt(Lexer *lexer);

std::optional<Node> parse_if(Lexer *lexer);
std::optional<Node> parse_else(Lexer *lexer);

std::optional<Node> parse_fn(Lexer *lexer);
std::optional<Node> parse_fbody(Lexer *lexer);
std::optional<Node> parse_ret(Lexer *lexer);

std::optional<Node> parse_bind(Lexer *lexer);
std::optional<Node> parse_typedsym(Lexer *lexer);
std::optional<Node> parse_bindop(Lexer *lexer);
std::optional<Node> parse_typeanno(Lexer *lexer);
std::optional<Node> parse_subtype(Lexer *lexer);

std::optional<Node> parse_pipe(Lexer *lexer);
std::optional<Node> parse_logic(Lexer *lexer);
std::optional<Node> parse_eqcmp(Lexer *lexer);
std::optional<Node> parse_difcmp(Lexer *lexer);

std::optional<Node> parse_expr(Lexer *lexer);
std::optional<Node> parse_term(Lexer *lexer);
std::optional<Node> parse_fact(Lexer *lexer);
std::optional<Node> parse_cast(Lexer *lexer);
std::optional<Node> parse_not(Lexer *lexer);
std::optional<Node> parse_neg(Lexer *lexer);
std::optional<Node> parse_atom(Lexer *lexer);

std::optional<Node> parse_call(Lexer *lexer);
std::optional<Node> parse_arg(Lexer *lexer);

std::optional<Node> parse_lit(Lexer *lexer);
std::optional<Node> parse_arr(Lexer *lexer);
std::optional<Node> parse_range(Lexer *lexer);
std::optional<Node> parse_dot(Lexer *lexer);

/* higher-order parsers */
using Parser = std::optional<Node> (*)(Lexer*);

std::optional<Node> parse_many(Lexer *lexer, Parser p);
std::optional<Node> parse_sepby(Lexer *lexer, Parser p, Parser delim);
std::optional<Node> parse_either(Lexer *lexer, std::vector<Parser> ps);
std::optional<Node> parse_seq(Lexer *lexer, std::vector<Parser> ps);

/* primitive parsers */
#define X(token) std::optional<Node> parse_##token(Lexer *lexer);
	LORD_LP_TOKENS
#undef X

#endif
