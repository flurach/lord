#include "node.hh"

Node::Node(Range range, Token token, std::string val)
	: range(range), token(token), val(val)
{
}

void Node::push(Node *child)
{
	ns.push_back(child);
}

Node *Node::pop()
{
	auto last = ns.back();
	ns.pop_back();
	return last;
}

bool Node::binarify()
{
	if (ns.size() != 3)
		return false;

	auto fst = pop();
	auto snd = pop();
	auto trd = pop();

	snd->push(fst);
	snd->push(trd);
	*this = *snd;

	return true;
}

void Node::print()
{
	static size_t indent = 0;

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

	indent++;
	for (i = 0; i < ns.size(); i++)
		ns[i]->print();
	indent--;
}
