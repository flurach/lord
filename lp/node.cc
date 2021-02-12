#include "lp.hh"

Node::Node(Range range, Token token, std::string val)
	: range(range), token(token), val(val)
{
}

void Node::push(Node child)
{
	push_back(child);
}

Node Node::pop()
{
	auto last = back();
	pop_back();
	return last;
}

bool Node::binarify()
{
	if (size() != 3)
		return false;

	auto trd = pop();
	auto snd = pop();
	auto fst = pop();

	snd.push(fst);
	snd.push(trd);
	*this = snd;

	return true;
}

void Node::print(size_t indent)
{
	size_t i = 0;
	while (i++ < indent)
		putchar('\t');

	std::cout
		<< id
		<< " "
		<< Token_str[token]
		<< " '"
		<< val
		<< "' "
		<< range.begin
		<< ".."
		<< range.end
		<< std::endl;

	for (auto c : *this)
		c.print(indent + 1);
}
