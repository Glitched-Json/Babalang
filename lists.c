#ifndef LISTS_C
#define LISTS_C
#include "lists.c"
#include "line.h"
#include "vars.h"

struct List* listDup(struct List* list) {
	struct List* node = new_list(list->value);
	struct List* s = node;
	struct List* temp = list;
	while (list->next != NULL) {
		list = list->next;
		add_node(node, new_list(list->value));
		node = node->next;
	}
	node = s;
	return node;
}

struct List* new_list(struct Value value) {
	struct List* node = (struct List*)malloc(sizeof(struct List));
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

struct List* get_reduced_list(struct List* list) {
	struct List* s = list;
	while (s->value.type == POINTER) s = get_val(s->value.val.s);
	return s;
}

struct List* expand_pointers(struct List* list) {
	if (list == NULL) return null_list();
	struct List* result, *s = list;
	if (list->value.type == POINTER) result = expand_pointers(get_val(list->value.val.s)); else result = new_list(list->value); list = list->next;
	while (list != NULL) {
		if (list->value.type == POINTER) add_node(result, expand_pointers(get_val(list->value.val.s))); else add_node(result, new_list(list->value));
		list = list->next;
	}
	list = s;
	return result;
}

struct List* token_to_list(struct Token* token) {
	struct Token* s = token, *temp;
	struct List* result = NULL;
	
