#ifndef LORD_LC_PY_PYGEN_HH
#define LORD_LC_PY_PYGEN_HH

class PygenVisitor : public Visitor {
private:
	Struct *s = NULL;
	Fn *f = NULL;

public:
	size_t ilvl = 0;
	std::string buf =
		"# stdlib\n"
		"class Array:\n"
		"    def __init__(self, value):\n"
		"        self.value = value\n"
		"    def at(self, i):\n"
		"        return self.value[i]\n"
		"class Cast:\n"
		"    def i64(value):\n"
		"        return int(value)\n"
		"    def i32(value):\n"
		"        return int(value)\n"
		"    def i16(value):\n"
		"        return int(value)\n"
		"    def i8(value):\n"
		"        return int(value)\n"
		"    def u64(value):\n"
		"        return int(value)\n"
		"    def u32(value):\n"
		"        return int(value)\n"
		"    def u16(value):\n"
		"        return int(value)\n"
		"    def u8(value):\n"
		"        return int(value)\n"
		"    def f64(value):\n"
		"        return float(value)\n"
		"    def f32(value):\n"
		"        return float(value)\n"
		"\n\n"
		"# code\n";

public:
	PygenVisitor(Module *m);

	void visit_MODULE(Node *n) override;

	void gen_struct(Struct *s);
	void gen_structfield(Field *f);
	void gen_structmethod(Fn *m);
	void gen_fn(Fn *m);

	void visit_methodcall(Node *n);
	void visit_fncall(Node *n);

	void visit_CALL(Node *n) override;
	void visit_STR(Node *n) override;
	void visit_RET(Node *n) override;
	void visit_INT(Node *n) override;
	void visit_FLT(Node *n) override;
	void visit_EQ(Node *n) override;
	void visit_STRUCTINIT(Node *n) override;
	void visit_MUL(Node *n) override;
	void visit_DOT(Node *n) override;
	void visit_SYM(Node *n) override;
	void visit_COLN(Node *n) override;
	void visit_ARR(Node *n) override;
	void visit_DEREF(Node *n) override;
	void visit_CAST(Node *n) override;
	void visit_ADD(Node *n) override;

	void addtabs();
};

#endif
