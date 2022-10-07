#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdio.h>
#include <string.h>

struct Value add_op(struct Value v1, struct Value v2);
struct Value sub_op(struct Value v1, struct Value v2);
struct Value mult_op(struct Value v1, struct Value v2);
struct Value split_op(struct Value v1, struct Value v2);
struct Value div_op(struct Value v1, struct Value v2);
struct Value mod_op(struct Value v1, struct Value v2);
struct Value sublist_op(struct List* v1, struct Value v2);
struct Value or_op(struct Value v1, struct Value v2);
struct Value xor_op(struct Value v1, struct Value v2);
struct Value eq_op(struct Value v1, struct Value v2);
struct Value not_op(struct Value v);

struct Value add_op(struct Value v1, struct Value v2) {
	if (v1.type == BOOL || v2.type == BOOL) {
		if (v1.type == BOOL) {
			return add_op(val_i(v1.val.b?1:0), v2);
		} else {
			return add_op(v1, val_i(v2.val.b?1:0));
		}
	}
	
	if (v1.type == STRING || v2.type == STRING) {
		char* c;
		if (v1.type == STRING) {
			c = strdup(v1.val.s);
			switch (v2.type) {
				case INT: strcat(c, itoa(v2.val.i)); return val_s(c);
				case FLOAT: char* t = ftoa(v2.val.f); strcat(c, t); return val_s(c);
				case STRING: strcat(c, v2.val.s); return val_s(c);
				case CHAR: strcat(c, ctoa(v2.val.c)); return val_s(c);
				default: return val_s(c);
			}
		} else {
			switch (v1.type) {
				case INT: c = itoa(v1.val.i); strcat(c, v2.val.s); return val_s(c);
				case FLOAT: c = ftoa(v1.val.f); strcat(c, v2.val.s); return val_s(c);
				case CHAR: c = ctoa(v1.val.c); strcat(c, v2.val.s); return val_s(c);
				default: return val_s(v2.val.s);
			}
		}
	}
	
	if (v1.type == CHAR || v2.type == CHAR) {
		if (v1.type == CHAR) {
			switch (v2.type) {
				case INT: return val_c(v1.val.c+v2.val.i);
				case FLOAT: return val_c(v1.val.c+((int)v2.val.f));
				case CHAR: return val_c(v1.val.c+v2.val.c);
				default: return val_c(v1.val.c);
			}
		} else {
			switch (v1.type) {
				case INT: return val_c(v2.val.c+v1.val.i);
				case FLOAT: return val_c(v2.val.c+((int)v1.val.f));
				default: return val_c(v2.val.c);
			}
		}
	}
	
	if (v1.type == FLOAT || v2.type == FLOAT) {
		if (v1.type == FLOAT) {
			switch (v2.type) {
				case INT: return val_f(v1.val.f+((float)v2.val.i));
				case FLOAT: return val_f(v1.val.f+v2.val.f);
				default: return val_f(v1.val.f);
			}
		} else {
			switch (v1.type) {
				case INT: return val_f(((float)v1.val.i)+v2.val.f);
				default: return val_f(v2.val.f);
			}
		}
	}
	if (v1.type == INT || v2.type == INT) {
		if (v1.type == INT) {
			switch (v2.type) {
				case INT: return val_i(v1.val.i+v2.val.i);
				default: return val_i(v1.val.i);
			}
		} else {
			switch (v1.type) {
				default: return val_i(v2.val.i);
			}
		}
	}
	return val_null();
}

struct Value sub_op(struct Value v1, struct Value v2) {
	if (v1.type == BOOL || v2.type == BOOL) {
		if (v1.type == BOOL) {
			return sub_op(val_i(v1.val.b?1:0), v2);
		} else {
			return sub_op(v1, val_i(v2.val.b?1:0));
		}
	}
	
	if (v1.type == STRING || v2.type == STRING) {
		char* c;
		char* c2;
		if (v1.type == STRING) {
			c = strdup(v1.val.s);
			switch (v2.type) {
				case INT: c2 = strdup(v1.val.s); int i = MAX(MIN(strlen(v1.val.s)-v2.val.i, strlen(v1.val.s)),0); c2[i]=0; return val_s(c2);
				case FLOAT: return sub_op(v1, val_i((int)v2.val.f));
				case STRING: c2 = str_replace(v1.val.s, v2.val.s, ""); return val_s(c2);
				case CHAR: c2 = remove_char(v1.val.s, v2.val.c); return val_s(c2);
				default: return val_s(c);
			}
		} else {
			c = strdup(v2.val.s);
			switch (v1.type) {
				case INT: c2 = strdup(v2.val.s); int i = MAX(MIN(strlen(v2.val.s)-v1.val.i, strlen(v2.val.s)),0); c2[i]=0; return val_s(c2);
				case FLOAT: return sub_op(v2, val_i((int)v1.val.f));
				case CHAR: c2 = remove_char(v2.val.s, v1.val.c); return val_s(c2);
				default: return val_s(v2.val.s);
			}
		}
	}
	
