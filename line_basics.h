#ifndef LINE_BASICS_H
#define LINE_BASICS_H
#include "line.h"

void printTokenEnum(struct Token* t) {
	switch (t->type) {
		case NOUN: debug_("Noun") break;
		case LIST: debug_("List") break;
		case FUNC: debug_("Func") break;
		case INSTR: debug_("Instr") break;
		case LINE: debug_("Line") break;
	}
}

void free_line(struct Line* line) {
	free_token_list(line->tokens, 1);
	free_token_list(line->instr, -1);
	free(line);
}

void free_token_list(struct TokensList* list, int ammount) {
	struct TokensList* temp = list;
	while (list != NULL) {
		temp = list->next;
		free_token(list->val, ammount);
		free(list);
		list = temp;
	}
}

void free_token(struct Token* token, int ammount) {
	struct Token* temp = token;
	while (token != NULL && ammount-- != 0) {
		temp = token->next;
		if (token->type == NOUN || token->type == BLOCK) free(token->val.noun);
		free(token);
		token = temp;
	}
}

void free_funciton_list(struct FunctionList* fList) {
	struct FunctionList* temp = fList;
	while (fList != NULL) {
		temp = fList->next;
		free(fList);
		fList = temp;
	}
}

struct Loop* new_loop(struct Token* t, int inst) {
	struct Loop* loop = (struct Loop*)malloc(sizeof(struct Loop));
	loop->token = t;
	loop->instruction = inst;
	return loop;
}

struct If_Statement* new_if(struct Token* t, struct Token* block, struct Token* next) {
	struct If_Statement* IF = (struct If_Statement*)malloc(sizeof(struct If_Statement));
	IF->statement = t;
	IF->block = block;
	IF->next = next;
	return IF;
}

struct Token* token_v(char* key) {
	struct Token* node = (struct Token*)malloc(sizeof(struct Token));
	node->val.noun = (char*)malloc(sizeof(char)*(strlen(key)+1));
	int i=0; while (*key!=0) node->val.noun[i++]=*key++; node->val.noun[i]=0;
	node->type = (enum T)NOUN;
	node->next = NULL;
	return node;
}

struct Token* token_e(struct List* l) {
	struct Token* node = (struct Token*)malloc(sizeof(struct Token));
	node->val.list = l;
	node->type = (enum T)LIST;
	node->next = NULL;
	return node;
}

struct Token* token_f(int f) {
	struct Token* node = (struct Token*)malloc(sizeof(struct Token));
	node->val.func = f;
	node->type = (enum T)FUNC;
	node->next = NULL;
	return node;
}

struct Token* token_i(int i) {
	struct Token* node = (struct Token*)malloc(sizeof(struct Token));
	node->val.func = i;
	node->type = (enum T)INSTR;
	node->next = NULL;
	return node;
}

struct Token* token_l(struct Line* l) {
	struct Token* node = (struct Token*)malloc(sizeof(struct Token));
	node->val.line = l;
	node->type = (enum T)LINE;
	node->next = NULL;
	return node;
}

struct Token* token_b(char* block) {
	struct Token* node = (struct Token*)malloc(sizeof(struct Token));
	node->val.BlockVal.b = (char*)malloc(sizeof(char)*(strlen(block)+1));
	node->val.BlockVal.reduced = NULL;
	node->val.BlockVal.needsReducing = true;
	int i=0; while (*block!=0) node->val.noun[i++]=*block++; node->val.noun[i]=0;
	node->type = (enum T)BLOCK;
	node->next = NULL;
	return node;
}

struct Token* token_b_loop(char* block) {
	struct Token* node = token_b(block);
	node->val.BlockVal.needsReducing = false;
	return node;
}

struct Token* token_if(struct If_Statement* if_statement) {
	struct Token* node = (struct Token*)malloc(sizeof(struct Token));
	node->val.if_statement = if_statement;
	node->type = (enum T)IF;
	node->next = NULL;
	return node;
}

struct Token* tokenDup(struct Token* token) {
	switch (token->type) {
		case NOUN: return token_v(token->val.noun);
		case LIST: return token_e(token->val.list);
		case FUNC: return token_f(token->val.func);
		case INSTR: return token_i(token->val.func);
		case LINE: return token_l(token->val.line);
		case BLOCK: return token_b(token->val.BlockVal.b);
		default: 
			struct Token* node = (struct Token*)malloc(sizeof(struct Token));
			node->val.list = null_list();
			node->type = (enum T)LIST;
			node->next = NULL;
			return node;
	}
}

#endif
