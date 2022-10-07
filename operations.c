#ifndef OPERATIONS_C
#define OPERATIONS_C
#include "vars.c"
#include "operations.h"

struct List* not_var_s(char* var);
struct List* not_val(struct List* v);
struct List* eq_vars_s(char* var1, char* var2);
struct List* eq_vals(struct List* v1, struct List* v2);
struct List* xor_vars_s(char* var1, char* var2);
struct List* xor_vals(struct List* v1, struct List* v2);
struct List* or_vars_s(char* var1, char* var2);
struct List* or_vals(struct List* v1, struct List* v2);
struct List* mod_vars_s(char* var1, char* var2);
struct List* mod_vals(struct List* v1, struct List* v2);
struct List* div_vars_s(char* var1, char* var2);
struct List* div_vals(struct List* v1, struct List* v2);
struct List* split_vars_s(char* var1, char* var2);
struct List* split_vals(struct List* v1, struct List* v2);
struct List* mult_vars_s(char* var1, char* var2);
struct List* mult_vals(struct List* v1, struct List* v2);
struct List* sub_vars_s(char* var1, char* var2);
struct List* sub_vals(struct List* v1, struct List* v2);
struct List* add_vars_s(char* var1, char* var2);
struct List* sublist_vals(struct List* v1, struct List* v2);
struct List* sublist_vars_s(char* var1, char* var2);
struct List* add_vals(struct List* v1, struct List* v2);
struct Value list_get(struct List* list, int pos);
struct List* noun_get_from_list(char* key, struct List* list);
struct List* list_get_from_list(struct List* list1, struct List* list2);
struct List* generate_spectrum_float(float f1, float f2);
struct List* generate_spectrum_char(char c1, char c2);
struct List* generate_spectrum(int i1, int i2);
struct List* concat_vars(char* var1, char* var2);
int to_int(struct List* list);
bool is_true(struct List* var);

//--------------------------------------------------------------------------------

struct List* generate_spectrum(int i1, int i2) {
	struct List* node = int_list(i1);
	if (i1<=i2) {
		for (int i=i1+1; i<=i2; i++) add_node(node, int_list(i));
	} else {
		for (int i=i1-1; i>=i2; i--) add_node(node, int_list(i));
	}
	return node;
}

struct List* generate_spectrum_char(char c1, char c2) {
	struct List* node = char_list(c1);
	if (c1<c2) {
		for (int i = (int)c1+1; i<=(int)c2; i++) {add_node(node, char_list(i));}
	} else {
		for (int i = (int)c1-1; i>=(int)c2; i--) {add_node(node, char_list(i));}
	}
	return node;
}

struct List* generate_spectrum_float(float f1, float f2) {
	struct List* node = float_list(f1);
	int a = (int)f1, b = (int)f2;
	float s = f1-a, d;
	if (a-b!=0) d = (f2-b-s)/abs(a-b); else d = 0;
	if (f1<f2) {
		for (int i = a+1, k=1; i<=b; i++) {add_node(node, float_list(i+s+d*(k++)));}
	} else {
		for (int i = a-1, k=1; i>=b; i--) {add_node(node, float_list(i+s+d*(k++)));}
	}
	return node;
}

struct List* add_vals(struct List* v1, struct List* v2) {
	struct List* temp1 = v1; struct List* temp2 = v2;
	v1 = expand_pointers(v1);
	v2 = expand_pointers(v2);
	if (v1==NULL) return v2;
	if (v2==NULL) return v1;
	
	struct List* result = new_list(add_op(v1->value, v2->value));
	while (v1->next!=NULL && v2->next!=NULL) {
		v1=v1->next; v2=v2->next;
		add_node(result, new_list(add_op(v1->value, v2->value)));
	}
	while (v1->next!=NULL) {v1=v1->next; add_node(result, new_list(v1->value));}
	while (v2->next!=NULL) {v2=v2->next; add_node(result, new_list(v2->value));}
	v1=temp1; v2=temp2;
	return result;
}
struct List* add_vars_s(char* var1, char* var2) {
	return add_vals(get_val(var1), get_val(var2));
}

struct List* sub_vals(struct List* v1, struct List* v2) {
	struct List* temp1 = v1; struct List* temp2 = v2;
	v1 = expand_pointers(v1);
	v2 = expand_pointers(v2);
	if (v1==NULL) return v2;
	if (v2==NULL) return v1;
	
	struct List* result = new_list(sub_op(v1->value, v2->value));
	while (v1->next!=NULL && v2->next!=NULL) {
		v1=v1->next; v2=v2->next;
		add_node(result, new_list(sub_op(v1->value, v2->value)));
	}
	while (v1->next!=NULL) {v1=v1->next; add_node(result, new_list(v1->value));}
	while (v2->next!=NULL) {v2=v2->next; add_node(result, new_list(v2->value));}
	v1=temp1; v2=temp2;
	return result;
}
struct List* sub_vars_s(char* var1, char* var2) {
	return sub_vals(get_val(var1), get_val(var2));
}

