#ifndef LORD_LC_COMMON_TYPES_BUILTIN_I64_HH
#define LORD_LC_COMMON_TYPES_BUILTIN_I64_HH

class TypeI64 : public Type {
public:
	size_t byte_size() override;
	std::string as_str() override;
};

#endif
