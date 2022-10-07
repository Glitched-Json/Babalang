#ifndef INSTRUCTIONS_C
#define INSTRUCTIONS_C

#include "instructions.h"
#include "operations.c"

void instruction_is(struct Line* line, int andDepth) {
	line->tokens = line->tokens->next;
	struct List* list = NULL;
	struct FunctionList* fList = NULL;
	struct Token* lastToken, *temp;
	
	emptyDictionary();
	struct Token* s = line->tokens->prev->val;
	while (line->tokens->prev->val != NULL) {
		lastToken = get_reduced(line->tokens->prev->val);
		switch (lastToken->type) {
			case FUNC: fList = addFunc(fList, lastToken->val.func); break;
			case LIST: if (list == NULL) list = listDup(lastToken->val.list); 
				   else add_node(list, listDup(lastToken->val.list)); break;
			case NOUN: install(lastToken->val.noun, "");
				   if (list == NULL) list = listDup(get_val(lastToken->val.noun)); 
				   else add_node(list, listDup(get_val(lastToken->val.noun))); break;
			case BLOCK: if (list == NULL) list = listDup(str_list(strdup(lastToken->val.BlockVal.b)));
				    else add_node(list, listDup(str_list(strdup(lastToken->val.BlockVal.b)))); break;
			default: if (list == NULL) list = new_list(to_value(lastToken));
				 else add_node(list, new_list(to_value(lastToken)));
		}
		line->tokens->prev->val = line->tokens->prev->val->next;
	}
	line->tokens->prev->val = s;
	
	if (list != NULL) {
		s = line->tokens->val;
		while (line->tokens->val != NULL) {
			switch (line->tokens->val->type) {
				case NOUN: save_val(line->tokens->val->val.noun, list);
					   if (lookup(line->tokens->val->val.noun)) make_constant(line->tokens->val->val.noun);
					   break;
				case LINE: struct Token* r = line->tokens->val->val.line->reduced, *temp = r;
					   while (r != NULL) {
					   	switch (r->type) {
					   		case NOUN: save_val(r->val.noun, list);
					   			   if (lookup(r->val.noun)) make_constant(r->val.noun);
					   			   break;
					   	}
					   	r = r->next;
					   }
					   r = temp;
					   break;
			}
			line->tokens->val = line->tokens->val->next;
		}
		line->tokens->val = s;
	}
	
	while (fList != NULL) {
		func(get_reduced(line->tokens->val), fList->f);
		fList = fList->next;
	}
	free_funciton_list(fList);
	emptyDictionary();
}

void instruction_to(struct Line* line) {
	struct Token* v1 = get_reduced(line->tokens->val), *v2 = get_reduced(line->tokens->prev->val);
	struct List* l1 = v1->type==LIST?v1->val.list:get_val(v1->val.noun),
		    *l2 = v2->type==LIST?v2->val.list:get_val(v2->val.noun),
		    *result = listDup(l1);
	
	while (l1->next != NULL) l1 = l1->next;
	while (l1->value.type == POINTER) {
		l1 = l1 = get_val(l1->value.val.s);
		struct List* temp = result;
		while (result->next != NULL) result = result->next;
					
		if (result->prev == NULL) {
			//TODO: free result node with a free_node function (for list values)
			result = listDup(l1);
		} else {
			result = result->prev;
			//TODO: replace the next line with a free_node function (for list values)
			result->next = NULL;
			
			add_node(result, listDup(l1));
		}
		
		result = temp;
		while (l1->next != NULL) l1 = l1->next;
	}
	while (l2->value.type == POINTER) {l2 = get_val(l2->value.val.s);}
	
	if (l1->value.type != l2->value.type) {line->tokens = line->tokens->prev; return;}
	
	struct List* spectrum; int i=0;
	switch (l1->value.type) {
		case INT: spectrum = generate_spectrum(l1->value.val.i, l2->value.val.i); break;
		case CHAR: spectrum = generate_spectrum_char(l1->value.val.c, l2->value.val.c); break;
		case FLOAT: spectrum = generate_spectrum_float(l1->value.val.f, l2->value.val.f); break;
		case STRING: spectrum = generate_spectrum_char(l1->value.val.s[strlen(l1->value.val.s)-1], l2->value.val.s[0]); break;
		default: line->tokens = line->tokens->prev; return;
	}
	struct List* s = spectrum->next;
	while (spectrum->next != NULL) {spectrum = spectrum->next; i++;}
	
	if (i>=2) {
		spectrum->prev->next = NULL;
		add_node(result, s);
	}
	add_node(result, listDup(l2));
	
	line->tokens->val = token_e(result);
	line->tokens = line->tokens->prev;
}

