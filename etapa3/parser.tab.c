/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include <stdio.h>
#include "tree.h"
#include "lexVal.h"
int yylex(void);
extern int get_line_number(void); // avisa que função deve ser lincada e está em outro arquivo
int yyerror (char const *s){
	printf("%s, on line %d\n", s, get_line_number());
	return -1;
}

extern void* arvore;

int parsingSucceded = FALSE;
extern Node *danglingNodes;


#line 84 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_PR_INT = 258,
    TK_PR_FLOAT = 259,
    TK_PR_BOOL = 260,
    TK_PR_CHAR = 261,
    TK_PR_STRING = 262,
    TK_PR_IF = 263,
    TK_PR_THEN = 264,
    TK_PR_ELSE = 265,
    TK_PR_WHILE = 266,
    TK_PR_DO = 267,
    TK_PR_INPUT = 268,
    TK_PR_OUTPUT = 269,
    TK_PR_RETURN = 270,
    TK_PR_CONST = 271,
    TK_PR_STATIC = 272,
    TK_PR_FOREACH = 273,
    TK_PR_FOR = 274,
    TK_PR_SWITCH = 275,
    TK_PR_CASE = 276,
    TK_PR_BREAK = 277,
    TK_PR_CONTINUE = 278,
    TK_PR_CLASS = 279,
    TK_PR_PRIVATE = 280,
    TK_PR_PUBLIC = 281,
    TK_PR_PROTECTED = 282,
    TK_OC_LE = 283,
    TK_OC_GE = 284,
    TK_OC_EQ = 285,
    TK_OC_NE = 286,
    TK_OC_AND = 287,
    TK_OC_OR = 288,
    TK_OC_SL = 289,
    TK_OC_SR = 290,
    TK_OC_FORWARD_PIPE = 291,
    TK_OC_BASH_PIPE = 292,
    TK_LIT_INT = 293,
    TK_LIT_FLOAT = 294,
    TK_LIT_FALSE = 295,
    TK_LIT_TRUE = 296,
    TK_LIT_CHAR = 297,
    TK_LIT_STRING = 298,
    TK_IDENTIFICADOR = 299,
    TOKEN_ERRO = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 21 "parser.y" /* yacc.c:355  */

	struct lexval* valor_lexico;
	struct node* ast;

