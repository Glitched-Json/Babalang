/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "babalang.y"

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

#line 87 "babalang.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_INT = 258,                   /* T_INT  */
    T_NOUN = 259,                  /* T_NOUN  */
    T_STR = 260,                   /* T_STR  */
    T_FLOAT = 261,                 /* T_FLOAT  */
    T_CHAR = 262,                  /* T_CHAR  */
    T_BOOL = 263,                  /* T_BOOL  */
    T_IS = 264,                    /* T_IS  */
    T_AND = 265,                   /* T_AND  */
    T_MINUS = 266,                 /* T_MINUS  */
    T_GET = 267,                   /* T_GET  */
    T_TO = 268,                    /* T_TO  */
    T_NULL = 269,                  /* T_NULL  */
    T_FOR = 270,                   /* T_FOR  */
    T_MIMIC = 271,                 /* T_MIMIC  */
    T_IF = 272,                    /* T_IF  */
    T_ELSE = 273,                  /* T_ELSE  */
    T_CALL = 274,                  /* T_CALL  */
    T_ADD = 275,                   /* T_ADD  */
    T_MULT = 276,                  /* T_MULT  */
    T_BL = 277,                    /* T_BL  */
    T_BR = 278,                    /* T_BR  */
    T_OR = 279,                    /* T_OR  */
    T_EQUALS = 280,                /* T_EQUALS  */
    T_SUB = 281,                   /* T_SUB  */
    T_SPLIT = 282,                 /* T_SPLIT  */
    T_DIV = 283,                   /* T_DIV  */
    T_MOD = 284,                   /* T_MOD  */
    T_NOT = 285,                   /* T_NOT  */
    T_XOR = 286,                   /* T_XOR  */
    T_PRINT = 287,                 /* T_PRINT  */
    T_PRINT_STRUCTURED = 288,      /* T_PRINT_STRUCTURED  */
    T_DONE = 289,                  /* T_DONE  */
    T_NL = 290,                    /* T_NL  */
    T_SBL = 291,                   /* T_SBL  */
    T_SBR = 292,                   /* T_SBR  */
    T_COMA = 293,                  /* T_COMA  */
    T_NOR = 294                    /* T_NOR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "babalang.y"

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

#line 186 "babalang.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);


/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_INT = 3,                      /* T_INT  */
  YYSYMBOL_T_NOUN = 4,                     /* T_NOUN  */
  YYSYMBOL_T_STR = 5,                      /* T_STR  */
  YYSYMBOL_T_FLOAT = 6,                    /* T_FLOAT  */
  YYSYMBOL_T_CHAR = 7,                     /* T_CHAR  */
  YYSYMBOL_T_BOOL = 8,                     /* T_BOOL  */
  YYSYMBOL_T_IS = 9,                       /* T_IS  */
  YYSYMBOL_T_AND = 10,                     /* T_AND  */
  YYSYMBOL_T_MINUS = 11,                   /* T_MINUS  */
  YYSYMBOL_T_GET = 12,                     /* T_GET  */
  YYSYMBOL_T_TO = 13,                      /* T_TO  */
  YYSYMBOL_T_NULL = 14,                    /* T_NULL  */
  YYSYMBOL_T_FOR = 15,                     /* T_FOR  */
  YYSYMBOL_T_MIMIC = 16,                   /* T_MIMIC  */
  YYSYMBOL_T_IF = 17,                      /* T_IF  */
  YYSYMBOL_T_ELSE = 18,                    /* T_ELSE  */
  YYSYMBOL_T_CALL = 19,                    /* T_CALL  */
  YYSYMBOL_T_ADD = 20,                     /* T_ADD  */
  YYSYMBOL_T_MULT = 21,                    /* T_MULT  */
  YYSYMBOL_T_BL = 22,                      /* T_BL  */
  YYSYMBOL_T_BR = 23,                      /* T_BR  */
  YYSYMBOL_T_OR = 24,                      /* T_OR  */
  YYSYMBOL_T_EQUALS = 25,                  /* T_EQUALS  */
  YYSYMBOL_T_SUB = 26,                     /* T_SUB  */
  YYSYMBOL_T_SPLIT = 27,                   /* T_SPLIT  */
  YYSYMBOL_T_DIV = 28,                     /* T_DIV  */
  YYSYMBOL_T_MOD = 29,                     /* T_MOD  */
  YYSYMBOL_T_NOT = 30,                     /* T_NOT  */
  YYSYMBOL_T_XOR = 31,                     /* T_XOR  */
  YYSYMBOL_T_PRINT = 32,                   /* T_PRINT  */
  YYSYMBOL_T_PRINT_STRUCTURED = 33,        /* T_PRINT_STRUCTURED  */
  YYSYMBOL_T_DONE = 34,                    /* T_DONE  */
  YYSYMBOL_T_NL = 35,                      /* T_NL  */
  YYSYMBOL_T_SBL = 36,                     /* T_SBL  */
  YYSYMBOL_T_SBR = 37,                     /* T_SBR  */
  YYSYMBOL_T_COMA = 38,                    /* T_COMA  */
  YYSYMBOL_T_NOR = 39,                     /* T_NOR  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_S = 41,                         /* S  */
  YYSYMBOL_line = 42,                      /* line  */
  YYSYMBOL_loop = 43,                      /* loop  */
  YYSYMBOL_loop_instr = 44,                /* loop_instr  */
  YYSYMBOL_if_statement = 45,              /* if_statement  */
  YYSYMBOL_instruction = 46,               /* instruction  */
  YYSYMBOL_token = 47,                     /* token  */
  YYSYMBOL_func = 48,                      /* func  */
  YYSYMBOL_block = 49,                     /* block  */
  YYSYMBOL_block_start = 50,               /* block_start  */
  YYSYMBOL_var = 51,                       /* var  */
  YYSYMBOL_primitive = 52,                 /* primitive  */
  YYSYMBOL_int = 53,                       /* int  */
  YYSYMBOL_float = 54                      /* float  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   393

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  84

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    97,    97,    98,    99,   101,   102,   105,   106,   108,
     109,   110,   111,   114,   118,   121,   122,   123,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   156,   157,   158,   161,   164,   165,
     168,   169,   172,   173,   174,   175,   176,   177,   181,   182,
     185,   186
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_INT", "T_NOUN",
  "T_STR", "T_FLOAT", "T_CHAR", "T_BOOL", "T_IS", "T_AND", "T_MINUS",
  "T_GET", "T_TO", "T_NULL", "T_FOR", "T_MIMIC", "T_IF", "T_ELSE",
  "T_CALL", "T_ADD", "T_MULT", "T_BL", "T_BR", "T_OR", "T_EQUALS", "T_SUB",
  "T_SPLIT", "T_DIV", "T_MOD", "T_NOT", "T_XOR", "T_PRINT",
  "T_PRINT_STRUCTURED", "T_DONE", "T_NL", "T_SBL", "T_SBR", "T_COMA",
  "T_NOR", "$accept", "S", "line", "loop", "loop_instr", "if_statement",
  "instruction", "token", "func", "block", "block_start", "var",
  "primitive", "int", "float", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
#endif

#define YYPACT_NINF (-57)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -57,    56,   -57,   -57,   -57,   -57,   -57,   -57,   -57,     7,
     -57,    90,   192,   192,    16,   192,   -57,   -57,   -57,    90,
     268,   -30,   -27,   -57,   -57,   -57,   -57,    -9,   -57,   -57,
     -57,   -57,   -57,   -57,   -57,   292,   -27,   -57,    90,   220,
     -57,   292,   -57,    -1,   -57,   -57,   -57,   -57,   -57,   -57,
     -57,   -57,   -57,   -57,   -57,   -57,   362,   124,   -57,   -57,
     -57,    90,   362,    -4,   244,   -57,   316,   -57,   -57,   158,
     192,   -57,   292,   -11,   -57,   339,   -57,   192,   -57,   -57,
     -57,   -57,   -57,   -57
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,    58,    50,    53,    60,    56,    55,     0,
      57,     0,     0,     0,     0,     0,    45,    46,    44,     0,
       3,     5,     0,    42,     7,    36,    41,     0,    34,    35,
      52,    54,    51,    59,    61,    14,     0,     8,     0,     0,
      43,    48,    18,    19,    27,    26,    28,    20,    24,    29,
      31,    23,    25,    21,    22,    30,     4,     0,     6,    13,
      47,     0,     0,    15,     0,    37,     0,    33,    32,     0,
       0,    11,    49,     0,    38,     0,    39,     0,     9,    12,
      17,    16,    40,    10
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -57,   -57,    -7,   -57,   -57,   -56,    10,   -12,   -57,   -20,
     -57,    17,   -57,    23,    25
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    20,    21,    22,    23,    57,    24,    25,    26,
      27,    28,    29,    30,    31
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      36,    37,    59,    40,    35,    58,    12,    39,    67,    19,
       3,     4,    41,     6,    73,    68,    63,    80,     9,     3,
       4,     5,     6,     7,     8,    19,    32,     9,    60,    61,
      10,    64,    33,    12,    34,    13,     0,     0,    14,     0,
       0,     0,     0,     0,     0,    71,    15,     0,    16,    17,
      18,    38,    19,    81,    72,     0,     2,    78,    79,     3,
       4,     5,     6,     7,     8,    83,    69,     9,     0,     0,
      10,    11,    69,    12,     0,    13,    69,     0,    14,     0,
       0,     0,     0,     0,     0,    69,    15,     0,    16,    17,
      18,     0,    19,     3,     4,     5,     6,     7,     8,     0,
       0,     9,     0,     0,    10,     0,     0,    12,     0,    13,
       0,     0,    14,     0,     0,     0,     0,     0,     0,     0,
      15,     0,    16,    17,    18,     0,    19,     3,     4,     5,
       6,     7,     8,     0,     0,     9,     0,     0,    10,     0,
       0,    12,     0,     0,     0,     0,    14,     0,     0,     0,
       0,     0,     0,     0,    15,     0,    16,    17,    18,    70,
      19,     3,     4,     5,     6,     7,     8,     0,     0,     9,
       0,     0,    10,     0,     0,    12,     0,     0,     0,     0,
      14,     0,     0,     0,     0,     0,     0,     0,    15,     0,
      16,    17,    18,    77,    19,     3,     4,     5,     6,     7,
       8,     0,     0,     9,     0,     0,    10,     0,     0,    12,
       0,     0,     0,     0,    14,     0,     0,     0,     0,     0,
       0,     0,    15,     0,    16,    17,    18,     0,    19,    42,
      43,     0,    44,    45,     0,     0,    46,     0,     0,     0,
      47,    48,     0,    65,    49,    50,    51,    52,    53,    54,
       0,    55,     0,    42,    43,    66,    44,    45,     0,     0,
      46,     0,     0,     0,    47,    48,     0,    74,    49,    50,
      51,    52,    53,    54,     0,    55,     0,    42,    43,    75,
      44,    45,     0,     0,    46,     0,     0,     0,    47,    48,
       0,     0,    49,    50,    51,    52,    53,    54,     0,    55,
       0,    42,    43,    56,    44,    45,     0,     0,    46,     0,
       0,     0,    47,    48,     0,     0,    49,    50,    51,    52,
      53,    54,     0,    55,     0,    42,    43,    62,    44,    45,
       0,     0,    46,     0,     0,     0,    47,    48,     0,    76,
      49,    50,    51,    52,    53,    54,     0,    55,    42,    43,
       0,    44,    45,     0,     0,    46,     0,     0,     0,    47,
      48,     0,    82,    49,    50,    51,    52,    53,    54,     0,
      55,    42,    43,     0,    44,    45,     0,     0,    46,     0,
       0,     0,    47,    48,     0,     0,    49,    50,    51,    52,
      53,    54,     0,    55
};

static const yytype_int8 yycheck[] =
{
      12,    13,    22,    15,    11,    35,    17,    14,     9,    36,
       3,     4,    19,     6,    18,    16,    36,    73,    11,     3,
       4,     5,     6,     7,     8,    36,     9,    11,    37,    38,
      14,    38,     9,    17,     9,    19,    -1,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    30,    -1,    32,    33,
      34,    35,    36,    73,    61,    -1,     0,    69,    70,     3,
       4,     5,     6,     7,     8,    77,    56,    11,    -1,    -1,
      14,    15,    62,    17,    -1,    19,    66,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    30,    -1,    32,    33,
      34,    -1,    36,     3,     4,     5,     6,     7,     8,    -1,
      -1,    11,    -1,    -1,    14,    -1,    -1,    17,    -1,    19,
      -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    32,    33,    34,    -1,    36,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    -1,    14,    -1,
      -1,    17,    -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,    35,
      36,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    14,    -1,    -1,    17,    -1,    -1,    -1,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      32,    33,    34,    35,    36,     3,     4,     5,     6,     7,
       8,    -1,    -1,    11,    -1,    -1,    14,    -1,    -1,    17,
      -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    32,    33,    34,    -1,    36,     9,
      10,    -1,    12,    13,    -1,    -1,    16,    -1,    -1,    -1,
      20,    21,    -1,    23,    24,    25,    26,    27,    28,    29,
      -1,    31,    -1,     9,    10,    35,    12,    13,    -1,    -1,
      16,    -1,    -1,    -1,    20,    21,    -1,    23,    24,    25,
      26,    27,    28,    29,    -1,    31,    -1,     9,    10,    35,
      12,    13,    -1,    -1,    16,    -1,    -1,    -1,    20,    21,
      -1,    -1,    24,    25,    26,    27,    28,    29,    -1,    31,
      -1,     9,    10,    35,    12,    13,    -1,    -1,    16,    -1,
      -1,    -1,    20,    21,    -1,    -1,    24,    25,    26,    27,
      28,    29,    -1,    31,    -1,     9,    10,    35,    12,    13,
      -1,    -1,    16,    -1,    -1,    -1,    20,    21,    -1,    23,
      24,    25,    26,    27,    28,    29,    -1,    31,     9,    10,
      -1,    12,    13,    -1,    -1,    16,    -1,    -1,    -1,    20,
      21,    -1,    23,    24,    25,    26,    27,    28,    29,    -1,
      31,     9,    10,    -1,    12,    13,    -1,    -1,    16,    -1,
      -1,    -1,    20,    21,    -1,    -1,    24,    25,    26,    27,
      28,    29,    -1,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    41,     0,     3,     4,     5,     6,     7,     8,    11,
      14,    15,    17,    19,    22,    30,    32,    33,    34,    36,
      42,    43,    44,    45,    47,    48,    49,    50,    51,    52,
      53,    54,    51,    53,    54,    42,    47,    47,    35,    42,
      47,    42,     9,    10,    12,    13,    16,    20,    21,    24,
      25,    26,    27,    28,    29,    31,    35,    46,    35,    49,
      37,    38,    35,    49,    42,    23,    35,     9,    16,    46,
      35,    47,    42,    18,    23,    35,    23,    35,    47,    47,
      45,    49,    23,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    41,    41,    41,    41,    42,    42,    42,
      42,    42,    42,    43,    44,    45,    45,    45,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    48,    48,    48,    49,    50,    50,
      51,    51,    52,    52,    52,    52,    52,    52,    53,    53,
      54,    54
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     3,     2,     3,     1,     2,     4,
       5,     3,     4,     2,     2,     3,     5,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     3,     4,     4,
       5,     1,     1,     2,     1,     1,     1,     2,     2,     3,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* S: %empty  */
