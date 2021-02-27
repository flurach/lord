#ifndef LORD_LC_ENTITIES_FN_HH
#define LORD_LC_ENTITIES_FN_HH


struct Fn {
	using Type = Node;

	Type *type = NULL;
	std::map<std::string, Type*> locals;

	~Fn();
	void print(size_t i = 0);
};

#endif
