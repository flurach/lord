/* C libs */
#include <unistd.h>

/* Lord's libs */
#include "helpers.h"
#include "parser.h"
#include "visitors/all.h"
#include "visitors/base.h"

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

void simple_file(char *fpath)
{
	char *s = NULL;
	if ((s = ftoa(fpath)) == NULL) {
		puts("failed to open file");
		return;
	}

	Lexer *lexer = Lexer_new(s);
	Node *ast = parse(lexer);

	Visitor *simple_visitor = SimpleVisitor_new();
	Visitor_visit(simple_visitor, ast);

	Visitor_free(simple_visitor);
	Node_free(ast);
	Lexer_free(lexer);
}

int main(int argc, char **argv)
{
	int opt = 0;

	while ((opt = getopt(argc, argv, "l:p:s:")) != -1) {
		switch (opt) {
		case 'l':
			lex_file(optarg);
			break;

		case 'p':
			parse_file(optarg);
			break;

		case 's':
			simple_file(optarg);
			break;

		default:
			printf("unknown option %c\n", opt);
			break;
		}
	}
}
