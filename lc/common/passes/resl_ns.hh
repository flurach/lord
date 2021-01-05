#ifndef LORD_LC_COMMON_PASSES_RESL_NS_HH
#define LORD_LC_COMMON_PASSES_RESL_NS_HH

#include "visitor.hh"

class ReslNsVisitor : public Visitor {
public:
	ReslNsVisitor(CompState *state);

	void visit_ADD(Node *n) override;
};

#endif
