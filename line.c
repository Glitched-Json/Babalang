#ifndef LINE_C
#define LINE_C

#include <stdio.h>
#include <string.h>
#include "line.h"
#include "line_basics.h"
#include "lists.c"
#include "instructions.c"
#include "operations.c"
#include "file_reader.c"

struct Line* new_line() {
	struct Line* line = (struct Line*)malloc(sizeof(struct Line));
	line->tokens = NULL;
	line->instr = NULL;
	line->reduced = NULL;
	return line;
}

struct TokensList* new_tokens_list(struct Token* t) {
	struct TokensList* list = (struct TokensList*)malloc(sizeof(struct TokensList*));
	list->val = t;
	list->next = NULL;
	list->prev = NULL;
	return list;
}

int executeInstructions(struct Line* line) {
	if (line->reduced == NULL) {reduce(line); return 0;}
	//char* s = save_line(line), *t=s; printf("%s\n", s); while(*s!=0)printf("%d ",*s++); s=t; printf("\n"); free(s);
	struct TokensList* startInstr = line->instr;
	struct TokensList* startTokens = line->tokens;
	if (line->tokens != NULL) while (line->tokens->next != NULL) line->tokens = line->tokens->next;
	if (line->instr != NULL) while (line->instr->next != NULL) line->instr = line->instr->next;
	struct TokensList* endInstr = line->instr;
	struct TokensList* endTokens = line->tokens;
	line->instr = startInstr;
	line->tokens = startTokens;
	
	//AND priority mode - (a and b is ... == a,b is ...)
	int andtois = 0;
	while (line->instr != NULL) {
		if (andtois == 0 && line->instr->val->val.func == i_is) andtois = 1;
		if (andtois >= 1 && line->instr->val->val.func == i_and) andtois = 2; else
		if (andtois >= 1 && line->instr->val->val.func == i_is) andtois = 1; else andtois = 0;
		line->instr = line->instr->next;
	}
	line->instr = startInstr;
	if (andtois == 2) {
		andtois = 0;
		while (line->instr->next != NULL) line->instr = line->instr->next;
		while (line->tokens->next != NULL) line->tokens = line->tokens->next;
		while (line->instr->val->val.func == i_and) {
			instruction_and_priority_mode(line);
			line->instr->val->val.func = i_and_priority;
			line->instr = line->instr->prev;
			andtois++;
		}
		line->instr = startInstr;
		line->tokens = startTokens;
	} else andtois = 0;
	
	//HAS priority mode - (a has b and is c ... == a is *b and *c ...}
	
	//MATH instruction priority mode
	for (int i=0; i<sizeof(MATH_PRIORITY)/sizeof(int); i++) {
		line->instr = endInstr;
		line->tokens = endTokens;
		while (line->instr != NULL) {
			if (line->instr->val->val.func == MATH_PRIORITY[i])
				switch (MATH_PRIORITY[i]) {
					case i_mult:
						instruction_mult(line);
						break;
					case i_split:
						instruction_split(line);
						break;
					case i_div:
						instruction_div(line);
						break;
					case i_mod:
						instruction_mod(line);
						break;
					case i_add:
						instruction_add(line);
						break;
					case i_sub:
						instruction_sub(line);
						break;
					case i_to:
						instruction_to(line);
						break;
					case i_or:
						instruction_or(line);
						break;
					case i_xor:
						instruction_xor(line);
						break;
					case i_eq:
						instruction_eq(line);
						break;
					case i_get:
						instruction_get(line);
						break;
					default: line->tokens = line->tokens->prev;
				}
			else
				line->tokens = line->tokens->prev;
			line->instr = line->instr->prev;
		}
	}
	
	int andDepth = 0;
	line->instr = startInstr;
	line->tokens = startTokens;
	//continue parsing
	while (line->instr != NULL) {
		switch (line->instr->val->val.func) {
			case i_is:
				instruction_is(line, 0);
				break;
			case i_and:
				andDepth++;
				instruction_and(line);
				break;
			case i_for:
				instruction_for(line);
				break;
			case i_if:
				instruction_if(line);
				break;
			case i_mimic:
				instruction_mimic(line, ++andDepth);
				instruction_is(line, --andDepth);
				andDepth = 0;
				break;
			case i_and_is:
				instruction_and(line);
				andDepth = 0;
				break;
			case i_and_mimic:
				instruction_mimic(line, ++andDepth);
				instruction_and(line);
				andDepth = 0;
				break;
			case i_call:
				instruction_call(line);
				break;
			
			default: line->tokens = line->tokens->next;
		}
		line->instr = line->instr->next;
	}
	line->instr = startInstr;
	line->tokens = startTokens;
	
	return andtois;
}

