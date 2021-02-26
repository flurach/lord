#include "lp.hh"

Lexer::Lexer(std::string src)
{
	this->src = src;
}

char Lexer::curr()
{
	return this->src[this->i];
}

char Lexer::ch()
{
	if (this->src[this->i] != '\0')
		return src[this->i++];
	return '\0';
}

Token Lexer::next()
{
	this->cached = false;
	this->val = "";

	/* skip whitespace */
	while (isspace(curr()))
		ch();

	this->range.begin = this->i;

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
			this->val.push_back(ch());

		if (this->val == "import")
			this->token = T_IMPORT;
		else if (this->val == "fn")
			this->token = T_FN;
		else if (this->val == "if")
			this->token = T_IF;
		else if (this->val == "then")
			this->token = T_THEN;
		else if (this->val == "else")
			this->token = T_ELSE;
		else if (this->val == "let")
			this->token = T_LET;
		else if (this->val == "in")
			this->token = T_IN;
		else if (this->val == "to")
			this->token = T_TO;
		else if (this->val == "and")
			this->token = T_AND;
		else if (this->val == "or")
			this->token = T_ORR;
		else if (this->val == "not")
			this->token = T_NOT;
		else
			this->token = T_SYM;
	}

	/* numbers */
	else if (isdigit(curr())) {
		this->token = T_INT;
		while (isdigit(curr()) || curr() == '.')  {
			if (this->token == T_INT && curr() == '.')
				this->token = T_FLT;
			else if (curr() == '.')
				break;
			this->val.push_back(ch());
		}
	}

	/* strings */
	else if (curr() == '\'' || curr() == '\"') {
		const char pair = ch();
		this->token = pair == '\'' ? T_CHR : T_STR;
		while (curr() != pair && curr() != '\0')
			this->val.push_back(ch());
		ch();
	}

	/* operators */
	else if (curr() == '=') {
		this->token = T_EQ;
		this->val.push_back(ch());
	}
	else if (curr() == '[') {
		this->token = T_LBRC;
		this->val.push_back(ch());
	}
	else if (curr() == ']') {
		this->token = T_RBRC;
		this->val.push_back(ch());
	}
	else if (curr() == '.') {
		this->token = T_DOT;
		this->val.push_back(ch());
	}
	else if (curr() == '|') {
		this->val.push_back(ch());
		if (curr() == '>') {
			this->val.push_back(ch());
			this->token = T_PIPE;
		} else {
			this->token = T_ERR;
		}
	}

	/* punctuation */
	else if (curr() == '(') {
		this->token = T_LPAR;
		this->val.push_back(ch());
	}
	else if (curr() == ')') {
		this->token = T_RPAR;
		this->val.push_back(ch());
	}
	else if (curr() == '{') {
		this->token = T_LCRL;
		this->val.push_back(ch());
	}
	else if (curr() == '}') {
		this->token = T_RCRL;
		this->val.push_back(ch());
	}
	else if (curr() == ',') {
		this->token = T_COMA;
		this->val.push_back(ch());
	}
	else if (curr() == ';') {
		this->token = T_SEMI;
		this->val.push_back(ch());
	}
	else if (curr() == ':') {
		this->token = T_COLN;
		this->val.push_back(ch());
	}

	/* maths */
	else if (curr() == '+') {
		this->token = T_ADD;
		this->val.push_back(ch());
	}
	else if (curr() == '-') {
		this->token = T_SUB;
		this->val.push_back(ch());
	}
	else if (curr() == '*') {
		this->token = T_MUL;
		this->val.push_back(ch());
	}
	else if (curr() == '/') {
		this->val.push_back(ch());
		if (curr() == '/') {
			this->token = T_DDIV;
			this->val.push_back(ch());
		} else {
			this->token = T_DIV;
		}
	}
	else if (curr() == '%') {
		this->token = T_MOD;
		this->val.push_back(ch());
	}

	/* logic */
	else if (curr() == '!') {
		this->token = T_NOT;
		this->val.push_back(ch());
	}
	else if (curr() == '<') {
		this->token = T_LSS;
		this->val.push_back(ch());
	}
	else if (curr() == '>') {
		this->token = T_GTR;
		this->val.push_back(ch());
	}

	/* end of file */
	else if (curr() == '\0') {
		this->token = T_EOF;
	}

	this->range.end = this->i;
	return this->token;
}

Token Lexer::peek()
{
	if (this->cached)
		return this->cache;

	Lexer backup = *this;
	Token token = next();
	*this = backup;

	this->cached = true;
	this->cache = token;
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
