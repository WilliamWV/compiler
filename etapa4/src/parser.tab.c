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
#line 1 "parser/parser.y" /* yacc.c:339  */

#include <stdio.h>
#include "../include/tree.h"
#include "../include/lexVal.h"
#include "../include/userTypeField.h"
#include "../include/defines.h"
#include "../include/expression.h"
#include "../include/functionArgs.h"
int yylex(void);
extern int get_line_number(void); // avisa que função deve ser lincada e está em outro arquivo
int yyerror (char const *s){
	printf("%s, on line %d\n", s, get_line_number());
	return -1;
}

extern void* arvore;

extern Fields *currentFields;
extern Args *currentArgs;

int parsingSucceded = FALSE;
extern Node *danglingNodes;

//Retorna constante representando o tipo
//opera sobre regra tipo ou tipoPrimitivo
int getType(struct node* type){
	if (strcmp(type->token->value.str, "int") == 0) return INT;
	if (strcmp(type->token->value.str, "float") == 0) return FLOAT;
	if (strcmp(type->token->value.str, "char") == 0) return CHAR;
	if (strcmp(type->token->value.str, "bool") == 0) return BOOL;
	if (strcmp(type->token->value.str, "string") == 0) return STRING;
	return USER;
}

//opera sovre tipo
char* getUserType(struct node* type){
	if (getType(type) != USER){
		return NULL;
	}
	else return type->token->value.str;
}

//TODO: implementar função addArgs ->operar sobre nodo args
void addArgs(char* symbol, struct node* args){

}

//TODO: implementar função verifyArguments // operar sobre argsCall
int verifyArguments(char* symbol, struct node* argsCall){
	return TRUE;
}


#line 120 "parser.tab.c" /* yacc.c:339  */

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
#line 57 "parser/parser.y" /* yacc.c:355  */

	struct lexval* valor_lexico;
	struct node* ast;

#line 211 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 228 "parser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   481

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  186
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  316

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
       0,   201,   201,   209,   213,   214,   217,   218,   312,   321,
     345,   351,   356,   360,   366,   367,   372,   373,   374,   375,
     378,   379,   380,   381,   382,   385,   386,   389,   390,   393,
     394,   397,   398,   399,   400,   401,   402,   407,   419,   426,
     427,   436,   445,   453,   454,   457,   466,   469,   472,   485,
     493,   494,   497,   498,   503,   504,   505,   506,   507,   512,
     513,   514,   515,   516,   517,   518,   519,   520,   521,   522,
     523,   524,   528,   544,   545,   548,   565,   586,   601,   618,
     619,   626,   627,   635,   649,   659,   668,   677,   688,   697,
     704,   712,   720,   727,   737,   747,   757,   767,   777,   787,
     795,   804,   814,   824,   833,   842,   851,   860,   868,   878,
     882,   886,   890,   897,   901,   905,   909,   913,   917,   925,
     939,   959,   975,  1003,  1007,  1012,  1018,  1022,  1029,  1039,
    1050,  1051,  1058,  1059,  1062,  1063,  1065,  1077,  1093,  1113,
    1143,  1147,  1152,  1157,  1158,  1161,  1162,  1165,  1170,  1175,
    1180,  1188,  1193,  1194,  1195,  1196,  1197,  1198,  1199,  1202,
    1215,  1220,  1229,  1248,  1249,  1250,  1251,  1252,  1253,  1254,
    1255,  1258,  1259,  1260,  1261,  1262,  1263,  1264,  1265,  1266,
    1267,  1268,  1269,  1270,  1271,  1272,  1273
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
  "'#'", "'^'", "'.'", "'$'", "$accept", "programa", "scopeOpenner",
  "componentes", "componente", "depoisDeIdent", "fechaVarOuFunc",
  "encapsulamento", "tiposPrimitivos", "tipo", "static", "tipoConst",
  "literais", "novoTipo", "listaCampos", "list", "campo", "tamanhoVetor",
  "args", "parameters", "parameter", "argsAndCommands", "blocoComandos",
  "comando", "comandos", "comandoSimples", "comandosSemVirgula",
  "ifThenElse", "optElse", "foreach", "for", "while_do", "do_while",
  "foreachList", "forList", "switch", "case", "localVarDefinition",
  "negativeOrPositiveIdentifier", "negativeOrPositiveLiteral",
  "assignment", "input", "output", "continueOutput", "funcCall",
  "argsCall", "argCall", "shiftOp", "shift", "return", "expression",
  "infiniteQuestionMarks", "pipe", "parenthesisOrOperand", "operands",
  "operators", YY_NULLPTR
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

#define YYPACT_NINF -220

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-220)))