#line 97 "babalang.y"
    {;}
#line 1346 "babalang.tab.c"
    break;

  case 3: /* S: S line  */
#line 98 "babalang.y"
           {executeInstructions((yyvsp[0].line)); free_line((yyvsp[0].line));}
#line 1352 "babalang.tab.c"
    break;

  case 4: /* S: S line T_NL  */
#line 99 "babalang.y"
                {executeInstructions((yyvsp[-1].line)); free_line((yyvsp[-1].line));}
#line 1358 "babalang.tab.c"
    break;

  case 5: /* S: S loop  */
#line 101 "babalang.y"
           {executeInstructions((yyvsp[0].line)); free_line((yyvsp[0].line));}
#line 1364 "babalang.tab.c"
    break;

  case 6: /* S: S loop T_NL  */
#line 102 "babalang.y"
                {executeInstructions((yyvsp[-1].line)); free_line((yyvsp[-1].line));}
#line 1370 "babalang.tab.c"
    break;

  case 7: /* line: token  */
#line 105 "babalang.y"
             {(yyval.line) = new_line(); addNewToken((yyval.line), (yyvsp[0].token)); if ((yyvsp[0].token)->type == IF) addNewToken((yyval.line), token_i(i_if));}
#line 1376 "babalang.tab.c"
    break;

  case 8: /* line: T_CALL token  */
