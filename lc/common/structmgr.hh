#ifndef LORD_LC_COMMON_STRUCTMGR_HH
#define LORD_LC_COMMON_STRUCTMGR_HH

struct Field {
	Range range;
	std::string name;

	Field(Range r, std::string n);
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
	std::vector<Struct*> structs;

	~StructMgr();

	void add(Struct *s);
	Struct *get(std::string s);

	void print();
};

#endif