struct List* mult_vals(struct List* v1, struct List* v2) {
	struct List* temp1 = v1; struct List* temp2 = v2;
	if (v1==NULL) return v2;
	if (v2==NULL) return v1;
	struct List* result = new_list(mult_op(v1->value, v2->value));
	
	while (v1->next!=NULL && v2->next!=NULL) {
		v1=v1->next; v2=v2->next;
		add_node(result, new_list(mult_op(v1->value, v2->value)));
	}
	while (v1->next!=NULL) {v1=v1->next; add_node(result, new_list(v1->value));}
	while (v2->next!=NULL) {v2=v2->next; add_node(result, new_list(v2->value));}
	v1=temp1; v2=temp2;
	return result;
}
struct List* mult_vars_s(char* var1, char* var2) {
	return mult_vals(get_val(var1), get_val(var2));
}

struct List* split_vals(struct List* v1, struct List* v2) {
	struct List* temp1 = v1; struct List* temp2 = v2;
	if (v1==NULL) return v2;
	if (v2==NULL) return v1;
	struct List* result = new_list(split_op(v1->value, v2->value));
	
	while (v1->next!=NULL && v2->next!=NULL) {
		v1=v1->next; v2=v2->next;
		add_node(result, new_list(split_op(v1->value, v2->value)));
	}
	while (v1->next!=NULL) {v1=v1->next; add_node(result, new_list(v1->value));}
	while (v2->next!=NULL) {v2=v2->next; add_node(result, new_list(v2->value));}
	v1=temp1; v2=temp2;
	return result;
}
struct List* split_vars_s(char* var1, char* var2) {
	return split_vals(get_val(var1), get_val(var2));
}

struct List* div_vals(struct List* v1, struct List* v2) {
	struct List* temp1 = v1; struct List* temp2 = v2;
	if (v1==NULL) return v2;
	if (v2==NULL) return v1;
	struct List* result = new_list(div_op(v1->value, v2->value));
	
	while (v1->next!=NULL && v2->next!=NULL) {
		v1=v1->next; v2=v2->next;
		add_node(result, new_list(div_op(v1->value, v2->value)));
	}
	while (v1->next!=NULL) {v1=v1->next; add_node(result, new_list(v1->value));}
	while (v2->next!=NULL) {v2=v2->next; add_node(result, new_list(v2->value));}
	v1=temp1; v2=temp2;
	return result;
}
struct List* div_vars_s(char* var1, char* var2) {
	return div_vals(get_val(var1), get_val(var2));
}

struct List* mod_vals(struct List* v1, struct List* v2) {
	struct List* temp1 = v1; struct List* temp2 = v2;
	if (v1==NULL) return v2;
	if (v2==NULL) return v1;
	struct List* result = new_list(mod_op(v1->value, v2->value));
	
	while (v1->next!=NULL && v2->next!=NULL) {
		v1=v1->next; v2=v2->next;
		add_node(result, new_list(mod_op(v1->value, v2->value)));
	}
	while (v1->next!=NULL) {v1=v1->next; add_node(result, new_list(v1->value));}
	while (v2->next!=NULL) {v2=v2->next; add_node(result, new_list(v2->value));}
	v1=temp1; v2=temp2;
	return result;
}
struct List* mod_vars_s(char* var1, char* var2) {
	return mod_vals(get_val(var1), get_val(var2));
}

struct List* sublist_vals(struct List* v1, struct List* v2) {
	struct List* temp1 = v1; struct List* temp2 = v2;
	if (v1==NULL) return v2;
	if (v2==NULL) return v1;
	struct List* result = new_list(sublist_op(v1, v2->value));
	
	while (v2->next!=NULL) {
		v2=v2->next;
		add_node(result, new_list(sublist_op(v1, v2->value)));
	}
	v1=temp1; v2=temp2;
	
	return result;
}
struct List* sublist_vars_s(char* var1, char* var2) {
	return sublist_vals(get_val(var1), get_val(var2));
}

struct List* or_vals(struct List* v1, struct List* v2) {
	struct List* temp1 = v1; struct List* temp2 = v2;
	v1 = expand_pointers(v1);
	v2 = expand_pointers(v2);
	if (v1==NULL) return v2;
	if (v2==NULL) return v1;
	
