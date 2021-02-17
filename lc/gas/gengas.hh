#ifndef LORD_LC_CC_GENGAS_HH
#define LORD_LC_CC_GENGAS_HH

class GenGasVisitor : public Visitor {
public:
	std::string strs =
		"\t.section .rodata\n"
	;

	std::string buf =
		"\t.text\n"
		"\t.extern puts\n"
		"\t.globl main\n"
	;

public:
	StrMgr strmgr = StrMgr();

public:
	GenGasVisitor(Module& m);

public:
	void visit_MODULE(Node& n);

	void visit_FN(Node& n);
	void visit_RET(Node& n);

	void visit_CALL(Node& n);

	void visit_INT(Node& n);
	void visit_STR(Node& n);
};

#endif
