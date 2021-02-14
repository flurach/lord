#ifndef LORD_LC_COMMON_POST_INFER_HH
#define LORD_LC_COMMON_POST_INFER_HH

class PostInferVisitor : public Visitor {
private:
	Scope s = Scope();

public:
	PostInferVisitor(Module& m);

public:
	void visit_MODULE(Node& n) override;
};

#endif
