#ifndef LORD_LC_COMMON_PASSES_SYM_NAME_HH
#define LORD_LC_COMMON_PASSES_SYM_NAME_HH

class SymNameVisitor : public Visitor {
private:
	Fn *f = NULL;

public:
	SymNameVisitor(Module *m);

	void visit_MODULE(Node *n) override;

	void visit_EQ(Node *n) override;
};

#endif
