#ifndef LORD_LC_COMMON_DESUGAR_HH
#define LORD_LC_COMMON_DESUGAR_HH

class DesugarVisitor : public Visitor {
public:
	DesugarVisitor(Module& m);

public:

	// type sugars
	void visit_FN(Node& n) override;

	// operator sugars
	void visit_EQ(Node& n) override;
	void visit_PIPE(Node& n) override;
};

#endif
