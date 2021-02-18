#include "lc.hh"

std::string compile()
{
	return data_section + text_section;
}

void ext(std::string func_name)
{
	data_section += "\t.extern " + func_name + "\n";
}

void call(std::string func_name, bool pic = false)
{
	text_section += "\tcall " + func_name;
	if (pic)
		text_section += "@PLT";
	text_section += "\n";
}

void str(size_t id, std::string s)
{
	data_section += ".S" + std::to_string(id) + ":\n";
	data_section += "\t.string \"" + s + "\"\n";
}

void mov(size_t size, Mem from, Mem to)
{
	// TODO remove this. makes no sense
	// I love my sisters ❤️
}

void add(size_t size, Mem from, Mem to)
{

}

void sub(size_t size, Mem from, Mem to)
{
}

void mul(size_t size, Mem from, Mem to)
{
}

void div(size_t size, Mem from, Mem to)
{
}