#line 106 "babalang.y"
                    {(yyval.line) = new_line(); addNewToken((yyval.line), (yyvsp[0].token)); addNewToken((yyval.line), token_i(i_call));}
#line 1382 "babalang.tab.c"
    break;

  case 9: /* line: line T_NL instruction token  */
#line 108 "babalang.y"
                                   {(yyval.line) = (yyvsp[-3].line); addNewToken((yyval.line), token_i((yyvsp[-1].intv))); addNewToken((yyval.line), (yyvsp[0].token));}
#line 1388 "babalang.tab.c"
    break;

  case 10: /* line: line T_NL instruction T_NL token  */
#line 109 "babalang.y"
                                        {(yyval.line) = (yyvsp[-4].line); addNewToken((yyval.line), token_i((yyvsp[-2].intv))); addNewToken((yyval.line), (yyvsp[0].token));}
#line 1394 "babalang.tab.c"
    break;

  case 11: /* line: line instruction token  */
#line 110 "babalang.y"
                              {(yyval.line) = (yyvsp[-2].line); addNewToken((yyval.line), token_i((yyvsp[-1].intv))); addNewToken((yyval.line), (yyvsp[0].token));}
#line 1400 "babalang.tab.c"
    break;

  case 12: /* line: line instruction T_NL token  */
