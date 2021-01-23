#ifndef LORD_LC_COMMON_PASSES_STRUCT_HH
#define LORD_LC_COMMON_PASSES_STRUCT_HH

class StructVisitor : public Visitor {
public:
	StructVisitor(Module *m);

	void visit_STRUCT(Node *n) override;
};

#endif