struct FunctionList* addFunc(struct FunctionList* fList, int func) {
	if (fList == NULL) {
		fList = (struct FunctionList*)malloc(sizeof(struct FunctionList));
		fList->f = func;
		fList->next = NULL;
		return fList;
	}
	struct FunctionList* start = fList;
	while (fList != NULL) fList = fList->next;
	fList = (struct FunctionList*)malloc(sizeof(struct FunctionList));
	fList->f = func;
	fList->next = NULL;
	return start;
}

struct Token* reduce(struct Line* line) {
	struct Token* reduced = NULL;
	struct TokensList* start = line->tokens;
	if (line->tokens != NULL) {
		while (line->tokens->next != NULL) line->tokens = line->tokens->next;
		reduced = tokenDup(line->tokens->val);
		while (line->tokens != NULL) {
			if (line->tokens->val->type == LINE) reduce(line->tokens->val->val.line);
			if (line->tokens->val->type == BLOCK) if (line->tokens->val->val.BlockVal.needsReducing) reduceBlock(line->tokens->val);
			line->tokens = line->tokens->prev;
		}
		line->tokens = start;
	}
	
	line->reduced = token_f(0);
	int i = executeInstructions(line);
	free_token(line->reduced, -1);
	
	if (line->tokens != NULL) {
		while (line->tokens->next != NULL) line->tokens = line->tokens->next;
		for (int j = i; j > 0; j--) line->tokens = line->tokens->prev;
		line->reduced = get_reduced(line->tokens->val);
		line->tokens = start;
	} else line->reduced = token_e(null_list());
	
	return reduced;
}

struct Token* get_reduced(struct Token* t) {
	while (t->type == LINE) t = t->val.line->reduced;
	return t;
}

void addNewToken(struct Line* line, struct Token* t) {
	if (line == NULL) return;
	switch (t->type) {
		case INSTR:
			if (line->instr == NULL) {
				line->instr = new_tokens_list(t);
			} else {
				struct TokensList* list = new_tokens_list(t);
				list->next = line->instr;
				line->instr->prev = list;
				line->instr = list;
			}
			break;
		default:
			if (line->tokens == NULL) {
				line->tokens = new_tokens_list(t);
			} else {
				struct TokensList* list = new_tokens_list(t);
				list->next = line->tokens;
				line->tokens->prev = list;
				line->tokens = list;
			}
	}
}

struct Token* reduceBlock(struct Token* t) {
	struct Token* reduced = NULL;
	if (t->type != BLOCK) return NULL;
	char* block = strdup(t->val.BlockVal.b);
	char* temp = (char*)malloc(sizeof(char)*strlen(block));
	int i = 0, block_depth = 0;
	struct Line* line; struct Token* r = NULL, *blockToken;
	while (*block != '\0') {
		if (block_depth > 0)
		switch (*block) {
			case '{': block_depth++; temp[i++] = *block; break;
			case '}': if (--block_depth == 0) {
				  	temp[i] = '\0';
				  	blockToken = token_b(temp);
				  	reduceBlock(blockToken);
				  	//TODO: free blockToken
				  	for (int j=0; j<i; j++) temp[j] = '\0'; i=0;
				  } break;
			default: temp[i++] = *block;
		}
		else
		switch (*block) {
			case '{': block_depth = 1; break;
			case ',': if (i==0) break;
				  temp[i] = '\0';
				  line = load_line(temp);
				  
				  if (reduced == NULL) reduced = reduce(line);
				  else add_token_to_list(reduced, reduce(line));
				  
				  if (r == NULL) r = tokenDup(line->reduced); else add_token_to_list(r, tokenDup(line->reduced));
				  free_line(line);
				  for (int j=0; j<i; j++) temp[j] = '\0'; i=0;
				  break;
			default: temp[i++] = *block;
		}
		block++;
	}
	temp[i] = '\0';
	line = load_line(temp);
	
