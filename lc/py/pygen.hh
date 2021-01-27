#ifndef LORD_LC_PY_PYGEN_HH
#define LORD_LC_PY_PYGEN_HH

class PygenVisitor : public Visitor {
private:
	Struct *s = NULL;
	Fn *f = NULL;

public:
	size_t ilvl = 0;
	std::string buf;

public:
	PygenVisitor(Module *m);

	void visit_MODULE(Node *n) override;

	void gen_struct(Struct *s);
	void gen_structfield(Field *f);
	void gen_structmethod(Fn *m);
	void gen_fn(Fn *m);

	void visit_CALL(Node *n) override;
	void visit_STR(Node *n) override;
	void visit_RET(Node *n) override;
	void visit_INT(Node *n) override;
	void visit_EQ(Node *n) override;
	void visit_STRUCTINIT(Node *n) override;
	void visit_MUL(Node *n) override;
	void visit_DOT(Node *n) override;
	void visit_SYM(Node *n) override;
	void visit_COLN(Node *n) override;
	void visit_ARR(Node *n) override;
	void visit_DEREF(Node *n) override;

	void addtabs();
};

#endif
