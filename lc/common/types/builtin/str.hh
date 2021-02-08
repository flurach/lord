#ifndef LORD_LC_COMMON_TYPES_BUILTIN_STR_HH
#define LORD_LC_COMMON_TYPES_BUILTIN_STR_HH

class TypeStr : public Type {
public:
	size_t byte_size() override;
	std::string as_str() override;
};

#endif
