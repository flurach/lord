#ifndef LORD_LC_PASSES_INFER_HH
#define LORD_LC_PASSES_INFER_HH

class InferVisitor : public Visitor {
public:
	Node *f = NULL;
	std::map<std::string, Node*> locals;

public:
	InferVisitor(Module& m);

public:
	void visit_MODULE(Node& n) override;

	void visit_FN(Node& n) override;
	void visit_CALL(Node& n) override;
	void visit_RET(Node& n) override;

	void visit_EQ(Node& n) override;
	void visit_ADD(Node& n) override;
	void visit_MUL(Node& n) override;

	void visit_SYM(Node& n) override;
	void visit_INT(Node& n) override;
	void visit_FLT(Node& n) override;
};

#endif
