#ifndef LORD_LC_COMMON_PASSES_RESL_STRUCT_HH
#define LORD_LC_COMMON_PASSES_RESL_STRUCT_HH

#include "visitor.hh"

class ReslStructVisitor : public Visitor {
public:
	ReslStructVisitor(Module *mod);

	void visit_TYPE(Node *n) override;
};

#endif