#line 111 "babalang.y"
                                   {(yyval.line) = (yyvsp[-3].line); addNewToken((yyval.line), token_i((yyvsp[-2].intv))); addNewToken((yyval.line), (yyvsp[0].token));}
#line 1406 "babalang.tab.c"
    break;

  case 13: /* loop: loop_instr block  */
#line 114 "babalang.y"
                        {(yyval.line) = new_line(); addNewToken((yyval.line), (yyvsp[-1].loop)->token); addNewToken((yyval.line), token_b_loop((yyvsp[0].noun))); addNewToken((yyval.line), token_i((yyvsp[-1].loop)->instruction));}
#line 1412 "babalang.tab.c"
    break;

  case 14: /* loop_instr: T_FOR line  */
#line 118 "babalang.y"
                        {(yyval.loop) = new_loop(token_l((yyvsp[0].line)), i_for);}
#line 1418 "babalang.tab.c"
    break;

  case 15: /* if_statement: T_IF token block  */
#line 121 "babalang.y"
                               {(yyval.IF) = new_if((yyvsp[-1].token), token_b((yyvsp[0].noun)), NULL);}
#line 1424 "babalang.tab.c"
    break;

  case 16: /* if_statement: T_IF token block T_ELSE block  */
#line 122 "babalang.y"
                                            {(yyval.IF) = new_if((yyvsp[-3].token), token_b((yyvsp[-2].noun)), token_if(new_if(token_e(bool_list(true)), token_b((yyvsp[0].noun)), NULL)));}