#define YYTABLE_NINF -53

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -220,     8,   168,  -220,  -220,  -220,  -220,  -220,  -220,    22,
     -25,   159,  -220,   168,   -20,  -220,  -220,  -220,   -13,   -14,
      22,    21,    14,  -220,    28,    63,  -220,    12,    12,   134,
      36,    45,  -220,   210,  -220,  -220,    47,  -220,  -220,    22,
    -220,  -220,  -220,  -220,  -220,   271,    58,    68,  -220,  -220,
      22,  -220,    84,    82,  -220,    94,  -220,    96,   107,  -220,
     134,  -220,  -220,   115,   210,  -220,  -220,  -220,  -220,  -220,
    -220,    42,   132,   135,   115,   362,   362,   362,    29,   215,
     138,   140,   150,  -220,  -220,   282,   177,   153,  -220,    42,
     146,   154,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,
    -220,  -220,  -220,  -220,    69,  -220,  -220,   118,   362,   362,
     193,  -220,  -220,  -220,  -220,  -220,  -220,   -29,   362,   362,
     362,   362,   362,   362,   362,    69,  -220,   232,   118,   253,
    -220,   160,  -220,   167,   181,   142,   183,   184,   185,   362,
     182,  -220,  -220,  -220,   298,   362,   362,   188,   362,   187,
     214,  -220,  -220,  -220,   194,   194,   194,   194,   200,   201,
     204,   362,   211,   206,  -220,  -220,  -220,  -220,  -220,  -220,
    -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,
    -220,  -220,  -220,  -220,  -220,  -220,  -220,   362,  -220,   362,
     362,  -220,  -220,   229,   222,   223,  -220,   240,   221,   230,
    -220,  -220,  -220,   -33,  -220,  -220,   220,  -220,    44,  -220,
     114,   392,   246,  -220,  -220,  -220,  -220,   270,   284,   362,
     247,  -220,  -220,  -220,  -220,   160,   399,  -220,   273,   418,
     362,   115,   330,  -220,   -19,   362,   362,  -220,    93,    69,
    -220,  -220,  -220,  -220,  -220,  -220,  -220,    59,   139,  -220,
    -220,  -220,   115,   115,   252,   233,  -220,  -220,  -220,  -220,
    -220,   425,  -220,  -220,  -220,  -220,   -32,  -220,  -220,  -220,
     362,   260,   362,  -220,  -220,   114,   362,  -220,  -220,  -220,
    -220,  -220,  -220,  -220,  -220,  -220,  -220,   295,  -220,  -220,
     262,  -220,  -220,  -220,  -220,   362,   115,  -220,    50,  -220,
    -220,   272,   115,  -220,  -220,  -220,  -220,   362,   362,   114,
    -220,  -220,  -220,    54,   115,  -220
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     4,     1,    20,    21,    22,    23,    24,     0,
       0,     0,     2,     4,     0,     6,    26,    25,     0,     0,
       0,     0,     0,     7,     0,    28,     5,     0,     0,    16,
       0,     0,    14,    43,    13,    15,     0,    12,    27,     0,
       8,     9,    17,    18,    19,     0,     0,    39,    37,    11,
       0,    30,     0,     0,    44,    46,    42,     0,     0,    38,
      16,    29,    47,     0,     0,    10,    41,    40,     3,    48,
      45,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    63,    64,     0,     0,     0,    71,     3,
       0,     0,    54,    66,    57,    58,    67,    68,    69,    51,
      59,    60,    61,    55,    56,    62,    65,    70,     0,     0,
       0,   163,   164,   166,   165,   167,   168,   160,     0,     0,
       0,     0,     0,     0,     0,   169,   123,   144,   170,   143,
     152,   125,   140,     0,     0,     0,     0,     0,     0,     0,
       0,   134,   135,    88,     0,     0,     0,     0,     0,     0,
      92,    53,    49,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   154,   153,   156,   155,   157,   158,
     184,   183,   181,   182,   177,   178,   171,   172,   179,   146,
     173,   174,   185,   186,   180,   175,   176,     0,   145,     0,
       0,   124,    86,    90,     0,     0,    85,    89,     0,     0,
      84,   129,   133,     0,   130,   132,     0,   119,     0,   136,
       0,     0,     0,   147,   149,   148,   150,     0,     0,     0,
       0,   161,   151,   142,   141,   126,     0,    87,    91,     0,
       0,     0,     0,   128,     0,     0,     0,    81,     0,     0,
      31,    32,    33,    34,    35,    36,    99,     0,     0,   107,
     100,   108,     0,     0,     0,   159,   127,    95,   105,    96,
     106,     0,    93,   103,    94,   104,     0,    79,    83,   131,
       0,     0,     0,   121,   137,     0,     0,   117,   118,   112,
     111,   116,   114,   115,   110,   109,   113,    73,    77,    78,
       0,    97,   101,    98,   102,     0,     0,   120,     0,   138,
      82,     0,     0,    72,   162,    80,    75,     0,     0,     0,
      74,   122,   139,     0,     0,    76
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -220,  -220,     6,   309,  -220,  -220,  -220,  -220,    -2,    73,
    -220,  -220,  -219,  -220,  -220,   263,  -220,  -220,  -220,   261,
    -220,   152,   -62,  -220,   235,  -220,  -208,  -220,  -220,  -220,
    -220,  -220,  -220,  -220,    18,  -220,  -220,  -220,   -91,   -24,
    -220,  -220,  -220,   103,   -66,  -220,    97,  -204,  -220,  -220,
     -37,  -220,   -68,   125,  -220,   203
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    86,    12,    13,    23,    34,    45,    17,    51,
      39,    52,   249,    15,    30,    46,    47,    25,    53,    54,
      55,    35,    88,    89,    90,    91,    92,    93,   303,    94,
      95,    96,    97,   266,   238,    98,    99,   100,   250,   251,
     101,   102,   103,   191,   125,   203,   204,   148,   105,   106,
     205,   127,   128,   129,   130,   187
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,    69,   237,   107,   236,   104,     2,   258,     3,    24,
     263,    14,   110,   232,   295,   141,   142,   233,   296,    19,
     144,   107,   161,   104,    27,     4,     5,     6,     7,     8,
     272,    28,     4,     5,     6,     7,     8,    29,   126,   131,
     132,   162,   292,    58,   270,     4,     5,     6,     7,     8,
      72,   271,    36,    73,    74,    75,    76,    77,    78,    79,
      80,    33,    81,    82,    83,    84,    16,   300,    32,    87,
      33,   158,   159,   133,    71,    37,   134,   137,   141,   142,
      38,   163,    18,    48,   141,   142,    85,    87,   213,   214,
     215,   216,    49,    31,   308,    68,   -52,   277,   278,    56,
     275,   237,   199,   279,   314,   154,   155,   235,   206,   207,
      59,   209,    57,   307,   247,   248,    60,     4,     5,     6,
       7,     8,    72,    61,   220,    73,    74,    75,    62,    77,
      78,    79,    63,   195,    81,   259,    83,    84,   264,   275,
      64,   276,   107,    65,   239,     4,     5,     6,     7,     8,
     223,    66,   224,   225,   156,   157,   280,   285,    85,    42,
      43,    44,     4,     5,     6,     7,     8,    68,    68,   268,
     293,     4,     5,     6,     7,     8,    20,   282,   283,    40,
      41,   108,   254,   284,   109,     9,   194,   138,   140,   139,
     287,   288,    10,   267,   247,   248,   149,   150,   273,   274,
     152,   153,   260,    21,   160,   265,   190,   107,    87,   239,
      22,   192,    11,     4,     5,     6,     7,     8,     4,     5,
       6,     7,     8,   281,   286,   193,    50,   196,   197,   198,
     200,   135,   208,   297,   306,   299,   210,   294,   212,   301,
     310,   107,   211,   239,   164,   165,   166,   167,   168,   169,
     217,   218,   315,   219,    16,   221,   222,   226,   305,   136,
     170,   171,   172,   173,   174,   175,   227,   228,   229,   230,
     311,   312,   234,    87,     4,     5,     6,     7,     8,   252,
     231,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   144,   253,   184,   185,   255,
     186,   261,   289,   290,   298,   302,   304,    87,   176,   177,
     178,   188,   180,   181,   182,   183,   141,   142,   184,   185,
     309,   186,    26,    67,   151,    70,   143,   313,   256,   269,
       0,   144,   189,   145,     0,     0,   111,   112,   113,   114,
     115,   116,   117,     0,     0,   146,     0,   118,   201,     0,
       0,     0,   147,   119,   120,     0,     0,   121,     0,     0,
       0,     0,   122,   123,     0,   124,     0,   202,   111,   112,
     113,   114,   115,   116,   117,     0,     0,     0,     0,   118,
       0,     0,     0,     0,     0,   119,   120,     0,     0,   121,
       0,     0,     0,     0,   122,   123,     0,   124,     0,   202,
     111,   112,   113,   114,   115,   116,   117,     0,     0,     0,
       0,   118,     0,     0,     0,     0,     0,   119,   120,     0,
       0,   121,     0,     0,     0,     0,   122,   123,     0,   124,
     240,   241,   242,   243,   244,   245,   246,   240,   241,   242,
     243,   244,   245,   257,     0,     0,     0,   247,   248,     0,
       0,     0,     0,     0,   247,   248,   240,   241,   242,   243,
     244,   245,   262,   240,   241,   242,   243,   244,   245,   291,
       0,     0,     0,   247,   248,     0,     0,     0,     0,     0,
     247,   248
};

