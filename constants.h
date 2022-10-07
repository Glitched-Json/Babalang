#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "lists.h"
#define return_blank return new_list((struct Value){.val = (union Val){.i=0}, .type = (enum Type)INT});

#define val_i(a) (struct Value){.val = (union Val){.i=a}, .type = (enum Type)INT}
#define int_list(a) (new_list(val_i(a)))

#define val_s(str) (struct Value){.val = (union Val){.s=str}, .type = (enum Type)STRING}
#define str_list(str) (new_list(val_s(str)))

#define val_f(float) (struct Value){.val = (union Val){.f=float}, .type = (enum Type)FLOAT}
#define float_list(f) (new_list(val_f(f)))

#define val_b(bool) (struct Value){.val = (union Val){.b=bool}, .type = (enum Type)BOOL}
#define bool_list(b) (new_list(val_b(b)))

#define val_c(char) (struct Value){.val = (union Val){.c=char}, .type = (enum Type)CHAR}
#define char_list(c) (new_list(val_c(c)))

#define val_p(str) (struct Value){.val = (union Val){.s=str}, .type = (enum Type)POINTER}
#define pointer_list(str) (new_list(val_p(str)))

#define val_null() (struct Value){.type = (enum Type)IS_NULL}
#define null_list() (new_list(val_null()))

#define val_0(type) (type==INT?val_i(0):type==FLOAT?val_f(0):type==STRING?val_s(""):type==CHAR?val_c('\0'):type==BOOL?val_b(false):val_null())



#define i_is        0
#define i_and       1
#define i_and_priority -2
#define i_for       2
#define i_if	    3
#define i_get       4
#define i_mimic     5
#define i_and_mimic 6
#define i_and_is    7
#define i_call	    8

//MATH priority mode instructions || max -> min priority between them
#define i_mult    9
#define i_split   10
#define i_add     11
#define i_sub	  12
#define i_div     13
#define i_mod	  14
#define i_to      15
#define i_or      16
#define i_xor	  17
#define i_eq	  18
static int MATH_PRIORITY[] = {i_mult, i_split, i_div, i_mod,
			      i_add, i_sub,
			      i_to, i_get,
			      i_or, i_xor, i_eq};

#define f_done      0
#define f_print     1
#define f_print_str 2

#define TKN_DIV   186 //-70
#define LST_DIV   205 //-51
#define TKN_INSTR 161 //-95
#define LN_STR    244 //-12
#define LN_END    245 //-11
#define TKN_FUNC  237 //-19
#define BLK_STR   174 //-82
#define BLK_END   175 //-81

char *my_itoa(char *dest, int i) {
  sprintf(dest, "%d", i);
  char* s = strdup(dest);
  return s;
}
char *my_ftoa(char *dest, float f) {
  sprintf(dest, "%f", f);
  while (dest[strlen(dest)-1]=='0') dest[strlen(dest)-1]=0;
  if (dest[strlen(dest)-1]=='.') dest[strlen(dest)-1]='f'; else dest[strlen(dest)]='f';
  char* s = strdup(dest);
  return s;
}
char *my_ctoa(char c) {
  char* cpointer = malloc(2*sizeof(char));
  cpointer[0]=c; cpointer[1]='\0';
  return cpointer;
}

#define itoa(n) my_itoa((char [41]) { 0 }, (n))
#define ctoa(c) my_ctoa(c)
#define ftoa(f) my_ftoa((char [41]) { 0 }, (f))

#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAX(a, b) (((a)>(b))?(a):(b))

void strrev(unsigned char *str) {
	int i; int j; unsigned char a; unsigned len = strlen((const char *)str);
	for (i = 0, j = len - 1; i < j; i++, j--) {
		a = str[i];
		str[i] = str[j];
		str[j] = a;
	}
}

#define debug fprintf(stderr, "[%d]%s\n" , __LINE__, __FILE__);
#define debug_(s) fprintf(stderr, "[%d]%s: %s\n", __LINE__, __FILE__, s);
#define debug_addr(p) fprintf(stderr, "[%d]%s - %p\n", __LINE__, __FILE__, p);
#define debug_addr_(s, p) fprintf(stderr, "[%d]%s [%p] - %s\n", __LINE__, __FILE__, p, s);
#endif
