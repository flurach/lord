#ifndef LORD_LC_COMMON_INFER_HH
#define LORD_LC_COMMON_INFER_HH

class InferVisitor : public Visitor {
public:
	InferVisitor(Module& m);

public:
	void visit_EQ(Node& n) override;
};

#endif
