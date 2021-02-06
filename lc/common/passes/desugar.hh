#ifndef LORD_LC_COMMON_PASSES_DESUGAR_HH
#define LORD_LC_COMMON_PASSES_DESUGAR_HH

class DesugarVisitor : public Visitor {
public:
	DesugarVisitor(Module *m);

	void visit_FN(Node *n) override;
	void visit_PIPE(Node *n) override;
};

#endif
