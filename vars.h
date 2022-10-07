#ifndef VARS_H
#define VARS_H
#define HASH_LEN 101

struct HashNode {
	char* key;
	struct List* value;
	struct HashNode* next;
	struct HashNode* prev;
	bool constant;
};

struct HashNode* hashMap[HASH_LEN];

unsigned hash(char* key);
bool is_const(char* key);
void save_val(char* key, struct List* value);
void addHashNode(struct HashNode* node1, struct HashNode* node2);
void print_var(char* var, bool structured);
void make_constant(char* var);
struct HashNode* createHashNode(char* key, struct List* value);
struct List* get_val(char* str);
struct HashNode* get_hashnode_variable(char* key);

#endif
