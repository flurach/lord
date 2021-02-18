#ifndef LORD_LC_COMMON_FNMGR_HH
#define LORD_LC_COMMON_FNMGR_HH

struct Fn {
	bool plt;
	std::unordered_map<std::string, size_t> args;
	std::unordered_map<std::string, size_t> locals;

	Fn(bool plt = false);

	size_t frame_size();
	std::pair<size_t, size_t> make_arg(std::string name, size_t s);
	std::pair<size_t, size_t> make_local(std::string name, size_t s);
	std::pair<size_t, size_t> get_local(std::string name);
};

#endif