#line 175 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 192 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   461

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  184
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  312

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,     2,    67,    70,    66,    65,     2,
      49,    50,    59,    55,    46,    56,    69,    60,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    47,
      61,    63,    62,    58,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    51,     2,    52,    68,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,    57,    54,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   164,   164,   165,   168,   169,   174,   178,   187,   193,
     198,   202,   208,   209,   214,   215,   216,   217,   220,   221,
     222,   223,   224,   227,   228,   231,   232,   235,   236,   239,
     240,   241,   242,   243,   244,   249,   256,   263,   264,   271,
     280,   288,   289,   292,   297,   300,   303,   316,   323,   324,
     327,   328,   333,   334,   335,   336,   337,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     358,   369,   370,   373,   385,   399,   409,   421,   422,   429,
     430,   438,   447,   457,   462,   467,   473,   477,   482,   487,
     493,   498,   505,   512,   519,   526,   534,   542,   548,   555,
     563,   571,   578,   585,   592,   599,   605,   613,   617,   621,
     625,   632,   636,   640,   644,   648,   652,   660,   665,   673,
     680,   692,   696,   701,   707,   711,   718,   724,   731,   732,
     739,   740,   743,   744,   746,   751,   758,   766,   779,   783,
     788,   793,   794,   797,   798,   801,   806,   811,   816,   824,
     829,   830,   831,   832,   833,   834,   835,   838,   844,   845,
     850,   858,   859,   860,   861,   862,   863,   864,   865,   868,
     869,   870,   871,   872,   873,   874,   875,   876,   877,   878,
     879,   880,   881,   882,   883
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_PR_INT", "TK_PR_FLOAT", "TK_PR_BOOL",
  "TK_PR_CHAR", "TK_PR_STRING", "TK_PR_IF", "TK_PR_THEN", "TK_PR_ELSE",
  "TK_PR_WHILE", "TK_PR_DO", "TK_PR_INPUT", "TK_PR_OUTPUT", "TK_PR_RETURN",
  "TK_PR_CONST", "TK_PR_STATIC", "TK_PR_FOREACH", "TK_PR_FOR",
  "TK_PR_SWITCH", "TK_PR_CASE", "TK_PR_BREAK", "TK_PR_CONTINUE",
  "TK_PR_CLASS", "TK_PR_PRIVATE", "TK_PR_PUBLIC", "TK_PR_PROTECTED",
  "TK_OC_LE", "TK_OC_GE", "TK_OC_EQ", "TK_OC_NE", "TK_OC_AND", "TK_OC_OR",
  "TK_OC_SL", "TK_OC_SR", "TK_OC_FORWARD_PIPE", "TK_OC_BASH_PIPE",
  "TK_LIT_INT", "TK_LIT_FLOAT", "TK_LIT_FALSE", "TK_LIT_TRUE",
  "TK_LIT_CHAR", "TK_LIT_STRING", "TK_IDENTIFICADOR", "TOKEN_ERRO", "','",
  "';'", "':'", "'('", "')'", "'['", "']'", "'{'", "'}'", "'+'", "'-'",
  "'|'", "'?'", "'*'", "'/'", "'<'", "'>'", "'='", "'!'", "'&'", "'%'",
  "'#'", "'^'", "'.'", "'$'", "$accept", "programa", "componente",
  "depoisDeIdent", "fechaVarOuFunc", "encapsulamento", "tiposPrimitivos",
  "tipo", "static", "tipoConst", "literais", "novoTipo", "listaCampos",
  "list", "campo", "tamanhoVetor", "args", "parameters", "parameter",
  "argsAndCommands", "blocoComandos", "comando", "comandos",
  "comandoSimples", "comandosSemVirgula", "ifThenElse", "optElse",
  "foreach", "for", "while_do", "do_while", "foreachList", "forList",
  "switch", "case", "localVarDefinition", "negativeOrPositiveIdentifier",
  "negativeOrPositiveLiteral", "assignment", "input", "output",
  "continueOutput", "funcCall", "argsCall", "argCall", "shiftOp", "shift",
  "return", "expression", "infiniteQuestionMarks", "pipe",
  "parenthesisOrOperand", "operands", "operators", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,    44,    59,    58,    40,
      41,    91,    93,   123,   125,    43,    45,   124,    63,    42,
      47,    60,    62,    61,    33,    38,    37,    35,    94,    46,
      36
};
# endif

