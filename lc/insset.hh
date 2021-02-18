#ifndef LORD_LC_INSSET_HH
#define LORD_LC_INSSET_HH

// memory destination
enum MemDest {
	MD_REG,
	MD_STACK
};


// first:  destination
// second: payload
typedef std::pair<MemDest, size_t> Mem;


// abstract instruction set
class InsSet {
public:
	// compiles collected data to string
	virtual std::string compile() {}

public:
	// functions
	virtual void ext(std::string func_name) {}
	virtual void call(std::string func_name, bool pic = false) {}

public:
	// memory
	virtual void str(std::string s, size_t id) {}
	virtual void mov(size_t size, Mem from, Mem to) {}

public:
	// maths
	virtual void add(size_t size, Mem from, Mem to) {}
	virtual void sub(size_t size, Mem from, Mem to) {}
	virtual void mul(size_t size, Mem from, Mem to) {}
	virtual void div(size_t size, Mem from, Mem to) {}
};

#endif