	if (v1.type == CHAR || v2.type == CHAR) {
		if (v1.type == CHAR) {
			switch (v2.type) {
				case INT: return val_c(v1.val.c-v2.val.i);
				case FLOAT: return val_c(v1.val.c-((int)v2.val.f));
				case CHAR: return val_c(v1.val.c-v2.val.c);
				default: return val_c(v1.val.c);
			}
		} else {
			switch (v1.type) {
				case INT: return val_c(v2.val.c-v1.val.i);
				case FLOAT: return val_c(v2.val.c-((int)v1.val.f));
				default: return val_c(v2.val.c);
			}
		}
	}
	
	if (v1.type == FLOAT || v2.type == FLOAT) {
		if (v1.type == FLOAT) {
			switch (v2.type) {
				case INT: return val_f(v1.val.f-((float)v2.val.i));
				case FLOAT: return val_f(v1.val.f-v2.val.f);
				default: return val_f(v1.val.f);
			}
		} else {
			switch (v1.type) {
				case INT: return val_f(((float)v1.val.i)-v2.val.f);
				default: return val_f(v2.val.f);
			}
		}
	}
	if (v1.type == INT || v2.type == INT) {
		if (v1.type == INT) {
			switch (v2.type) {
				case INT: return val_i(v1.val.i-v2.val.i);
				default: return val_i(v1.val.i);
			}
		} else {
			switch (v1.type) {
				default: return val_i(v2.val.i);
			}
		}
	}
	return val_null();
}

struct Value mult_op(struct Value v1, struct Value v2) {
	if (v1.type == BOOL || v2.type == BOOL) {
		if (v1.type == BOOL) {
			return v1.val.b?v2:val_0(v2.type);
		} else {
			return v2.val.b?v1:val_0(v1.type);
		}
	}
	
	if (v1.type == STRING || v2.type == STRING) {
		char* c;
		char* c2;
		if (v1.type == STRING) {
			c = strdup(v1.val.s);
			c2 = "";
			switch (v2.type) {
				case INT:
					if (v2.val.i>0) {
						c2 = (char *)malloc(sizeof(char)*v2.val.i*strlen(c));
						c2 = c2+strlen(c2);
						for (int i = v2.val.i; i>0; i--) strcat(c2, c);
					} else {
						strrev(c);
						c2 = (char *)malloc(sizeof(char)*-v2.val.i*strlen(c));
						c2 = c2+strlen(c2);
						for (int i = v2.val.i; i<0; i++) strcat(c2, c);
					}
					return val_s(c2);
				case FLOAT:
					int extra;
					if (v2.val.f>0) {
						extra = (int)((v2.val.f - (int)v2.val.f)*strlen(c));
						c2 = (char *)malloc(sizeof(char)*(((int)v2.val.f)*strlen(c)+extra));
						c2 = c2+strlen(c2);
						for (int i = (int)v2.val.f; i>0; i--) strcat(c2, c);
						strncat(c2, c, extra);
					} else {
						extra = (int)((-v2.val.f - (int)(-v2.val.f))*strlen(c));
						c2 = (char *)malloc(sizeof(char)*(-((int)v2.val.f)*strlen(c)+extra));
						c2 = c2+strlen(c2);
						for (int i = (int)v2.val.f; i<0; i++) strcat(c2, c);
						strncat(c2, c, extra);
						strrev(c2);
					}
					return val_s(c2);
				case STRING: return val_s(strdup(strcat(c, v2.val.s)));
				case CHAR: return mult_op(v1, val_i((int)(v2.val.c-'0')));
				default: return val_s(c);
			}
		} else {
			c = strdup(v2.val.s);
			c2 = "";
			switch (v1.type) {
				case INT: 
					if (v1.val.i>0) {
						c2 = (char *)malloc(sizeof(char)*(v1.val.i)*strlen(v2.val.s));
						c2 = c2+strlen(c2);
						for (int i=0; i<v1.val.i; i++) strcat(c2, c);
					} else {
						strrev(c);
						c2 = (char *)malloc(sizeof(char)*-v1.val.i*strlen(c));
						c2 = c2+strlen(c2);
						for (int i = v1.val.i; i<0; i++) strcat(c2, c);
					}
					return val_s(c2);
				case FLOAT:
					int extra;
					if (v1.val.f>0) {
						extra = (int)((v1.val.f - (int)v1.val.f)*strlen(c));
						c2 = (char *)malloc(sizeof(char)*(((int)v1.val.f)*strlen(c)+extra));
						c2 = c2+strlen(c2);
						for (int i = (int)v1.val.f; i>0; i--) strcat(c2, c);
						strncat(c2, c, extra);
					} else {
						extra = (int)((-v1.val.f - (int)(-v1.val.f))*strlen(c));
						c2 = (char *)malloc(sizeof(char)*(-((int)v1.val.f)*strlen(c)+extra));
						c2 = c2+strlen(c2);
						for (int i = (int)v1.val.f; i<0; i++) strcat(c2, c);
						strncat(c2, c, extra);
						strrev(c2);
					}
					return val_s(c2);
				case STRING: return val_s(strdup(strcat(c, v1.val.s)));
				case CHAR: return mult_op(v2, val_i((int)(v1.val.c-'0')));
				default: return val_s(c);
			}
		}
	}
	
