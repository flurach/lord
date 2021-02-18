#include "lc.hh"

Module::Module(Compiler *c, std::string name)
	: c(c), name(name)
{
	/* add standard functions */
	auto fn_puts = Fn(true);
	fn_puts.make_arg("s", 8);
	fns["puts"] = fn_puts;
}

bool Module::load_file(std::string fpath)
{
	if (!name.length())
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
	});

	return true;
}

void Module::print()
{
	std::cout << "=== MODULE '" << name << "' ===" << std::endl;

	std::cout << " => AST " << std::endl;
	ast.print(1);
}
