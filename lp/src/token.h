#ifndef LORD_LP_TOKEN_H
#define LORD_LP_TOKEN_H

#define LORD_TOKENS\
	\
	/* invisibles */\
	X(ERR)\
	X(EOF)\
	X(EOL)\
	\
	/* literals */\
	X(SYM)\
	X(STR)\
	\
	/* keywords */\
	X(FN)\
	X(EXT)\
	\
	/* operators */\
	X(EQ)\
	X(SEMI)\
	\
	/* AST specific */\
	X(MOD)\
	X(CALL)\
	\
	X(LAST)


typedef enum {
	#define X(token) T_##token,
		LORD_TOKENS
	#undef X
} Token;

static const char *Token_str[] = {
	#define X(token) #token,
		LORD_TOKENS
	#undef X
};

#endif
