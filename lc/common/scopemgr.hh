#ifndef LORD_LC_COMMON_SCOPEMGR_HH
#define LORD_LC_COMMON_SCOPEMGR_HH

struct Scope {
	std::map<std::string, Type> types;
	std::map<std::string, size_t> muts;

	void setType(std::string sym, Type type);
	void incMut(std::string sym);

	void print();
};

#endif
