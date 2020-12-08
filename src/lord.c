/* C libs */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

/* Lord's libs */
#include "helpers.h"
#include "lex.h"

struct Node *parse_fcall(struct Lex *lex)
{
	struct Node *sym, *arg;

	if (lex_peek(lex) != T_SYM)
		return NULL;

	lex_next(lex);
	sym = lex_node(lex);

	if (lex_peek(lex) != T_STR)
		return sym;
	lex_next(lex);
	arg = lex_node(lex);

	sym->ns[0] = arg;
	return sym;
}

struct Node *parse_fdef(struct Lex *lex)
{
	struct Node *sym, *eq, *fcall;

	if (lex_peek(lex) != T_SYM)
		return NULL;

	lex_next(lex);
	sym = lex_node(lex);

	if (lex_peek(lex) != T_EQ)
		return sym;
	lex_next(lex);
	eq = lex_node(lex);
	eq->ns[0] = sym;

	if ((fcall = parse_fcall(lex)) == NULL)
		return eq;

	eq->ns[1] = fcall;
	return eq;
}

struct Node *parse(struct Lex *lex)
{
	return parse_fdef(lex);
}

int main(int argc, char **argv)
{
	int opt = 0;
	char *s = NULL;
	struct Lex lex = {0};

	while ((opt = getopt(argc, argv, "l:p:")) != -1) {
		switch (opt) {
		case 'l':
			if ((s = ftoa(optarg)) == NULL) {
				puts("failed to open file");
				return 0;
			}

			lex.it = s;
			while (lex_next(&lex) != T_EOF)
				lex_print(&lex);

			free(s);
			break;

		case 'p':
			if ((s = ftoa(optarg)) == NULL) {
				puts("failed to open file");
				return 0;
			}

			lex.it = s;

			struct Node *ast = parse(&lex);
			node_print(ast);
			free_node(ast);

			free(s);
			break;

		default:
			printf("unknown option %c\n", opt);
			break;
		}
	}
}
