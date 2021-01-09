#include "compiler.hh"
#include "passes/all.hh"

bool Compiler::load_mod(std::string fpath)
{
	Module m = Module(this);

	auto r = m.load_file(fpath);
	if (r)
		mods.push_back(m);

	return r;
}