static const yytype_int16 yycheck[] =
{
       2,    63,   210,    71,   208,    71,     0,   226,     0,    11,
     229,    13,    74,    46,    46,    34,    35,    50,    50,    44,
      49,    89,    51,    89,    44,     3,     4,     5,     6,     7,
     234,    44,     3,     4,     5,     6,     7,    51,    75,    76,
      77,    70,   261,    45,    63,     3,     4,     5,     6,     7,
       8,    70,    38,    11,    12,    13,    14,    15,    16,    17,
      18,    49,    20,    21,    22,    23,    44,   275,    47,    71,
      49,   108,   109,    44,    68,    47,    78,    79,    34,    35,
      17,   118,     9,    47,    34,    35,    44,    89,   154,   155,
     156,   157,    47,    20,   298,    53,    54,    38,    39,    52,
      46,   309,   139,    44,    50,    36,    37,    63,   145,   146,
      52,   148,    39,    63,    55,    56,    48,     3,     4,     5,
       6,     7,     8,    50,   161,    11,    12,    13,    44,    15,
      16,    17,    50,   135,    20,   226,    22,    23,   229,    46,
      46,    48,   210,    47,   210,     3,     4,     5,     6,     7,
     187,    44,   189,   190,    36,    37,   247,   248,    44,    25,
      26,    27,     3,     4,     5,     6,     7,    53,    53,   231,
     261,     3,     4,     5,     6,     7,    17,    38,    39,    27,
      28,    49,   219,    44,    49,    17,    44,    49,    38,    49,
     252,   253,    24,   230,    55,    56,    19,    44,   235,   236,
      54,    47,   226,    44,    11,   229,    46,   275,   210,   275,
      51,    44,    44,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,   247,   248,    44,    16,    44,    44,    44,
      48,    16,    44,   270,   296,   272,    49,   261,    44,   276,
     302,   309,    28,   309,   119,   120,   121,   122,   123,   124,
      50,    50,   314,    49,    44,    44,    50,    28,   295,    44,
      28,    29,    30,    31,    32,    33,    44,    44,    28,    48,
     307,   308,    52,   275,     3,     4,     5,     6,     7,     9,
      50,    28,    29,    30,    31,    32,    33,    55,    56,    57,
      58,    59,    60,    61,    62,    49,    12,    65,    66,    52,
      68,    28,    50,    70,    44,    10,    44,   309,    55,    56,
      57,    58,    59,    60,    61,    62,    34,    35,    65,    66,
      48,    68,    13,    60,    89,    64,    44,   309,   225,   232,
      -1,    49,   129,    51,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    63,    -1,    49,    50,    -1,
      -1,    -1,    70,    55,    56,    -1,    -1,    59,    -1,    -1,
      -1,    -1,    64,    65,    -1,    67,    -1,    69,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,    59,
      -1,    -1,    -1,    -1,    64,    65,    -1,    67,    -1,    69,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,
      -1,    59,    -1,    -1,    -1,    -1,    64,    65,    -1,    67,
      38,    39,    40,    41,    42,    43,    44,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    55,    56,    -1,
      -1,    -1,    -1,    -1,    55,    56,    38,    39,    40,    41,
      42,    43,    44,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,
      55,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    72,    73,     0,     3,     4,     5,     6,     7,    17,
      24,    44,    74,    75,    79,    84,    44,    79,    80,    44,
      17,    44,    51,    76,    79,    88,    74,    44,    44,    51,
      85,    80,    47,    49,    77,    92,    38,    47,    17,    81,
      92,    92,    25,    26,    27,    78,    86,    87,    47,    47,
      16,    80,    82,    89,    90,    91,    52,    80,    79,    52,
      48,    80,    44,    50,    46,    47,    44,    86,    53,    93,
      90,    73,     8,    11,    12,    13,    14,    15,    16,    17,
      18,    20,    21,    22,    23,    44,    73,    79,    93,    94,
      95,    96,    97,    98,   100,   101,   102,   103,   106,   107,
     108,   111,   112,   113,   115,   119,   120,   123,    49,    49,
      93,    38,    39,    40,    41,    42,    43,    44,    49,    55,
      56,    59,    64,    65,    67,   115,   121,   122,   123,   124,
     125,   121,   121,    44,    79,    16,    44,    79,    49,    49,
      38,    34,    35,    44,    49,    51,    63,    70,   118,    19,
      44,    95,    54,    47,    36,    37,    36,    37,   121,   121,
      11,    51,    70,   121,   124,   124,   124,   124,   124,   124,
      28,    29,    30,    31,    32,    33,    55,    56,    57,    58,
      59,    60,    61,    62,    65,    66,    68,   126,    58,   126,
      46,   114,    44,    44,    44,    79,    44,    44,    44,   121,
      48,    50,    69,   116,   117,   121,   121,   121,    44,   121,
      49,    28,    44,   115,   115,   115,   115,    50,    50,    49,
     121,    44,    50,   121,   121,   121,    28,    44,    44,    28,
      48,    50,    46,    50,    52,    63,   118,    97,   105,   115,
      38,    39,    40,    41,    42,    43,    44,    55,    56,    83,
     109,   110,     9,    12,   121,    52,   114,    44,    83,   109,
     110,    28,    44,    83,   109,   110,   104,   121,    93,   117,
      63,    70,   118,   121,   121,    46,    48,    38,    39,    44,
     109,   110,    38,    39,    44,   109,   110,    93,    93,    50,
      70,    44,    83,   109,   110,    46,    50,   121,    44,   121,
      97,   121,    10,    99,    44,   121,    93,    63,   118,    48,
      93,   121,   121,   105,    50,    93
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    73,    74,    74,    75,    75,    75,    75,
      76,    76,    76,    76,    77,    77,    78,    78,    78,    78,
      79,    79,    79,    79,    79,    80,    80,    81,    81,    82,
      82,    83,    83,    83,    83,    83,    83,    84,    85,    86,
      86,    87,    88,    89,    89,    90,    90,    91,    92,    93,
      94,    94,    95,    95,    96,    96,    96,    96,    96,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    98,    99,    99,   100,   101,   102,   103,   104,
     104,   105,   105,   106,   107,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   109,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   111,
     111,   111,   111,   112,   113,   113,   114,   114,   115,   115,
     116,   116,   117,   117,   118,   118,   119,   119,   119,   119,
     120,   121,   121,   121,   121,   122,   122,   123,   123,   123,
     123,   124,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     0,     2,     1,     2,     3,     4,
       4,     3,     2,     2,     1,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     4,     3,     1,
       3,     3,     3,     0,     1,     3,     1,     2,     4,     4,
       2,     1,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     7,     0,     2,     7,    10,     6,     6,     1,
       3,     1,     3,     5,     3,     3,     3,     4,     2,     3,
       3,     4,     2,     5,     5,     5,     5,     6,     6,     4,
       4,     6,     6,     5,     5,     5,     5,     4,     4,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     3,
       6,     5,     8,     2,     3,     2,     2,     3,     4,     3,
       1,     3,     1,     1,     1,     1,     3,     5,     6,     8,
       2,     3,     3,     1,     1,     2,     2,     3,     3,     3,
       3,     3,     1,     2,     2,     2,     2,     2,     2,     4,
       1,     3,     6,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
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
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1336 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 4: /* TK_PR_FLOAT  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1350 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 5: /* TK_PR_BOOL  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1364 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 6: /* TK_PR_CHAR  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1378 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 7: /* TK_PR_STRING  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1392 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 8: /* TK_PR_IF  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1406 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 9: /* TK_PR_THEN  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1420 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 10: /* TK_PR_ELSE  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1434 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 11: /* TK_PR_WHILE  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1448 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 12: /* TK_PR_DO  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1462 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 13: /* TK_PR_INPUT  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1476 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 14: /* TK_PR_OUTPUT  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1490 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 15: /* TK_PR_RETURN  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1504 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 16: /* TK_PR_CONST  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1518 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 17: /* TK_PR_STATIC  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1532 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 18: /* TK_PR_FOREACH  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1546 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 19: /* TK_PR_FOR  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1560 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 20: /* TK_PR_SWITCH  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1574 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 21: /* TK_PR_CASE  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1588 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 22: /* TK_PR_BREAK  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1602 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 23: /* TK_PR_CONTINUE  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1616 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 24: /* TK_PR_CLASS  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1630 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 25: /* TK_PR_PRIVATE  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1644 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 26: /* TK_PR_PUBLIC  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1658 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 27: /* TK_PR_PROTECTED  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1672 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 28: /* TK_OC_LE  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1686 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 29: /* TK_OC_GE  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1700 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 30: /* TK_OC_EQ  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1714 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 31: /* TK_OC_NE  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1728 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 32: /* TK_OC_AND  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1742 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 33: /* TK_OC_OR  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1756 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 34: /* TK_OC_SL  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1770 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 35: /* TK_OC_SR  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1784 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 36: /* TK_OC_FORWARD_PIPE  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1798 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 37: /* TK_OC_BASH_PIPE  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1812 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 38: /* TK_LIT_INT  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1826 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 39: /* TK_LIT_FLOAT  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1840 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 40: /* TK_LIT_FALSE  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1854 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 41: /* TK_LIT_TRUE  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1868 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 42: /* TK_LIT_CHAR  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1882 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 43: /* TK_LIT_STRING  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1896 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 44: /* TK_IDENTIFICADOR  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1910 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 45: /* TOKEN_ERRO  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1924 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 46: /* ','  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1938 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 47: /* ';'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1952 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 48: /* ':'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1966 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 49: /* '('  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1980 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 50: /* ')'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1994 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 51: /* '['  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2008 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 52: /* ']'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2022 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 53: /* '{'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2036 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 54: /* '}'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2050 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 55: /* '+'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2064 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 56: /* '-'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2078 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 57: /* '|'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2092 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 58: /* '?'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2106 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 59: /* '*'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2120 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 60: /* '/'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2134 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 61: /* '<'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2148 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 62: /* '>'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2162 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 63: /* '='  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2176 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 64: /* '!'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2190 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 65: /* '&'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2204 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 66: /* '%'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2218 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 67: /* '#'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2232 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 68: /* '^'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2246 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 69: /* '.'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2260 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 70: /* '$'  */
#line 167 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2274 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 72: /* programa  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2284 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 74: /* componentes  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2294 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 75: /* componente  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2304 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 76: /* depoisDeIdent  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2314 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 77: /* fechaVarOuFunc  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2324 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 78: /* encapsulamento  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2334 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 79: /* tiposPrimitivos  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2344 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 80: /* tipo  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2354 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 81: /* static  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2364 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 82: /* tipoConst  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2374 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 83: /* literais  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2384 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 84: /* novoTipo  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2394 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 85: /* listaCampos  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2404 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 86: /* list  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2414 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 87: /* campo  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2424 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 88: /* tamanhoVetor  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2434 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 89: /* args  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2444 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 90: /* parameters  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2454 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 91: /* parameter  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2464 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 92: /* argsAndCommands  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2474 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 93: /* blocoComandos  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2484 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 94: /* comando  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2494 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 95: /* comandos  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2504 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 96: /* comandoSimples  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2514 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 97: /* comandosSemVirgula  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2524 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 98: /* ifThenElse  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2534 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 99: /* optElse  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2544 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 100: /* foreach  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2554 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 101: /* for  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2564 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 102: /* while_do  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2574 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 103: /* do_while  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2584 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 104: /* foreachList  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2594 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 105: /* forList  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2604 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 106: /* switch  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2614 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 107: /* case  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2624 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 108: /* localVarDefinition  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2634 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 109: /* negativeOrPositiveIdentifier  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2644 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 110: /* negativeOrPositiveLiteral  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2654 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 111: /* assignment  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2664 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 112: /* input  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2674 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 113: /* output  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2684 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 114: /* continueOutput  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2694 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 115: /* funcCall  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2704 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 116: /* argsCall  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2714 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 117: /* argCall  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2724 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 118: /* shiftOp  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2734 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 119: /* shift  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2744 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 120: /* return  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2754 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 121: /* expression  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2764 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 122: /* infiniteQuestionMarks  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2774 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 123: /* pipe  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2784 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 124: /* parenthesisOrOperand  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2794 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 125: /* operands  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2804 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 126: /* operators  */
#line 176 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2814 "parser.tab.c" /* yacc.c:1257  */
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
#line 201 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast); arvore = (yyval.ast); 
		parsingSucceded = TRUE;
		closeTable(); // fecha escopo global
	}
