#include "lc.hh"

Module* Compiler::load_mod(std::string fpath, std::string name)
{
	Module m = Module(this, name);

	if (m.load_file(fpath)) {
		mods.push_back(m);
		return mods.end().base();
	}

	return NULL;
}

void Compiler::print()
{
	for (auto& m : mods)
		m.print();
}
