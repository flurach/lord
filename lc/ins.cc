#include "lc.hh"

std::ostream& operator<<(std::ostream& stream, const Ins::Register& self)
{
	return stream
		<< "%r" << self.index
		<< "(" << self.size << ")";
}

std::ostream& operator<<(std::ostream& stream, const Ins::Literal& self)
{
	return stream << "$" << self.value;
}

std::ostream& operator<<(std::ostream& stream, const Ins::LabelRef& self)
{
	return stream << "." << self.value;
}

std::ostream& operator<<(std::ostream& stream, const Ins::Mem& self)
{
	if (auto s = std::get_if<Ins::Register>(&self))
		stream << *s;
	else if (auto s = std::get_if<Ins::Literal>(&self))
		stream << *s;
	else if (auto s = std::get_if<Ins::LabelRef>(&self))
		stream << *s;
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Ins::Label& self)
{
	return stream
		<< "Label { "
		<< "name = " << '"' << self.name << '"'
		<< " }";
}

std::ostream& operator<<(std::ostream& stream, const Ins::Add& self)
{
	return stream
		<< "Add { "
		<< "left = " << self.left << ", "
		<< "right = " << self.right << ", "
		<< "into = " << self.into
		<< " }";
}

std::ostream& operator<<(std::ostream& stream, const Ins::Sub& self)
{
	return stream
		<< "Sub { "
		<< "left = " << self.left << ", "
		<< "right = " << self.right << ", "
		<< "into = " << self.into
		<< " }";
}

std::ostream& operator<<(std::ostream& stream, const Ins::Mul& self)
{
	return stream
		<< "Mul { "
		<< "left = " << self.left << ", "
		<< "right = " << self.right << ", "
		<< "into = " << self.into
		<< " }";
}

std::ostream& operator<<(std::ostream& stream, const Ins::Div& self)
{
	return stream
		<< "Div { "
		<< "left = " << self.left << ", "
		<< "right = " << self.right << ", "
		<< "into = " << self.into
		<< " }";
}

std::ostream& operator<<(std::ostream& stream, const Ins::Mov& self)
{
	return stream
		<< "Mov { "
		<< "from = " << self.from << ", "
		<< "to = " << self.to
		<< " }";
}

std::ostream& operator<<(std::ostream& stream, const Ins::Ret& self)
{
	(void)self;
	return stream << "Ret";
}

std::ostream& operator<<(std::ostream& stream, const Ins::Ins& self)
{
	if (auto s = std::get_if<Ins::Label>(&self))
		stream << *s;
	else if (auto s = std::get_if<Ins::Add>(&self))
		stream << *s;
	else if (auto s = std::get_if<Ins::Sub>(&self))
		stream << *s;
	else if (auto s = std::get_if<Ins::Mul>(&self))
		stream << *s;
	else if (auto s = std::get_if<Ins::Div>(&self))
		stream << *s;
	else if (auto s = std::get_if<Ins::Mov>(&self))
		stream << *s;
	else if (auto s = std::get_if<Ins::Ret>(&self))
		stream << *s;
	return stream;
}
