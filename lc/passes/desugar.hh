#ifndef LORD_LC_PASSES_DESUGAR_HH
#define LORD_LC_PASSES_DESUGAR_HH

struct Fn;

class DesugarVisitor : public Visitor {
public:
	Fn *f = NULL;
	std::set<std::string> locals;

public:
	DesugarVisitor(Module& m);

public:
	void visit_FN(Node& n) override;
	void visit_INDENT(Node& n) override;

	void visit_EQ(Node& n) override;

	void visit_CALL(Node& n) override;
	void visit_PIPE(Node& n) override;
};

#endif
