#include "lc.hh"

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
	ast = *parse(&l);

	pipe_visitors(ast, {
		new DesugarVisitor(*this),
		new PreInferVisitor(*this),
		new PostInferVisitor(*this),
		// new GenVisitor(*this), // TODO
	});

	return true;
}

void Module::print_analysed()
{
	std::cout << "=== MODULE '" << name << "' ===" << std::endl;

	std::cout << " => AST " << std::endl;
	ast.print(1);

	// TODO: print this
	// std::cout << " => FNS " << std::endl;
	// for (auto& fn : fns)
	// 	fn.print(1);
}
