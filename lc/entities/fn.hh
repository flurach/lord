#ifndef LORD_LC_ENTITIES_FN_HH
#define LORD_LC_ENTITIES_FN_HH


struct Fn {
	Node type = Node(Range {0, 0}, T_NONE);
	std::map<std::string, Node> locals;

	void print(size_t i = 0);
};

#endif
