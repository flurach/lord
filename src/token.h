#ifndef LORD_TOKEN_H
#define LORD_TOKEN_H

#define LORD_TOKENS\
	\
	X(ERR)\
	X(EOF)\
	X(EOL)\
	\
	X(SYM)\
	X(STR)\
	\
	X(EQ)\
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
