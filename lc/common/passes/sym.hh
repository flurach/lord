#ifndef LORD_LC_COMMON_PASSES_SYM_HH
#define LORD_LC_COMMON_PASSES_SYM_HH

class SymVisitor : public Visitor {
private:
	Symgr symgr;

public:
	SymVisitor(Module *m);

public:
	void visit_MODULE(Node *n) override;

	// skip functions
	void visit_FN(Node *n) override;
	void visit_ARGS(Node *n) override;

	// collect symbols declared with '='
	void visit_EQ(Node *n) override;
	void visit_lval(Node *n);

	// visit present symbols
	void visit_SYM(Node *n) override;
};

#endif