#line 3082 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 209 "parser/parser.y" /* yacc.c:1646  */
    {initTable();}
#line 3088 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 213 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3094 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 214 "parser/parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3100 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 217 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3106 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 218 "parser/parser.y" /* yacc.c:1646  */
    { // Regra introduzida para resolver conflitos
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		/*Pode ser:
			1) Declaração de vetor -> cabeça da regra tem valor léxico '[' 
			   correspondente à abertura dos colchetes para declarar o tamanho
			2) Função -> primeiro filho da cabeça é '(' indicando
			   abertura dos parênteses para os parâmetros da função
			3) Variáveis globais -> caso contrário	
		*/
		if ((yyvsp[0].ast)->token->value.c == '['){
			//trata vetor
			// kids[0] = TK_LIT_INT
			// kids[1] = ']'
			// kids[2] = static | NULL
			// kids[3] = tipo
			// kids[4] = ';'
			int flag = 0;
			if ((yyvsp[0].ast)->kids[2]->token != NULL) 
				flag = STATIC;
			int type = getType((yyvsp[0].ast)->kids[3]);			
			if (type == USER){
				int isUsr = isUserType((yyvsp[0].ast)->kids[3]->token->value.str);
				if(isUsr!=TRUE) exit(isUsr);
				int addSymb = addSymbol(
					(yyvsp[-1].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyvsp[0].ast)->kids[3]),
					(yyvsp[0].ast)->kids[0]->token->value.i, FALSE, flag
				);
				if (addSymb!=0) exit(addSymb);
			}
			else{
				int addSymb = addSymbol(
					(yyvsp[-1].valor_lexico), NATUREZA_IDENTIFICADOR, type, NULL, (yyvsp[0].ast)->kids[0]->token->value.i, 
					FALSE, flag 
				);
				if(addSymb!=0) exit(addSymb);
			}
		}
		else if ((yyvsp[0].ast)->kids[0]->token->value.c == '('){ //
			//trata função
			//$1 = tipo
			//head = TK_IDENTIFICADOR -> nome
			//kids[0] = '('
			//kids[0]->kids[0] = args
			//kids[0]->kids[1] = ')' 
			int isUsr = isUserType((yyval.ast)->token->value.str);
			if(isUsr!=TRUE) exit(isUsr);
			int addSymb = addSymbol((yyvsp[0].ast)->token, NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)), 0, TRUE, 0);			
			if(addSymb!=0) exit(addSymb);
			addArgsToSymbol((yyvsp[0].ast)->token->value.str, currentArgs);
			clearCurrentArgs();
		}
		else{
			//Existem diferentes variações:
			//var global com tipos primitivos não estático -> head = tipoPrimitivo, kids[0] = ';'
			//var global estatica -> head = TK_PR_STATIC, kids[0] = tipo, kids[1] = ';'
			//var global não estática com tipo de usuário -> head = tipodeUser, kids[0] = ';'
			
			if ((yyvsp[0].ast)->kidsNumber == 2){
				//var global estática
				int type = getType((yyvsp[0].ast)->kids[0]);				
				if (type == USER){
					int isUsr = isUserType((yyvsp[0].ast)->kids[0]->token->value.str);
					if(isUsr!=TRUE) exit(isUsr);
					int addSymb = addSymbol(
						(yyvsp[-1].valor_lexico), NATUREZA_IDENTIFICADOR, USER, 
						getUserType((yyvsp[0].ast)->kids[0]), 0, FALSE, STATIC
					);
					if(addSymb!=0) exit(addSymb);
				}
				else{
					int addSymb = addSymbol(
						(yyvsp[-1].valor_lexico), NATUREZA_IDENTIFICADOR, type, 
						NULL, 0, FALSE, STATIC
					);
					if(addSymb!=0) exit(addSymb);
				}
				
			}else{
				int type = getType((yyvsp[0].ast));
				if (type == USER){
					int isUsr = isUserType((yyvsp[0].ast)->token->value.str);
					if(isUsr!=TRUE) exit(isUsr);
					int addSymb = addSymbol((yyvsp[-1].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyvsp[0].ast)), 0, FALSE, 0);
					if(addSymb!=0) exit(addSymb);
				}
				else{
					int addSymb = addSymbol((yyvsp[-1].valor_lexico), NATUREZA_IDENTIFICADOR, type, NULL, 0, FALSE, 0);
					if(addSymb!=0) exit(addSymb);
				}
			}
		}
	}
