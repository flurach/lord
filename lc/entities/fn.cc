#include "lc.hh"

Fn::~Fn()
{
	if (type)
		delete type;

	for (auto& pair : locals) {
		if (pair.second)
			delete pair.second;
	}
}

void Fn::print(size_t i)
{
	size_t x = 0;
	while (x++ < i)
		putchar('\t');

	std::cout << "type:" << std::endl;
	if (type)
		type->print(i + 1);

	x = 0;
	while (x++ < i)
		putchar('\t');
	std::cout << "locals:" << std::endl;
	for (auto& pair : locals) {
		x = 0;
		while (x++ < i)
			putchar('\t');
		putchar('\t');
		putchar('\t');

		std::cout << pair.first << std::endl;
		if (pair.second)
			pair.second->print(i + 3);
	}
}
