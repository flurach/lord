#ifndef LORD_LP_LEX_HH
#define LORD_LP_LEX_HH

struct Range {
	size_t begin, end;
};

struct Lexer {
	std::string src = "";
	size_t i = 0;
	size_t i_len = 0, i_dep = 0;

	Range range = {0, 0};
	Token token = T_EOF;
	std::string val = "";

	bool cached = false;
	Token cache = T_EOF;

	/* constructor & destructor */
	Lexer(std::string src);

	/* methods */
	char curr();
	char ch();
	Token next();
	Token peek();

	/* debug */
	void print();
};

#endif
