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
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   463

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  185
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  313

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
       0,   165,   165,   169,   170,   173,   174,   179,   183,   192,
     198,   203,   207,   213,   214,   219,   220,   221,   222,   225,
     226,   227,   228,   229,   232,   233,   236,   237,   240,   241,
     244,   245,   246,   247,   248,   249,   254,   261,   268,   269,
     276,   285,   293,   294,   297,   302,   305,   308,   321,   328,
     329,   332,   333,   338,   339,   340,   341,   342,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   363,   374,   375,   378,   390,   404,   414,   426,   427,
     434,   435,   443,   452,   462,   467,   472,   478,   482,   487,
     492,   498,   503,   510,   517,   524,   531,   539,   547,   553,
     560,   568,   576,   583,   590,   597,   604,   610,   618,   622,
     626,   630,   637,   641,   645,   649,   653,   657,   665,   670,
     678,   685,   697,   701,   706,   712,   716,   723,   729,   736,
     737,   744,   745,   748,   749,   751,   756,   763,   771,   784,
     788,   793,   798,   799,   802,   803,   806,   811,   816,   821,
     829,   834,   835,   836,   837,   838,   839,   840,   843,   849,
     850,   855,   863,   864,   865,   866,   867,   868,   869,   870,
     873,   874,   875,   876,   877,   878,   879,   880,   881,   882,
     883,   884,   885,   886,   887,   888
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
  "'#'", "'^'", "'.'", "'$'", "$accept", "programa", "componentes",
  "componente", "depoisDeIdent", "fechaVarOuFunc", "encapsulamento",
  "tiposPrimitivos", "tipo", "static", "tipoConst", "literais", "novoTipo",
  "listaCampos", "list", "campo", "tamanhoVetor", "args", "parameters",
  "parameter", "argsAndCommands", "blocoComandos", "comando", "comandos",
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

