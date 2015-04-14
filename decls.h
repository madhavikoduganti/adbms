struct Users{
	int userId;
	char * userName;
	char * password;
	struct Users * next;
	struct DatabaseAccess * dbAccessList;	
} *userHead;

struct DatabaseAccess{
	struct Databases * database;
	int accessRights;
	struct DatabaseAccess * next;
};

struct Databases{
	int dbId;
	char * dbname;
	struct Tables * tableList;
	struct Database *next;
} *dbHead;

struct Tables{
	int tableId;
	char * tableName;
	char * dbId;
	struct tableSpec * tablespec;
	struct Tables * next;	
} *tableHead;

struct tableSpec{
	int columns;
	int tuples;
};
