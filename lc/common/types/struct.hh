#ifndef LORD_LC_COMMON_TYPES_STRUCT_HH
#define LORD_LC_COMMON_TYPES_STRUCT_HH

class TypeStruct : public Type {
public:
	Module *m = NULL;
	Struct *s = NULL;

public:
	TypeStruct(Module *m, Struct *s);
	size_t byte_size() override;
	std::string as_str() override;
};

#endif
