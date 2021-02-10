#include "lc.hh"

PygenVisitor::PygenVisitor(Module *m)
	: Visitor(m)
{
}

void PygenVisitor::visit_MODULE(Node *n)
{
	(void)n;

	for (auto& pair : m->fns) {
		f = pair.second;
		gen_fn(f);
	}
}

void PygenVisitor::gen_structmethod(Type *m)
{
	/* method name */
	addtabs();
	buf += "def " + m->ref->at(0)->at(0)->val + "(";

	/* method args */
	for (auto a : *m->ref->at(1))
		buf += a->val + ", ";
	buf.pop_back();
	buf.pop_back();
	buf += "):\n";

	/* method body */
	ilvl++;
	for (auto s : *m->ref->at(3)) {
		if (s->token == T_EOL)
			continue;
		addtabs();
		visit(s);
		buf += "\n";
	}
	buf += "\n";
	ilvl--;
}

void PygenVisitor::gen_fn(Type *f)
{
	/* fn name */
	addtabs();
	buf += "def " + f->ref->at(0)->val + "(";

	/* fn args */
	for (auto a : *f->ref->at(1))
		buf += a->val + ", ";
	if (f->ref->at(1)->size()) {
		buf.pop_back();
		buf.pop_back();
	}
	buf += "):\n";

	/* fn body */
	ilvl++;
	if (f->ref->at(3)->token == T_INDENT) {
		for (auto s : *f->ref->at(3)) {
			if (s->token == T_EOL)
				continue;
			addtabs();
			visit(s);
			buf += '\n';
		}
	} else {
		addtabs();
		visit(f->ref->at(3));
		buf += '\n';
	}
	ilvl--;
}

void PygenVisitor::visit_CALL(Node *n)
{
	auto fname = n->at(0);
	visit(fname);

	if (fname->token == T_DOT)
		visit_methodcall(n);
	else
		visit_fncall(n);
}

void PygenVisitor::visit_methodcall(Node *n)
{
	bool is_field = false;

	if (!is_field) {
		buf += "(";
		for (auto a : *n->at(1)) {
			visit(a);
			buf += ", ";
		}
		if (n->at(1)->size()) {
			buf.pop_back();
			buf.pop_back();
		}
		buf += ")";
	}
}

void PygenVisitor::visit_fncall(Node *n)
{
	bool is_sym = false;

	for (auto ss : m->symgr.syms) {
		if (ss == n->at(0)->val) {
			is_sym = true;
			break;
		}
	}

	if (!is_sym) {
		buf += "(";
		for (auto a : *n->at(1)) {
			visit(a);
			buf += ", ";
		}
		if (n->at(1)->size()) {
			buf.pop_back();
			buf.pop_back();
		}
		buf += ")";
	}
}

void PygenVisitor::visit_STR(Node *n)
{
	buf += '\"';
	buf += n->val;
	buf += '\"';
}

void PygenVisitor::visit_RET(Node *n)
{
	buf += "return";
	if (n->size()) {
		buf += ' ';
		visit(n->at(0));
	}
}

void PygenVisitor::visit_INT(Node *n)
{
	buf += n->val;
}

void PygenVisitor::visit_FLT(Node *n)
{
	buf += n->val;
}

void PygenVisitor::visit_EQ(Node *n)
{
	visit(n->at(0));
	buf += " = ";
	visit(n->at(1));
}

void PygenVisitor::visit_ARR(Node *n)
{
	buf += "Array([";
	for (auto e : *n->at(1)) {
		if (e->token == T_COMA)
			continue;
		visit(e);
		buf += ", ";
	}
	if (n->at(1)->size()) {
		buf.pop_back();
		buf.pop_back();
	}
	buf += "])";
}

void PygenVisitor::visit_STRUCTINIT(Node *n)
{
	visit(n->at(0));
	buf += "(";
	for (auto ff : *n->at(2)) {
		if (ff->token == T_COMA)
			continue;
		buf += ff->at(0)->val;
		buf += "=";
		visit(ff->at(1));
		buf += ", ";
	}
	if (n->at(2)->size()) {
		buf.pop_back();
		buf.pop_back();
	}
	buf += ")";
}

void PygenVisitor::visit_MUL(Node *n)
{
	visit(n->at(0));
	buf += " * ";
	visit(n->at(1));
}

void PygenVisitor::visit_DOT(Node *n)
{
	visit(n->at(0));
	buf.push_back('.');
	visit(n->at(1));
}

