#ifndef LORD_LC_COMMON_TYPES_ARR_HH
#define LORD_LC_COMMON_TYPES_ARR_HH

class TypeArr : public Type {
public:
	TypeArr(Type *subtype);
	std::string as_str() override;
};

#endif
