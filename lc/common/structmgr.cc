#include "lc.hh"

Field::Field(Range r, std::string n, Type t)
	: range(r), name(n), type(t)
{
}

void Field::print()
{
	std::cout << name << " of type ";
	type.print();
	std::cout << std::endl;
}

Struct::Struct(Range r, std::string n)
	: defined_at(r), name(n)
{
}

void Struct::addField(Field f)
{
	fields.push_back(f);
}

void Struct::print()
{
	std::cout << name << std::endl;
	for (auto f : fields) {
		putchar('\t');
		f.print();
	}
}

StructMgr::~StructMgr()
{
	for (auto s : structs)
		delete s;
}

void StructMgr::add(Struct *s)
{
	structs.push_back(s);
}

Struct *StructMgr::get(std::string s)
{
	for (auto st : structs) {
		if (st->name == s)
			return st;
	}
	return NULL;
}

void StructMgr::print()
{
	for (auto s : structs)
		s->print();
}

