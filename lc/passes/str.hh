#ifndef LORD_LC_PASSES_STR_HH
#define LORD_LC_PASSES_STR_HH

class StrVisitor : public Visitor {
public:
	StrVisitor(Module& m);

public:
	void visit_STR(Node& n) override;
};

#endif