#line 1430 "babalang.tab.c"
    break;

  case 17: /* if_statement: T_IF token block T_ELSE if_statement  */
#line 123 "babalang.y"
                                                   {(yyval.IF) = new_if((yyvsp[-3].token), token_b((yyvsp[-2].noun)), token_if((yyvsp[0].IF)));}
#line 1436 "babalang.tab.c"
    break;

  case 18: /* instruction: T_IS  */
#line 126 "babalang.y"
                          {(yyval.intv) = i_is;}
#line 1442 "babalang.tab.c"
    break;

  case 19: /* instruction: T_AND  */
#line 127 "babalang.y"
                          {(yyval.intv) = i_and;}
#line 1448 "babalang.tab.c"
    break;

  case 20: /* instruction: T_ADD  */
#line 128 "babalang.y"
                          {(yyval.intv) = i_add;}
#line 1454 "babalang.tab.c"
    break;

  case 21: /* instruction: T_DIV  */
#line 129 "babalang.y"
                          {(yyval.intv) = i_div;}
#line 1460 "babalang.tab.c"
    break;

  case 22: /* instruction: T_MOD  */
#line 130 "babalang.y"
                          {(yyval.intv) = i_mod;}
#line 1466 "babalang.tab.c"
    break;

  case 23: /* instruction: T_SUB  */