void instruction_for(struct Line* line) {
	if (line->tokens->val->type != BLOCK) return;
	struct Token* blk = line->tokens->val;
	char* block = blk->val.BlockVal.b;
	line->tokens = line->tokens->next;
	struct Token* tkn = get_reduced(line->tokens->val);
	struct List* i = NULL, *s, *dup;
	switch (tkn->type) {
		case NOUN: char* noun = tkn->val.noun;
			   i = get_val(noun); s=i;
			   dup = listDup(i);
			   while (i != NULL) {
				   char* instr = format_instruction(noun, i->value);
				   struct Line* line = load_line(instr);
				   executeInstructions(line);
				   free_line(line);
				   free(instr);
				   reduceBlock(blk);	//TODO: replace reduceBlock with executeBlock
				   i = i->next;
			   } i=s;
			   save_val(noun, dup);
			   //TODO: free list dup
			break;
		case LIST:
			i = tkn->val.list, s = i;
			while (i != NULL) {
				reduceBlock(blk);
				i = i->next;
			} i = s;
			break;
	}
}

void instruction_if(struct Line* line) {
	struct Token* IFStatement = line->tokens->val;
	line->tokens = line->tokens->next;
	
	reduce_if(IFStatement);
}

struct Token* reduce_if(struct Token* IFStatement) {
	struct Token* reduced = NULL;
	bool found = false;
	while (IFStatement != NULL && !found) {
		if (IFStatement->val.if_statement->statement->type == LINE) {
			reduce(IFStatement->val.if_statement->statement->val.line);
			IFStatement->val.if_statement->statement = get_reduced(IFStatement->val.if_statement->statement);
		}
		struct List* list = NULL;
		switch (IFStatement->val.if_statement->statement->type) {
			case NOUN: list = get_val(IFStatement->val.if_statement->statement->val.noun); break;
			case LIST: list = IFStatement->val.if_statement->statement->val.list; break;
			case IF: struct Token* r = reduce_if(IFStatement->val.if_statement->statement); 
				 while (r != NULL) {
				 	switch (r->type) {
				 	case NOUN: if (list == NULL) list = get_val(r->val.noun);
				 		   else add_node(list, get_val(r->val.noun));
				 		   break;
				 	case LIST: if (list == NULL) list = new_list(r->val.list->value);
				 		   else add_node(list, new_list(r->val.list->value));
				 		   break;
				 	}
				 	r = r->next;
				 }
				 if (list == NULL) return reduced;
				 break;
			default: debug_("default") return reduced;
		}
		
		bool istrue = true;
		while (list != NULL && istrue) {
			struct Value v = or_op(list->value, val_b(false));
			istrue = v.val.b;
			list = list->next;
		}
		
		if (istrue) {
			reduced = reduceBlock(IFStatement->val.if_statement->block);
			found = true;
		} else IFStatement = IFStatement->val.if_statement->next;
	}
	return reduced;
}