#line 3204 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 312 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-1].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-2].ast)), NULL, 0, TRUE, 0);		
		if(addSymb!=0) exit(addSymb);		
		addArgsToSymbol((yyvsp[-1].valor_lexico)->value.str, currentArgs);
		printArgs((yyvsp[-1].valor_lexico)->value.str);
		clearCurrentArgs();
	}
#line 3218 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 321 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int type = getType((yyvsp[-2].ast));		
		if(type == USER){
			int isUsr = isUserType((yyvsp[-2].ast)->token->value.str);
			if(isUsr!=TRUE) exit(isUsr);
			int addSymb = addSymbol((yyvsp[-1].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyvsp[-2].ast)), 0, TRUE, STATIC);
			if(addSymb!=0) exit(addSymb);		
			addArgsToSymbol((yyvsp[-1].valor_lexico)->value.str, currentArgs);
			clearCurrentArgs();
		}
		else{
			int addSymb = addSymbol((yyvsp[-1].valor_lexico), NATUREZA_IDENTIFICADOR, type, NULL, 0, TRUE, STATIC);
			if(addSymb!=0) exit(addSymb);		
			addArgsToSymbol((yyvsp[-1].valor_lexico)->value.str, currentArgs);
			clearCurrentArgs();
		}
	}
#line 3244 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 345 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3255 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 351 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3265 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 356 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3274 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 360 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3283 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 366 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3289 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 367 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3295 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 372 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3301 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 373 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3307 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 374 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3313 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 375 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3319 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 378 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3325 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 379 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3331 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 380 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3337 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 381 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3343 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 382 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3349 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 385 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3355 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 386 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3361 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 389 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3367 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 390 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3373 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 393 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3379 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 394 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3385 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 397 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3391 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 398 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3397 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 399 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3403 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 400 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3409 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 401 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3415 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 402 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3421 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 407 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, USER, NULL, 0, FALSE, 0);		
		if(addSymb!=0) exit(addSymb);
		addFieldsToSymbol((yyvsp[-2].valor_lexico)->value.str, currentFields);
		//printFields("pessoa");
		clearCurrentFields();
	}