	struct List* result = new_list(or_op(v1->value, v2->value));
	while (v1->next!=NULL && v2->next!=NULL) {
		v1=v1->next; v2=v2->next;
		add_node(result, new_list(or_op(v1->value, v2->value)));
	}
	while (v1->next!=NULL) {v1=v1->next; add_node(result, new_list(v1->value));}
	while (v2->next!=NULL) {v2=v2->next; add_node(result, new_list(v2->value));}
	v1=temp1; v2=temp2;
	return result;
}
struct List* or_vars_s(char* var1, char* var2) {
	return or_vals(get_val(var1), get_val(var2));
}

struct List* xor_vals(struct List* v1, struct List* v2) {
	struct List* temp1 = v1; struct List* temp2 = v2;
	v1 = expand_pointers(v1);
	v2 = expand_pointers(v2);
	if (v1==NULL) return v2;
	if (v2==NULL) return v1;
	
	struct List* result = new_list(xor_op(v1->value, v2->value));
	while (v1->next!=NULL && v2->next!=NULL) {
		v1=v1->next; v2=v2->next;
		add_node(result, new_list(xor_op(v1->value, v2->value)));
	}
	while (v1->next!=NULL) {v1=v1->next; add_node(result, new_list(v1->value));}
	while (v2->next!=NULL) {v2=v2->next; add_node(result, new_list(v2->value));}
	v1=temp1; v2=temp2;
	return result;
}
struct List* xor_vars_s(char* var1, char* var2) {
	return xor_vals(get_val(var1), get_val(var2));
}

struct List* eq_vals(struct List* v1, struct List* v2) {
	struct List* temp1 = v1; struct List* temp2 = v2;
	v1 = expand_pointers(v1);
	v2 = expand_pointers(v2);
	if (v1==NULL) return v2;
	if (v2==NULL) return v1;
	
	struct List* result = new_list(eq_op(v1->value, v2->value));
	while (v1->next!=NULL && v2->next!=NULL) {
		v1=v1->next; v2=v2->next;
		add_node(result, new_list(eq_op(v1->value, v2->value)));
	}
	while (v1->next!=NULL) {v1=v1->next; add_node(result, new_list(v1->value));}
	while (v2->next!=NULL) {v2=v2->next; add_node(result, new_list(v2->value));}
	v1=temp1; v2=temp2;
	return result;
}
struct List* eq_vars_s(char* var1, char* var2) {
	return eq_vals(get_val(var1), get_val(var2));
}

struct List* not_val(struct List* v) {
	struct List* temp = v;
	v = expand_pointers(v);
	if (v==NULL) return null_list();
	
	struct List* result = new_list(not_op(v->value));
	while (v->next!=NULL) {
		v=v->next;
		add_node(result, new_list(not_op(v->value)));
	}
	v=temp;
	return result;
}
struct List* not_var_s(char* var) {
	return not_val(get_val(var));
}

bool is_true(struct List* var) {
	struct List* temp = new_list(val_b(true));
	struct List* start = var;
	while (start != NULL) {
		start = start->next;
		add_node(temp, bool_list(true));
	}
	struct List* result = eq_vals(var, temp);
	bool r = result->value.val.b;
	while (result->next != NULL && !r) {
		result = result->next;
		r = result->value.val.b;
	}
	return r;
}

struct List* concat_vars(char* var1, char* var2) {
	struct List* v1 = get_val(var1);
	struct List* v2 = get_val(var2);
	struct List* temp1 = v1; struct List* temp2 = v2;
	if (v1==NULL) return v2;
	if (v2==NULL) return v1;
	struct List* result = new_list(v1->value);
	while (v1->next!=NULL) {v1=v1->next; add_node(result, new_list(v1->value));}
	while (v2!=NULL) {add_node(result, new_list(v2->value)); v2=v2->next;}
	v1=temp1; v2=temp2;
	return result;
}

struct List* list_get_from_list(struct List* list1, struct List* list2) {
	struct List* new = new_list(list_get(list1, to_int(list2)));
	while (list2->next!=NULL) {
		list2 = list2->next;
		add_node(new, new_list(list_get(list1, to_int(list2))));
	}
	return new;
}
struct List* noun_get_from_list(char* key, struct List* list) {
	return list_get_from_list(get_val(key), list);
}

int to_int(struct List* list) {
	switch (list->value.type) {
		case INT: return list->value.val.i;
		case FLOAT: return (int)(list->value.val.f);
		case STRING: int i=0; char* s = list->value.val.s; while (*s!='\0') {i+=*s-'a'; s++;} return i;
		case BOOL: return list->value.val.b?1:0;
		case CHAR: return list->value.val.c;
		//TODO: pointer
		default: return -1;
	}
}

struct Value list_get(struct List* list, int pos) {
	struct List* node = list;
	while (list!=NULL && pos>0) {
		list=list->next;
		pos--;
	}
	struct Value v;
	if (pos==0) v = list->value; else v = val_null();
	list = node;
	return v;
}
#endif
