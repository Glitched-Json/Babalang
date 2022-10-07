%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "constants.h"
#include "dictionary.c"
#include "line.c"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
    long int intv;
    float f;
    char* noun;
    char c;
    bool b;
    struct List* list;
    struct Token* token;
    struct Line* line;
    struct Loop* loop;
    struct If_Statement* IF;
};

%token<intv> T_INT
%token<noun> T_NOUN T_STR
%token<f> T_FLOAT
%token<c> T_CHAR
%token<b> T_BOOL
%token T_IS T_AND T_MINUS T_GET T_TO T_NULL T_FOR T_MIMIC T_IF T_ELSE T_CALL
%token T_ADD T_MULT T_BL T_BR T_OR T_EQUALS T_SUB T_SPLIT T_DIV T_MOD T_NOT T_XOR
%token T_PRINT T_PRINT_STRUCTURED
%token T_DONE T_NL T_SBL T_SBR T_COMA

%left T_GET T_MULT T_SPLIT
%left T_TO T_MINUS T_AND T_ADD T_OR T_EQUALS T_SUB T_DIV T_MOD T_NOR T_XOR
%right T_IS T_NL T_FOR T_SBL T_SBR

%start S
%type<list> primitive
%type<noun> var block block_start
%type<intv> int func instruction
%type<f> float
%type<token> token
%type<loop> loop_instr
%type<IF> if_statement
%type<line> loop line

%%
//TODO: pow operation
//TODO: read function
//TODO: fill in the operations.h file
//TODO: get [FIX]
//TODO: implement while / do while loops    while -reduced line- { ... } || do { ... } while -reduced line-

//TODO: split & div [STRING - STRING] interaction:
//		"String" split "night" = ["St", "ri", "n", "g"] (splits the first string in an array, split on and including the characters from the second string)
//		"String" div   "night" = ["S", "r"] (splits the first string in an array, split on and excluding the characters from the second string)
//TODO: do one more check on every single operation interaction

/*
a is more / a is less / a is ... more / a is ... less

add - sub - mult - split - div - mod - or - xor - not - eq

a mimic b and is 5
a get b

*/
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//TODO: list1 is list2 <-> all future references of list1 are replaced with list2
//TODO: mimic list - mimic func

/* mimic
int
float
char
string
bool
null
*/
// has string - import file with name string. Imports the file's byte data, which can be decoded with various other functions


//TODO: prevent overflowing by using variable integer vars, which can increase / decrease their byte usage on demand using malloc/realloc
//TODO: implement goto function             line is -var-             || goto -var-
//TODO: implement #imports            -file name- is import         || -file name- has -file name- ??
//TODO: implement threads
//TODO: add gpu support
//TODO: easy functions for window making

S : {;}
  | S line {executeInstructions($2); free_line($2);}
  | S line T_NL {executeInstructions($2); free_line($2);}
  
  | S loop {executeInstructions($2); free_line($2);}
  | S loop T_NL {executeInstructions($2); free_line($2);}
  ;

line : token {$$ = new_line(); addNewToken($$, $1); if ($1->type == IF) addNewToken($$, token_i(i_if));}
     | T_CALL token {$$ = new_line(); addNewToken($$, $2); addNewToken($$, token_i(i_call));}

     | line T_NL instruction token {$$ = $1; addNewToken($$, token_i($3)); addNewToken($$, $4);}
     | line T_NL instruction T_NL token {$$ = $1; addNewToken($$, token_i($3)); addNewToken($$, $5);}
     | line instruction token {$$ = $1; addNewToken($$, token_i($2)); addNewToken($$, $3);}
     | line instruction T_NL token {$$ = $1; addNewToken($$, token_i($2)); addNewToken($$, $4);}
     ;

loop : loop_instr block {$$ = new_line(); addNewToken($$, $1->token); addNewToken($$, token_b_loop($2)); addNewToken($$, token_i($1->instruction));}
     //| loop_instr line  {$$ = new_line(); addNewToken($$, $1->token); addNewToken($$, token_b_loop(block_add_line(NULL, $2))); addNewToken($$, token_i($1->instruction));}
     ;

loop_instr : T_FOR line {$$ = new_loop(token_l($2), i_for);}
     	   ;

if_statement: T_IF token block {$$ = new_if($2, token_b($3), NULL);}
	    | T_IF token block T_ELSE block {$$ = new_if($2, token_b($3), token_if(new_if(token_e(bool_list(true)), token_b($5), NULL)));}
	    | T_IF token block T_ELSE if_statement {$$ = new_if($2, token_b($3), token_if($5));}
	    ;

instruction : T_IS        {$$ = i_is;}
	    | T_AND       {$$ = i_and;}
	    | T_ADD       {$$ = i_add;}
	    | T_DIV	  {$$ = i_div;}
	    | T_MOD	  {$$ = i_mod;}
	    | T_SUB	  {$$ = i_sub;}
	    | T_MULT      {$$ = i_mult;}
	    | T_SPLIT     {$$ = i_split;}
	    | T_TO        {$$ = i_to;}
	    | T_GET       {$$ = i_get;}
	    | T_MIMIC     {$$ = i_mimic;}
	    | T_OR	  {$$ = i_or;}
	    | T_XOR	  {$$ = i_xor;}
	    | T_EQUALS    {$$ = i_eq;}
	    | T_AND T_MIMIC {$$ = i_and_mimic;}
	    | T_AND T_IS  {$$ = i_and_is;}
	    ;

token: var  			{$$ = token_v($1);}
     | primitive 		{$$ = token_e($1);}
     | func 			{$$ = token_f($1);}
     | T_BL line T_BR 		{$$ = token_l($2);}
     | T_BL T_NL line T_BR	{$$ = token_l($3);}
     | T_BL line T_NL T_BR	{$$ = token_l($2);}
     | T_BL T_NL line T_NL T_BR {$$ = token_l($3);}
     | block			{$$ = token_b($1);}
     | if_statement		{$$ = token_if($1);}
     | T_NOT token		{$$ = instruction_not($2);}
     ;

func : T_DONE {$$ = f_done;}
     | T_PRINT {$$ = f_print;}
     | T_PRINT_STRUCTURED {$$ = f_print_str;}
     ;

block : block_start T_SBR {$$ = $1;}
      ;

block_start : T_SBL line {$$ = block_add_line(NULL, $2);}
	    | block_start T_COMA line {$$ = block_add_line($1, $3);}
	    ;

var : T_NOUN
    | T_MINUS var {$$ = $2;}
    ;

primitive : int {$$ = int_list($1);}
	  | T_STR {$$ = str_list($1);}
	  | float {$$ = float_list($1);}
	  | T_BOOL {$$ = bool_list($1);}
	  | T_CHAR {$$ = char_list($1);}
	  | T_NULL {$$ = null_list();}
	  //| T_HAS var {$$ = pointer_list($2);}
	  ;

int : T_INT
    | T_MINUS int {$$ = -$2;}
    ;

float : T_FLOAT
      | T_MINUS float {$$ = -$2;}
      ;

%%

int main() {
    FILE* file = read_file("main.baba");
    
    yyin = file;
    yyparse();
    
    file_close(file);
    yyrestart(yyin);
    printf("end of the exercise\n"); //TODO: remove after the exam
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