	while (token != NULL) {
		temp = token;
		while (token->type == LINE) token = token->val.line->reduced;
		if (result == NULL)
		switch (token->type) {
			case NOUN: result = listDup(get_val(get_reduced(token)->val.noun)); break;
			case LIST: result = listDup(get_reduced(token)->val.list); break;
			case BLOCK: result = token_to_list(token->val.BlockVal.reduced); break;
		} else
		switch (token->type) {
			case NOUN: add_node(result, listDup(get_val(get_reduced(token)->val.noun))); break;
			case LIST: add_node(result, listDup(get_reduced(token)->val.list)); break;
			case BLOCK: add_node(result, token_to_list(token->val.BlockVal.reduced)); break;
		}
		token = temp;
		token = token->next;
	}
	token = s;
	if (result == NULL) return null_list();
	return result;
}

void add_node(struct List* node1, struct List* node2) {
	while (node1->next != NULL) node1 = node1->next;
	node1->next = node2;
	node2->prev = node1;
}

void mult_list(struct List* list, int val) {
	do {
		switch (list->value.type) {
			case 0: list->value.val.i*=val; break;
			case 1: list->value.val.f*=val; break;
			case 2: char* str = ""; for (int i=0; i<=val; i++) strcat(str,list->value.val.s); list->value.val.s = str; break;
		}
		list=list->next;
	} while (list!=NULL);
}

char* list_to_string(struct List* list) {
	struct List* start = list;
	int l = 10, i = 0, size;
	char* s = (char*)malloc(sizeof(char)*l);
	while (list != NULL) {
		char* temp = val_to_string(list->value);
		size = strlen(temp);
		while (i+size+1>=l) {l*=2; s = (char*)realloc(s, sizeof(char)*l);}
		strcat(s, ctoa(LST_DIV));
		strcat(s, temp);
		i+=size+1;
		
		list = list->next;
	}
	list = start;
	if (++i != l) s = (char*)realloc(s, sizeof(char)*i);
	s[i-1] = '\0';
	return s;
}

char* val_to_string(struct Value v) {
	char* s;
	switch (v.type) {
		case INT: return itoa(v.val.i);
		case FLOAT: return ftoa(v.val.f);
		case STRING: s = (char*)malloc(sizeof(char)*(strlen(v.val.s)+2)); s[0]='"'; s[1] = 0; strcat(s,v.val.s); strcat(s,"\""); return s;
		case BOOL: return v.val.b?"TRUE":"FALSE";
		case CHAR: s = (char*)malloc(sizeof(char)*4); s[0]='\''; s[1]=v.val.c; s[2]='\''; s[3]='\0'; return s;
		case POINTER: s = (char*)malloc(sizeof(char)*(strlen(v.val.s)+1)); s[0] = '*'; s[1] = 0; strcat(s, v.val.s); return s;
		default: return "NULL";
	}
}

bool list_contains(struct List* list, struct Value val) {
	bool found = false;
	while (list != NULL && !found) {
		found = are_vals_equal(list->value, val);
		list = list->next;
	}
	return found;
}

bool are_vals_equal(struct Value val1, struct Value val2) {
	if (val1.type != val2.type) return false;
	switch (val1.type) {
		case INT: return val1.val.i == val2.val.i;
		case FLOAT: return val1.val.f == val2.val.f;
		case STRING: case POINTER: return strcmp(val1.val.s, val2.val.s);
		case BOOL: return val1.val.b == val2.val.b;
		case CHAR: return val1.val.c == val2.val.c;
		case IS_NULL: return true;
		default: return false;
	}
}

void print_list(struct List* node, bool structured) {
	if (node == NULL) {if (structured) printf("[]\n"); return;}
	struct List* start = node;
	if (structured) printf("[");
	do {
		switch (node->value.type) {
			case INT: printf("%ld",node->value.val.i); break;
			case FLOAT: printf("%s",ftoa(node->value.val.f)); break;
			case STRING:
				if (structured) printf("\"%s\"", str_replace(node->value.val.s, "\n", "\\n")); else
					        printf("%s", node->value.val.s);
				break;
			case BOOL: printf(node->value.val.b?"true":"false"); break;
			case CHAR: structured?(node->value.val.c=='\n'?printf("\'\\n\'"):printf("\'%c\'",node->value.val.c)):printf("%c",node->value.val.c); break;
			case POINTER: if (structured) {
					if (lookup(node->value.val.s) == NULL) {
						install(node->value.val.s, "printlist");
						printf("*%s",node->value.val.s); print_list(get_val(node->value.val.s), true);
					} else {
						printf("*%s[...]", node->value.val.s);
						emptyDictionary();
					}
				      } else printf("*%s",node->value.val.s); break;
			default: printf(structured?"null":""); break;
		}
		if (node->next != NULL && structured) printf(", ");
		node = node->next;
	} while (node != NULL);
	printf(structured?"]":"");
	node = start;
}

struct Value get_val_index(struct List* list, int index) {
	for (int i=index; i>0 && list!=NULL; i--, list=list->next);
	if (list!=NULL && index>=0) return list->value;
	return val_i(0);
}

struct Value get_val_pointer(struct List* list, char* noun) {
	bool found = false;
	while (list!=NULL && !found) {
		if (list->value.type == POINTER && strcmp(list->value.val.s, noun)) found=true; else list=list->next;
	}
	if (found) return list->value;
	return val_null();
}

struct Value string_to_value(char* s) {
	char* t, *start; int i;
	if (*s == '"')  {
		t = (char*)malloc(sizeof(char)*(strlen(++s)-1)); start = s-1; i = 0;
		while (*(++s)!=0) t[i++]=*(s-1); t[i]=0; s=start;
		return val_s(t);
		}
	if (*s == '\'') {char t = s[1]; return val_c(t);}
	if (*s == '*') {
		t = (char*)malloc(sizeof(char)*(strlen(++s))); start = s-1; i = 0;
		while (*(s)!=0) t[i++]=*s++; t[i]=0; s=start;
		return val_p(t);
	}
	if (strcmp(s, "null")==0 || strcmp(s, "NULL")==0) {return val_null();}
	if (strcmp(s, "true")==0 || strcmp(s, "TRUE")==0) {return val_b(true);}
	if (strcmp(s, "false")==0 || strcmp(s, "FALSE")==0) {return val_b(false);}
	if (strchr(s, '.')!=NULL || strchr(s, 'f')!=NULL || strchr(s, 'F')!=NULL) return val_f(atof(s));
	return val_i(atoi(s)); 
}

struct Value value_to_bool(struct Value v) {
	bool a;
	switch (v.type) {
		case INT: a = (v.val.i == 0); break;
		case FLOAT: a = (v.val.f == 0); break;
		case STRING: a = (v.val.s == "true"); break;
		case BOOL: a = v.val.b; break;
		case IS_NULL: a = false; break;
		default: a = false;
	}
	return val_b(a);
}

struct Value to_value(struct Token* t) {
	if (t == NULL) return val_null();
	switch (t->type) {
		case NOUN: return get_val(t->val.noun)->value;
		case LIST: return t->val.list->value;
		default: return val_null();
	}
}
#endif
