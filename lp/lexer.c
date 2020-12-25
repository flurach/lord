#include "lexer.h"

char *strdup(char *s)
{
	if (s == NULL)
		return NULL;

	size_t s_len = strlen(s);
	if (s_len == 0)
		return NULL;

	return strcpy(malloc(s_len), s);
}

Lexer *Lexer_new(char *src)
{
	Lexer *self = malloc(sizeof(Lexer));
	*self = (Lexer){
		.src = src,
		.i = 0,
		.i_len = 0,
		.i_dep = 0,

		.range = {0, 0},
		.token = T_EOF,
		.val = strdup(src)
	};
	self->val[0] = '\0';
	return self;
}

void Lexer_free(Lexer *self)
{
	free(self->val);
	free(self->src);
	free(self);
}

char Lexer_curr(Lexer *self)
{
	return self->src[self->i];
}

char Lexer_char(Lexer *self)
{
	if (self->src[self->i] != '\0')
		return self->src[self->i++];
	return '\0';
}

Token Lexer_next(Lexer *self)
{
	char *vi = self->val;

	/* skip whitespace */
	while (Lexer_curr(self) == '\t' || Lexer_curr(self) == ' ')
		Lexer_char(self);

	self->range.begin = self->i;

	/* comments */
	if (Lexer_curr(self) == '#') {
		while (Lexer_curr(self) != '\n' && Lexer_curr(self) != '\0')
			Lexer_char(self);
		Lexer_char(self);
		return Lexer_next(self);
	}

	/* indentation */
	else if (Lexer_curr(self) == '\n') {
		while (Lexer_curr(self) == '\n')
			Lexer_char(self);

		size_t new_i_len = 0;
		while (Lexer_curr(self) == '\t' || Lexer_curr(self) == ' ') {
			Lexer_char(self);
			new_i_len++;
		}

		if (new_i_len > self->i_len) {
			self->token = T_INDENT;
			self->i_dep++;
		} else if (new_i_len < self->i_len) {
			self->token = T_DEDENT;
			self->i_dep--;
		} else {
			self->token = T_EOL;
		}

		self->i_len = new_i_len;
	}

	/* keywords, logic & symbols */
	else if (isalpha(Lexer_curr(self))) {
		while (isalnum(Lexer_curr(self)) || Lexer_curr(self) == '_')
			*vi++ = Lexer_char(self);
		*vi = '\0';

		if (strcmp(self->val, "pass") == 0)
			self->token = T_PASS;
		else if (strcmp(self->val, "ext") == 0)
			self->token = T_EXT;
		else if (strcmp(self->val, "fn") == 0)
			self->token = T_FN;
		else if (strcmp(self->val, "if") == 0)
			self->token = T_IF;
		else if (strcmp(self->val, "else") == 0)
			self->token = T_ELSE;
		else if (strcmp(self->val, "for") == 0)
			self->token = T_FOR;
		else if (strcmp(self->val, "in") == 0)
			self->token = T_IN;
		else if (strcmp(self->val, "to") == 0)
			self->token = T_TO;
		else if (strcmp(self->val, "type") == 0)
			self->token = T_TYPE;
		else if (strcmp(self->val, "as") == 0)
			self->token = T_AS;
		else if (strcmp(self->val, "and") == 0)
			self->token = T_AND;
		else if (strcmp(self->val, "or") == 0)
			self->token = T_ORR;
		else if (strcmp(self->val, "not") == 0)
			self->token = T_NOT;
		else
			self->token = T_SYM;
	}

	/* numbers */
	else if (isdigit(Lexer_curr(self))) {
		self->token = T_INT;
		while (isdigit(Lexer_curr(self)) || Lexer_curr(self) == '.')  {
			if (self->token == T_INT && Lexer_curr(self) == '.')
				self->token = T_FLT;
			else if (Lexer_curr(self) == '.')
				break;
			*vi++ = Lexer_char(self);
		}
	}

	/* strings */
	else if (Lexer_curr(self) == '\'' || Lexer_curr(self) == '\"') {
		const char pair = Lexer_char(self);
		self->token = pair == '\'' ? T_CHR : T_STR;
		while (Lexer_curr(self) != pair && Lexer_curr(self) != '\0')
			*vi++ = Lexer_char(self);
		Lexer_char(self);
	}

	/* operators */
	else if (Lexer_curr(self) == '=') {
		*vi++ = Lexer_char(self);
		if (Lexer_curr(self) == '=') {
			self->token = T_EEQ;
			*vi++ = Lexer_char(self);
		} else {
			self->token = T_EQ;
		}
	}
	else if (Lexer_curr(self) == '[') {
		self->token = T_LBRC;
		*vi++ = Lexer_char(self);
	}
	else if (Lexer_curr(self) == ']') {
		self->token = T_RBRC;
		*vi++ = Lexer_char(self);
	}
	else if (Lexer_curr(self) == '.') {
		*vi++ = Lexer_char(self);
		self->token = T_DOT;
	}

	/* punctuation */
	else if (Lexer_curr(self) == '(') {
		self->token = T_LPAR;
		*vi++ = Lexer_char(self);
	}
	else if (Lexer_curr(self) == ')') {
		self->token = T_RPAR;
		*vi++ = Lexer_char(self);
	}
	else if (Lexer_curr(self) == '{') {
		self->token = T_LCRL;
		*vi++ = Lexer_char(self);
	}
	else if (Lexer_curr(self) == '}') {
		self->token = T_RCRL;
		*vi++ = Lexer_char(self);
	}
	else if (Lexer_curr(self) == ',') {
		self->token = T_COMA;
		*vi++ = Lexer_char(self);
	}
	else if (Lexer_curr(self) == ';') {
		self->token = T_SEMI;
		*vi++ = Lexer_char(self);
	}
	else if (Lexer_curr(self) == ':') {
		self->token = T_COLN;
		*vi++ = Lexer_char(self);
	}

	/* maths */
	else if (Lexer_curr(self) == '+') {
		*vi++ = Lexer_char(self);
		if (Lexer_curr(self) == '=') {
			self->token = T_AEQ;
			*vi++ = Lexer_char(self);
		} else {
			self->token = T_ADD;
		}
	}
	else if (Lexer_curr(self) == '-') {
		*vi++ = Lexer_char(self);
		if (Lexer_curr(self) == '=') {
			self->token = T_SEQ;
			*vi++ = Lexer_char(self);
		} else {
			self->token = T_SUB;
		}
	}
	else if (Lexer_curr(self) == '*') {
		*vi++ = Lexer_char(self);
		if (Lexer_curr(self) == '=') {
			self->token = T_MEQ;
			*vi++ = Lexer_char(self);
		} else {
			self->token = T_MUL;
		}
	}
	else if (Lexer_curr(self) == '/') {
		*vi++ = Lexer_char(self);
		if (Lexer_curr(self) == '=') {
			self->token = T_DEQ;
			*vi++ = Lexer_char(self);
		} else {
			self->token = T_DIV;
		}
	}
	else if (Lexer_curr(self) == '%') {
		*vi++ = Lexer_char(self);
		if (Lexer_curr(self) == '=') {
			self->token = T_MOQ;
			*vi++ = Lexer_char(self);
		} else {
			self->token = T_MOD;
		}
	}

	/* logic */
	else if (Lexer_curr(self) == '!') {
		*vi++ = Lexer_char(self);
		if (Lexer_curr(self) == '=') {
			self->token = T_NEQ;
			*vi++ = Lexer_char(self);
		} else {
			self->token = T_NOT;
		}
	}
	else if (Lexer_curr(self) == '<') {
		*vi++ = Lexer_char(self);
		if (Lexer_curr(self) == '=') {
			self->token = T_LEQ;
			*vi++ = Lexer_char(self);
		} else {
			self->token = T_LSS;
		}
	}
	else if (Lexer_curr(self) == '>') {
		*vi++ = Lexer_char(self);
		if (Lexer_curr(self) == '=') {
			self->token = T_GEQ;
			*vi++ = Lexer_char(self);
		} else {
			self->token = T_GTR;
		}
	}

	/* end of file */
	else if (Lexer_curr(self) == '\0') {
		/* leading dedents */
		if (self->i_dep != 0) {
			self->token = T_DEDENT;
			self->i_dep--;
		} else {
			self->token = T_EOF;
		}
	}

	self->range.end = self->i;
	*vi = '\0';
	return self->token;
}

Token Lexer_peek(Lexer *self)
{
	size_t i = self->i;
	Token token = Lexer_next(self);
	self->i = i;
	return token;
}

void Lexer_print(Lexer *self)
{
	printf(
		"%s '%s' %lu..%lu\n",
		Token_str[self->token],
		self->val,
		self->range.begin,
		self->range.end
	);
}
