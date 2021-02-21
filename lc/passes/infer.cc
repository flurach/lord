#include "lc.hh"

InferVisitor::InferVisitor(Module& m)
	: Visitor(m)
{
}

void InferVisitor::visit_MODULE(Node& n)
{
	// first visit all children
	for (auto& child : n)
		visit(child);

	// next get rid of unnecessary constraints
	// e.g when references are the same
	std::vector<Constraint> new_constraints;
	for (auto c : m.constraints) {
		if (c.lhop != c.rhop)
			new_constraints.push_back(c);
	}
	m.constraints = new_constraints;

	// then start the unification algorithm
	unif(m.constraints);
}

void InferVisitor::visit_FN(Node& n)
{
	// create a type for function
	f = new Node(n.range, T_FN, n.val);
	m.left_over_types.push_back(f);

	//
	// TODO: assign types to arguments here
	//

	// push a dummy return type
	f->push(Node(n.range, T_NONE, "()"));

	// visit body
	visit(n[1]);
}

void InferVisitor::visit_RET(Node& n)
{
	visit(n[0]);
	m.constraints.push_back(Constraint(n.range, &f->back(), n[0].type));
}

void InferVisitor::visit_EQ(Node& n)
{
	// visit left-hand side
	visit(n[0]);

	// visit right-hand side
	visit(n[1]);

	// create a type constraint
	m.constraints.push_back(Constraint(n.range, n[0].type, n[1].type));
	n.type = n[0].type;
}

void InferVisitor::visit_MUL(Node& n)
{
	// visit left-hand side
	visit(n[0]);

	// visit right-hand side
	visit(n[1]);

	// create a type constraint
	m.constraints.push_back(Constraint(n.range, n[0].type, n[1].type));
	n.type = n[0].type;
}

void InferVisitor::visit_SYM(Node& n)
{
	if (locals[n.val]) {
		n.type = locals[n.val];
		return;
	}

	locals[n.val] = new Node(n.range, T_NONE, n.val);
	n.type = locals[n.val];
}

void InferVisitor::visit_INT(Node& n)
{
	n.type = new Node(n.range, T_SYM, "i64");
	m.left_over_types.push_back(n.type);
}

void InferVisitor::visit_CALL(Node& n)
{
	// do nothing for calls
	(void)n;
}
