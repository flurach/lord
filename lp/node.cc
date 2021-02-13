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

void Node::print(size_t indent) const
{
	size_t i = 0;
	while (i++ < indent)
		putchar('\t');

	std::cout
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

bool Node::operator==(const Node& other) const
{
	if (range.begin != other.range.begin || range.end != other.range.end)
		return false;

	if (token != other.token)
		return false;

	if (val != other.val)
		return false;

	if (size() != other.size())
		return false;

	for (size_t i = 0; i < size(); i++) {
		if ((*this)[i] != other[i])
			return false;
	}

	return true;
}

bool Node::operator!=(const Node& other) const
{
	return !(*this == other);
}
