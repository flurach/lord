#include "lc.hh"

size_t get_lineno(std::string src, size_t idx)
{
	size_t it = 0;
	size_t lineno = 0;

	while (it != idx)
		lineno += (src[it++] == '\n');

	return lineno + 1;
}

std::string gen_indicator(std::string src, Range r)
{
	auto it = src.begin() + r.begin;
	size_t tab = 0;

	while (it != src.begin()) {
		if (*it-- == '\n')
			break;
		tab++;
	}

	std::string indicator = "";
	while (tab-- > 1)
		indicator.push_back(' ');

	indicator.push_back('^');

	tab = 0;
	while (tab++ < r.end - r.begin - 1)
		indicator.push_back('~');

	return indicator;
}

std::string get_range_line(std::string src, Range r, size_t span)
{
	auto begin = src.begin() + r.begin;
	auto end = src.begin() + r.end;
	size_t cnt;

	cnt = 0;
	while (begin != src.begin() && cnt != span)
		cnt += (*begin-- == '\n');
	begin += 2;

	cnt = 0;
	while (end != src.end() && cnt != span)
		cnt += (*end++ == '\n');
	end--;

	return std::string(begin, end);
}

void print_err(std::string src, Err e, size_t i)
{
	std::string indent = "";
	size_t x = 0;
	while (x++ < i)
		indent.push_back('\t');

	// TODO: change color depending on e.type here
	switch (e.type)
	{
	case E_WARN:
		std::cout << indent << "Warning: ";
		break;

	case E_FATAL:
		std::cout << indent << "Fatal: ";
		break;
	}

	auto lineno = get_lineno(src, e.rng.begin);
	std::cerr << e.msg << ", on line " << lineno << std::endl;
	std::cerr << indent << indent << get_range_line(src, e.rng, 1) << std::endl;
	std::cerr << indent << indent << gen_indicator(src, e.rng) << std::endl;
}