	if (reduced == NULL) reduced = reduce(line);
	else add_token_to_list(reduced, reduce(line));
	
	if (r == NULL) r = tokenDup(line->reduced); else add_token_to_list(r, tokenDup(line->reduced));
	while (r->prev != NULL) r = r->prev;
	
	free_line(line);
	free(temp);
	
	t->val.BlockVal.reduced = r;
	return reduced;
}

struct Line* load_line(char* s) {
	char* temp = (char*)malloc(sizeof(char)*strlen(s));
	int i = 0, line_depth = 0, block_depth = 0;
	struct Line* line = new_line();
	while (*s != '\0') {
		if (line_depth > 0)
		switch ((int)*s+256) {
			case LN_STR: line_depth++; temp[i++] = *s; break;
			case LN_END: if (--line_depth > 0) temp[i++] = *s; break;
			default: temp[i++] = *s;
		}
		else if (block_depth > 0)
		switch ((int)*s+256) {
			case BLK_STR: block_depth++; temp[i++] = *s; break;
			case BLK_END: if (--block_depth > 0) temp[i++] = *s; break;
			default: temp[i++] = *s;
		}
		else
		switch ((int)*s+256) {
			case TKN_DIV: temp[i] = '\0';
				  addNewToken(line, string_to_token(temp));
				  for (int j=0; j<i; j++) temp[j] = '\0'; i=0;
				  break;
			case TKN_FUNC: temp[i] = '\0';
				  addNewToken(line, token_f(atoi(temp)));
				  for (int j=0; j<i; j++) temp[j] = '\0'; i=0;
				  break;
			case TKN_INSTR: temp[i] = '\0';
				  addNewToken(line, token_i(atoi(temp)));
				  for (int j=0; j<i; j++) temp[j] = '\0'; i=0;
				  break;
			case LN_STR: temp[i++] = *s; line_depth=1; break;
			case BLK_STR: temp[i++] = *s; block_depth=1; break;
			default: temp[i++] = *s;
		}
		s++;
	}
	free(temp);
	return line;
}

char* save_line(struct Line* line) {
	int l = 10, i = 0, size;
	char* s = (char*)malloc(sizeof(char)*l);
	struct TokensList* start;
	if (line->tokens != NULL) {
		start = line->tokens;
		while (line->tokens->next != NULL) line->tokens = line->tokens->next;
		while (line->tokens != NULL) {
			char* temp = token_to_string(line->tokens->val);
			size = strlen(temp);
			while (i+size+1>=l) {l*=2; s = (char*)realloc(s, sizeof(char)*l);}
			strcat(s, temp);
			switch (line->tokens->val->type) {
				case NOUN: strcat(s, ctoa(TKN_DIV)); break;
				case FUNC: strcat(s, ctoa(TKN_FUNC)); break;
				default: strcat(s, ctoa(TKN_DIV));
			}
			i+=size+1;
			
			line->tokens = line->tokens->prev;
		}
		line->tokens = start;
	}
	
	if (line->instr != NULL) {
		start = line->instr;
		while (line->instr->next != NULL) line->instr = line->instr->next;
		while (line->instr != NULL) {
			char* temp = token_to_string(line->instr->val);
			size = strlen(temp);
			while (i+size+1>=l) {l*=2; s = (char*)realloc(s, sizeof(char)*l);}
			strcat(s, temp);
			strcat(s, ctoa(TKN_INSTR));
			i+=size+1;
			
			line->instr = line->instr->prev;
		}
		line->instr = start;
	}
	if (++i != l) s = (char*)realloc(s, sizeof(char)*(i+1));
	s[i-1] = '\0';
	return s;
}