#define YYPACT_NINF -206

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-206)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      35,  -206,  -206,  -206,  -206,  -206,   180,   -15,    19,    43,
    -206,    35,   -12,  -206,  -206,  -206,     4,    18,   180,    26,
      34,  -206,    45,    85,  -206,  -206,    76,    76,    59,    79,
      80,  -206,    50,  -206,  -206,    78,  -206,  -206,   180,  -206,
    -206,  -206,  -206,  -206,   353,    82,    87,  -206,  -206,   180,
    -206,    84,    86,  -206,    98,  -206,   102,   109,  -206,    59,
    -206,  -206,   103,    50,  -206,  -206,  -206,   101,  -206,  -206,
     110,   111,   103,   338,   338,   338,   190,   164,   112,   115,
     117,   134,  -206,  -206,   258,   131,  -206,   101,   124,   142,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,    28,  -206,  -206,    74,   338,   338,   179,  -206,
    -206,  -206,  -206,  -206,  -206,   -21,   338,   338,   338,   338,
     338,   338,   338,    28,  -206,   215,    74,   229,  -206,   166,
    -206,   169,   170,   195,   172,   174,   175,   135,   338,   177,
    -206,  -206,  -206,   274,   338,   338,   182,   338,   201,  -206,
    -206,  -206,   188,   188,   188,   188,   187,   202,   206,   338,
     212,   213,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,   338,  -206,   338,   338,  -206,
    -206,   236,   221,   222,  -206,   240,   230,  -206,    32,    28,
     219,  -206,  -206,  -206,   -41,  -206,  -206,   227,  -206,   -28,
    -206,   368,   233,  -206,  -206,  -206,  -206,   289,   287,   338,
     248,  -206,  -206,  -206,  -206,   166,   375,  -206,   273,   394,
     338,   135,   338,   103,   306,  -206,    11,   338,   338,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,   165,   167,  -206,  -206,
    -206,   103,   103,   253,   234,  -206,  -206,  -206,  -206,  -206,
     401,  -206,  -206,  -206,  -206,   -36,  -206,  -206,   257,  -206,
    -206,   338,   262,   338,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,   298,  -206,  -206,   266,
    -206,  -206,  -206,  -206,   338,   103,   135,  -206,    27,  -206,
     103,  -206,  -206,  -206,  -206,   -30,   338,   338,  -206,   103,
    -206,  -206,  -206
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    19,    20,    21,    22,    23,     0,     0,     0,     0,
       2,     3,     0,     5,    25,    24,     0,     0,     0,     0,
       0,     6,     0,    27,     1,     4,     0,     0,    15,     0,
       0,    13,    42,    12,    14,     0,    11,    26,     0,     7,
       8,    16,    17,    18,     0,     0,    38,    36,    10,     0,
      29,     0,     0,    43,    45,    41,     0,     0,    37,    15,
      28,    46,     0,     0,     9,    40,    39,    51,    47,    44,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    62,    63,     0,     0,    70,    51,     0,     0,
      53,    65,    56,    57,    66,    67,    68,    50,    58,    59,
      60,    54,    55,    61,    64,    69,     0,     0,     0,   162,
     163,   165,   164,   166,   167,   159,     0,     0,     0,     0,
       0,     0,     0,   168,   122,   143,   169,   142,   151,   124,
     139,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     133,   134,    87,     0,     0,     0,     0,     0,    91,    52,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   153,   152,   155,   154,   156,   157,   183,   182,
     180,   181,   176,   177,   170,   171,   178,   145,   172,   173,
     184,   185,   179,   174,   175,     0,   144,     0,     0,   123,
      85,    89,     0,     0,    84,    88,     0,    80,     0,     0,
       0,    83,   128,   132,     0,   129,   131,     0,   118,     0,
     135,     0,     0,   146,   148,   147,   149,     0,     0,     0,
       0,   160,   150,   141,   140,   125,     0,    86,    90,     0,
       0,     0,     0,     0,     0,   127,     0,     0,     0,    30,
      31,    32,    33,    34,    35,    98,     0,     0,   106,    99,
     107,     0,     0,     0,   158,   126,    94,   104,    95,   105,
       0,    92,   102,    93,   103,     0,    78,    81,     0,    82,
     130,     0,     0,     0,   120,   136,   116,   117,   111,   110,
     115,   113,   114,   109,   108,   112,    72,    76,    77,     0,
      96,   100,    97,   101,     0,     0,     0,   119,     0,   137,
       0,    71,   161,    79,    74,     0,     0,     0,    73,     0,
     121,   138,    75
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -206,  -206,   300,  -206,  -206,  -206,  -206,     0,     9,  -206,
    -206,  -192,  -206,  -206,   260,  -206,  -206,  -206,   259,  -206,
      69,   -60,  -206,   238,  -206,  -134,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,    24,  -206,  -206,  -206,   -19,     7,  -206,
    -206,  -206,   106,   -54,  -206,    92,  -205,  -206,  -206,   -56,
    -206,   -66,   341,  -206,   200
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    21,    33,    44,    15,    50,    38,
      51,   248,    13,    29,    45,    46,    23,    52,    53,    54,
      34,    86,    87,    88,    89,    90,    91,   301,    92,    93,
      94,    95,   265,   198,    96,    97,    98,   249,   250,    99,
     100,   101,   189,   123,   204,   205,   147,   103,   104,   206,
     125,   126,   127,   128,   185
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      12,   105,    68,   197,   238,   234,   140,   141,    22,   235,
     294,    12,   108,   102,   295,    16,   231,   124,   129,   130,
     309,   105,     1,     2,     3,     4,     5,    30,   143,    17,
     159,   273,    26,   102,   257,   237,    18,   262,     1,     2,
       3,     4,     5,    24,    57,   140,   141,    56,    27,   160,
     156,   157,     6,     1,     2,     3,     4,     5,    60,     7,
     161,   140,   141,    19,   152,   153,    49,    85,   291,    28,
      20,   105,    35,    31,   271,    32,   132,   135,   231,     8,
     232,   272,   200,   199,    41,    42,    43,    85,   207,   208,
     306,   210,    36,   307,    14,    39,    40,   267,   213,   214,
     215,   216,    37,   220,     1,     2,     3,     4,     5,    70,
     154,   155,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    32,    47,    48,    61,   223,
      55,   224,   225,   193,    58,    59,    62,    85,     1,     2,
       3,     4,     5,    70,    63,    84,    71,    72,    73,    64,
      75,    76,    77,    65,    67,    80,    67,    82,    83,   106,
     107,   136,   197,   253,   137,   105,   138,     1,     2,     3,
       4,     5,   139,   269,   266,   148,   268,   199,   150,    84,
     133,   274,   275,     1,     2,     3,     4,     5,    67,   151,
     158,   286,   287,     1,     2,     3,     4,     5,     1,     2,
       3,     4,     5,   276,   277,   281,   282,   258,   134,   278,
     263,   283,   188,   190,   191,   297,   194,   299,   195,   196,
     246,   247,   246,   247,    14,   201,   209,   279,   284,   211,
     105,    85,   212,   259,   131,   304,   264,   217,   303,   192,
     308,   292,   199,   168,   169,   170,   171,   172,   173,   312,
     310,   311,   218,   280,   285,   219,   221,   168,   169,   170,
     171,   172,   173,   222,   226,   227,   228,   293,   229,   233,
     174,   175,   176,   177,   178,   179,   180,   181,   230,   236,
     182,   183,   143,   184,   174,   175,   176,   186,   178,   179,
     180,   181,   140,   141,   182,   183,    85,   184,   251,   252,
     254,   260,   142,   288,   289,   296,   298,   143,   300,   144,
     302,    25,   109,   110,   111,   112,   113,   114,   115,    66,
     305,   145,    69,   116,   202,   149,   270,   187,   146,   117,
     118,   255,     0,   119,     0,     0,     0,     0,   120,   121,
       0,   122,     0,   203,   109,   110,   111,   112,   113,   114,
     115,     0,     0,     0,     0,   116,     1,     2,     3,     4,
       5,   117,   118,     0,     0,   119,     0,     0,     0,     0,
     120,   121,     0,   122,     0,   203,   109,   110,   111,   112,
     113,   114,   115,     0,     0,     0,     0,   116,     0,     0,
       0,     0,     0,   117,   118,     0,     0,   119,     0,     0,
       0,     0,   120,   121,     0,   122,   239,   240,   241,   242,
     243,   244,   245,   239,   240,   241,   242,   243,   244,   256,
       0,     0,     0,   246,   247,     0,     0,     0,     0,     0,
     246,   247,   239,   240,   241,   242,   243,   244,   261,   239,
     240,   241,   242,   243,   244,   290,     0,     0,     0,   246,
     247,     0,     0,     0,     0,     0,   246,   247,   162,   163,
     164,   165,   166,   167
};

