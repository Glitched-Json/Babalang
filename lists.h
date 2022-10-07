#ifndef LISTS_H
#define LISTS_H
#include "line.h"

struct Value {
	union Val {
		long int i;
		float f;
		char* s;
		bool b;
		char c;
	} val;
	enum Type{INT, FLOAT, STRING, BOOL, CHAR, POINTER, IS_NULL} type;
};

struct List {
	struct Value value;
	struct List* next;
	struct List* prev;
};

char* val_to_string(struct Value v);
char* list_to_string(struct List* list);
bool list_contains(struct List* list, struct Value val);
bool are_vals_equal(struct Value val1, struct Value val2);
void add_node(struct List* node1, struct List* node2);
void mult_list(struct List* list, int val);
void print_list(struct List* node, bool structured);
struct List* new_list(struct Value value);
struct List* listDup(struct List* list);
struct List* get_reduced_list(struct List* list);
struct List* expand_pointers(struct List* list);
struct List* token_to_list(struct Token* token);
struct Value get_val_index(struct List* list, int index);
struct Value get_val_pointer(struct List* list, char* noun);
struct Value string_to_value(char* s);
struct Value value_to_bool(struct Value v);

#endif