char* token_to_string(struct Token* t) {
	if (t == NULL) return "";
	char* temp, *s;
	switch (t->type) {
		case NOUN: return t->val.noun;
		case LIST: return list_to_string(t->val.list);
		case FUNC: case INSTR: return itoa(t->val.func);
		case LINE: temp = save_line(t->val.line);
		           s = (char*)malloc(sizeof(char)*(strlen(temp)+2));
		           s[0] = LN_STR; s[1]=0; strcat(s, temp); strcat(s, ctoa(LN_END));
		           return s;
		case BLOCK: temp = t->val.noun;
			    s = (char*)malloc(sizeof(char)*(strlen(temp)+2));
			    *s = BLK_STR; strcat(s, temp); strcat(s, ctoa(BLK_END));
			    return s;
		default: return "";
	}
}

struct Token* string_to_token(char* str) {
	char* s; int i;
	switch ((int)*str+256) {
		case LST_DIV:
			s = (char*)malloc(sizeof(char)*strlen(str));
			i = 0;
			struct List* list = NULL;
			while (*str++ != '\0') {
				if ((int)*str+256 == LST_DIV) {
					s[i] = '\0';
					if (list == NULL)
						list = new_list(string_to_value(s));
					else
						add_node(list, new_list(string_to_value(s)));
					for (int j=0; j<i; j++) s[j]='\0'; i=0;
				} else s[i++] = *str;
			}
			s[i] = '\0';
			if (list == NULL)
				list = new_list(string_to_value(s));
			else
				add_node(list, new_list(string_to_value(s)));
			for (int j=0; j<i; j++) s[j]='\0';
			free(s);
			return token_e(list);
		case LN_STR:
			s = (char*)malloc(sizeof(char)*strlen(++str));
			i = 0; while (*str!=0) s[i++]=*str++; s[i]=0;
			struct Line* line = load_line(s);
			free(s);
			return token_l(line);
		case BLK_STR:
			s = (char*)malloc(sizeof(char)*strlen(++str));
			i = 0; while (*str!=0) s[i++]=*str++; s[i]=0;
			struct Token* token = token_b(s);
			free(s);
			return token;
		default:
			s = (char*)malloc(sizeof(char)*(strlen(str)+1));
			i = 0; char* t = str;
			while (*str!='\0') s[i++]=*str++; s[i]=0;
			str = t;
			return token_v(s);
	}
}

char* block_add_line(char* block, struct Line* line) {
	char* s = save_line(line);
	if (block == NULL) {
		block = (char*)malloc(sizeof(char)*strlen(s));
		strcat(block, s);
		free(s);
		return block;
	}
	block = (char*)realloc(block, sizeof(char)*(strlen(block)+strlen(s)+1));
	strcat(block, ","); strcat(block, s);
	free(s);
	return block;
}

char* block_add_block(char* block1, char* block2) {
	char* s = ""; int i = 0;
	if (block1 == NULL) s = (char*)malloc(sizeof(char)*(strlen(block2)+2));
	else s = (char*)malloc(sizeof(char)*(strlen(block1)+strlen(block2)+2));
	char* temp = block2;
	s[0] = '{'; while (*block2 != '\0') s[++i]=*(block2++); s[++i]='}'; s[++i]='\0'; block2 = temp;
	free(block1); free(block2);
	return s;
}

