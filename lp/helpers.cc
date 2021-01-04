#include "helpers.hh"

std::optional<std::string> ftoa(char *fpath)
{
	std::ifstream ifs(fpath);
	if (ifs.is_open() == false)
		return {};
	std::string content(
		(std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>())
	);
	return content;
}
