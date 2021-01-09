#include "lc.hh"

bool Compiler::load_mod(std::string fpath)
{
	Module m = Module(this);

	auto r = m.load_file(fpath);
	if (r)
		mods.push_back(m);

	return r;
}

void Compiler::print()
{
	for (auto m : mods)
		m.print();
}
