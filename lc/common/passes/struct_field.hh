#ifndef LORD_LC_COMMON_PASSES_STRUCT_FIELD_HH
#define LORD_LC_COMMON_PASSES_STRUCT_FIELD_HH

class StructFieldVisitor : public Visitor {
private:
	Struct *s = NULL;

public:
	StructFieldVisitor(Module *m);

	void visit_MODULE(Node *n) override;

	void visit_COLN(Node *n) override;
};


#endif
