#include <fstream>
#include <optional>
#include <unistd.h>
#include <lc.hh>
#include <readline/readline.h>
#include <readline/history.h>

/* CLI state */
std::string backend = "gas-x86_64";

/* helpers */
std::optional<std::string> ftoa(char *fpath)
{
	std::ifstream ifs(fpath);
	if (ifs.is_open() == false)
		return {};
	std::string content(
		(std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>())
	);
	return content;
}

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
		auto ast = parse(&lexer);
		ast->print();
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
		auto ast = parse(&lexer);
		ast->print();
		free(src);
	}
}

void compile_file(char *fpath)
{
	if (auto maybe_m = load_module(fpath)) {
		auto m = *maybe_m;
		RegAllocVisitor(m, m.ast);
		GenVisitor(m, m.ast);

		for (auto& ins : m.ins)
			std::cout << ins << std::endl;
	} else {
		puts("failed to open file");
	}
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

		case ':': {
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
		}

		default:
			printf("unknown option %c\n", optopt);
			break;
		}
	}
}