#line 131 "babalang.y"
                          {(yyval.intv) = i_sub;}
#line 1472 "babalang.tab.c"
    break;

  case 24: /* instruction: T_MULT  */
#line 132 "babalang.y"
                          {(yyval.intv) = i_mult;}
#line 1478 "babalang.tab.c"
    break;

  case 25: /* instruction: T_SPLIT  */
#line 133 "babalang.y"
                          {(yyval.intv) = i_split;}
#line 1484 "babalang.tab.c"
    break;

  case 26: /* instruction: T_TO  */
#line 134 "babalang.y"
                          {(yyval.intv) = i_to;}
#line 1490 "babalang.tab.c"
    break;

  case 27: /* instruction: T_GET  */
#line 135 "babalang.y"
                          {(yyval.intv) = i_get;}
#line 1496 "babalang.tab.c"
    break;

  case 28: /* instruction: T_MIMIC  */
#line 136 "babalang.y"
                          {(yyval.intv) = i_mimic;}
#line 1502 "babalang.tab.c"
    break;

  case 29: /* instruction: T_OR  */
#line 137 "babalang.y"
                          {(yyval.intv) = i_or;}
#line 1508 "babalang.tab.c"
    break;

  case 30: /* instruction: T_XOR  */
#line 138 "babalang.y"
                          {(yyval.intv) = i_xor;}
#line 1514 "babalang.tab.c"
    break;

  case 31: /* instruction: T_EQUALS  */
#line 139 "babalang.y"
                          {(yyval.intv) = i_eq;}
#line 1520 "babalang.tab.c"
    break;

  case 32: /* instruction: T_AND T_MIMIC  */
#line 140 "babalang.y"
                            {(yyval.intv) = i_and_mimic;}
#line 1526 "babalang.tab.c"
    break;

  case 33: /* instruction: T_AND T_IS  */
#line 141 "babalang.y"
                          {(yyval.intv) = i_and_is;}
#line 1532 "babalang.tab.c"
    break;

  case 34: /* token: var  */
#line 144 "babalang.y"
                                {(yyval.token) = token_v((yyvsp[0].noun));}
#line 1538 "babalang.tab.c"
    break;

  case 35: /* token: primitive  */
#line 145 "babalang.y"
                                {(yyval.token) = token_e((yyvsp[0].list));}
#line 1544 "babalang.tab.c"
    break;

  case 36: /* token: func  */
#line 146 "babalang.y"
                                {(yyval.token) = token_f((yyvsp[0].intv));}
#line 1550 "babalang.tab.c"
    break;

  case 37: /* token: T_BL line T_BR  */
#line 147 "babalang.y"
                                {(yyval.token) = token_l((yyvsp[-1].line));}
#line 1556 "babalang.tab.c"
    break;

  case 38: /* token: T_BL T_NL line T_BR  */
#line 148 "babalang.y"
                                {(yyval.token) = token_l((yyvsp[-1].line));}
#line 1562 "babalang.tab.c"
    break;

  case 39: /* token: T_BL line T_NL T_BR  */
