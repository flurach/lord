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
	for (auto a : m->ref->ns[1]->ns)
		buf += a->val + ", ";
	buf.pop_back();
	buf.pop_back();
	buf += "):\n";

	/* method body */
	ilvl++;
	for (auto s : m->ref->ns[3]->ns) {
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
	for (auto a : f->ref->ns[1]->ns)
		buf += a->val + ", ";
	buf.pop_back();
	buf.pop_back();
	buf += "):\n";

	/* method body */
	ilvl++;
	for (auto s : f->ref->ns[3]->ns) {
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
	visit(n->ns[0]);

	bool is_field = false;
	if (n->ns[0]->token == T_DOT && n->ns[0]->ns[0]->val == f->ref->ns[1]->ns[0]->val) {
		for (auto ff : s->fields) {
			if (ff.name == n->ns[0]->ns[1]->val) {
				is_field = true;
				break;
			}
		}
	}

	if (!is_field) {
		buf += "(";
		for (auto a : n->ns[1]->ns) {
			visit(a);
			buf += ", ";
		}
		if (n->ns[1]->ns.size()) {
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
	visit(n->ns[0]);
}

void PygenVisitor::visit_INT(Node *n)
{
	buf += n->val;
}

void PygenVisitor::visit_EQ(Node *n)
{
	visit(n->ns[0]);
	buf += " = ";
	visit(n->ns[1]);
}

void PygenVisitor::visit_STRUCTINIT(Node *n)
{
	visit(n->ns[0]);
	buf += "(";
	for (auto ff : n->ns[2]->ns) {
		if (ff->token == T_COMA)
			continue;
		buf += ff->ns[0]->val;
		buf += "=";
		visit(ff->ns[1]);
		buf += ", ";
	}
	if (n->ns[2]->ns.size()) {
		buf.pop_back();
		buf.pop_back();
	}
	buf += ")";
}

void PygenVisitor::visit_MUL(Node *n)
{
	visit(n->ns[0]);
	buf += " * ";
	visit(n->ns[1]);
}

void PygenVisitor::visit_DOT(Node *n)
{
	visit(n->ns[0]);
	buf.push_back('.');
	visit(n->ns[1]);
}

void PygenVisitor::visit_SYM(Node *n)
{
	buf += n->val;
}

void PygenVisitor::addtabs()
{
	size_t x = 0;
	while (x++ < ilvl)
		buf += "    ";
}
