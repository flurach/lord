#include "lc.hh"

Field::Field(Range r, std::string n, Type *type)
	: defined_at(r), name(n), type(type)
{
}

void Field::print(size_t i)
{
	size_t x = 0;
	while (x++ < i)
		putchar('\t');
	std::cout << name << ": ";
	type->print();
	std::cout << std::endl;
}

Struct::Struct(Node *ref)
	: ref(ref)
{
	defined_at = ref->range;
	name = ref->at(0)->val;
}

void Struct::addMethod(Fn *fn)
{
	fnmgr.add(fn);
}

void Struct::addField(Field f)
{
	fields.push_back(f);
}

void Struct::print(size_t i)
{
	size_t x = 0;
	while (x++ < i)
		putchar('\t');
	std::cout << name << std::endl;

	for (auto f : fields)
		f.print(i + 1);

	for (auto m : fnmgr.fns)
		m->print(i + 1);
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
	for (auto& st : structs) {
		if (st->name == s)
			return st;
	}
	return NULL;
}

void StructMgr::print(size_t i)
{
	for (auto s : structs)
		s->print(i + 1);
}

