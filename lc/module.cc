#include "lc.hh"

Constraint::Constraint(Range range, Node *lhop, Node *rhop)
	: range(range), lhop(lhop), rhop(rhop)
{
}

Module::~Module()
{
	for (auto t : left_over_types)
		delete t;
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
	ast = *parse(&l);

	pipe_visitors(ast, {
		new DesugarVisitor(*this),
		new InferVisitor(*this),
		// new GenVisitor(*this), // TODO
	});

	return true;
}

void Module::print_analysed()
{
	std::cout << "=== MODULE '" << name << "' ===" << std::endl;

	std::cout << " => AST " << std::endl;
	ast.print(1);

	std::cout << " => CONSTRAINTS " << std::endl;
	for (auto& c : constraints) {
		std::cout << '\t';
		c.lhop->printType();
		std::cout << " = ";
		c.rhop->printType();
		std::cout << std::endl;
	}

	// std::cout << " => FNS " << std::endl;
	// for (auto& fn : fns)
	// 	fn.print(1);
}
