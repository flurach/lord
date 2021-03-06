#ifndef LORD_LC_ERR_HH
#define LORD_LC_ERR_HH

enum ErrType {
	E_WARN,
	E_FATAL
};

struct Err {
	ErrType type;
	Range rng;
	std::string msg;
};

void print_err(std::string src, Err e, size_t i = 0);

#endif
