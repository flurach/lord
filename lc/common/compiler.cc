#include "lc.hh"

Module *Compiler::load_mod(std::string fpath, std::string name)
{
	Module m = Module(this, name);

	if (m.load_file(fpath)) {
		mods.push_back(m);
		return mods.end().base();
	}

	return NULL;
}

void Compiler::gencc()
{
	for (auto m : mods) {
		GenccVisitor g(m);
		g.visit(m.ast);
		std::cout << g.buf << std::endl;
	}
}

void Compiler::print()
{
	for (auto& m : mods)
		m.print();
}
