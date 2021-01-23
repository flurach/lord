#ifndef LORD_LC_COMMON_PASSES_FN_NAME_HH
#define LORD_LC_COMMON_PASSES_FN_NAME_HH

class FnAndMethodVisitor : public Visitor {
public:
	FnAndMethodVisitor(Module *m);

	void visit_FN(Node *n) override;

	void visit_method(Node *n);
	void visit_fdef(Node *n);
};

#endif
