#include "lc.hh"

Fn::Fn(bool plt)
	: plt(plt)
{
}

size_t Fn::frame_size()
{
	size_t start = 0;

	for (auto& pair : locals)
		start += pair.second;

	return start;
}

std::pair<size_t, size_t> Fn::make_arg(std::string name, size_t s)
{
	args[name] = s;
	return make_local(name, s);
}

std::pair<size_t, size_t> Fn::make_local(std::string name, size_t s)
{
	size_t start = 0;

	for (auto& pair : locals) {
		if (pair.first == name)
			return std::make_pair(start, s);
		start += pair.second;
	}

	locals[name] = s;
	return std::make_pair(start, s);
}

std::pair<size_t, size_t> Fn::get_local(std::string name)
{
	size_t start = 0;

	for (auto& pair : locals) {
		if (pair.first == name)
			return std::make_pair(start, pair.second);
		start += pair.second;
	}

	return std::make_pair(start, 0);
}
