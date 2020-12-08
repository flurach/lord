#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

char *ftoa(char *fpath)
{
	FILE *fp = fopen(fpath, "r");
	if (fp == NULL)
		return NULL;

	fseek(fp, 0, SEEK_END);
	const size_t s = ftell(fp);
	rewind(fp);

	char *buf = malloc(s + 1);
	fread(buf, 1, s, fp);

	fclose(fp);
	return buf;
}

enum TokenType {
	T_ERR,
	T_EOF,
	T_EOL,

	T_SYM,
	T_STR,

	T_EQ,
};

struct Lex {
	char *it;

	enum TokenType type;
	char val[256];
};

struct Node {
	enum TokenType type;
	char val[256];
	struct Node *ns[2];
};

enum TokenType lex_next(struct Lex *lex)
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

enum TokenType lex_peek(struct Lex *lex)
{
	char *it = lex->it;
	enum TokenType type = lex_next(lex);
	lex->it = it;
	return type;
}

void lex_print(struct Lex *lex)
{
	printf("%d '%s'\n", lex->type, lex->val);
}

struct Node *lex_node(struct Lex *lex)
{
	struct Node *node = malloc(sizeof(struct Node));

	node->type = lex->type;
	strcpy(node->val, lex->val);

	node->ns[0] = NULL;
	node->ns[1] = NULL;

	return node;
}

void free_node(struct Node *node)
{
	if (node == NULL)
		return;
	free_node(node->ns[0]);
	free_node(node->ns[1]);
	free(node);
}

void node_print(struct Node *node)
{
	static int indent = 0;

	if (node == NULL)
		return;

	int x = 0;
	while (x++ < indent)
		putchar('\t');

	printf("%d '%s'\n", node->type, node->val);
	indent++;
	node_print(node->ns[0]);
	node_print(node->ns[1]);
	indent--;
}

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
