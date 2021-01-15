#ifndef LORD_LC_COMMON_STRUCTMGR_HH
#define LORD_LC_COMMON_STRUCTMGR_HH

struct Field {
	Range defined_at;
	std::string name;
	Type type;

	Field(Range r, std::string n, Type t);
	void print();
};

struct Struct {
	/* known data */
	Node *ref;

	/* collected data */
	Range defined_at;
	std::string name = "";
	FnMgr fnmgr = FnMgr();
	std::vector<Field> fields;

	/* constructor */
	Struct(Node *ref);

	/* debug */
	void addMethod(Fn *fn);
	void addField(Field f);

	/* debug */
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