	if (v1.type == CHAR || v2.type == CHAR) {
		if (v1.type == CHAR) {
			switch (v2.type) {
				case INT: return val_c((((int)(v1.val.c-'0'))*v2.val.i+'0')%128);
				case FLOAT: return val_c(((int)(((int)(v1.val.c-'0'))*v2.val.f)+'0')%128);
				case CHAR: return mult_op(v1, val_i((int)(v2.val.c-'0')));
				default: return val_c(v1.val.c);
			}
		} else {
			switch (v1.type) {
				case INT: return val_c((((int)(v2.val.c-'0'))*v1.val.i+'0')%128);
				case FLOAT: return val_c(((int)(((int)(v2.val.c-'0'))*v1.val.f)+'0')%128);
				default: return val_c(v2.val.c);
			}
		}
	}
	
	if (v1.type == FLOAT || v2.type == FLOAT) {
		if (v1.type == FLOAT) {
			switch (v2.type) {
				case INT: return val_f(v1.val.f*((float)v2.val.i));
				case FLOAT: return val_f(v1.val.f*v2.val.f);
				default: return val_f(v1.val.f);
			}
		} else {
			switch (v1.type) {
				case INT: return val_f(((float)v1.val.i)*v2.val.f);
				default: return val_f(v2.val.f);
			}
		}
	}
	if (v1.type == INT || v2.type == INT) {
		if (v1.type == INT) {
			switch (v2.type) {
				case INT: return val_i(v1.val.i*v2.val.i);
				default: return val_i(v1.val.i);
			}
		} else {
			switch (v1.type) {
				default: return val_i(v2.val.i);
			}
		}
	}
	return val_null();
}

struct Value split_op(struct Value v1, struct Value v2) {
	if (v1.type == BOOL || v2.type == BOOL) {
		if (v1.type == BOOL) {
			return split_op(val_i(v1.val.b?1:0), v2);
		} else {
			return split_op(v1, val_i(v2.val.b?1:0));
		}
	}
	
	if (v1.type == STRING || v2.type == STRING) {//TODO: "STRING" split 3 = ["ST", "RI", "NG"]
		char* c;
		char* c2;
		if (v1.type == STRING) {
			c = strdup(v1.val.s);
			c2 = "";
			switch (v2.type) {
				case INT: return mult_op(val_s(v1.val.s), val_f(1.0/v2.val.i));
				case FLOAT: return mult_op(val_s(v1.val.s), val_f(1.0/v2.val.f));
				case STRING: return sub_op(val_s(v2.val.s), val_s(v1.val.s));
				case CHAR: return sub_op(val_s(v1.val.s), val_c(v2.val.c));
				default: return val_null();
			}
		} else {
			c = strdup(v2.val.s);
			c2 = "";
			switch (v1.type) {
				case INT: return mult_op(val_s(v2.val.s), val_f(1.0/v1.val.i));
				case FLOAT: return mult_op(val_s(v2.val.s), val_f(1.0/v1.val.f));
				case STRING: return sub_op(val_s(v2.val.s), val_s(v1.val.s));
				case CHAR: return sub_op(val_s(v2.val.s), val_c(v1.val.c));
				default: return val_null();
			}
		}
	}
	
