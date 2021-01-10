#include "lc.hh"

Module::Module(Compiler *c)
	: c(c)
{
}

bool Module::load_file(std::string fpath)
{
	name = fpath;

	std::ifstream ifs(fpath);
	if (ifs.is_open() == false)
		return false;

	src = std::string(
		(std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>())
	);

	auto l = Lexer(src);
	ast = parse(&l);

	pipe_visitors(ast, {
		new StructNameVisitor(this),
		new ReslNsVisitor(this),
	});

	return true;

}

void Module::print()
{
	std::cout << "=== MODULE '" << name << "' ===" << std::endl;

	std::cout << " => STRUCTS " << std::endl;
	structmgr.print();
}
