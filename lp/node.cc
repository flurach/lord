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

Node Node::toType() const
{
	if (token == T_SYM) {
		return Node(range, T_SYM, val);
	} else if (token == T_ARR) {
		auto t = Node(range, T_ARR);
		t.push(this->at(0).toType());
		return t;
	} else if (token == T_INT) {
		return Node(range, T_SYM, "i64");
	} else if (token == T_INT) {
		return Node(range, T_SYM, "f64");
	} else if (token == T_STR) {
		return Node(range, T_SYM, "str");
	} else if (size()) {
		return at(0).toType();
	}

	return Node(range, T_NONE);
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