#define YYPACT_NINF -203

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-203)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     143,  -203,  -203,  -203,  -203,  -203,   199,   -41,   134,    14,
     143,   -35,  -203,  -203,  -203,   -24,   -16,   199,    24,     8,
    -203,    20,    39,  -203,  -203,    42,    42,    58,    27,    77,
    -203,   152,  -203,  -203,    75,  -203,  -203,   199,  -203,  -203,
    -203,  -203,  -203,   351,    81,    86,  -203,  -203,   199,  -203,
      85,    92,  -203,    89,  -203,    96,   101,  -203,    58,  -203,
    -203,    99,   152,  -203,  -203,  -203,   100,  -203,  -203,   115,
     116,    99,   336,   336,   336,   214,   194,   120,   121,   127,
     141,  -203,  -203,    19,   138,  -203,   100,   129,   137,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,    60,  -203,  -203,    63,   336,   336,   175,  -203,  -203,
    -203,  -203,  -203,  -203,     9,   336,   336,   336,   336,   336,
     336,   336,    60,  -203,   223,    63,   241,  -203,   142,  -203,
     145,   148,   219,   149,   163,   165,    25,   336,   179,  -203,
    -203,  -203,   272,   336,   336,   167,   336,   185,  -203,  -203,
    -203,   184,   184,   184,   184,   190,   191,   180,   336,   198,
     195,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,   336,  -203,   336,   336,  -203,  -203,
     207,   200,   203,  -203,   229,   213,  -203,    16,    60,   212,
    -203,  -203,  -203,   -31,  -203,  -203,   215,  -203,   -29,  -203,
     366,   217,  -203,  -203,  -203,  -203,   255,   256,   336,   234,
    -203,  -203,  -203,  -203,   142,   373,  -203,   247,   392,   336,
      25,   336,    99,   304,  -203,    91,   336,   336,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,   221,   279,  -203,  -203,  -203,
      99,    99,   237,   220,  -203,  -203,  -203,  -203,  -203,   399,
    -203,  -203,  -203,  -203,   -25,  -203,  -203,   244,  -203,  -203,
     336,   249,   336,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,   284,  -203,  -203,   260,  -203,
    -203,  -203,  -203,   336,    99,    25,  -203,    17,  -203,    99,
    -203,  -203,  -203,  -203,    15,   336,   336,  -203,    99,  -203,
    -203,  -203
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    18,    19,    20,    21,    22,     0,     0,     0,     0,
       2,     0,     4,    24,    23,     0,     0,     0,     0,     0,
       5,     0,    26,     1,     3,     0,     0,    14,     0,     0,
      12,    41,    11,    13,     0,    10,    25,     0,     6,     7,
      15,    16,    17,     0,     0,    37,    35,     9,     0,    28,
       0,     0,    42,    44,    40,     0,     0,    36,    14,    27,
      45,     0,     0,     8,    39,    38,    50,    46,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    62,     0,     0,    69,    50,     0,     0,    52,
      64,    55,    56,    65,    66,    67,    49,    57,    58,    59,
      53,    54,    60,    63,    68,     0,     0,     0,   161,   162,
     164,   163,   165,   166,   158,     0,     0,     0,     0,     0,
       0,     0,   167,   121,   142,   168,   141,   150,   123,   138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   132,
     133,    86,     0,     0,     0,     0,     0,    90,    51,    47,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   152,   151,   154,   153,   155,   156,   182,   181,   179,
     180,   175,   176,   169,   170,   177,   144,   171,   172,   183,
     184,   178,   173,   174,     0,   143,     0,     0,   122,    84,
      88,     0,     0,    83,    87,     0,    79,     0,     0,     0,
      82,   127,   131,     0,   128,   130,     0,   117,     0,   134,
       0,     0,   145,   147,   146,   148,     0,     0,     0,     0,
     159,   149,   140,   139,   124,     0,    85,    89,     0,     0,
       0,     0,     0,     0,   126,     0,     0,     0,    29,    30,
      31,    32,    33,    34,    97,     0,     0,   105,    98,   106,
       0,     0,     0,   157,   125,    93,   103,    94,   104,     0,
      91,   101,    92,   102,     0,    77,    80,     0,    81,   129,
       0,     0,     0,   119,   135,   115,   116,   110,   109,   114,
     112,   113,   108,   107,   111,    71,    75,    76,     0,    95,
      99,    96,   100,     0,     0,     0,   118,     0,   136,     0,
      70,   160,    78,    73,     0,     0,     0,    72,     0,   120,
     137,    74
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -203,   295,  -203,  -203,  -203,  -203,     0,     7,  -203,  -203,
    -202,  -203,  -203,   250,  -203,  -203,  -203,   257,  -203,    84,
     -60,  -203,   238,  -203,  -132,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,    30,  -203,  -203,  -203,   -51,   -13,  -203,  -203,
    -203,   102,   -59,  -203,    87,  -196,  -203,  -203,   -56,  -203,
     -64,   340,  -203,   204
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    20,    32,    43,    14,    49,    37,    50,
     247,    12,    28,    44,    45,    22,    51,    52,    53,    33,
      85,    86,    87,    88,    89,    90,   300,    91,    92,    93,
      94,   264,   197,    95,    96,    97,   248,   249,    98,    99,
     100,   188,   122,   203,   204,   146,   102,   103,   205,   124,
     125,   126,   127,   184
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      11,    67,   104,    16,   196,   139,   140,   101,    21,    25,
      11,   107,   237,    15,    23,   233,   123,   128,   129,   234,
      26,   293,   104,   256,    29,   294,   261,   101,     1,     2,
       3,     4,     5,    69,   236,    27,    70,    71,    72,   272,
      74,    75,    76,    56,    55,    79,    34,    81,    82,   155,
     156,   139,   140,   139,   140,    59,    36,   290,   142,   160,
     158,   230,   230,   141,   231,   308,    84,    35,   142,    83,
     143,    30,   104,    31,    46,   131,   134,   198,    66,   159,
     305,   199,   144,    40,    41,    42,    84,   206,   207,   145,
     209,    31,   212,   213,   214,   215,   151,   152,   266,   153,
     154,   306,   219,     1,     2,     3,     4,     5,    69,    38,
      39,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    47,   139,   140,    54,   222,    60,
     223,   224,   192,    57,    58,    62,    84,     1,     2,     3,
       4,     5,    61,    63,    83,    64,     1,     2,     3,     4,
       5,    17,    66,    66,   270,     1,     2,     3,     4,     5,
       6,   271,   252,   196,   105,   106,   104,     7,    48,   135,
     136,   198,   268,   265,   257,   267,   137,   262,    18,   138,
     273,   274,   147,   149,   150,    19,   157,     8,   187,   189,
     285,   286,   190,   193,   278,   283,    13,     1,     2,     3,
       4,     5,     1,     2,     3,     4,     5,   194,   291,   195,
     132,   208,   258,   210,   296,   263,   298,     1,     2,     3,
       4,     5,     1,     2,     3,     4,     5,   200,   211,   218,
      84,   104,   279,   284,   303,   225,   198,   302,   133,   307,
     216,   217,   220,    13,   226,   221,   292,   227,   311,   309,
     310,   167,   168,   169,   170,   171,   172,   228,   130,   275,
     276,   229,   232,   191,   250,   277,   142,   235,   251,   167,
     168,   169,   170,   171,   172,   259,   245,   246,   173,   174,
     175,   176,   177,   178,   179,   180,   253,   287,   181,   182,
     288,   183,   295,   297,   299,    84,   173,   174,   175,   185,
     177,   178,   179,   180,   301,    24,   181,   182,    65,   183,
     108,   109,   110,   111,   112,   113,   114,   280,   281,    68,
     269,   115,   201,   282,   148,   304,   254,   116,   117,     0,
     186,   118,     0,     0,   245,   246,   119,   120,     0,   121,
       0,   202,   108,   109,   110,   111,   112,   113,   114,     0,
       0,     0,     0,   115,     1,     2,     3,     4,     5,   116,
     117,     0,     0,   118,     0,     0,     0,     0,   119,   120,
       0,   121,     0,   202,   108,   109,   110,   111,   112,   113,
     114,     0,     0,     0,     0,   115,     0,     0,     0,     0,
       0,   116,   117,     0,     0,   118,     0,     0,     0,     0,
     119,   120,     0,   121,   238,   239,   240,   241,   242,   243,
     244,   238,   239,   240,   241,   242,   243,   255,     0,     0,
       0,   245,   246,     0,     0,     0,     0,     0,   245,   246,
     238,   239,   240,   241,   242,   243,   260,   238,   239,   240,
     241,   242,   243,   289,     0,     0,     0,   245,   246,     0,
       0,     0,     0,     0,   245,   246,   161,   162,   163,   164,
     165,   166
};

