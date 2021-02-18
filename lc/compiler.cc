#include "lc.hh"

// TODO make sure loaded modules are unique
// and loaded only once in here.
//
// return ref to the requested module if it exists.
Module *Compiler::load_mod(std::string fpath, std::string name)
{
	Module m = Module(this, name);

	if (m.load_file(fpath)) {
		mods.push_back(m);
		return mods.end().base();
	}

	return NULL;
}

std::string Compiler::compile()
{
	std::string output = "";

	if (backend == "gas-x86_64") {
		for (auto m : mods) {
			GenGasX86_64 g(m);
			g.visit(m.ast);
			output += g.buf;
		}
	}

	return output;
}

void Compiler::analyze()
{
	for (auto& m : mods)
		m.print();
}
