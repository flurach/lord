/* C libs */
#include <unistd.h>

/* Lord's libs */
#include <helpers.hh>
#include <parser.hh>

/* Ext libs */
#include <readline/readline.h>
#include <readline/history.h>

/* cli state */
int repl = 0;

void lex_file(char *fpath)
{
	if (auto s = ftoa(fpath)) {
		Lexer lexer = Lexer(*s);
		while (lexer.next() != T_EOF)
			lexer.print();
	} else {
		puts("failed to open file");
	}
}

void lex_repl()
{
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

		Lexer lexer = Lexer(src);
		while (lexer.next() != T_EOF)
			lexer.print();
	}
}

void parse_file(char *fpath)
{
	if (auto s = ftoa(fpath)) {
		Lexer lexer = Lexer(*s);
		Node *ast = parse(&lexer);
		ast->print();
		delete ast;
	} else {
		puts("failed to open file");
	}
}

void parse_repl()
{
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

		Lexer lexer = Lexer(src);
		Node *ast = parse(&lexer);
		ast->print();
		delete ast;
		free(src);
	}
}

void compile_file(char *fpath)
{
	(void)fpath;
}

int main(int argc, char **argv)
{
	int opt = 0;

	while ((opt = getopt(argc, argv, "l::p::c::")) != -1) {
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