static const yytype_int16 yycheck[] =
{
       0,    61,    66,    44,   136,    34,    35,    66,     8,    44,
      10,    71,   208,     6,     0,    46,    72,    73,    74,    50,
      44,    46,    86,   225,    17,    50,   228,    86,     3,     4,
       5,     6,     7,     8,    63,    51,    11,    12,    13,   235,
      15,    16,    17,    43,    37,    20,    38,    22,    23,   105,
     106,    34,    35,    34,    35,    48,    17,   259,    49,   115,
      51,    46,    46,    44,    48,    50,    66,    47,    49,    44,
      51,    47,   136,    49,    47,    75,    76,   136,    53,    70,
      63,   137,    63,    25,    26,    27,    86,   143,   144,    70,
     146,    49,   151,   152,   153,   154,    36,    37,   230,    36,
      37,   297,   158,     3,     4,     5,     6,     7,     8,    25,
      26,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    47,    34,    35,    52,   184,    44,
     186,   187,   132,    52,    48,    46,   136,     3,     4,     5,
       6,     7,    50,    47,    44,    44,     3,     4,     5,     6,
       7,    17,    53,    53,    63,     3,     4,     5,     6,     7,
      17,    70,   218,   295,    49,    49,   230,    24,    16,    49,
      49,   230,   232,   229,   225,   231,    49,   228,    44,    38,
     236,   237,    44,    54,    47,    51,    11,    44,    46,    44,
     250,   251,    44,    44,   245,   246,    44,     3,     4,     5,
       6,     7,     3,     4,     5,     6,     7,    44,   259,    44,
      16,    44,   225,    28,   270,   228,   272,     3,     4,     5,
       6,     7,     3,     4,     5,     6,     7,    48,    44,    49,
     230,   295,   245,   246,   294,    28,   295,   293,    44,   299,
      50,    50,    44,    44,    44,    50,   259,    44,   308,   305,
     306,    28,    29,    30,    31,    32,    33,    28,    44,    38,
      39,    48,    50,    44,     9,    44,    49,    52,    12,    28,
      29,    30,    31,    32,    33,    28,    55,    56,    55,    56,
      57,    58,    59,    60,    61,    62,    52,    50,    65,    66,
      70,    68,    48,    44,    10,   295,    55,    56,    57,    58,
      59,    60,    61,    62,    44,    10,    65,    66,    58,    68,
      38,    39,    40,    41,    42,    43,    44,    38,    39,    62,
     233,    49,    50,    44,    86,   295,   224,    55,    56,    -1,
     126,    59,    -1,    -1,    55,    56,    64,    65,    -1,    67,
      -1,    69,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,     3,     4,     5,     6,     7,    55,
      56,    -1,    -1,    59,    -1,    -1,    -1,    -1,    64,    65,
      -1,    67,    -1,    69,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    55,    56,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      64,    65,    -1,    67,    38,    39,    40,    41,    42,    43,
      44,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    55,    56,
      38,    39,    40,    41,    42,    43,    44,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    55,    56,    -1,
      -1,    -1,    -1,    -1,    55,    56,   116,   117,   118,   119,
     120,   121
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    17,    24,    44,    72,
      73,    77,    82,    44,    77,    78,    44,    17,    44,    51,
      74,    77,    86,     0,    72,    44,    44,    51,    83,    78,
      47,    49,    75,    90,    38,    47,    17,    79,    90,    90,
      25,    26,    27,    76,    84,    85,    47,    47,    16,    78,
      80,    87,    88,    89,    52,    78,    77,    52,    48,    78,
      44,    50,    46,    47,    44,    84,    53,    91,    88,     8,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    44,    77,    91,    92,    93,    94,    95,
      96,    98,    99,   100,   101,   104,   105,   106,   109,   110,
     111,   113,   117,   118,   121,    49,    49,    91,    38,    39,
      40,    41,    42,    43,    44,    49,    55,    56,    59,    64,
      65,    67,   113,   119,   120,   121,   122,   123,   119,   119,
      44,    77,    16,    44,    77,    49,    49,    49,    38,    34,
      35,    44,    49,    51,    63,    70,   116,    44,    93,    54,
      47,    36,    37,    36,    37,   119,   119,    11,    51,    70,
     119,   122,   122,   122,   122,   122,   122,    28,    29,    30,
      31,    32,    33,    55,    56,    57,    58,    59,    60,    61,
      62,    65,    66,    68,   124,    58,   124,    46,   112,    44,
      44,    44,    77,    44,    44,    44,    95,   103,   113,   119,
      48,    50,    69,   114,   115,   119,   119,   119,    44,   119,
      28,    44,   113,   113,   113,   113,    50,    50,    49,   119,
      44,    50,   119,   119,   119,    28,    44,    44,    28,    48,
      46,    48,    50,    46,    50,    52,    63,   116,    38,    39,
      40,    41,    42,    43,    44,    55,    56,    81,   107,   108,
       9,    12,   119,    52,   112,    44,    81,   107,   108,    28,
      44,    81,   107,   108,   102,   119,    95,   119,    91,   115,
      63,    70,   116,   119,   119,    38,    39,    44,   107,   108,
      38,    39,    44,   107,   108,    91,    91,    50,    70,    44,
      81,   107,   108,    46,    50,    48,   119,    44,   119,    10,
      97,    44,   119,    91,   103,    63,   116,    91,    50,   119,
     119,    91
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    72,    73,    73,    73,    73,    74,    74,
      74,    74,    75,    75,    76,    76,    76,    76,    77,    77,
      77,    77,    77,    78,    78,    79,    79,    80,    80,    81,
      81,    81,    81,    81,    81,    82,    83,    84,    84,    85,
      86,    87,    87,    88,    88,    89,    90,    91,    92,    92,
      93,    93,    94,    94,    94,    94,    94,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      96,    97,    97,    98,    99,   100,   101,   102,   102,   103,
     103,   104,   105,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   107,   107,   107,
     107,   108,   108,   108,   108,   108,   108,   109,   109,   109,
     109,   110,   111,   111,   112,   112,   113,   113,   114,   114,
     115,   115,   116,   116,   117,   117,   117,   117,   118,   119,
     119,   119,   119,   120,   120,   121,   121,   121,   121,   122,
     122,   122,   122,   122,   122,   122,   122,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     3,     4,     4,     3,
       2,     2,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     1,     3,     3,
       3,     0,     1,     3,     1,     2,     4,     3,     2,     1,
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       7,     0,     2,     7,     9,     6,     6,     1,     3,     1,
       3,     5,     3,     3,     3,     4,     2,     3,     3,     4,
       2,     5,     5,     5,     5,     6,     6,     4,     4,     6,
       6,     5,     5,     5,     5,     4,     4,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     3,     6,     5,
       8,     2,     3,     2,     2,     3,     4,     3,     1,     3,
       1,     1,     1,     1,     3,     5,     6,     8,     2,     3,
       3,     1,     1,     2,     2,     3,     3,     3,     3,     3,
       1,     2,     2,     2,     2,     2,     2,     4,     1,     3,
       6,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 3: /* TK_PR_INT  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1295 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 4: /* TK_PR_FLOAT  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1309 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 5: /* TK_PR_BOOL  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1323 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 6: /* TK_PR_CHAR  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1337 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 7: /* TK_PR_STRING  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1351 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 8: /* TK_PR_IF  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1365 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 9: /* TK_PR_THEN  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1379 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 10: /* TK_PR_ELSE  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1393 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 11: /* TK_PR_WHILE  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1407 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 12: /* TK_PR_DO  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1421 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 13: /* TK_PR_INPUT  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1435 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 14: /* TK_PR_OUTPUT  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1449 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 15: /* TK_PR_RETURN  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1463 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 16: /* TK_PR_CONST  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1477 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 17: /* TK_PR_STATIC  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1491 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 18: /* TK_PR_FOREACH  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1505 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 19: /* TK_PR_FOR  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1519 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 20: /* TK_PR_SWITCH  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1533 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 21: /* TK_PR_CASE  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1547 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 22: /* TK_PR_BREAK  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1561 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 23: /* TK_PR_CONTINUE  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1575 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 24: /* TK_PR_CLASS  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1589 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 25: /* TK_PR_PRIVATE  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1603 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 26: /* TK_PR_PUBLIC  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1617 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 27: /* TK_PR_PROTECTED  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1631 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 28: /* TK_OC_LE  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1645 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 29: /* TK_OC_GE  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1659 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 30: /* TK_OC_EQ  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1673 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 31: /* TK_OC_NE  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1687 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 32: /* TK_OC_AND  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1701 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 33: /* TK_OC_OR  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1715 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 34: /* TK_OC_SL  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1729 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 35: /* TK_OC_SR  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1743 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 36: /* TK_OC_FORWARD_PIPE  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1757 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 37: /* TK_OC_BASH_PIPE  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1771 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 38: /* TK_LIT_INT  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1785 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 39: /* TK_LIT_FLOAT  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1799 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 40: /* TK_LIT_FALSE  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1813 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 41: /* TK_LIT_TRUE  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1827 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 42: /* TK_LIT_CHAR  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1841 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 43: /* TK_LIT_STRING  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1855 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 44: /* TK_IDENTIFICADOR  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1869 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 45: /* TOKEN_ERRO  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1883 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 46: /* ','  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1897 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 47: /* ';'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1911 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 48: /* ':'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1925 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 49: /* '('  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1939 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 50: /* ')'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1953 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 51: /* '['  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1967 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 52: /* ']'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1981 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 53: /* '{'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1995 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 54: /* '}'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2009 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 55: /* '+'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2023 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 56: /* '-'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2037 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 57: /* '|'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2051 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 58: /* '?'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2065 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 59: /* '*'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2079 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 60: /* '/'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2093 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 61: /* '<'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2107 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 62: /* '>'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2121 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 63: /* '='  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2135 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 64: /* '!'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2149 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 65: /* '&'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2163 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 66: /* '%'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2177 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 67: /* '#'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2191 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 68: /* '^'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2205 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 69: /* '.'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2219 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 70: /* '$'  */
#line 130 "parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2233 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 72: /* programa  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2243 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 73: /* componente  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2253 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 74: /* depoisDeIdent  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2263 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 75: /* fechaVarOuFunc  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2273 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 76: /* encapsulamento  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2283 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 77: /* tiposPrimitivos  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2293 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 78: /* tipo  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2303 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 79: /* static  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2313 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 80: /* tipoConst  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2323 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 81: /* literais  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2333 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 82: /* novoTipo  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2343 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 83: /* listaCampos  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2353 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 84: /* list  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2363 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 85: /* campo  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2373 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 86: /* tamanhoVetor  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2383 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 87: /* args  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2393 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 88: /* parameters  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2403 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 89: /* parameter  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2413 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 90: /* argsAndCommands  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2423 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 91: /* blocoComandos  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2433 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 92: /* comando  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2443 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 93: /* comandos  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2453 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 94: /* comandoSimples  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2463 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 95: /* comandosSemVirgula  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2473 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 96: /* ifThenElse  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2483 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 97: /* optElse  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2493 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 98: /* foreach  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2503 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 99: /* for  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2513 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 100: /* while_do  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2523 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 101: /* do_while  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2533 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 102: /* foreachList  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2543 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 103: /* forList  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2553 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 104: /* switch  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2563 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 105: /* case  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2573 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 106: /* localVarDefinition  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2583 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 107: /* negativeOrPositiveIdentifier  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2593 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 108: /* negativeOrPositiveLiteral  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2603 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 109: /* assignment  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2613 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 110: /* input  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2623 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 111: /* output  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2633 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 112: /* continueOutput  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2643 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 113: /* funcCall  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2653 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 114: /* argsCall  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2663 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 115: /* argCall  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2673 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 116: /* shiftOp  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2683 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 117: /* shift  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2693 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 118: /* return  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2703 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 119: /* expression  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2713 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 120: /* infiniteQuestionMarks  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2723 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 121: /* pipe  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2733 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 122: /* parenthesisOrOperand  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2743 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 123: /* operands  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2753 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 124: /* operators  */
#line 139 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2763 "parser.tab.c" /* yacc.c:1257  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 164 "parser.y" /* yacc.c:1646  */
    {parsingSucceded = TRUE; (yyval.ast) = criaNodo(NULL); arvore = (yyval.ast);}
#line 3027 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 165 "parser.y" /* yacc.c:1646  */
    {parsingSucceded = TRUE; (yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast)); arvore = (yyval.ast);}
