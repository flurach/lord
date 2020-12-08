/* C libs */
#include <unistd.h>

/* Lord's libs */
#include "helpers.h"
#include "lex.h"
#include "parser.h"

void lex_file(char *fpath)
{
	char *s = NULL;
	if ((s = ftoa(fpath)) == NULL) {
		puts("failed to open file");
		return;
	}

	struct Lex *lex = new_lex(s);
	while (lex_next(lex) != T_EOF)
		lex_print(lex);

	free_lex(lex);
}

void parse_file(char *fpath)
{
	char *s = NULL;
	if ((s = ftoa(fpath)) == NULL) {
		puts("failed to open file");
		return;
	}

	struct Lex *lex = new_lex(s);
	struct Node *ast = parse(lex);

	node_print(ast);
	free_node(ast);
	free_lex(lex);
}

int main(int argc, char **argv)
{
	int opt = 0;

	while ((opt = getopt(argc, argv, "l:p:")) != -1) {
		switch (opt) {
		case 'l':
			lex_file(optarg);
			break;

		case 'p':
			parse_file(optarg);
			break;

		default:
			printf("unknown option %c\n", opt);
			break;
		}
	}
}