#line 3437 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 419 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3447 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 426 "parser/parser.y" /* yacc.c:1646  */
    {adicionaCampo(criaCampo((yyvsp[0].ast))); (yyval.ast) = (yyvsp[0].ast);}
#line 3453 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 427 "parser/parser.y" /* yacc.c:1646  */
    {		
		adicionaCampo(criaCampo((yyvsp[-2].ast)));

		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3465 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 436 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3475 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 445 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3485 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 453 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3491 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 454 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3497 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 457 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		
		adicionaArg(criaArg((yyvsp[-2].ast)));

		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));

	}
#line 3511 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 466 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); adicionaArg(criaArg((yyvsp[0].ast)));}
#line 3517 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 469 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 3523 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 472 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3534 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 485 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		closeTable();                     //Fecha escopo local
	}
#line 3545 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 493 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 3551 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 494 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3557 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 497 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3563 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 498 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3569 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 503 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3575 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 504 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3581 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 505 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3587 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 506 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 507 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3599 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 512 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3605 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 513 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3611 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 514 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3617 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 515 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3623 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 516 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3629 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 517 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3635 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 518 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3641 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 519 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3647 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 520 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3653 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 521 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3659 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 522 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3665 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 523 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3671 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 524 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3677 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 528 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-6].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-5].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-4].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));

		parseOperands((yyvsp[-4].ast));
		int correctOperands =  coercion(BOOL, (yyvsp[-4].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
	}
#line 3696 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 544 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3702 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 545 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3708 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 548 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-6].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-5].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVar = isVariable((yyvsp[-4].valor_lexico)->value.str);
		if(isVar!=TRUE) exit(isVar);
	}