#line 3033 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 168 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3039 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 169 "parser.y" /* yacc.c:1646  */
    { // Regra introduzida para resolver conflitos
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3048 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 174 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3057 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 178 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3068 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 187 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3079 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 193 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3089 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 198 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3098 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 202 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3107 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 208 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3113 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 209 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3119 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 214 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3125 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 215 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3131 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 216 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3137 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 217 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3143 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 220 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3149 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 221 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3155 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 222 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3161 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 223 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3167 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 224 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3173 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 227 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3179 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 228 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3185 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 231 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3191 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 232 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3197 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 235 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3203 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 236 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3209 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 239 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3215 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 240 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3221 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 241 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3227 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 242 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3233 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 243 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3239 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 244 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3245 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 249 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3256 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 256 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3266 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 263 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3272 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 264 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3282 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 271 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3292 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 280 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3302 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 288 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3308 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 289 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3314 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 292 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3324 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 297 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3330 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 300 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 3336 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 303 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3347 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 316 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3357 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 323 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 3363 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 324 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3369 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 327 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3375 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 328 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3381 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 333 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3387 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 334 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3393 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 335 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3399 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 336 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3405 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 337 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3411 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 342 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3417 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 343 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3423 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 344 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3429 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 345 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3435 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 346 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3441 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 347 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3447 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 348 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3453 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 349 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3459 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 350 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3465 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 351 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3471 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 352 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3477 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 353 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3483 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 354 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3489 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 358 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-6].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-5].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-4].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3503 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 369 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3509 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 370 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3515 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 373 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-6].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-5].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3529 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 385 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-8].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-7].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-6].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-5].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-4].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3545 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 399 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3558 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 409 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-4].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3571 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 421 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3577 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 422 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3587 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 429 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 430 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3603 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 438 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3615 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 447 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3625 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 457 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3635 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 462 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3645 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 467 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3656 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 473 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3665 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 477 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3675 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 482 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3685 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 487 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3696 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 493 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3705 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 498 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3717 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 505 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3729 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 512 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3741 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 519 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3753 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 526 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3766 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 534 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3779 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 542 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3790 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 548 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3801 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 555 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3814 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 563 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 571 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3839 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 578 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3851 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 585 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3863 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 592 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3875 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 599 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3886 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 605 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3897 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 613 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3906 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 617 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3915 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 621 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3924 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 625 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3933 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 632 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3942 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 636 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3951 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 640 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3960 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 644 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3969 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 648 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3978 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 652 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3987 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 660 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3997 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 665 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4010 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 673 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4022 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 680 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-7].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-6].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-5].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4037 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 692 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4043 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 696 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4053 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 701 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4062 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 707 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4071 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 711 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4081 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 718 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4092 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 724 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4102 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 731 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4108 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 732 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4118 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 739 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4124 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 740 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4130 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 743 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4136 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 744 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4142 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 746 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4152 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 751 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico)));
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4164 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 758 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico)));
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast));
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4177 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 766 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-7].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-6].valor_lexico)));
		adicionaFilho((yyval.ast), (yyvsp[-5].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4192 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 779 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4198 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 783 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4208 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 788 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4218 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 793 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4224 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 794 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4230 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 797 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 4236 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 798 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 4242 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 801 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4252 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 806 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4262 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 811 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4272 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 816 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4282 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 824 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4292 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 829 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4298 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 830 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4304 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 831 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4310 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 832 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4316 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 833 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4322 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 834 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4328 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 835 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4334 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 838 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4345 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 844 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4351 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 845 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4361 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 850 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4374 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 858 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4380 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 859 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4386 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 860 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4392 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 861 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4398 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 862 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4404 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 863 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4410 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 864 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4416 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 865 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4422 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 868 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4428 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 869 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4434 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 870 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4440 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 871 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4446 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 872 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4452 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 873 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4458 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 874 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4464 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 875 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4470 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 876 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4476 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 877 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4482 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 878 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4488 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 879 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4494 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 880 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4500 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 881 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4506 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 882 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4512 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 883 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4518 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 4522 "parser.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 886 "parser.y" /* yacc.c:1906  */