void instruction_and(struct Line* line) {
	struct Token* t1 = line->tokens->val;
	line->tokens = line->tokens->next;
	struct TokensList* prev = line->instr;
	line->instr = line->instr->next;
	bool done = false;
	while (!done) {
		if (line->instr == NULL) {done = true; break;}
		if (line->instr->val->val.func != i_add) {done = true; break;}
		prev = line->instr;
		line->tokens = line->tokens->next;
		line->instr = line->instr->next;
	}
	line->instr = prev;
	add_token_to_list(get_reduced(line->tokens->val), get_reduced(t1));
}
void instruction_and_priority_mode(struct Line* line) {
	line->tokens = line->tokens->prev;
	add_token_to_list(get_reduced(line->tokens->val), get_reduced(line->tokens->next->val));
}

void instruction_mimic(struct Line* line, int andDepth) {
	struct Token* t = line->tokens->val, *s, *converted = NULL; char* str;
	while (t != NULL && andDepth--!=0) {
		s = get_reduced(t);
		switch (s->type) {
			case NOUN: if (converted == NULL) converted = token_e(pointer_list(strdup(s->val.noun)));
				   else add_token_to_list(converted, token_e(pointer_list(strdup(s->val.noun))));
				   break;
			case LIST: break;
		}
		t = t->next;
	}
	while (t != NULL) {
		if (converted == NULL) converted = tokenDup(t); else
		add_token_to_list(converted, tokenDup(t));
		t = t->next;
	}
	line->tokens->val = converted;
}

void instruction_get(struct Line* line) {
	struct Token* t1, *t2;
	t2 = get_reduced(line->tokens->prev->val);
	struct Token* t = line->tokens->val;
	line->tokens = line->tokens->prev;
	struct TokensList* prevI = line->instr, *prevT = line->tokens;
	line->instr = line->instr->next;
	bool done = false;
	while (!done) {
		if (line->instr == NULL) {done = true; break;}
		if (line->instr->val->val.func != i_get) {done = true; break;}
		prevI = line->instr;
		line->tokens = line->tokens->prev;
		line->instr = line->instr->prev;
	}
	if (done) t1 = get_reduced(line->tokens->next->val);
	line->instr = prevI;
	line->tokens = prevT;
	//struct Token* t2 = get_reduced(line->tokens->val);
	
	struct List* templist;
	switch (t1->type) {
		case LIST: templist = t1->val.list; break;
		case NOUN: templist = get_val(t1->val.noun); break;
		default: return;
	}
	
	switch (t2->type) {
		case NOUN: line->tokens->next->val = token_e(sublist_vals(templist, get_val(t2->val.noun))); break;
		case LIST: line->tokens->next->val = token_e(sublist_vals(templist, t2->val.list)); break;
	}
}

void instruction_call(struct Line* line) {
	if (line->tokens->val->type != NOUN) return;
	struct List* val = get_val(line->tokens->val->val.noun);
	while (val != NULL) {
		if (val->value.type == STRING) if (val->value.val.s[0]+256 == LST_DIV) {
			struct Line* line = new_line();
			addNewToken(line, token_b(val->value.val.s));
			executeInstructions(line);
			free_line(line);
		}
		val = val->next;
	}
}

void instruction_add(struct Line* line) {
	line->tokens = line->tokens->prev;
	struct List *v1, *v2;
	
	v1 = token_to_list(line->tokens->val);
	if (v1 == NULL) return;
	
	int i = 0; struct TokensList* l = line->tokens->next;
	while (line->instr->next != NULL) {
		line->instr = line->instr->next; i++;
		if (line->instr->val->val.func != i_add) break;
		l = l->next;
	}
	for (int j=0; j<i; j++) line->instr = line->instr->prev;
	
	v2 = token_to_list(l->val);
	if (v2 == NULL) return;
	
	l->val->val.list = add_vals(v2, v1);
	l->val->type = (enum T)LIST;
}

