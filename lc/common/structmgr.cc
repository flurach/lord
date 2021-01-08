#include "structmgr.hh"

Field::Field(Range r, std::string n, Type t)
	: range(r), name(n), type(t)
{
}

void Field::print()
{
	std::cout << name << " of type " << type.name << std::endl;
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

void StructMgr::addStruct(Struct s)
{
	structs.push_back(s);
}

void StructMgr::addField(Field f)
{
	structs.back().addField(f);
}

void StructMgr::print()
{
	for (auto s : structs)
		s.print();
}

