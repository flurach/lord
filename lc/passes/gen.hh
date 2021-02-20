#ifndef LORD_LC_PASSES_GEN_HH
#define LORD_LC_PASSES_GEN_HH

class GenVisitor : public Visitor {
private:
	Fn *f = NULL;

public:
	GenVisitor(Module& m);

public:
	void visit_FN(Node& n);
};

#endif
