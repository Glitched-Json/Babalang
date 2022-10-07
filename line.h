#ifndef LINE_H
#define LINE_H
#include "constants.h"

struct Token {
	union V {
		char* noun;
		struct List* list;
		int func;
		struct Line* line;
		struct If_Statement* if_statement;
		struct BlockValStruct {
			char* b;
			struct Token* reduced;
			bool needsReducing;
		} BlockVal;
	} val;
	enum T{NOUN, LIST, FUNC, INSTR, LINE, BLOCK, IF} type;
	struct Token* next;
	struct Token* prev;
};

struct TokensList {
	struct Token* val;
	struct TokensList* next;
	struct TokensList* prev;
};

struct Line {
	struct TokensList* tokens;
	struct TokensList* instr;
	struct Token* reduced;
};

struct FunctionList {
	int f;
	struct FunctionList* next;
};

struct Loop {
	struct Token* token;
	int instruction;
};

struct If_Statement {
	struct Token* statement;
	struct Token* block;
	struct Token* next;
};

char* save_line(struct Line* line);
char* token_to_string(struct Token* t);
char* block_add_line(char* block, struct Line* line);
char* block_add_block(char* block1, char* block2);
int executeInstructions(struct Line* line);
void addNewToken(struct Line* line, struct Token* t);
void print_line(struct Line* line);
void print_line_str(struct Line* line);
void print_token(struct Token* t, bool include_coma);
void print_block(char* block);
void add_token_to_list(struct Token* t1, struct Token* t2);
struct Token* reduce(struct Line* line);
struct Token* reduceBlock(struct Token* t);
void free_token(struct Token* token, int ammount);
void free_token_list(struct TokensList* list, int ammount);
void free_line(struct Line* line);
void free_funciton_list(struct FunctionList* fList);
void add_if_else(struct If_Statement* IF, struct Token* t, int inst);
void if_to_line(struct Line* line, struct If_Statement* i);
struct Loop* new_loop(struct Token* t, int inst);
struct If_Statement* new_if(struct Token* t, struct Token* block, struct Token* next);
struct FunctionList* addFunc(struct FunctionList* fList, int func);
struct Line* new_line();
struct Line* load_line(char* s);
struct TokensList* new_tokens_list(struct Token* t);
struct Token* get_reduced(struct Token* t);
struct Token* string_to_token(char* str);
struct Token* tokenDup(struct Token* token);
struct Token* token_v(char* key);
struct Token* token_b(char* block);
struct Token* token_b_loop(char* block);
struct Token* token_e(struct List* l);
struct Token* token_f(int f);
struct Token* token_i(int i);
struct Token* token_l(struct Line* l);
struct Token* token_if(struct If_Statement* if_statement);

#endif
