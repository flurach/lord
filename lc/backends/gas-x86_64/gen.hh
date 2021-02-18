#ifndef LORD_LC_BACKENDS_GAS_X86_64_GEN_HH
#define LORD_LC_BACKENDS_GAS_X86_64_GEN_HH

class GenGasX86_64 : public Visitor {
public:
	std::string buf;

public:
	Fn *f = NULL;

public:
	GenGasX86_64(Module& m);

public:
	void visit_MODULE(Node& n);

	void visit_FN(Node& n);
	void visit_RET(Node& n);

	void visit_CALL(Node& n);

	void visit_ADD(Node& n);
	void visit_SUB(Node& n);

	void visit_SYM(Node& n);
	void visit_INT(Node& n);
	void visit_STRREF(Node& n);
};

#endif
