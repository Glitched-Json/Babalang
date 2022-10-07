#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

void func_print_structured(struct Token* t);
void func_print(struct Token* t);
void func(struct Token* t, int f);
void instruction_eq(struct Line* line);
void instruction_xor(struct Line* line);
void instruction_or(struct Line* line);
void instruction_mod(struct Line* line);
void instruction_div(struct Line* line);
void instruction_split(struct Line* line);
void instruction_mult(struct Line* line);
void instruction_sub(struct Line* line);
void instruction_add(struct Line* line);
void instruction_call(struct Line* line);
void instruction_mimic(struct Line* line, int andDepth);
void instruction_and_priority_mode(struct Line* line);
void instruction_and(struct Line* line);
void instruction_if(struct Line* line);
void instruction_for(struct Line* line);
void instruction_to(struct Line* line);
void instruction_is(struct Line* line, int andDepth);
void instruction_get(struct Line* line);
char* format_instruction(char* noun, struct Value v);
struct Token* getLastToken(struct Line* line);
struct Token* instruction_not(struct Token* t);
struct Token* reduce_if(struct Token* IFStatement);

#endif
