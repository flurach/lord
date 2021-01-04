#ifndef LORD_LP_NODE_HH
#define LORD_LP_NODE_HH

#include <iostream>
#include <vector>
#include "token.hh"
#include "common.hh"

/* node class */
struct Node {
	int id = -1;
	Range range = {0, 0};
	Token token = T_EOF;
	std::string val = "";
	std::vector<Node*> ns = {};

	/* constructor & destructor */
	Node(Range range = {0, 0}, Token token = T_EOF, std::string val = "");

	/* methods */
	void push(Node *child);
	Node *pop();
	bool binarify();

	/* debugging */
	void print();
};

#endif