	if (v1.type == CHAR || v2.type == CHAR) {
		int val1, val2;
		if (v1.type == CHAR) {
			val1 = (int)(v1.val.c-'0');
			switch (v2.type) {
				case INT: if (v2.val.i == 0) return val_null(); return val_c((val1)/v2.val.i+'0');
				case FLOAT: if (v2.val.f == 0) return val_null(); return val_c( ((int)(val1/v2.val.f))+'0' );
				case CHAR: val2 = (int)(v2.val.c-'0'); if (val2 == 0) return val_null(); return val_c((val1/val2)+'0');
				default: return val_null();
			}
		} else {
			val2 = (int)(v2.val.c-'0');
			if (val2 == 0) return val_null();
			switch (v1.type) {
				case INT: return val_c(((int)(v1.val.i/val2))+'0');
				case FLOAT: return val_c(((int)(v1.val.f/val2))+'0');
				default: return val_null();
			}
		}
	}
	
	if (v1.type == FLOAT || v2.type == FLOAT) {
		if (v1.type == FLOAT) {
			switch (v2.type) {
				case INT: if (v2.val.i == 0) return val_null(); return val_f(v1.val.f/((float)v2.val.i));
				case FLOAT: if (v2.val.f == 0) return val_null(); return val_f(v1.val.f/v2.val.f);
				default: return val_null();	
			}
		} else {
			switch (v1.type) {
				case INT: if (v2.val.f == 0) return val_null(); return val_f(((float)v1.val.i)/v2.val.f);
				default: return val_null();
			}
		}
	}
	if (v1.type == INT || v2.type == INT) {
		if (v1.type == INT) {
			switch (v2.type) {
				case INT: if (v2.val.i == 0) return val_null(); return val_i(v1.val.i/v2.val.i);
				default: return val_null();
			}
		} else {
			switch (v1.type) {
				default: return val_null();
			}
		}
	}
	return val_null();
}

struct Value div_op(struct Value v1, struct Value v2) {
	if (v1.type == BOOL || v2.type == BOOL) {
		if (v1.type == BOOL) {
			return div_op(val_i(v1.val.b?1:0), v2);
		} else {
			return div_op(v1, val_i(v2.val.b?1:0));
		}
	}
	
	if (v1.type == STRING || v2.type == STRING) {
		char* c;
		char* c2;
		if (v1.type == STRING) {
			c = strdup(v1.val.s);
			c2 = "";
			switch (v2.type) {
				case INT: return mult_op(val_s(v1.val.s), val_f(1.0/v2.val.i));
				case FLOAT: return mult_op(val_s(v1.val.s), val_f(1.0/v2.val.f));
				case STRING: return sub_op(val_s(v2.val.s), val_s(v1.val.s));
				case CHAR: return sub_op(val_s(v1.val.s), val_c(v2.val.c));
				default: return val_s(c);
			}
		} else {
			c = strdup(v2.val.s);
			c2 = "";
			switch (v1.type) {
				case INT: return mult_op(val_s(v2.val.s), val_f(1.0/v1.val.i));
				case FLOAT: return mult_op(val_s(v2.val.s), val_f(1.0/v1.val.f));
				case STRING: return sub_op(val_s(v2.val.s), val_s(v1.val.s));
				case CHAR: return sub_op(val_s(v2.val.s), val_c(v1.val.c));
				default: return val_s(c);
			}
		}
	}
	
	if (v1.type == CHAR || v2.type == CHAR) {
		return split_op(v1, v2);
	}
	
	if (v1.type == FLOAT || v2.type == FLOAT) {
		if (v1.type == FLOAT) {
			switch (v2.type) {
				case INT: if (v2.val.i == 0) return val_null(); return val_i(v1.val.f/v2.val.i);
				case FLOAT: if (v2.val.f == 0) return val_null(); return val_i((int)v1.val.f/v2.val.f);
				default: return val_i((int)v1.val.f);
			}
		} else {
			switch (v1.type) {
				case INT: if (v2.val.i == 0) return val_null(); return val_i(v1.val.i/v2.val.f);
				default: return val_i((int)v2.val.f);
			}
		}
	}
	if (v1.type == INT || v2.type == INT) {
		return split_op(v1, v2);
	}
	return val_null();
}

struct Value mod_op(struct Value v1, struct Value v2) {
	if (v1.type == BOOL || v2.type == BOOL) {
		if (v1.type == BOOL) {
			return mod_op(val_i(v1.val.b?1:0), v2);
		} else {
			return mod_op(v1, val_i(v2.val.b?1:0));
		}
	}
	
