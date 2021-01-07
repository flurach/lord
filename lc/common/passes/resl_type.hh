#ifndef LORD_LC_COMMON_PASSES_RESL_TYPE_HH
#define LORD_LC_COMMON_PASSES_RESL_TYPE_HH

#include "visitor.hh"

class ReslTypeVisitor : public Visitor {
public:
	ReslTypeVisitor(CompState *state);

	void visit_TYPE(Node *n) override;
};

#endif
