#ifndef LORD_LC_COMMON_PRE_INFER_HH
#define LORD_LC_COMMON_PRE_INFER_HH

class PreInferVisitor : public Visitor {
public:
	PreInferVisitor(Module& m);

public:
	void visit_EQ(Node& n) override;
};

#endif
