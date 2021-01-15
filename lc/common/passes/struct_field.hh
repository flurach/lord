#ifndef LORD_LC_COMMON_PASSES_STRUCT_FIELD_HH
#define LORD_LC_COMMON_PASSES_STRUCT_FIELD_HH

class StructFieldVisitor : public Visitor {
public:
	StructFieldVisitor(Module *m);

	void visit_STRUCT(Node *n) override;
};


#endif
