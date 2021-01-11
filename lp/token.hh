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
	/* literals */\
	X(SYM)\
	X(INT)\
	X(FLT)\
	X(STR)\
	X(CHR)\
	\
	/* keywords */\
	X(PASS)\
	X(FN)\
	X(IF)\
	X(ELSE)\
	X(FOR)\
	X(IN)\
	X(TO)\
	X(STRUCT)\
	X(AS)\
	X(RET)\
	\
	/* operators */\
	X(EQ)\
	X(LBRC)\
	X(RBRC)\
	X(DOT)\
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
	X(AEQ)\
	X(SEQ)\
	X(MEQ)\
	X(DEQ)\
	X(DDEQ)\
	X(MOQ)\
	\
	/* logic */\
	X(AND)\
	X(ORR)\
	X(NOT)\
	X(NEQ)\
	X(EEQ)\
	X(LSS)\
	X(GTR)\
	X(LEQ)\
	X(GEQ)\
	\
	/* AST specific */\
	X(MODULE)\
	X(STMTS)\
	X(ARR)\
	X(CALL)\
	X(ARGS)\
	X(BIND)\
	X(TYPEANNO)\
	X(PTR_ACCESS)\
	X(EXPR)\
	X(CAST)\
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