void PygenVisitor::visit_SYM(Node *n)
{
	buf += n->val;
}

void PygenVisitor::visit_COLN(Node *n)
{
	visit(n->at(0));
}

void PygenVisitor::visit_DEREF(Node *n)
{
	auto inside = n->at(1);
	visit(inside);
}

void PygenVisitor::visit_CAST(Node *n)
{
	buf += "Cast.";
	visit(n->at(2));
	buf += '(';
	visit(n->at(0));
	buf += ')';
}

void PygenVisitor::visit_ADD(Node *n)
{
	visit(n->at(0));
	buf += " + ";
	visit(n->at(1));
}

void PygenVisitor::visit_DIV(Node *n)
{
	visit(n->at(0));
	buf += " / ";
	visit(n->at(1));
}

void PygenVisitor::visit_IF(Node *n)
{
	auto condition = n->at(0);
	auto body = n->at(1);

	buf += "if ";
	visit(condition);
	buf += ":\n";

	ilvl++;
	for (auto stmt : *body) {
		addtabs();
		visit(stmt);
		buf += '\n';
	}
	ilvl--;


	if (n->size() >= 3) {
		addtabs();
		auto _else = n->at(2);
		visit(_else);
	}
}

void PygenVisitor::visit_PASS(Node *n)
{
	(void)n;
	buf += "pass";
}

void PygenVisitor::visit_ELSE(Node *n)
{
	if (n->at(0)->token == T_IF) {
		auto condition = n->at(0)->at(0);
		auto body = n->at(0)->at(1);

		buf += "elif ";
		visit(condition);
		buf += ":\n";

		ilvl++;
		for (auto stmt : *body) {
			addtabs();
			visit(stmt);
			buf += '\n';
		}
		ilvl--;

		if (n->at(0)->size() >= 3) {
			addtabs();
			auto _else = n->at(0)->at(2);
			visit(_else);
		}
	} else {
		buf += "else:\n";
		ilvl++;
		addtabs();
		visit(n->at(0));
		buf += '\n';
		ilvl--;
	}
}

void PygenVisitor::visit_EEQ(Node *n)
{
	visit(n->at(0));
	buf += " == ";
	visit(n->at(1));
}

void PygenVisitor::visit_AEQ(Node *n)
{
	visit(n->at(0));
	buf += " += ";
	visit(n->at(1));
}

void PygenVisitor::visit_LSS(Node *n)
{
	visit(n->at(0));
	buf += " < ";
	visit(n->at(1));
}

void PygenVisitor::visit_IN(Node *n)
{
	visit(n->at(0));
	buf += " in ";
	visit(n->at(1));
}

void PygenVisitor::visit_TO(Node *n)
{
	buf += "range(";
	visit(n->at(0));
	buf += ", ";
	visit(n->at(1));
	buf += ")";
}

void PygenVisitor::visit_FOR(Node *n)
{
	auto head = n->at(0);

	if (head->token == T_STMTS && head->size() > 1)
		visit_normalfor(n);
	else if (head->token == T_IN)
		visit_rangefor(n);
	else
		visit_whilefor(n);
}

void PygenVisitor::visit_normalfor(Node *n)
{
	auto head = n->at(0);
	auto body = n->at(1);
	auto acc = head->at(0);
	auto cond = head->at(2);
	auto action = head->at(4);

	visit(acc);
	buf += "\n";

	addtabs();
	buf += "while ";
	visit(cond);
	buf += ':';

	ilvl++;
	for (auto stmt : *body) {
		buf += '\n';
		addtabs();
		visit(stmt);
	}
	buf += '\n';
	addtabs();
	visit(action);
	ilvl--;
}

void PygenVisitor::visit_rangefor(Node *n)
{
	auto head = n->at(0);
	auto body = n->at(1);

	buf += "for ";
	visit(head);
	buf += ':';

	ilvl++;
	for (auto stmt : *body) {
		buf += '\n';
		addtabs();
		visit(stmt);
	}
	ilvl--;
}

void PygenVisitor::visit_whilefor(Node *n)
{
	auto head = n->at(0);
	auto body = n->at(1);

	buf += "while ";
	visit(head);
	buf += ":";

	ilvl++;
	for (auto stmt : *body) {
		buf += '\n';
		addtabs();
		visit(stmt);
	}
	ilvl--;
}

void PygenVisitor::addtabs()
{
	size_t x = 0;
	while (x++ < ilvl)
		buf += "    ";
}
