%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include "lex_helper.h"

#define YY_DECL int yylex()
#include "babalang.tab.c"
%}
%x MULTILINE_COMMENT

%%
<INITIAL>{
[ \t]+    	 ; // ignore all whitespace
"//".*[ \t\s\n]* ; // ignore all comments
"/*" 		 BEGIN(MULTILINE_COMMENT); // ignore all multi-line comments
"is"        	 {return T_IS;}
"and"        	 {return T_AND;}
"add"		 {return T_ADD;}
"div" 		 {return T_DIV;}
"mod"		 {return T_MOD;}
"sub"		 {return T_SUB;}
"mult"		 {return T_MULT;}
"split"		 {return T_SPLIT;}
"for"		 {return T_FOR;}
"mimic"		 {return T_MIMIC;}
"if"		 {return T_IF;}
"else"		 {return T_ELSE;}

"get"		 {return T_GET;}
"to"		 {return T_TO;}
"call"		 {return T_CALL;}

"or"		 {return T_OR;}
"xor"		 {return T_XOR;}
"not"		 {return T_NOT;}
"equals"	 {return T_EQUALS;}

"done"        	 {return T_DONE;}
"print"		 {return T_PRINT;}
"print_structured" {return T_PRINT_STRUCTURED;}

"("              {return T_BL;}
")"              {return T_BR;}
"{"[ \t\n]*	 {return T_SBL;}
[ \t\n]*"}"	 {return T_SBR;}
[ \t\n]*","[ \t\n]* {return T_COMA;}
("true"|"TRUE")  {yylval.b=true; return T_BOOL;}
("false"|"FALSE") {yylval.b=false; return T_BOOL;}
("null"|"NULL")  {return T_NULL;}
[a-zA-Z][_a-zA-Z0-9]* {yylval.noun=strdup(yytext); return T_NOUN;}
\'\\n\' {yylval.c='\n'; return T_CHAR;}
\'\' {yylval.c=' '; return T_CHAR;}
\'.\' {yylval.c=*++yytext; return T_CHAR;}
\"(\\.|[^"\\])*\" {yylval.noun=strdup(yytext+1); yylval.noun[strlen(yylval.noun)-1]=0; yylval.noun = str_replace(yylval.noun, "\\n", "\n"); return T_STR;}
([0-9]+(f|F|\.))|([0-9]+\.[0-9]+(f|F)?) {yylval.f=atof(yytext); return T_FLOAT;} 
[0-9]+        {yylval.intv = atol(yytext); return T_INT;}
\n[ \t\n]*        {return T_NL;}
"-"    {return T_MINUS;}
. ;
}
<MULTILINE_COMMENT>{
"*/"[ \t\s\n]*	BEGIN(INITIAL);
[^*\n]+   	;
"*"       	;
\n        	yylineno++;
}

%%