#line 3724 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 565 "parser/parser.y" /* yacc.c:1646  */
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

		parseOperands((yyvsp[-4].ast));
		int correctOperands =  coercion(BOOL, (yyvsp[-4].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();

		closeTable();
	}
#line 3747 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 586 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));

		parseOperands((yyvsp[-3].ast));
		int correctOperands =  coercion(BOOL, (yyvsp[-3].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
	}
#line 3765 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 601 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-4].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));

		parseOperands((yyvsp[-1].ast));
		int correctOperands =  coercion(BOOL, (yyvsp[-1].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
	}
#line 3783 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 618 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3789 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 619 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3799 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 626 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3805 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 627 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3815 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 635 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		parseOperands((yyvsp[-2].ast));
		int correctOperands =  coercion(INT, (yyvsp[-2].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
	}
#line 3832 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 649 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3842 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 659 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = isUserType((yyvsp[-1].valor_lexico)->value.str);
		if (isUsr !=TRUE) exit(isUsr);
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)->kids[0]), 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 3856 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 668 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = isUserType((yyvsp[-1].valor_lexico)->value.str);
		if (isUsr !=TRUE) exit(isUsr);
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)->kids[0]), 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
#line 3870 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 677 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = isUserType((yyvsp[-1].valor_lexico)->value.str);
		if (isUsr !=TRUE) exit(isUsr);
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)->kids[1]), 0, FALSE, STATIC + CONST);
		if(addSymb!=0) exit(addSymb);
		
	}
#line 3886 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 688 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = isUserType((yyvsp[-1].valor_lexico)->value.str);
		if (isUsr !=TRUE) exit(isUsr);
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)), 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
		
	}
#line 3900 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 697 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 3912 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 704 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
		
	}
#line 3925 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 712 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 3938 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 720 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
	}
#line 3949 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 727 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
		
	}
#line 3964 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 737 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 3979 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 747 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
#line 3994 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 757 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
#line 4009 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 767 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 4024 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 777 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 4039 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 787 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
	}
#line 4052 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 795 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
	}
#line 4065 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 804 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 4080 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 814 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 4095 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 824 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 4109 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 833 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 4123 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 842 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
#line 4137 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 851 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
#line 4151 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 860 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
	}
#line 4164 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 868 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
#line 4177 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 878 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4186 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 882 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4195 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 886 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4204 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 890 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4213 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 897 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4222 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 901 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4231 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 905 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4240 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 909 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4249 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 913 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4258 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 917 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4267 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 925 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVar = isVariable((yyvsp[-2].valor_lexico)->value.str);
		if (isVar!=TRUE) exit(isVar);

		parseOperands((yyvsp[0].ast));
		int correctOperands =  coercion(identifierType((yyvsp[-2].valor_lexico)->value.str), (yyvsp[0].ast));
		//printf("%d\n\n", correctOperands);
		if (correctOperands != 0) exit(correctOperands);
		printCurrentOperands();
		clearCurrentOperands();
	}
