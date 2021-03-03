#include <fstream>
#include <optional>
#include <unistd.h>
#include <lc.hh>
#include <readline/readline.h>
#include <readline/history.h>

/* CLI state */
std::string backend = "gas-x86_64-intel";

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

void analyse_file(char *fpath)
{
	if (auto maybe_m = load_module(fpath)) {
		auto m = *maybe_m;
		pipe_all_passes(m);

		std::cout << "AST:" << std::endl;
		m.ast.print(1);

		std::cout << "\nFNS:" << std::endl;
		for (auto& pair : m.fns) {
			std::cout << '\t' << pair.first << ":" << std::endl;
			pair.second.print(2);
		}
	} else {
		puts("failed to open file");
	}
}

void analyse_repl()
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

		auto m = Module();
		m.src = src;
		auto l = Lexer(m.src);
		m.ast = *parse(&l);
		pipe_all_passes(m);

		std::cout << "AST:" << std::endl;
		m.ast.print(1);

		std::cout << "\nFNS:" << std::endl;
		for (auto& pair : m.fns) {
			std::cout << pair.first << ":" << std::endl;
			pair.second.print(1);
		}

		free(src);
	}
}

void compile_file(char *fpath)
{
	if (auto maybe_m = load_module(fpath)) {
		auto m = *maybe_m;
		pipe_all_passes(m);

		if (backend == "raw") {
			for (auto& ins : m.ins)
				std::cout << ins << std::endl;
		} else if (backend == "gas-x86_64-intel") {
			std::cout << GasX86_64_Intel::transpile(m) << std::endl;
		}
	} else {
		puts("failed to open file");
	}
}

void compile_repl()
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

		auto m = Module();
		m.src = src;
		auto l = Lexer(m.src);
		m.ast = *parse(&l);
		pipe_all_passes(m);

		if (backend == "raw") {
			for (auto& ins : m.ins)
				std::cout << ins << std::endl;
		} else if (backend == "gas-x86_64-intel") {
			std::cout << GasX86_64_Intel::transpile(m) << std::endl;
		}
		free(src);
	}
}

int main(int argc, char **argv)
{
	int opt = 0;

	while ((opt = getopt(argc, argv, ":l:p:a:c:b:")) != -1) {
		switch (opt) {
		case 'l':
			lex_file(optarg);
			break;

		case 'p':
			parse_file(optarg);
			break;

		case 'a':
			analyse_file(optarg);
			break;

		case 'c':
			compile_file(optarg);
			break;

		case 'b': {
			backend = optarg;
			break;
		}

		case ':': {
			switch (optopt) {
			case 'l':
				lex_repl();
				break;

			case 'p':
				parse_repl();
				break;

			case 'a':
				analyse_repl();
				break;

			case 'c':
				compile_repl();
				break;

			default:
				printf("%c requires an arg\n", optopt);
				break;
			}
			break;
		}

		default: {
			printf("unknown option %c\n", optopt);
			break;
		}
		}
	}
}
