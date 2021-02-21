#ifndef LORD_LC_FN_HH
#define LORD_LC_FN_HH

struct FnLocal {
	size_t starts_at;
	size_t has_size;
};

struct Fn {
	Node *type = NULL;

	std::unordered_map<std::string, size_t> args;
	std::unordered_map<std::string, FnLocal> locals;

	void make_arg(std::string name, size_t s);
	void make_local(std::string name, size_t s);

	size_t frame_size();
};

#endif
