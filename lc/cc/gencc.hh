#ifndef LORD_LC_CC_GENCC_HH
#define LORD_LC_CC_GENCC_HH

class GenccVisitor : public Visitor {
public:
	std::string buf =
		"typedef long i64;"
	;

public:
	GenccVisitor(Module& m);

public:
	void visit_FN(Node& n);
	void visit_INDENT(Node& n);
	void visit_RET(Node& n);
	void visit_INT(Node& n);
};

#endif
