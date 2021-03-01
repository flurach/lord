#include "lc.hh"

void Fn::print(size_t i)
{
	size_t x = 0;
	while (x++ < i)
		putchar('\t');

	std::cout << "type:" << std::endl;
	type.print(i + 1);

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
		pair.second.print(i + 3);
	}
}
