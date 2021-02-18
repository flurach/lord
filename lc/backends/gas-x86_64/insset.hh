#ifndef LORD_LC_BACKENDS_GAS_X86_64_INSSET_HH
#define LORD_LC_BACKENDS_GAS_X86_64_INSSET_HH

class InsSetX86_64 : public InsSet {
private:
	std::string data_section = "\t.section .rodata\n";
	std::string text_section = "\t.text\n";

public:
	std::string compile() override;

public:
	void ext(std::string func_name) override;
	void call(std::string func_name, bool pic = false) override;

public:
	void str(std::string s, size_t id) override;
	void mov(size_t size, Mem from, Mem to) override;

public:
	void add(size_t size, Mem from, Mem to) override;
	void sub(size_t size, Mem from, Mem to) override;
	void mul(size_t size, Mem from, Mem to) override;
	void div(size_t size, Mem from, Mem to) override;
};

#endif
