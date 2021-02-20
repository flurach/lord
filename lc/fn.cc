#include "lc.hh"

size_t Fn::frame_size()
{
	size_t start = 0;

	if (locals.size())
		start = locals.end()->second.starts_at;

	return start;
}

void Fn::make_arg(std::string name, size_t s)
{
	args[name] = s; // TODO: no two arguments must have the same name
			// check this beforehand with another pass
	make_local(name, s);
}

void Fn::make_local(std::string name, size_t s)
{
	auto already_exists = locals.find(name) != locals.end();
	if (already_exists)
		return;

	size_t start = s;
	if (locals.size())
		start = locals.end()->second.starts_at + s;

	locals[name] = (FnLocal){
		.starts_at = start,
		.has_size = s
	};
}
