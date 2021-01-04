#include "lexer.hh"

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
	while (curr() == '\t' || curr() == ' ')
		ch();

	this->range.begin = this->i;

	/* comments */
	if (curr() == '#') {
		while (curr() != '\n' && curr() != '\0')
			ch();
		ch();
		return next();
	}

	/* indentation */
	else if (curr() == '\n') {
		while (curr() == '\n')
			ch();

		size_t new_i_len = 0;
		while (curr() == '\t' || curr() == ' ') {
			ch();
			new_i_len++;
		}

		if (new_i_len > this->i_len) {
			this->token = T_INDENT;
			this->i_dep++;
		} else if (new_i_len < this->i_len) {
			this->token = T_DEDENT;
			this->i_dep--;
		} else {
			this->token = T_EOL;
		}

		this->i_len = new_i_len;
	}

	/* keywords, logic & symbols */
	else if (isalpha(curr())) {
		while (isalnum(curr()) || curr() == '_')
			this->val.push_back(ch());

		if (this->val == "pass")
			this->token = T_PASS;
		else if (this->val == "fn")
			this->token = T_FN;
		else if (this->val == "if")
			this->token = T_IF;
		else if (this->val == "else")
			this->token = T_ELSE;
		else if (this->val == "for")
			this->token = T_FOR;
		else if (this->val == "in")
			this->token = T_IN;
		else if (this->val == "to")
			this->token = T_TO;
		else if (this->val == "type")
			this->token = T_TYPE;
		else if (this->val == "as")
			this->token = T_AS;
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
		this->val.push_back(ch());
		if (curr() == '=') {
			this->token = T_EEQ;
			this->val.push_back(ch());
		} else {
			this->token = T_EQ;
		}
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
		this->val.push_back(ch());
		this->token = T_DOT;
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
		this->val.push_back(ch());
		if (curr() == '=') {
			this->token = T_AEQ;
			this->val.push_back(ch());
		} else {
			this->token = T_ADD;
		}
	}
	else if (curr() == '-') {
		this->val.push_back(ch());
		if (curr() == '=') {
			this->token = T_SEQ;
			this->val.push_back(ch());
		} else {
			this->token = T_SUB;
		}
	}
	else if (curr() == '*') {
		this->val.push_back(ch());
		if (curr() == '=') {
			this->token = T_MEQ;
			this->val.push_back(ch());
		} else {
			this->token = T_MUL;
		}
	}
	else if (curr() == '/') {
		this->val.push_back(ch());
		if (curr() == '=') {
			this->token = T_DEQ;
			this->val.push_back(ch());
		} else {
			this->token = T_DIV;
		}
	}
	else if (curr() == '%') {
		this->val.push_back(ch());
		if (curr() == '=') {
			this->token = T_MOQ;
			this->val.push_back(ch());
		} else {
			this->token = T_MOD;
		}
	}

	/* logic */
	else if (curr() == '!') {
		this->val.push_back(ch());
		if (curr() == '=') {
			this->token = T_NEQ;
			this->val.push_back(ch());
		} else {
			this->token = T_NOT;
		}
	}
	else if (curr() == '<') {
		this->val.push_back(ch());
		if (curr() == '=') {
			this->token = T_LEQ;
			this->val.push_back(ch());
		} else {
			this->token = T_LSS;
		}
	}
	else if (curr() == '>') {
		this->val.push_back(ch());
		if (curr() == '=') {
			this->token = T_GEQ;
			this->val.push_back(ch());
		} else {
			this->token = T_GTR;
		}
	}

	/* end of file */
	else if (curr() == '\0') {
		/* leading dedents */
		if (this->i_dep != 0) {
			this->token = T_DEDENT;
			this->i_dep--;
		} else {
			this->token = T_EOF;
		}
	}

	this->range.end = this->i;
	return this->token;
}

Token Lexer::peek()
{
	if (this->cached)
		return this->cache;

	size_t i = this->i;
	Token token = next();
	this->i = i;

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
