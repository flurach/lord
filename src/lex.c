#include "lex.h"

enum Token lex_next(struct Lex *lex)
{
	char *vi = lex->val;

	/* skip whitespace */
	while (isspace(*lex->it))
		lex->it++;

	/* comments */
	if (*lex->it == '#') {
		while (*lex->it != '\n' && *lex->it != '\0')
			lex->it++;
		return lex_next(lex);
	}

	/* symbols */
	else if (isalpha(*lex->it)) {
		lex->type = T_SYM;
		while (isalpha(*lex->it))
			*vi++ = *lex->it++;
	}

	/* strings */
	else if (*lex->it == '\'' || *lex->it == '\"') {
		lex->type = T_STR;
		const char pair = *lex->it++;
		while (*lex->it != pair && *lex->it != '\0')
			*vi++ = *lex->it++;
		lex->it++;
	}

	/* operators */
	else if (*lex->it == '=') {
		lex->type = T_EQ;
		*vi++ = *lex->it++;
	}

	/* end of file */
	else if (*lex->it == '\0') {
		lex->type = T_EOF;
	}

	*vi = '\0';
	return lex->type;
}

enum Token lex_peek(struct Lex *lex)
{
	char *it = lex->it;
	enum Token type = lex_next(lex);
	lex->it = it;
	return type;
}

void lex_print(struct Lex *lex)
{
	printf("%d '%s'\n", lex->type, lex->val);
}

struct Node *lex_node(struct Lex *lex)
{
	return new_node(lex->type, strdup(lex->val));
}
