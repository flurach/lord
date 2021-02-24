#include "lc.hh"

std::optional<Module> load_module(std::string fpath)
{
	std::ifstream ifs(fpath);
	if (ifs.is_open() == false)
		return {};

	auto src = std::string(
		(std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>())
	);
	auto l = Lexer(src);
	auto ast = *parse(&l);

	return Module {
		.name = fpath,
		.src = src,
		.ast = ast
	};
}