void instruction_sub(struct Line* line) {
	line->tokens = line->tokens->prev;
	struct List *v1, *v2;
	
	v1 = token_to_list(line->tokens->val);
	if (v1 == NULL) return;
	
	int i = 0; struct TokensList* l = line->tokens->next;
	while (line->instr->next != NULL) {
		line->instr = line->instr->next; i++;
		if (line->instr->val->val.func != i_sub) break;
		l = l->next;
	}
	for (int j=0; j<i; j++) line->instr = line->instr->prev;
	
	v2 = token_to_list(l->val);
	if (v2 == NULL) return;
	
	l->val->val.list = sub_vals(v2, v1);
	l->val->type = (enum T)LIST;
}

void instruction_mult(struct Line* line) {
	line->tokens = line->tokens->prev;
	struct List *v1, *v2;
	
	v1 = token_to_list(line->tokens->val);
	if (v1 == NULL) return;
	
	int i = 0; struct TokensList* l = line->tokens->next;
	while (line->instr->next != NULL) {
		line->instr = line->instr->next; i++;
		if (line->instr->val->val.func != i_mult) break;
		l = l->next;
	}
	for (int j=0; j<i; j++) line->instr = line->instr->prev;
	
	v2 = token_to_list(l->val);
	if (v2 == NULL) return;
	
	l->val->val.list = mult_vals(v2, v1);
	l->val->type = (enum T)LIST;
}

void instruction_split(struct Line* line) {
	line->tokens = line->tokens->prev;
	struct List *v1, *v2;
	
	v1 = token_to_list(line->tokens->val);
	if (v1 == NULL) return;
	
	int i = 0; struct TokensList* l = line->tokens->next;
	while (line->instr->next != NULL) {
		line->instr = line->instr->next; i++;
		if (line->instr->val->val.func != i_split) break;
		l = l->next;
	}
	for (int j=0; j<i; j++) line->instr = line->instr->prev;
	
	v2 = token_to_list(l->val);
	if (v2 == NULL) return;
	
	l->val->val.list = split_vals(v2, v1);
	l->val->type = (enum T)LIST;
}

void instruction_div(struct Line* line) {
	line->tokens = line->tokens->prev;
	struct List *v1, *v2;
	
	v1 = token_to_list(line->tokens->val);
	if (v1 == NULL) return;
	
	int i = 0; struct TokensList* l = line->tokens->next;
	while (line->instr->next != NULL) {
		line->instr = line->instr->next; i++;
		if (line->instr->val->val.func != i_div) break;
		l = l->next;
	}
	for (int j=0; j<i; j++) line->instr = line->instr->prev;
	
	v2 = token_to_list(l->val);
	if (v2 == NULL) return;
	
	l->val->val.list = div_vals(v2, v1);
	l->val->type = (enum T)LIST;
}

void instruction_mod(struct Line* line) {
	line->tokens = line->tokens->prev;
	struct List *v1, *v2;
	
	v1 = token_to_list(line->tokens->val);
	if (v1 == NULL) return;
	
	int i = 0; struct TokensList* l = line->tokens->next;
	while (line->instr->next != NULL) {
		line->instr = line->instr->next; i++;
		if (line->instr->val->val.func != i_mod) break;
		l = l->next;
	}
	for (int j=0; j<i; j++) line->instr = line->instr->prev;
	
	v2 = token_to_list(l->val);
	if (v2 == NULL) return;
	
	l->val->val.list = mod_vals(v2, v1);
	l->val->type = (enum T)LIST;
}

void instruction_or(struct Line* line) {
	line->tokens = line->tokens->prev;
	struct List *v1, *v2;
	
	v1 = token_to_list(line->tokens->val);
	if (v1 == NULL) return;
	
	int i = 0; struct TokensList* l = line->tokens->next;
	while (line->instr->next != NULL) {
		line->instr = line->instr->next; i++;
		if (line->instr->val->val.func != i_or) break;
		l = l->next;
	}
	for (int j=0; j<i; j++) line->instr = line->instr->prev;
	
	v2 = token_to_list(l->val);
	if (v2 == NULL) return;
	
	l->val->val.list = or_vals(v2, v1);
	l->val->type = (enum T)LIST;
}

