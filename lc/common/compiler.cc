#include "compiler.hh"
#include "passes/all.hh"

Compiler::Compiler()
{
}

Compiler::~Compiler()
{
	if (ast)
		delete ast;
}

bool Compiler::load_file(std::string fpath)
{
	std::ifstream ifs(fpath);
	if (!ifs.is_open())
		return false;

	src = std::string(
		(std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>())
	);

	auto lexer = Lexer(src);
	ast = parse(&lexer);
	pipe_visitors(ast, {
		new StructCollectVisitor(this),
		new ReslNsVisitor(this)
	});

	return true;
}

void Compiler::print()
{
	std::cout << "\n[STRUCTS NAMES]:" << std::endl;
	for (auto sn : structns.syms)
		std::cout << sn << std::endl;

	std::cout << "\n[STRUCTS]:" << std::endl;
	structmgr.print();

	/* std::cout << "\n[AST]:" << std::endl; */
	/* ast->print(); */

	std::cout << "\n[SOURCE]:" << std::endl;
	std::cout << src << std::endl;
}
