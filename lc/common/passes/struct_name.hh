#ifndef LORD_LC_COMMON_PASSES_STRUCT_NAME_HH
#define LORD_LC_COMMON_PASSES_STRUCT_NAME_HH

class StructNameVisitor : public Visitor {
public:
	StructNameVisitor(Module *m);

	void visit_STRUCT(Node *n) override;
};

#endif
