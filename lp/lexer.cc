#include "lp.hh"

Lexer::Lexer(std::string src)
{
	this->src = src;
}

char Lexer::curr()
{
	return src[i];
}

char Lexer::ch()
{
	if (src[i] != '\0')
		return src[i++];
	return '\0';
}

Token Lexer::next()
{
	cached = false;
	val = "";

	/* skip whitespace */
	while (isspace(curr()))
		ch();

	range.begin = i;

	/* comments */
	if (curr() == '#') {
		while (curr() != '\n' && curr() != '\0')
			ch();
		ch();
		return next();
	}

	/* keywords, logic & symbols */
	else if (isalpha(curr()) || curr() == '_') {
		while (isalnum(curr()) || curr() == '_')
			val.push_back(ch());

		if (val == "import")
			token = T_IMPORT;
		else if (val == "fn")
			token = T_FN;
		else if (val == "if")
			token = T_IF;
		else if (val == "then")
			token = T_THEN;
		else if (val == "else")
			token = T_ELSE;
		else if (val == "let")
			token = T_LET;
		else if (val == "in")
			token = T_IN;
		else if (val == "to")
			token = T_TO;
		else if (val == "and")
			token = T_AND;
		else if (val == "or")
			token = T_ORR;
		else if (val == "not")
			token = T_NOT;
		else
			token = T_SYM;
	}

	/* numbers */
	else if (isdigit(curr())) {
		token = T_INT;
		while (isdigit(curr()) || curr() == '.')  {
			if (token == T_INT && curr() == '.')
				token = T_FLT;
			else if (curr() == '.')
				break;
			val.push_back(ch());
		}
	}

	/* strings */
	else if (curr() == '\'' || curr() == '\"') {
		const char pair = ch();
		token = pair == '\'' ? T_CHR : T_STR;
		while (curr() != pair && curr() != '\0')
			val.push_back(ch());
		ch();
	}

	/* operators */
	else if (curr() == '=') {
		val.push_back(ch());
		if (curr() == '=') {
			val.push_back(ch());
			token = T_EEQ;
		} else {
			token = T_EQ;
		}
	}
	else if (curr() == '[') {
		token = T_LBRC;
		val.push_back(ch());
	}
	else if (curr() == ']') {
		token = T_RBRC;
		val.push_back(ch());
	}
	else if (curr() == '.') {
		token = T_DOT;
		val.push_back(ch());
	}
	else if (curr() == '|') {
		val.push_back(ch());
		if (curr() == '>') {
			val.push_back(ch());
			token = T_PIPE;
		} else {
			token = T_ERR;
		}
	}

	/* punctuation */
	else if (curr() == '(') {
		token = T_LPAR;
		val.push_back(ch());
	}
	else if (curr() == ')') {
		token = T_RPAR;
		val.push_back(ch());
	}
	else if (curr() == '{') {
		token = T_LCRL;
		val.push_back(ch());
	}
	else if (curr() == '}') {
		token = T_RCRL;
		val.push_back(ch());
	}
	else if (curr() == ',') {
		token = T_COMA;
		val.push_back(ch());
	}
	else if (curr() == ';') {
		token = T_SEMI;
		val.push_back(ch());
	}
	else if (curr() == ':') {
		token = T_COLN;
		val.push_back(ch());
	}

	/* maths */
	else if (curr() == '+') {
		token = T_ADD;
		val.push_back(ch());
	}
	else if (curr() == '-') {
		token = T_SUB;
		val.push_back(ch());
	}
	else if (curr() == '*') {
		token = T_MUL;
		val.push_back(ch());
	}
	else if (curr() == '/') {
		val.push_back(ch());
		if (curr() == '/') {
			token = T_DDIV;
			val.push_back(ch());
		} else {
			token = T_DIV;
		}
	}
	else if (curr() == '%') {
		token = T_MOD;
		val.push_back(ch());
	}

	/* logic */
	else if (curr() == '!') {
		val.push_back(ch());
		if (curr() == '=') {
			val.push_back(ch());
			token = T_NEQ;
		} else {
			token = T_NOT;
		}
	}
	else if (curr() == '<') {
		val.push_back(ch());
		if (curr() == '=') {
			val.push_back(ch());
			token = T_LEQ;
		} else {
			token = T_LSS;
		}
	}
	else if (curr() == '>') {
		val.push_back(ch());
		if (curr() == '=') {
			val.push_back(ch());
			token = T_GEQ;
		} else {
			token = T_GTR;
		}
	}

	/* end of file */
	else if (curr() == '\0') {
		token = T_EOF;
	}

	range.end = i;
	return token;
}

Token Lexer::peek()
{
	if (cached)
		return cache;

	Lexer backup = *this;
	Token token = next();
	*this = backup;

	cached = true;
	cache = token;
	return token;
}

void Lexer::print()
{
	std::cout
		<< Token_str[token]
		<< " '"
		<< val
		<< "' "
		<< range.begin
		<< ".."
		<< range.end
		<< std::endl;
}
