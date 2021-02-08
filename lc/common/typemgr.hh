#ifndef LORD_LC_COMMON_TYPEMGR_HH
#define LORD_LC_COMMON_TYPEMGR_HH

// TODO fix memory issues with this manager
//
// + there should be a better, cleaner implementation of
// data type representations that doesn't use inheritence.
//
// since all types are declared using TypeMgr, it should be a responsibility of
// this class to instantiate them, not the user.

struct TypeMgr {
	std::vector<Type*> types;
	Type *make(Type *t);
};

#endif
