#ifndef LORD_LC_COMMON_DESUGAR_HH
#define LORD_LC_COMMON_DESUGAR_HH

class DesugarVisitor : public Visitor {
public:
	DesugarVisitor(Module& m);

public:
	void visit_PIPE(Node& n);
};

#endif
