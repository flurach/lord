#include "lc.hh"

GenccVisitor::GenccVisitor(Module& m)
	: Visitor(m)
{
}

void GenccVisitor::visit_FN(Node& n)
{
	// name
	buf += n[0][1].val + " " + n[0][0].val + "(";

	// args
	for (auto arg : n[1])
		buf += arg[1].val + " " + arg[0].val + ",";
	if (n[1].size()) {
		buf.pop_back();
		buf.pop_back();
	}
	buf += ")";

	// body
	visit(n[2]);
}

void GenccVisitor::visit_INDENT(Node& n)
{
	buf += "{";
	for (auto stmt : n) {
		visit(stmt);
		buf += ";";
	}
	buf += "}";
}

void GenccVisitor::visit_RET(Node& n)
{
	buf += "return ";
	visit(n[0]);
}

void GenccVisitor::visit_INT(Node& n)
{
	buf += n.val;
}
