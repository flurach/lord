#ifndef LORD_LC_COMMON_SCOPE_HH
#define LORD_LC_COMMON_SCOPE_HH

struct Scope {
	std::vector<std::map<Node, Node*>> syms;

	Scope();

	Node *make(Node sym, Node *type);
	Node *get(Node sym);

	void ascend();
	void descend();
};

#endif