	if (v1.type == STRING || v2.type == STRING) {//TODO: "Hello" mod "World" = "Hello" split "World" sub "Hello" div "World"
		char* c;
		char* c2;
		if (v1.type == STRING) {
			c = strdup(v1.val.s);
			c2 = "";
			switch (v2.type) {
				case INT: return mult_op(val_s(v1.val.s), val_f(1.0/v2.val.i));
				case FLOAT: return mult_op(val_s(v1.val.s), val_f(1.0/v2.val.f));
				case STRING: return sub_op(val_s(v2.val.s), val_s(v1.val.s));
				case CHAR: return sub_op(val_s(v1.val.s), val_c(v2.val.c));
				default: return val_null();
			}
		} else {
			c = strdup(v2.val.s);
			c2 = "";
			switch (v1.type) {
				case INT: return mult_op(val_s(v2.val.s), val_f(1.0/v1.val.i));
				case FLOAT: return mult_op(val_s(v2.val.s), val_f(1.0/v1.val.f));
				case STRING: return sub_op(val_s(v2.val.s), val_s(v1.val.s));
				case CHAR: return sub_op(val_s(v2.val.s), val_c(v1.val.c));
				default: return val_null();
			}
		}
	}
	
	if (v1.type == CHAR || v2.type == CHAR) {
		int val1, val2;
		if (v1.type == CHAR) {
			val1 = (int)(v1.val.c-'0');
			switch (v2.type) {
				case INT: if (v2.val.i == 0) return val_null(); return val_c(val1%v2.val.i+'0');
				case FLOAT: if (v2.val.f == 0) return val_null(); return val_c(val1%(int)v2.val.f+'0');
				case CHAR: val2 = (int)(v2.val.c-'0'); if (val2 == 0) return val_null(); return val_c(val1%val2+'0');
				default: return val_null();
			}
		} else {
			val2 = (int)(v2.val.c-'0');
			if (val2 == 0) return val_null();
			switch (v1.type) {
				case INT: return val_c(v1.val.i%val2+'0');
				case FLOAT: return val_c(((int)v1.val.f)%val2+'0');
				default: return val_null();
			}
		}
	}
	
	if (v1.type == FLOAT || v2.type == FLOAT) { //TODO: check the /0 exceptions
		int v;
		if (v1.type == FLOAT) {
			switch (v2.type) {
				case INT: if (v2.val.i == 0) return val_null(); v = div_op(v1, v2).val.i; return val_f(v1.val.f-v*v2.val.i);
				case FLOAT: if (v2.val.f == 0) return val_null(); v = div_op(v1, v2).val.i; return val_f(v1.val.f-v*v2.val.f);
				default: return val_null();
			}
		} else {
			switch (v1.type) {
				case INT: if (v2.val.i == 0) return val_null(); v = div_op(v1, v2).val.i; return val_f(v1.val.i-v*v2.val.f);
				default: return val_null();
			}
		}
	}
	if (v1.type == INT || v2.type == INT) { //TODO: check the /0 exceptions
		if (v1.type == INT) {
			switch (v2.type) {
				case INT: if (v2.val.i == 0) return val_null(); return val_i(v1.val.i%v2.val.i);
				default: return val_null();
			}
		} else {
			switch (v1.type) {
				default: return val_null();
			}
		}
	}
	return val_null();
}

struct Value sublist_op(struct List* v1, struct Value v2) {
	switch (v2.type) {
		case INT: return get_val_index(v1, v2.val.i);
		case FLOAT: return get_val_index(v1, (int)v2.val.f);
		case STRING: return get_val_pointer(v1, v2.val.s);
		case CHAR: return get_val_index(v1, (int)(v2.val.c-'0'));
		default: return val_null();
	}
}

struct Value or_op(struct Value v1, struct Value v2) {
	return val_b(value_to_bool(v1).val.b | value_to_bool(v2).val.b);
}

struct Value xor_op(struct Value v1, struct Value v2) {
	return val_b(value_to_bool(v1).val.b ^ value_to_bool(v2).val.b);
}

struct Value eq_op(struct Value v1, struct Value v2) {
	if (v1.type != v2.type) return val_b(false);
	switch (v1.type) {
		case INT: return val_b(v1.val.i == v2.val.i);
		case FLOAT: return val_b(v1.val.f == v2.val.f);
		case STRING: return val_b(v1.val.s == v2.val.s);
		case BOOL: return val_b(v1.val.b == v2.val.b);
		case CHAR: return val_b(v1.val.c == v2.val.c);
		case POINTER: return val_b(v1.val.s == v2.val.s);
		case IS_NULL: return val_b(true); break;
		default: return val_b(false);
	}
}

struct Value not_op(struct Value v) {
	return val_b(value_to_bool(v).val.b?false:true);
}

#endif
