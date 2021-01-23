#ifndef LORD_LC_COMMON_PASSES_METHOD_BODY_HH
#define LORD_LC_COMMON_PASSES_METHOD_BODY_HH

class MethodBodyVisitor : public Visitor {
private:
	Struct *s = NULL;
	Fn *f = NULL;

public:
	MethodBodyVisitor(Module *m);

	void visit_MODULE(Node *n) override;

	void visit_FN(Node *n) override;
	void visit_fnargs(Node *n);

	void visit_EQ(Node *n) override;

	void visit_SYM(Node *n) override;
};

#endif
