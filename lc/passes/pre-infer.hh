#ifndef LORD_LC_PASSES_PRE_INFER_HH
#define LORD_LC_PASSES_PRE_INFER_HH

class PreInferVisitor : public Visitor {
public:
	PreInferVisitor(Module& m);

public:
	void visit_FN(Node& n) override;
	void visit_EQ(Node& n) override;
};

#endif