#line 149 "babalang.y"
                                {(yyval.token) = token_l((yyvsp[-2].line));}
#line 1568 "babalang.tab.c"
    break;

  case 40: /* token: T_BL T_NL line T_NL T_BR  */
#line 150 "babalang.y"
                                {(yyval.token) = token_l((yyvsp[-2].line));}
#line 1574 "babalang.tab.c"
    break;

  case 41: /* token: block  */
#line 151 "babalang.y"
                                {(yyval.token) = token_b((yyvsp[0].noun));}
#line 1580 "babalang.tab.c"
    break;

  case 42: /* token: if_statement  */
#line 152 "babalang.y"
                                {(yyval.token) = token_if((yyvsp[0].IF));}
#line 1586 "babalang.tab.c"
    break;

  case 43: /* token: T_NOT token  */
#line 153 "babalang.y"
                                {(yyval.token) = instruction_not((yyvsp[0].token));}
#line 1592 "babalang.tab.c"
    break;

  case 44: /* func: T_DONE  */
#line 156 "babalang.y"
              {(yyval.intv) = f_done;}
#line 1598 "babalang.tab.c"
    break;

  case 45: /* func: T_PRINT  */
#line 157 "babalang.y"
               {(yyval.intv) = f_print;}
#line 1604 "babalang.tab.c"
    break;

  case 46: /* func: T_PRINT_STRUCTURED  */
#line 158 "babalang.y"
                          {(yyval.intv) = f_print_str;}
#line 1610 "babalang.tab.c"
    break;

  case 47: /* block: block_start T_SBR  */
#line 161 "babalang.y"
                          {(yyval.noun) = (yyvsp[-1].noun);}
#line 1616 "babalang.tab.c"
    break;

  case 48: /* block_start: T_SBL line  */
#line 164 "babalang.y"
                         {(yyval.noun) = block_add_line(NULL, (yyvsp[0].line));}
#line 1622 "babalang.tab.c"
    break;

  case 49: /* block_start: block_start T_COMA line  */
#line 165 "babalang.y"
                                      {(yyval.noun) = block_add_line((yyvsp[-2].noun), (yyvsp[0].line));}
#line 1628 "babalang.tab.c"
    break;

  case 51: /* var: T_MINUS var  */
#line 169 "babalang.y"
                  {(yyval.noun) = (yyvsp[0].noun);}
#line 1634 "babalang.tab.c"
    break;

  case 52: /* primitive: int  */
#line 172 "babalang.y"
                {(yyval.list) = int_list((yyvsp[0].intv));}
#line 1640 "babalang.tab.c"
    break;

  case 53: /* primitive: T_STR  */
#line 173 "babalang.y"
                  {(yyval.list) = str_list((yyvsp[0].noun));}
#line 1646 "babalang.tab.c"
    break;

  case 54: /* primitive: float  */
#line 174 "babalang.y"
                  {(yyval.list) = float_list((yyvsp[0].f));}
#line 1652 "babalang.tab.c"
    break;

  case 55: /* primitive: T_BOOL  */
#line 175 "babalang.y"
                   {(yyval.list) = bool_list((yyvsp[0].b));}
#line 1658 "babalang.tab.c"
    break;

  case 56: /* primitive: T_CHAR  */
#line 176 "babalang.y"
                   {(yyval.list) = char_list((yyvsp[0].c));}
#line 1664 "babalang.tab.c"
    break;

  case 57: /* primitive: T_NULL  */
#line 177 "babalang.y"
                   {(yyval.list) = null_list();}
#line 1670 "babalang.tab.c"
    break;

  case 59: /* int: T_MINUS int  */
#line 182 "babalang.y"
                  {(yyval.intv) = -(yyvsp[0].intv);}
#line 1676 "babalang.tab.c"
    break;

  case 61: /* float: T_MINUS float  */
#line 186 "babalang.y"
                      {(yyval.f) = -(yyvsp[0].f);}
#line 1682 "babalang.tab.c"
    break;


#line 1686 "babalang.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 189 "babalang.y"


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
