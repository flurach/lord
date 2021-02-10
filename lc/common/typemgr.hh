#ifndef LORD_LC_COMMON_TYPEMGR_HH
#define LORD_LC_COMMON_TYPEMGR_HH

// TODO fix memory issues with this manager
//
// + there should be a better, cleaner implementation of
// data type representations that doesn't use inheritence.
//
// since all types are declared using TypeMgr, it should be a responsibility of
// this class to instantiate them, not the user.

class TypeMgr : std::vector<Type*> {
public:
	~TypeMgr();

	Type *make(Type *t);

	Type *make_atomic(std::string name);
	Type *make_arr(Type *t);

	Type *make_struct(Node *ref, std::string name);
	Type *make_fn(Node *ref, std::string name);
};

#endif