#line 4286 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 939 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVec = isVector((yyvsp[-5].valor_lexico)->value.str);
		if (isVec != TRUE) exit(isVec);
		
		parseOperands((yyvsp[-3].ast));
		int correctOperands =  coercion(INT, (yyvsp[-3].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();

		parseOperands((yyvsp[0].ast));
		correctOperands =  coercion(identifierType((yyvsp[-5].valor_lexico)->value.str), (yyvsp[0].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
	}
#line 4311 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 959 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoCampo((yyvsp[-2].valor_lexico), (yyvsp[-4].valor_lexico)->value.str)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isUsr = isUserVar((yyvsp[-4].valor_lexico)->value.str);
		if(isUsr!=TRUE) exit(isUsr);
		int hasF = hasField((yyvsp[-4].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str);
		if(hasF != TRUE) exit(hasF);
		
		parseOperands((yyvsp[0].ast));
		int correctOperands =  coercion(fieldType((yyvsp[-4].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str), (yyvsp[0].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
	}
#line 4332 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 975 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-7].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-6].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-5].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoCampo((yyvsp[-2].valor_lexico), (yyvsp[-7].valor_lexico)->value.str)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVec = isVector((yyvsp[-7].valor_lexico)->value.str);
		if (isVec != TRUE) exit(isVec);
		int isUsr = isUserVar((yyvsp[-7].valor_lexico)->value.str);
		if(isUsr!=TRUE) exit(isUsr);
		int hasF = hasField((yyvsp[-7].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str);
		if(hasF != TRUE) exit(hasF);

		parseOperands((yyvsp[-5].ast));
		int correctOperands =  coercion(INT, (yyvsp[-5].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();

		parseOperands((yyvsp[0].ast));
		correctOperands =  coercion(fieldType((yyvsp[-7].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str), (yyvsp[0].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
	}
#line 4363 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1003 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4369 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1007 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4379 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1012 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4388 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1018 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4397 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1022 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4407 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1029 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isFunc = isFunction((yyvsp[-3].valor_lexico)->value.str);
		if(isFunc!=TRUE) exit(isFunc);
		int correctArgs = verifyArguments((yyvsp[-3].valor_lexico)->value.str, (yyvsp[-1].ast));
		if(correctArgs != TRUE) exit(correctArgs);
	}
#line 4422 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1039 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isFunc = isFunction((yyvsp[-2].valor_lexico)->value.str);
		if(isFunc!=TRUE) exit(isFunc);
		int correctArgs = verifyArguments((yyvsp[-2].valor_lexico)->value.str, NULL);
		if(correctArgs != TRUE) exit(correctArgs);
	}
#line 4436 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1050 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4442 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1051 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4452 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1058 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4458 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1059 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4464 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1062 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4470 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1063 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4476 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1065 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVar = isVariable((yyvsp[-2].valor_lexico)->value.str);
		if (isVar!=TRUE) exit(isVar);

		parseOperands((yyvsp[0].ast));
		int correctOperands =  coercion(INT, (yyvsp[0].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
	}
#line 4493 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1077 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico)));
		adicionaFilho((yyval.ast), criaNodoCampo((yyvsp[-2].valor_lexico), (yyvsp[-4].valor_lexico)->value.str));
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isUsr = isUserVar((yyvsp[-4].valor_lexico)->value.str);
		if(isUsr!=TRUE) exit(isUsr);
		int hasF = hasField((yyvsp[-4].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str);
		if(hasF != TRUE) exit(hasF);

		parseOperands((yyvsp[0].ast));
		int correctOperands =  coercion(INT, (yyvsp[0].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
	}
#line 4514 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1093 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico)));
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast));
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVec = isVector((yyvsp[-5].valor_lexico)->value.str);
		if (isVec != TRUE) exit(isVec);

		parseOperands((yyvsp[-3].ast));
		int correctOperands =  coercion(INT, (yyvsp[-3].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
		
		parseOperands((yyvsp[0].ast));
		correctOperands =  coercion(INT, (yyvsp[0].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
	}
#line 4539 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1113 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-7].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-6].valor_lexico)));
		adicionaFilho((yyval.ast), (yyvsp[-5].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoCampo((yyvsp[-2].valor_lexico), (yyvsp[-7].valor_lexico)->value.str));
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVec = isVector((yyvsp[-7].valor_lexico)->value.str);
		if (isVec != TRUE) exit(isVec);
		int isUsr = isUserVar((yyvsp[-7].valor_lexico)->value.str);
		if(isUsr!=TRUE) exit(isUsr);
		int hasF = hasField((yyvsp[-7].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str);
		if(hasF != TRUE) exit(hasF);

		parseOperands((yyvsp[-5].ast));
		int correctOperands =  coercion(INT, (yyvsp[-5].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();

		parseOperands((yyvsp[0].ast));
		correctOperands =  coercion(INT, (yyvsp[0].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
	}
#line 4570 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1143 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4576 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1147 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4586 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1152 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4596 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1157 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4602 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1158 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4608 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1161 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 4614 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1162 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 4620 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1165 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4630 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1170 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4640 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1175 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4650 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1180 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4660 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1188 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4670 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1193 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4676 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1194 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4682 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1195 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4688 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1196 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4694 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1197 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4700 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1198 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4706 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1199 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4712 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1202 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isVec = isVector((yyvsp[-3].valor_lexico)->value.str);
		if (isVec != TRUE) exit(isVec);
		
		parseOperands((yyvsp[-1].ast));
		int correctOperands =  coercion(INT, (yyvsp[-1].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
	}
#line 4730 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1215 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));
		int isVar = isVariable((yyvsp[0].valor_lexico)->value.str);
		if (isVar != TRUE) exit(isVar);
	}
#line 4740 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1220 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoCampo((yyvsp[0].valor_lexico), (yyvsp[-2].valor_lexico)->value.str));
		int isUsr = isUserVar((yyvsp[-2].valor_lexico)->value.str);
		if(isUsr!=TRUE) exit(isUsr);
		int hasF = hasField((yyvsp[-2].valor_lexico)->value.str, (yyvsp[0].valor_lexico)->value.str);
		if(hasF != TRUE) exit(hasF);
	}
#line 4754 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1229 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoCampo((yyvsp[0].valor_lexico), (yyvsp[-5].valor_lexico)->value.str));
		int isVec = isVector((yyvsp[-5].valor_lexico)->value.str);
		if (isVec != TRUE) exit(isVec);
		int isUsr = isUserVar((yyvsp[-5].valor_lexico)->value.str);
		if(isUsr!=TRUE) exit(isUsr);
		int hasF = hasField((yyvsp[-5].valor_lexico)->value.str, (yyvsp[0].valor_lexico)->value.str);
		if(hasF != TRUE) exit(hasF);

		parseOperands((yyvsp[-3].ast));
		int correctOperands =  coercion(INT, (yyvsp[-3].ast));
		if (correctOperands != 0) exit(correctOperands);
		clearCurrentOperands();
	}
#line 4778 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1248 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4784 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1249 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4790 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1250 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4796 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1251 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4802 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1252 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4808 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1253 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4814 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1254 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4820 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1255 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4826 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1258 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4832 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1259 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4838 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1260 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4844 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1261 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4850 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1262 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4856 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1263 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4862 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1264 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4868 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1265 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4874 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1266 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4880 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1267 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4886 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1268 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4892 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1269 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4898 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1270 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4904 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1271 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4910 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1272 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4916 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1273 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4922 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 4926 "parser.tab.c" /* yacc.c:1646  */
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
#line 1276 "parser/parser.y" /* yacc.c:1906  */



