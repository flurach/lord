#ifndef LORD_LC_COMMON_STRUCTMGR_HH
#define LORD_LC_COMMON_STRUCTMGR_HH

struct Field {
	Range range;
	std::string name;
	Type type;

	Field(Range r, std::string n, Type t);
	void print();
};

struct Struct {
	/* known data */
	std::string module;
	Range range;
	Range defined_at;

	/* collected data */
	std::string name = "";
	std::vector<Field> fields;

	Struct(Range r, std::string n);

	void addField(Field f);

	void print();
};

struct StructMgr {
	std::vector<Struct> structs;

	void addStruct(Struct s);
	void addField(Field f);

	void print();
};

#endif
