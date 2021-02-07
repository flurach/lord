#ifndef LORD_LC_COMMON_PASSES_METHOD_BODY_HH
#define LORD_LC_COMMON_PASSES_METHOD_BODY_HH

class MethodBodyVisitor : public FnBodyVisitor {
public:
	Struct *s = NULL;

public:
	MethodBodyVisitor(Module *m);

	void visit_MODULE(Node *n) override;
	void visit_fnargs(Node *n);
};

#endif
