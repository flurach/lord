#ifndef LORD_LC_COMMON_PASSES_STRUCT_FIELD_HH
#define LORD_LC_COMMON_PASSES_STRUCT_FIELD_HH

class StructFieldVisitor : public Visitor {
private:
	Type *s = NULL;

public:
	StructFieldVisitor(Module *m);

	void visit_STRUCT(Node *n) override;
	void visit_coln(Node *n);
};


#endif
