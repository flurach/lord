#ifndef LORD_LP_PARSER_HH
#define LORD_LP_PARSER_HH

/* interface */
Node *parse(Lexer *lexer);

/* grammar */
Node *parse_stmt(Lexer *lexer);

Node *parse_for(Lexer *lexer);
Node *parse_forcond(Lexer *lexer);
Node *parse_forlogic(Lexer *lexer);

Node *parse_struct(Lexer *lexer);

Node *parse_if(Lexer *lexer);
Node *parse_else(Lexer *lexer);

Node *parse_ret(Lexer *lexer);

Node *parse_logic(Lexer *lexer);
Node *parse_eqcmp(Lexer *lexer);
Node *parse_difcmp(Lexer *lexer);

Node *parse_fdef(Lexer *lexer);
Node *parse_fbody(Lexer *lexer);

Node *parse_bind(Lexer *lexer);
Node *parse_bindsym(Lexer *lexer);
Node *parse_typedsym(Lexer *lexer);
Node *parse_typeanno(Lexer *lexer);

Node *parse_expr(Lexer *lexer);
Node *parse_term(Lexer *lexer);
Node *parse_fact(Lexer *lexer);

Node *parse_cast(Lexer *lexer);
Node *parse_not(Lexer *lexer);
Node *parse_lit(Lexer *lexer);

Node *parse_range(Lexer *lexer);
Node *parse_num(Lexer *lexer);
Node *parse_ptr(Lexer *lexer);
Node *parse_arr(Lexer *lexer);

Node *parse_call(Lexer *lexer);
Node *parse_arg(Lexer *lexer);

Node *parse_dot(Lexer *lexer);

/* higher-order parsers */
Node *parse_many(Lexer *lexer, Node *(*parser)(Lexer*));
Node *parse_sepby(Lexer *lexer, Node *(*parser)(Lexer*), Node *(*delim)(Lexer*));
Node *parse_either(Lexer *lexer, std::vector<Node *(*)(Lexer*)> parsers);
Node *parse_seq(Lexer *lexer, std::vector<Node *(*)(Lexer*)> parsers);

/* primitive parsers */
#define X(token) Node *parse_##token(Lexer *lexer);
	LORD_LP_TOKENS
#undef X

#endif
