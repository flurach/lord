#ifndef LORD_LC_COMMON_PASSES_STRUCT_COLLECT_HH
#define LORD_LC_COMMON_PASSES_STRUCT_COLLECT_HH

#include "visitor.hh"

class StructCollectVisitor : public Visitor {
public:
	StructCollectVisitor(Module *m);

	void visit_TYPE(Node *n) override;
};

#endif
