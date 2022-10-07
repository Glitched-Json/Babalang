#ifndef VARS_C
#define VARS_C
#include "lists.c"
#include "vars.h"

struct HashNode* get_hashnode_variable(char* key) {
	if (key == NULL) return NULL;
	int h = hash(key);
	if (hashMap[h] == NULL) return NULL;
	struct HashNode* node = hashMap[h];
	bool found = false;
	while (!found) {
		if (strcmp(node->key, key)==0) {found=true; break;}
		if (node->next == NULL) {break;}
		node = node->next;
	}
	if (!found) return NULL;
	return node;
}

void save_val(char* key, struct List* value) {
	int h = hash(key);
	if (hashMap[h] == NULL) {
		hashMap[h] = createHashNode(key, value);
		save_val(key, value);
	} else {
		struct HashNode* node = hashMap[h];
		bool found = false;
		while (!found) {
			if (strcmp(node->key, key)==0) {found=true; break;}
			if (node->next == NULL) {break;}
			node = node->next;
		}
		if (found) {
			if (node->constant) return;
			node->value = listDup(value);
		} else {
			addHashNode(node, createHashNode(key, listDup(value)));
		}
	}
}

struct HashNode* createHashNode(char* key, struct List* value) {
	struct HashNode* node = (struct HashNode*)malloc(sizeof(struct HashNode));
	node->key = strdup(key);
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	node->constant = false;
	return node;
}

void addHashNode(struct HashNode* node1, struct HashNode* node2) {
	while (node1->next != NULL) node1 = node1->next;
	node1->next = node2;
	node2->prev = node1;
}

void make_constant(char* var) {
	struct HashNode* node = get_hashnode_variable(var);
	if (node != NULL) node->constant = true;
}

bool is_const(char* key) {
	struct HashNode* node = get_hashnode_variable(key);
	if (node == NULL) return true; else return node->constant;
}

struct List* get_val(char* key) {
	struct HashNode* node = get_hashnode_variable(key);
	if (node == NULL) return_blank else return node->value;
}

unsigned hash(char* key) {
	unsigned h;
	for (h = 0; *key != '\0'; key++)
		h = *key + 31 * h;
	return h % HASH_LEN;
}

void print_var(char* var, bool structured) {
	install(var, "printlist");
	if (structured) {if (is_const(var)) printf("<%s> is ", var); else printf("%s is ",var);}
	print_list(get_val(var), structured);
	emptyDictionary();
}
#endif
