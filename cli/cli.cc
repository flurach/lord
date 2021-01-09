/* C libs */
#include <unistd.h>

/* Lord's libs */
#include <lc.hh>

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
	Compiler c = Compiler();

	if (!c.load_mod(std::string(fpath))) {
		puts("failed to open file");
		return;
	}

	c.print();
}

int main(int argc, char **argv)
{
	int opt = 0;

	while ((opt = getopt(argc, argv, ":l:p:c:")) != -1) {
		switch (opt) {
		case 'l':
			lex_file(optarg);
			break;

		case 'p':
			parse_file(optarg);
			break;

		case 'c':
			compile_file(optarg);
			break;

		case ':':
			switch (optopt) {
			case 'l':
				lex_repl();
				break;

			case 'p':
				parse_repl();
				break;

			default:
				printf("%c requires an arg\n", optopt);
				break;
			}
			break;

		default:
			printf("unknown option %c\n", optopt);
			break;
		}
	}
}