static const yytype_int16 yycheck[] =
{
       0,    67,    62,   137,   209,    46,    34,    35,     8,    50,
      46,    11,    72,    67,    50,     6,    46,    73,    74,    75,
      50,    87,     3,     4,     5,     6,     7,    18,    49,    44,
      51,   236,    44,    87,   226,    63,    17,   229,     3,     4,
       5,     6,     7,     0,    44,    34,    35,    38,    44,    70,
     106,   107,    17,     3,     4,     5,     6,     7,    49,    24,
     116,    34,    35,    44,    36,    37,    16,    67,   260,    51,
      51,   137,    38,    47,    63,    49,    76,    77,    46,    44,
      48,    70,   138,   137,    25,    26,    27,    87,   144,   145,
      63,   147,    47,   298,    44,    26,    27,   231,   152,   153,
     154,   155,    17,   159,     3,     4,     5,     6,     7,     8,
      36,    37,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    49,    47,    47,    44,   185,
      52,   187,   188,   133,    52,    48,    50,   137,     3,     4,
       5,     6,     7,     8,    46,    44,    11,    12,    13,    47,
      15,    16,    17,    44,    53,    20,    53,    22,    23,    49,
      49,    49,   296,   219,    49,   231,    49,     3,     4,     5,
       6,     7,    38,   233,   230,    44,   232,   231,    54,    44,
      16,   237,   238,     3,     4,     5,     6,     7,    53,    47,
      11,   251,   252,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,    38,    39,    38,    39,   226,    44,    44,
     229,    44,    46,    44,    44,   271,    44,   273,    44,    44,
      55,    56,    55,    56,    44,    48,    44,   246,   247,    28,
     296,   231,    44,   226,    44,   295,   229,    50,   294,    44,
     300,   260,   296,    28,    29,    30,    31,    32,    33,   309,
     306,   307,    50,   246,   247,    49,    44,    28,    29,    30,
      31,    32,    33,    50,    28,    44,    44,   260,    28,    50,
      55,    56,    57,    58,    59,    60,    61,    62,    48,    52,
      65,    66,    49,    68,    55,    56,    57,    58,    59,    60,
      61,    62,    34,    35,    65,    66,   296,    68,     9,    12,
      52,    28,    44,    50,    70,    48,    44,    49,    10,    51,
      44,    11,    38,    39,    40,    41,    42,    43,    44,    59,
     296,    63,    63,    49,    50,    87,   234,   127,    70,    55,
      56,   225,    -1,    59,    -1,    -1,    -1,    -1,    64,    65,
      -1,    67,    -1,    69,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    49,     3,     4,     5,     6,
       7,    55,    56,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      64,    65,    -1,    67,    -1,    69,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    55,    56,    -1,    -1,    59,    -1,    -1,
      -1,    -1,    64,    65,    -1,    67,    38,    39,    40,    41,
      42,    43,    44,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,
      55,    56,    38,    39,    40,    41,    42,    43,    44,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    -1,    55,    56,   117,   118,
     119,   120,   121,   122
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    17,    24,    44,    72,
      73,    74,    78,    83,    44,    78,    79,    44,    17,    44,
      51,    75,    78,    87,     0,    73,    44,    44,    51,    84,
      79,    47,    49,    76,    91,    38,    47,    17,    80,    91,
      91,    25,    26,    27,    77,    85,    86,    47,    47,    16,
      79,    81,    88,    89,    90,    52,    79,    78,    52,    48,
      79,    44,    50,    46,    47,    44,    85,    53,    92,    89,
       8,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    44,    78,    92,    93,    94,    95,
      96,    97,    99,   100,   101,   102,   105,   106,   107,   110,
     111,   112,   114,   118,   119,   122,    49,    49,    92,    38,
      39,    40,    41,    42,    43,    44,    49,    55,    56,    59,
      64,    65,    67,   114,   120,   121,   122,   123,   124,   120,
     120,    44,    78,    16,    44,    78,    49,    49,    49,    38,
      34,    35,    44,    49,    51,    63,    70,   117,    44,    94,
      54,    47,    36,    37,    36,    37,   120,   120,    11,    51,
      70,   120,   123,   123,   123,   123,   123,   123,    28,    29,
      30,    31,    32,    33,    55,    56,    57,    58,    59,    60,
      61,    62,    65,    66,    68,   125,    58,   125,    46,   113,
      44,    44,    44,    78,    44,    44,    44,    96,   104,   114,
     120,    48,    50,    69,   115,   116,   120,   120,   120,    44,
     120,    28,    44,   114,   114,   114,   114,    50,    50,    49,
     120,    44,    50,   120,   120,   120,    28,    44,    44,    28,
      48,    46,    48,    50,    46,    50,    52,    63,   117,    38,
      39,    40,    41,    42,    43,    44,    55,    56,    82,   108,
     109,     9,    12,   120,    52,   113,    44,    82,   108,   109,
      28,    44,    82,   108,   109,   103,   120,    96,   120,    92,
     116,    63,    70,   117,   120,   120,    38,    39,    44,   108,
     109,    38,    39,    44,   108,   109,    92,    92,    50,    70,
      44,    82,   108,   109,    46,    50,    48,   120,    44,   120,
      10,    98,    44,   120,    92,   104,    63,   117,    92,    50,
     120,   120,    92
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    73,    73,    74,    74,    74,    74,    75,
      75,    75,    75,    76,    76,    77,    77,    77,    77,    78,
      78,    78,    78,    78,    79,    79,    80,    80,    81,    81,
      82,    82,    82,    82,    82,    82,    83,    84,    85,    85,
      86,    87,    88,    88,    89,    89,    90,    91,    92,    93,
      93,    94,    94,    95,    95,    95,    95,    95,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    97,    98,    98,    99,   100,   101,   102,   103,   103,
     104,   104,   105,   106,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   108,   108,
     108,   108,   109,   109,   109,   109,   109,   109,   110,   110,
     110,   110,   111,   112,   112,   113,   113,   114,   114,   115,
     115,   116,   116,   117,   117,   118,   118,   118,   118,   119,
     120,   120,   120,   120,   121,   121,   122,   122,   122,   122,
     123,   123,   123,   123,   123,   123,   123,   123,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     3,     4,     4,
       3,     2,     2,     1,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     4,     3,     1,     3,
       3,     3,     0,     1,     3,     1,     2,     4,     3,     2,
       1,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     7,     0,     2,     7,     9,     6,     6,     1,     3,
       1,     3,     5,     3,     3,     3,     4,     2,     3,     3,
       4,     2,     5,     5,     5,     5,     6,     6,     4,     4,
       6,     6,     5,     5,     5,     5,     4,     4,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     3,     6,
       5,     8,     2,     3,     2,     2,     3,     4,     3,     1,
       3,     1,     1,     1,     1,     3,     5,     6,     8,     2,
       3,     3,     1,     1,     2,     2,     3,     3,     3,     3,
       3,     1,     2,     2,     2,     2,     2,     2,     4,     1,
       3,     6,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 131 "parser.y" /* yacc.c:1257  */
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
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2243 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 73: /* componentes  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2253 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 74: /* componente  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2263 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 75: /* depoisDeIdent  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2273 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 76: /* fechaVarOuFunc  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2283 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 77: /* encapsulamento  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2293 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 78: /* tiposPrimitivos  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2303 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 79: /* tipo  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2313 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 80: /* static  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2323 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 81: /* tipoConst  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2333 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 82: /* literais  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2343 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 83: /* novoTipo  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2353 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 84: /* listaCampos  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2363 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 85: /* list  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2373 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 86: /* campo  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2383 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 87: /* tamanhoVetor  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2393 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 88: /* args  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2403 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 89: /* parameters  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2413 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 90: /* parameter  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2423 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 91: /* argsAndCommands  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2433 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 92: /* blocoComandos  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2443 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 93: /* comando  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2453 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 94: /* comandos  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2463 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 95: /* comandoSimples  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2473 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 96: /* comandosSemVirgula  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2483 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 97: /* ifThenElse  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2493 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 98: /* optElse  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2503 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 99: /* foreach  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2513 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 100: /* for  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2523 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 101: /* while_do  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2533 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 102: /* do_while  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2543 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 103: /* foreachList  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2553 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 104: /* forList  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2563 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 105: /* switch  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2573 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 106: /* case  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2583 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 107: /* localVarDefinition  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2593 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 108: /* negativeOrPositiveIdentifier  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2603 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 109: /* negativeOrPositiveLiteral  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2613 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 110: /* assignment  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2623 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 111: /* input  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2633 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 112: /* output  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2643 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 113: /* continueOutput  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2653 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 114: /* funcCall  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2663 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 115: /* argsCall  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2673 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 116: /* argCall  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2683 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 117: /* shiftOp  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2693 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 118: /* shift  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2703 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 119: /* return  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2713 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 120: /* expression  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2723 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 121: /* infiniteQuestionMarks  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2733 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 122: /* pipe  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2743 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 123: /* parenthesisOrOperand  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2753 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 124: /* operands  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2763 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 125: /* operators  */
#line 140 "parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2773 "parser.tab.c" /* yacc.c:1257  */
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
#line 165 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); arvore = (yyval.ast); parsingSucceded = TRUE;}
#line 3037 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 169 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3043 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 170 "parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3049 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 173 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3055 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 174 "parser.y" /* yacc.c:1646  */
    { // Regra introduzida para resolver conflitos
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3064 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 179 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3073 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 183 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3084 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 192 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3095 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 198 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3105 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 203 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3114 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 207 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3123 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 213 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3129 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 214 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3135 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 219 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3141 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 220 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3147 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 221 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3153 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 222 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3159 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 225 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3165 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 226 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3171 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 227 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3177 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 228 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3183 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 229 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3189 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 232 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3195 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 233 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3201 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 236 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3207 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 237 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3213 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 240 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3219 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 241 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3225 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 244 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3231 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 245 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3237 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 246 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3243 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 247 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3249 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 248 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3255 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 249 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3261 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 254 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3272 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 261 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3282 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 268 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3288 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 269 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3298 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 276 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3308 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 285 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3318 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 293 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3324 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 294 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3330 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 297 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3340 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 302 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3346 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 305 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 3352 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 308 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3363 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 321 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3373 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 328 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 3379 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 329 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3385 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 332 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3391 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 333 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3397 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 338 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3403 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 339 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3409 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 340 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3415 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 341 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3421 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 342 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3427 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 347 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3433 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 348 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3439 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 349 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3445 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 350 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3451 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 351 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3457 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 352 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3463 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 353 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3469 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 354 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3475 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 355 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3481 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 356 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3487 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 357 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3493 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 358 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3499 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 359 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3505 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 363 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-6].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-5].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-4].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3519 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 374 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3525 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 375 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3531 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 378 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-6].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-5].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3545 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 390 "parser.y" /* yacc.c:1646  */
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
#line 3561 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 404 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3574 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 414 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-4].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3587 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 426 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 427 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3603 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 434 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3609 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 435 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3619 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 443 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3631 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 452 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3641 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 462 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3651 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 467 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3661 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 472 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3672 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 478 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3681 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 482 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3691 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 487 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3701 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 492 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3712 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 498 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3721 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 503 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3733 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 510 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3745 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 517 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3757 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 524 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3769 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 531 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3782 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 539 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3795 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 547 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3806 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 553 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3817 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 560 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3830 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 568 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3843 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 576 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3855 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 583 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3867 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 590 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3879 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 597 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3891 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 604 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3902 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 610 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3913 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 618 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3922 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 622 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3931 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 626 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3940 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 630 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3949 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 637 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3958 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 641 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3967 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 645 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3976 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 649 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3985 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 653 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3994 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 657 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4003 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 665 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4013 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 670 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4026 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 678 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4038 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 685 "parser.y" /* yacc.c:1646  */
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
#line 4053 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 697 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4059 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 701 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4069 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 706 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4078 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 712 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4087 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 716 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4097 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 723 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4108 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 729 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4118 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 736 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4124 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 737 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4134 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 744 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4140 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 745 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4146 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 748 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4152 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 749 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4158 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 751 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4168 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 756 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico)));
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4180 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 763 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico)));
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast));
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4193 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 771 "parser.y" /* yacc.c:1646  */
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
#line 4208 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 784 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4214 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 788 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4224 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 793 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4234 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 798 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4240 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 799 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4246 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 802 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 4252 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 803 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 4258 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 806 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4268 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 811 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4278 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 816 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4288 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 821 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4298 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 829 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4308 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 834 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4314 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 835 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4320 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 836 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4326 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 837 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4332 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 838 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4338 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 839 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4344 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 840 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4350 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 843 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4361 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 849 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4367 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 850 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4377 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 855 "parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4390 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 863 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4396 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 864 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4402 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 865 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4408 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 866 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4414 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 867 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4420 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 868 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4426 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 869 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4432 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 870 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4438 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 873 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4444 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 874 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4450 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 875 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4456 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 876 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4462 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 877 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4468 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 878 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4474 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 879 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4480 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 880 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4486 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 881 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4492 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 882 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4498 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 883 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4504 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 884 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4510 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 885 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4516 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 886 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4522 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 887 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4528 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 888 "parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4534 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 4538 "parser.tab.c" /* yacc.c:1646  */
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
#line 891 "parser.y" /* yacc.c:1906  */



