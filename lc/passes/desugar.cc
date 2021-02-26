#include "lc.hh"

void DesugarVisitor(Module& m, Node& n)
{
	switch (n.token)
	{

	//
	// NO SYNTACTIC SUGAR FOR NOW
	//

	default: {
		for (auto& child : n)
			DesugarVisitor(m, child);
		break;
	}

	}
}
