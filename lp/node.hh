#ifndef LORD_LP_NODE_HH
#define LORD_LP_NODE_HH

/* node class */
struct Node : std::vector<Node*> {
	int id = -1;
	Range range = {0, 0};
	Token token = T_EOF;
	std::string val = "";

	/* constructor & destructor */
	Node(Range range = {0, 0}, Token token = T_EOF, std::string val = "");

	/* methods */
	void push(Node *child);
	Node *pop();
	bool binarify();
	bool leadify();

	/* debugging */
	void print(size_t indent = 0);
};

#endif