void print_line_str(struct Line* line) {
	if (line == NULL) {printf("()"); return;}
	printf("(");
	struct TokensList* start = line->instr;
	if (line->tokens != NULL) while (line->tokens->next != NULL) line->tokens = line->tokens->next;
	if (line->instr != NULL) while (line->instr->next != NULL) line->instr = line->instr->next;
	if (line->tokens != NULL) print_token(line->tokens->val, false);
	while (line->instr != NULL) {
		line->tokens = line->tokens->prev;
		printf(" ");
		print_token(line->instr->val, false);
		printf(" ");
		print_token(line->tokens->val, false);
		line->instr = line->instr->prev;
	}
	while (line->tokens->prev != NULL) line->tokens = line->tokens->prev;
	line->instr = start;
	printf(")");
}
void print_line(struct Line* line) {
	if (line == NULL) {printf("null line\n"); return;}
	printf("Token List: [");
	if (line->tokens != NULL) {
		while (line->tokens->next!=NULL) line->tokens = line->tokens->next;
		print_token(line->tokens->val, false);
		while (line->tokens->prev!=NULL) {line->tokens = line->tokens->prev; print_token(line->tokens->val, true);}
	}
	printf("]\nInstruction List: [");
	if (line->instr != NULL) {
		struct TokensList* start = line->instr;
		bool coma = false;
		while (line->instr!=NULL) {print_token(line->instr->val, coma); coma = true; line->instr = line->instr->next;}
		line->instr = start;
	}
	printf("]\n");
}
void print_token(struct Token* t, bool include_coma) {
	if (t == NULL) return;
	if (include_coma) printf(", ");
	
	bool coma = false;
	struct Token* s = t;
	while (t != NULL) {
		if (coma) printf("-");
		switch (t->type) {
			case NOUN: printf("%s", t->val.noun); break;
			case LIST: print_list(t->val.list, false); break;
			case FUNC: switch (t->val.func) {
					case f_done: printf("done"); break;
					case f_print: printf("print"); break;
					case f_print_str: printf("print_structured"); break;
					default: printf("\"\"");
				   }
				   break;
			case INSTR: switch (t->val.func) {
					case i_is: printf("is"); break;
					case i_and: printf("and"); break;
					case i_and_priority: printf("and!"); break;
					case i_add: printf("add"); break;
					case i_for: printf("for"); break;
					case i_to: printf("to"); break;
					case i_mimic: printf("mimic"); break;
					case i_and_mimic: printf("and mimic"); break;
					case i_and_is: printf("and is"); break;
					case i_get: printf("get"); break;
					default: printf("\"\"");
				   }
				   break;
			case LINE: print_line_str(t->val.line); break;
			case BLOCK: printf("%s", t->val.noun); break;
		}
		t = t->next;
		coma = true;
	}
	t=s;
}

void print_block(char* block) {
	char* temp = (char*)malloc(sizeof(char)*strlen(block));
	int i = 0, block_depth = 0;
	struct Line* line;
	while (*block != '\0') {
		if (block_depth > 0)
		switch (*block) {
			case '{': block_depth++; temp[i++] = *block; break;
			case '}': if (--block_depth == 0) {
				  	temp[i] = '\0';
				  	print_block(temp);
				  	for (int j=0; j<i; j++) temp[j] = '\0'; i=0;
				  } break;
			default: temp[i++] = *block;
		}
		else
		switch (*block) {
			case '{': block_depth = 1; break;
			case ',': if (i==0) break;
				  temp[i] = '\0';
				  line = load_line(temp);
				  print_line_str(line);
				  free_line(line);
				  for (int j=0; j<i; j++) temp[j] = '\0'; i=0;
				  break;
			default: temp[i++] = *block;
		}
		block++;
	}
	temp[i] = '\0';
	line = load_line(temp);
	print_line_str(line);
	free_line(line);
	free(temp);
}

void print_debug_block(char* block) {
	char* t = block;
	while (*block!=0) printf("%c", *block++);
	block = t; printf("\n");
	while (*block!=0) {
		switch (*block+256) {
			case TKN_DIV: printf("T"); break;
			case LST_DIV: printf("L"); break;
			case TKN_INSTR: printf("I"); break;
			case LN_STR: printf("("); break;
			case LN_END: printf(")"); break;
			case TKN_FUNC: printf("F"); break;
			case BLK_STR: printf("["); break;
			case BLK_END: printf("]"); break;
			default: printf("%c", *block);
		}
		block++;
	} printf("\n");
	block = t;
}

void add_token_to_list(struct Token* t1, struct Token* t2) {
	if (t1 == NULL || t2 == NULL || t1 == t2) return;
	struct Token* start = t1;
	while (t1->next != NULL) t1 = t1->next;
	t1->next = t2;
	t2->prev = t1;
	t1 = start;
}
#endif
