#include "lc.hh"

PygenVisitor::PygenVisitor(Module *m)
	: Visitor(m)
{
}

void PygenVisitor::visit_MODULE(Node *n)
{
	(void)n;

	for (auto ss : m->structmgr.structs) {
		s = ss;
		gen_struct(ss);
	}
	s = NULL;

	for (auto ff : m->fnmgr.fns) {
		f = ff;
		gen_fn(ff);
	}
}

void PygenVisitor::gen_struct(Struct *s)
{
	/* class definition */
	addtabs();
	buf += "class " + s->name + ":\n";

	ilvl++;
		/* def __init__(args) */
		addtabs();
		buf += "def __init__(self, ";
		for (auto f : s->fields)
			buf += f.name + ", ";
		buf.pop_back();
		buf.pop_back();
		buf += "):\n";

		/* __init__ body */
		ilvl++;
			for (auto f : s->fields) {
				addtabs();
				buf += "self." + f.name + " = " + f.name + "\n";
			}
			buf.push_back('\n');
		ilvl--;

		/* method definitions */
		for (auto ff : s->fnmgr.fns) {
			f = ff;
			gen_structmethod(f);
		}
	ilvl--;
}

void PygenVisitor::gen_structmethod(Fn *m)
{
	/* method name */
	addtabs();
	buf += "def " + m->name + "(";

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

void PygenVisitor::gen_fn(Fn *f)
{
	/* method name */
	addtabs();
	buf += "def " + f->name + "(";

	/* method args */
	for (auto a : *f->ref->at(1))
		buf += a->val + ", ";
	buf.pop_back();
	buf.pop_back();
	buf += "):\n";

	/* method body */
	ilvl++;
	for (auto s : *f->ref->at(3)) {
		if (s->token == T_EOL)
			continue;
		addtabs();
		visit(s);
		buf += "\n";
	}
	ilvl--;
}

void PygenVisitor::visit_CALL(Node *n)
{
	visit(n->at(0));

	if (n->at(0)->token == T_DOT)
		visit_methodcall(n);
	else
		visit_fncall(n);

}

void PygenVisitor::visit_methodcall(Node *n)
{
	bool is_field = false;

	if (n->at(0)->at(0)->val == f->ref->at(1)->at(0)->val) {
		for (auto ff : s->fields) {
			if (ff.name == n->at(0)->at(1)->val) {
				is_field = true;
				break;
			}
		}
	}

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
	bool is_fn = false;

	for (auto ff : m->fnmgr.fns) {
		if (ff->name == n->at(0)->val) {
			is_fn = true;
			break;
		}
	}

	if (!is_fn) {
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
	buf += "return ";
	visit(n->at(0));
}

void PygenVisitor::visit_INT(Node *n)
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

void PygenVisitor::addtabs()
{
	size_t x = 0;
	while (x++ < ilvl)
		buf += "    ";
}
