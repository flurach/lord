#include "lc.hh"

Module::Module(Compiler *c, std::string name)
	: c(c), name(name)
{
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
	ast = parse(&l);

	pipe_visitors(ast, {
		new DesugarVisitor(this),
		new StructVisitor(this),
		new StructFieldVisitor(this),
		new FnAndMethodVisitor(this),
		new MethodBodyVisitor(this),
		new FnBodyVisitor(this),
	});

	return true;
}

void Module::print()
{
	std::cout << "=== MODULE '" << name << "' ===" << std::endl;

	std::cout << " => AST " << std::endl;
	ast->print(1);

	std::cout << " => STRUCTS " << std::endl;
	for (auto pair : structs) {
		if (!pair.second)
			continue;
		pair.second->print(1);
		std::cout << std::endl;
	}

	std::cout << " => FUNCTIONS " << std::endl;
	for (auto pair : fns) {
		putchar('\t');
		std::cout << pair.first << ": ";
		pair.second->print();
		std::cout << std::endl;
	}
}

std::string Module::genpy()
{
	PygenVisitor pygenv(this);
	pygenv.visit(ast);
	return pygenv.buf;
}
