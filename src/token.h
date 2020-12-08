#ifndef LORD_TOKEN_H
#define LORD_TOKEN_H

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
	\
	/* operators */\
	X(EQ)\
	\
	/* AST specific */\
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