void instruction_xor(struct Line* line) {
	line->tokens = line->tokens->prev;
	struct List *v1, *v2;
	
	v1 = token_to_list(line->tokens->val);
	if (v1 == NULL) return;
	
	int i = 0; struct TokensList* l = line->tokens->next;
	while (line->instr->next != NULL) {
		line->instr = line->instr->next; i++;
		if (line->instr->val->val.func != i_xor) break;
		l = l->next;
	}
	for (int j=0; j<i; j++) line->instr = line->instr->prev;
	
	v2 = token_to_list(l->val);
	if (v2 == NULL) return;
	
	l->val->val.list = xor_vals(v2, v1);
	l->val->type = (enum T)LIST;
}

void instruction_eq(struct Line* line) {
	line->tokens = line->tokens->prev;
	struct List *v1, *v2;
	
	v1 = token_to_list(line->tokens->val);
	if (v1 == NULL) return;
	
	int i = 0; struct TokensList* l = line->tokens->next;
	while (line->instr->next != NULL) {
		line->instr = line->instr->next; i++;
		if (line->instr->val->val.func != i_eq) break;
		l = l->next;
	}
	for (int j=0; j<i; j++) line->instr = line->instr->prev;
	
	v2 = token_to_list(l->val);
	if (v2 == NULL) return;
	
	l->val->val.list = eq_vals(v2, v1);
	l->val->type = (enum T)LIST;
}

struct Token* instruction_not(struct Token* t) {
	switch (t->type) {
		case NOUN: save_val(concat(t->val.noun, "'"), not_val(get_val(t->val.noun))); return token_v(concat(t->val.noun, "'"));
		case LIST: return token_e(not_val(t->val.list));
		default: return t;
	}
}

char* format_instruction(char* noun, struct Value v) {
	char* val = val_to_string(v);
	char* s = (char*)malloc(sizeof(char)*(sizeof(noun)+sizeof(val)+6)), *t=noun; int i=0;
	while (*noun!=0) s[i++]=*noun++; noun=t;
	s[i++] = TKN_DIV; s[i++] = LST_DIV; t=val;
	while (*val!=0) s[i++]=*val++; val=t;
	s[i++] = TKN_DIV; s[i++]=48; s[i++]=TKN_INSTR; s[i]='\0';
	return s;
}

struct Token* getLastToken(struct Line* line) {
	struct TokensList* start = line->tokens;
	while (line->tokens->next != NULL) line->tokens = line->tokens->next;
	struct Token* t = line->tokens->val;
	line->tokens = start;
	if (t->type == LINE) return getLastToken(t->val.line);
	return t;
}

void func(struct Token* t, int f) {
	struct Token* s = t;
	int i = 0;
	while (t->next != NULL) {t = t->next; i++;}
	
	while (t != NULL && i >= 0) {
		switch (f) {
			case f_done: break;
			case f_print: func_print(t); break;
			case f_print_str: func_print_structured(t); break;
		}
		t = t->prev;
		i--;
	}
	t = s;
}

void func_print(struct Token* t) {
	switch (t->type) {
		case NOUN: print_list(get_val(t->val.noun), false); break;
		case LIST: print_list(t->val.list, false); break;
		case LINE: func_print(t->val.line->reduced); break;
		case BLOCK: 
			struct Token* s = t->val.BlockVal.reduced;
			while (s != NULL) {
				func_print(s);
				s = s->next;
			}
		break;
	}
}

void func_print_structured(struct Token* t) {
	switch (t->type) {
		case NOUN: print_var(t->val.noun, true); printf("\n"); break;
		case LIST: print_list(t->val.list, true); printf("\n"); break;
		case LINE: func_print_structured(t->val.line->reduced); break;
		case BLOCK: 
			struct Token* s = t->val.BlockVal.reduced;
			while (s != NULL) {
				func_print_structured(s);
				s = s->next;
			}
		break;
	}
}
#endif
