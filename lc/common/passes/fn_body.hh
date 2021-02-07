#ifndef LORD_LC_COMMON_PASSES_FN_BODY_HH
#define LORD_LC_COMMON_PASSES_FN_BODY_HH

class FnBodyVisitor : public Visitor {
private:
	Fn *f = NULL;

public:
	FnBodyVisitor(Module *m);

	void visit_MODULE(Node *n) override;

	void visit_FN(Node *n) override;
	void visit_fnargs(Node *n);

	void visit_EQ(Node *n) override;

	void visit_SYM(Node *n) override;
};

#endif
