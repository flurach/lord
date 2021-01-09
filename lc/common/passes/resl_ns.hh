#ifndef LORD_LC_COMMON_PASSES_RESL_NS_HH
#define LORD_LC_COMMON_PASSES_RESL_NS_HH

class ReslNsVisitor : public Visitor {
public:
	ReslNsVisitor(Module *m);

	void visit_FN(Node *n) override;
	void visit_args(Node *n);
	void visit_TYPE(Node *n) override;

	void visit_EQ(Node *n) override;
	void visit_SYM(Node *n) override;
	void visit_COLN(Node *n) override;
};

#endif
