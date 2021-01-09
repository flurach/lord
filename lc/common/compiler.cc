#include "lc.hh"

Compiler::~Compiler()
{
	for (auto m : mods)
		delete m;
}

Module *Compiler::load_mod(std::string fpath)
{
	Module *m = new Module(this);

	if (m->load_file(fpath)) {
		mods.push_back(m);
		return mods.back();
	}

	return NULL;
}

void Compiler::print()
{
	for (auto m : mods)
		m->print();
}
