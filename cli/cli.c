/* C libs */
#include <unistd.h>

/* Lord's libs */
#include <helpers.h>
#include <parser.h>

/* Ext libs */
#include <readline/readline.h>
#include <readline/history.h>

/* cli state */
int repl = 0;

/* getopt */
extern int  getopt(int, char**, char*);
extern char *optarg;

void lex_file(char *fpath)
{
	char *s = NULL;
	if ((s = ftoa(fpath)) == NULL) {
		puts("failed to open file");
		return;
	}

	Lexer *lexer = Lexer_new(s);
	while (Lexer_next(lexer) != T_EOF)
		Lexer_print(lexer);

	Lexer_free(lexer);
}

void lex_repl()
{
	Lexer *lexer;

	while (1) {
		char *src = readline(" > ");
		if (src && *src)
			add_history(src);
		else
			break;

		if (strcmp(src, "exit") == 0) {
			free(src);
			break;
		}

		lexer = Lexer_new(src);
		while (Lexer_next(lexer) != T_EOF)
			Lexer_print(lexer);

		Lexer_free(lexer);
	}
}

void parse_file(char *fpath)
{
	char *s = NULL;
	if ((s = ftoa(fpath)) == NULL) {
		puts("failed to open file");
		return;
	}

	Lexer *lexer = Lexer_new(s);
	Node *ast = parse(lexer);

	Node_print(ast);
	Node_free(ast);
	Lexer_free(lexer);
}

void parse_repl()
{
	Lexer *lexer;
	Node *ast;

	while (1) {
		char *src = readline(" > ");
		if (src && *src)
			add_history(src);
		else
			break;

		if (strcmp(src, "exit") == 0) {
			free(src);
			break;
		}

		lexer = Lexer_new(src);
		ast = parse(lexer);

		if (ast) {
			Node_print(ast);
			Node_free(ast);
		}

		Lexer_free(lexer);
	}
}

void simple_file(char *fpath)
{
}

int main(int argc, char **argv)
{
	int opt = 0;

	while ((opt = getopt(argc, argv, "l:p:c:")) != -1) {
		switch (opt) {
		case 'l':
			if (optarg == NULL)
				lex_repl();
			else
				lex_file(optarg);
			break;

		case 'p':
			if (optarg == NULL)
				parse_repl();
			else
				parse_file(optarg);
			break;

		case 'c':
			compile_file(optarg);
			break;

		default:
			printf("unknown option %c\n", opt);
			break;
		}
	}
}
