#ifndef LORD_LP_TOKEN_HH
#define LORD_LP_TOKEN_HH

#define LORD_LP_TOKENS\
	\
	/* invisibles */\
	X(ERR)\
	X(EOF)\
	X(EOL)\
	X(INDENT)\
	X(DEDENT)\
	\
	/* types */\
	X(NONE)\
	X(SYM)\
	X(INT)\
	X(FLT)\
	X(STR)\
	X(CHR)\
	X(ARR)\
	\
	/* keywords */\
	X(IMPORT)\
	X(FN)\
	X(IF)\
	X(THEN)\
	X(ELSE)\
	X(LET)\
	X(IN)\
	X(TO)\
	\
	/* operators */\
	X(EQ)\
	X(LBRC)\
	X(RBRC)\
	X(DOT)\
	X(DDOT)\
	X(PIPE)\
	X(ARROW)\
	\
	/* punctuation */\
	X(LPAR)\
	X(RPAR)\
	X(LCRL)\
	X(RCRL)\
	X(COMA)\
	X(SEMI)\
	X(COLN)\
	\
	/* maths */\
	X(ADD)\
	X(SUB)\
	X(MUL)\
	X(DIV)\
	X(DDIV)\
	X(MOD)\
	\
	/* logic */\
	X(AND)\
	X(ORR)\
	X(NOT)\
	X(EEQ)\
	X(NEQ)\
	X(LSS)\
	X(GTR)\
	X(LEQ)\
	X(GEQ)\
	\
	/* AST specific */\
	X(MODULE)\
	X(STMTS)\
	X(TYPEDEC)\
	X(TYPEANNO)\
	X(CALL)\
	X(ARGS)\
	\
	X(LAST)


enum Token {
	#define X(token) T_##token,
		LORD_LP_TOKENS
	#undef X
};

static const char *Token_str[] = {
	#define X(token) #token,
		LORD_LP_TOKENS
	#undef X
};

#endif
