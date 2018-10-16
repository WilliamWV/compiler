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
extern char *currentFunc;

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

int verifyArguments(char* symbol, struct node* argsCall){
	Hash* func = getSymbol(symbol);
	int argsNum = func->argsNum;
	if(argsCall == NULL){ // função sem argumentos
		if (argsNum == 0) return TRUE;
		return ERR_MISSING_ARGS;
	}
	if(argsNum == 0){ // argsCall não é nulo mas a função exige 0 argumentos
		return ERR_EXCESS_ARGS;
	}
	// estrutura do nodo é:
	// head = argCall; filhos pares = ','; filhos ímpares = argCall
	// portanto argsCall deve ter 2*(argsNum-1) filhos
	if(argsCall->kidsNumber < 2*(argsNum - 1)) return ERR_MISSING_ARGS;
	if(argsCall->kidsNumber > 2*(argsNum - 1)) return ERR_EXCESS_ARGS;
	
	int currentArg = 0;	
	//pipe
	if (!(argsCall->token->tokenType == SPEC_CHAR || argsCall->token->value.c == '.')){
		if (argsCall->type != func->args[currentArg]->argType) {
			return ERR_WRONG_TYPE_ARGS;
		
		}
	}
	for(int i = 1; i<argsNum; i+=2){
		currentArg++;
		//pipe
		if (!(argsCall->kids[i]->token->tokenType == SPEC_CHAR || 
			  argsCall->kids[i]->token->value.c == '.') )
		{		
			if(argsCall->kids[i]->type != func->args[currentArg]->argType) {
				return ERR_WRONG_TYPE_ARGS;
			}
		}
	}
	return TRUE;
}


#line 149 "parser.tab.c" /* yacc.c:339  */

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
#line 86 "parser/parser.y" /* yacc.c:355  */

	struct lexval* valor_lexico;
	struct node* ast;

#line 240 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 257 "parser.tab.c" /* yacc.c:358  */

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
#define YYLAST   488

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  187
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  319

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
       0,   231,   231,   239,   243,   244,   247,   248,   342,   363,
     369,   374,   378,   384,   385,   394,   395,   396,   397,   400,
     401,   402,   403,   404,   407,   408,   411,   412,   415,   416,
     419,   420,   421,   422,   423,   424,   429,   441,   448,   449,
     458,   467,   475,   476,   479,   488,   491,   516,   523,   543,
     555,   563,   564,   567,   568,   573,   574,   575,   576,   577,
     582,   583,   584,   585,   586,   587,   588,   589,   590,   591,
     592,   593,   594,   598,   614,   615,   618,   635,   656,   671,
     688,   689,   696,   697,   705,   719,   729,   738,   747,   758,
     767,   774,   782,   790,   797,   807,   817,   827,   837,   847,
     857,   865,   874,   884,   894,   903,   912,   921,   930,   938,
     948,   952,   956,   960,   967,   971,   975,   979,   983,   987,
     995,  1009,  1029,  1045,  1073,  1086,  1093,  1101,  1107,  1116,
    1126,  1137,  1138,  1145,  1153,  1156,  1157,  1159,  1171,  1187,
    1207,  1237,  1245,  1250,  1255,  1256,  1259,  1260,  1263,  1268,
    1273,  1278,  1286,  1291,  1292,  1293,  1294,  1295,  1296,  1297,
    1300,  1313,  1318,  1327,  1346,  1347,  1348,  1349,  1350,  1351,
    1352,  1353,  1356,  1357,  1358,  1359,  1360,  1361,  1362,  1363,
    1364,  1365,  1366,  1367,  1368,  1369,  1370,  1371
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
  "args", "parameters", "parameter", "funcName", "funcArgs",
  "blocoComandos", "comando", "comandos", "comandoSimples",
  "comandosSemVirgula", "ifThenElse", "optElse", "foreach", "for",
  "while_do", "do_while", "foreachList", "forList", "switch", "case",
  "localVarDefinition", "negativeOrPositiveIdentifier",
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

#define YYPACT_NINF -223

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-223)))

#define YYTABLE_NINF -54

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -223,    13,   221,  -223,  -223,  -223,  -223,  -223,  -223,   126,
     -19,    14,  -223,   221,   -10,  -223,  -223,  -223,  -223,     7,
       6,   126,    17,    51,  -223,    23,    78,  -223,  -223,    53,
    -223,    58,    72,    74,  -223,    53,  -223,    76,  -223,  -223,
     126,    56,    73,  -223,  -223,  -223,   145,    82,    87,  -223,
    -223,    73,  -223,    90,   126,  -223,    95,    91,  -223,    96,
    -223,  -223,   101,  -223,    58,  -223,  -223,  -223,  -223,  -223,
      56,   169,  -223,  -223,  -223,    97,   105,    73,   369,   369,
     369,   152,    70,   116,   118,   133,  -223,  -223,   289,   159,
     135,  -223,   169,   134,   146,  -223,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,     4,  -223,  -223,
      62,   369,   369,   183,  -223,  -223,  -223,  -223,  -223,  -223,
      -4,   369,   369,   369,   369,   369,   369,   369,     4,  -223,
     239,    62,   260,  -223,   153,  -223,   166,   176,   157,   177,
     185,   189,   369,   186,  -223,  -223,  -223,   305,   369,   369,
     191,   369,   188,   211,  -223,  -223,  -223,   196,   196,   196,
     196,   193,   194,   201,   369,   197,   202,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
     369,  -223,   369,   369,  -223,  -223,   225,   210,   212,  -223,
     229,   213,   208,  -223,  -223,  -223,   -23,  -223,  -223,   207,
    -223,    18,  -223,   100,   399,   214,  -223,  -223,  -223,  -223,
     253,   252,   369,   223,  -223,  -223,  -223,  -223,   153,   406,
    -223,   245,   425,   369,    73,   337,  -223,   -20,   369,   369,
    -223,     0,     4,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
     192,   312,  -223,  -223,  -223,    73,    73,   227,   209,  -223,
    -223,  -223,  -223,  -223,   432,  -223,  -223,  -223,  -223,   -13,
    -223,  -223,  -223,   369,   236,   369,  -223,  -223,   100,   369,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
     271,  -223,  -223,   238,  -223,  -223,  -223,  -223,   369,    73,
    -223,    75,  -223,  -223,   235,    73,  -223,  -223,  -223,  -223,
     369,   369,   100,  -223,  -223,  -223,    32,    73,  -223
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     4,     1,    19,    20,    21,    22,    23,     0,
       0,     0,     2,     4,     0,     6,     3,    25,    24,     0,
       0,     0,     3,     0,     7,     0,    27,     5,    47,     0,
      48,    15,     0,     0,    13,     0,    12,     0,    11,    26,
       0,    42,     0,    16,    17,    18,     0,     0,    38,    36,
      10,     0,    41,     0,     0,    29,     0,     0,    43,    45,
       3,     8,     0,    37,    15,    14,     9,    28,    46,    49,
       0,     3,    40,    39,    44,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64,    65,     0,     0,
       0,    72,     3,     0,     0,    55,    67,    58,    59,    68,
      69,    70,    52,    60,    61,    62,    56,    57,    63,    66,
      71,     0,     0,     0,   164,   165,   167,   166,   168,   169,
     161,     0,     0,     0,     0,     0,     0,     0,   170,   124,
     145,   171,   144,   153,   126,   141,     0,     0,     0,     0,
       0,     0,     0,     0,   135,   136,    89,     0,     0,     0,
       0,     0,     0,    93,    54,    50,    51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   155,   154,   157,
     156,   158,   159,   185,   184,   182,   183,   178,   179,   172,
     173,   180,   147,   174,   175,   186,   187,   181,   176,   177,
       0,   146,     0,     0,   125,    87,    91,     0,     0,    86,
      90,     0,     0,    85,   130,   134,     0,   131,   133,     0,
     120,     0,   137,     0,     0,     0,   148,   150,   149,   151,
       0,     0,     0,     0,   162,   152,   143,   142,   127,     0,
      88,    92,     0,     0,     0,     0,   129,     0,     0,     0,
      82,     0,     0,    30,    31,    32,    33,    34,    35,   100,
       0,     0,   108,   101,   109,     0,     0,     0,   160,   128,
      96,   106,    97,   107,     0,    94,   104,    95,   105,     0,
      80,    84,   132,     0,     0,     0,   122,   138,     0,     0,
     118,   119,   113,   112,   117,   115,   116,   111,   110,   114,
      74,    78,    79,     0,    98,   102,    99,   103,     0,     0,
     121,     0,   139,    83,     0,     0,    73,   163,    81,    76,
       0,     0,     0,    75,   123,   140,     0,     0,    77
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -223,  -223,     8,   272,  -223,  -223,  -223,  -223,    -2,    -5,
    -223,  -223,  -193,  -223,  -223,   220,  -223,  -223,  -223,   232,
    -223,  -223,   268,   -39,  -223,   216,  -223,  -211,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,    -6,  -223,  -223,  -223,  -222,
     -32,  -223,  -223,  -223,    81,   -66,  -223,    77,  -205,  -223,
    -223,   -24,  -223,   -70,    80,  -223,   179
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    89,    12,    13,    24,    36,    46,    18,    55,
      40,    56,   252,    15,    32,    47,    48,    26,    57,    58,
      59,    16,    42,    91,    92,    93,    94,    95,    96,   306,
      97,    98,    99,   100,   269,   241,   101,   102,   103,   253,
     254,   104,   105,   106,   194,   128,   206,   207,   151,   108,
     109,   208,   130,   131,   132,   133,   190
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,   110,   240,    61,    19,   107,   239,   262,     2,    25,
     267,    14,    65,     3,   144,   145,    33,     4,     5,     6,
       7,     8,   110,   235,    29,    20,   107,   236,   283,   288,
      35,    21,   275,   298,    28,    53,   261,   299,   113,   266,
     157,   158,   296,   273,    62,   147,   278,   164,   279,    67,
     274,    30,   144,   145,   129,   134,   135,    31,    22,     4,
       5,     6,     7,     8,    34,    23,   165,   303,    71,    90,
      38,   295,    54,     4,     5,     6,     7,     8,   278,   137,
     140,   238,   317,    43,    44,    45,   138,   161,   162,    37,
      90,   216,   217,   218,   219,    39,   311,   166,   159,   160,
      17,   240,    41,     4,     5,     6,     7,     8,    75,   144,
     145,    76,    77,    78,   139,    80,    81,    82,   202,    49,
      84,    50,    86,    87,   209,   210,    60,   212,    52,     4,
       5,     6,     7,     8,    63,    64,   198,    66,   310,    68,
     223,    69,    70,   110,    88,    72,   111,   242,     4,     5,
       6,     7,     8,    60,   112,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,   141,   226,   142,   227,   228,
      17,   143,     4,     5,     6,     7,     8,    75,   152,   153,
      76,    77,    78,    79,    80,    81,    82,    83,   155,    84,
      85,    86,    87,   156,   163,   271,   136,   263,   257,   193,
     268,   197,   167,   168,   169,   170,   171,   172,   110,   270,
     195,    90,   242,    88,   276,   277,   290,   291,   284,   289,
     196,   199,    60,   -53,     4,     5,     6,     7,     8,   200,
     280,   281,   297,   201,   203,   211,   282,   213,     9,   214,
     215,   224,   110,   220,   221,    10,   242,   250,   251,   300,
     222,   302,   225,   229,   230,   304,   231,   232,   234,   237,
     309,   233,   255,   147,   256,    11,   313,   173,   174,   175,
     176,   177,   178,   264,   308,   258,    90,   292,   318,   293,
     301,   305,   307,   312,    73,    27,   314,   315,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,    74,    51,   187,   188,   316,   189,   154,   259,
      90,   192,   272,     0,     0,   179,   180,   181,   191,   183,
     184,   185,   186,   144,   145,   187,   188,     0,   189,     0,
       0,     0,     0,   146,     0,     0,     0,     0,   147,     0,
     148,     0,     0,   114,   115,   116,   117,   118,   119,   120,
     285,   286,   149,     0,   121,   204,   287,     0,     0,   150,
     122,   123,     0,     0,   124,     0,     0,   250,   251,   125,
     126,     0,   127,     0,   205,   114,   115,   116,   117,   118,
     119,   120,     0,     0,     0,     0,   121,     0,     0,     0,
       0,     0,   122,   123,     0,     0,   124,     0,     0,     0,
       0,   125,   126,     0,   127,     0,   205,   114,   115,   116,
     117,   118,   119,   120,     0,     0,     0,     0,   121,     0,
       0,     0,     0,     0,   122,   123,     0,     0,   124,     0,
       0,     0,     0,   125,   126,     0,   127,   243,   244,   245,
     246,   247,   248,   249,   243,   244,   245,   246,   247,   248,
     260,     0,     0,     0,   250,   251,     0,     0,     0,     0,
       0,   250,   251,   243,   244,   245,   246,   247,   248,   265,
     243,   244,   245,   246,   247,   248,   294,     0,     0,     0,
     250,   251,     0,     0,     0,     0,     0,   250,   251
};

static const yytype_int16 yycheck[] =
{
       2,    71,   213,    42,     9,    71,   211,   229,     0,    11,
     232,    13,    51,     0,    34,    35,    21,     3,     4,     5,
       6,     7,    92,    46,    16,    44,    92,    50,   250,   251,
      22,    17,   237,    46,    44,    40,   229,    50,    77,   232,
      36,    37,   264,    63,    46,    49,    46,    51,    48,    54,
      70,    44,    34,    35,    78,    79,    80,    51,    44,     3,
       4,     5,     6,     7,    47,    51,    70,   278,    60,    71,
      47,   264,    16,     3,     4,     5,     6,     7,    46,    81,
      82,    63,    50,    25,    26,    27,    16,   111,   112,    38,
      92,   157,   158,   159,   160,    17,   301,   121,    36,    37,
      44,   312,    49,     3,     4,     5,     6,     7,     8,    34,
      35,    11,    12,    13,    44,    15,    16,    17,   142,    47,
      20,    47,    22,    23,   148,   149,    53,   151,    52,     3,
       4,     5,     6,     7,    52,    48,   138,    47,    63,    44,
     164,    50,    46,   213,    44,    44,    49,   213,     3,     4,
       5,     6,     7,    53,    49,     3,     4,     5,     6,     7,
       3,     4,     5,     6,     7,    49,   190,    49,   192,   193,
      44,    38,     3,     4,     5,     6,     7,     8,    19,    44,
      11,    12,    13,    14,    15,    16,    17,    18,    54,    20,
      21,    22,    23,    47,    11,   234,    44,   229,   222,    46,
     232,    44,   122,   123,   124,   125,   126,   127,   278,   233,
      44,   213,   278,    44,   238,   239,   255,   256,   250,   251,
      44,    44,    53,    54,     3,     4,     5,     6,     7,    44,
      38,    39,   264,    44,    48,    44,    44,    49,    17,    28,
      44,    44,   312,    50,    50,    24,   312,    55,    56,   273,
      49,   275,    50,    28,    44,   279,    44,    28,    50,    52,
     299,    48,     9,    49,    12,    44,   305,    28,    29,    30,
      31,    32,    33,    28,   298,    52,   278,    50,   317,    70,
      44,    10,    44,    48,    64,    13,   310,   311,    28,    29,
      30,    31,    32,    33,    55,    56,    57,    58,    59,    60,
      61,    62,    70,    35,    65,    66,   312,    68,    92,   228,
     312,   132,   235,    -1,    -1,    55,    56,    57,    58,    59,
      60,    61,    62,    34,    35,    65,    66,    -1,    68,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    49,    -1,
      51,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      38,    39,    63,    -1,    49,    50,    44,    -1,    -1,    70,
      55,    56,    -1,    -1,    59,    -1,    -1,    55,    56,    64,
      65,    -1,    67,    -1,    69,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    59,    -1,    -1,    -1,
      -1,    64,    65,    -1,    67,    -1,    69,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    55,    56,    -1,    -1,    59,    -1,
      -1,    -1,    -1,    64,    65,    -1,    67,    38,    39,    40,
      41,    42,    43,    44,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,
      -1,    55,    56,    38,    39,    40,    41,    42,    43,    44,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      55,    56,    -1,    -1,    -1,    -1,    -1,    55,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    72,    73,     0,     3,     4,     5,     6,     7,    17,
      24,    44,    74,    75,    79,    84,    92,    44,    79,    80,
      44,    17,    44,    51,    76,    79,    88,    74,    44,    73,
      44,    51,    85,    80,    47,    73,    77,    38,    47,    17,
      81,    49,    93,    25,    26,    27,    78,    86,    87,    47,
      47,    93,    52,    80,    16,    80,    82,    89,    90,    91,
      53,    94,    79,    52,    48,    94,    47,    80,    44,    50,
      46,    73,    44,    86,    90,     8,    11,    12,    13,    14,
      15,    16,    17,    18,    20,    21,    22,    23,    44,    73,
      79,    94,    95,    96,    97,    98,    99,   101,   102,   103,
     104,   107,   108,   109,   112,   113,   114,   116,   120,   121,
     124,    49,    49,    94,    38,    39,    40,    41,    42,    43,
      44,    49,    55,    56,    59,    64,    65,    67,   116,   122,
     123,   124,   125,   126,   122,   122,    44,    79,    16,    44,
      79,    49,    49,    38,    34,    35,    44,    49,    51,    63,
      70,   119,    19,    44,    96,    54,    47,    36,    37,    36,
      37,   122,   122,    11,    51,    70,   122,   125,   125,   125,
     125,   125,   125,    28,    29,    30,    31,    32,    33,    55,
      56,    57,    58,    59,    60,    61,    62,    65,    66,    68,
     127,    58,   127,    46,   115,    44,    44,    44,    79,    44,
      44,    44,   122,    48,    50,    69,   117,   118,   122,   122,
     122,    44,   122,    49,    28,    44,   116,   116,   116,   116,
      50,    50,    49,   122,    44,    50,   122,   122,   122,    28,
      44,    44,    28,    48,    50,    46,    50,    52,    63,   119,
      98,   106,   116,    38,    39,    40,    41,    42,    43,    44,
      55,    56,    83,   110,   111,     9,    12,   122,    52,   115,
      44,    83,   110,   111,    28,    44,    83,   110,   111,   105,
     122,    94,   118,    63,    70,   119,   122,   122,    46,    48,
      38,    39,    44,   110,   111,    38,    39,    44,   110,   111,
      94,    94,    50,    70,    44,    83,   110,   111,    46,    50,
     122,    44,   122,    98,   122,    10,   100,    44,   122,    94,
      63,   119,    48,    94,   122,   122,   106,    50,    94
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    73,    74,    74,    75,    75,    75,    76,
      76,    76,    76,    77,    77,    78,    78,    78,    78,    79,
      79,    79,    79,    79,    80,    80,    81,    81,    82,    82,
      83,    83,    83,    83,    83,    83,    84,    85,    86,    86,
      87,    88,    89,    89,    90,    90,    91,    92,    92,    93,
      94,    95,    95,    96,    96,    97,    97,    97,    97,    97,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    99,   100,   100,   101,   102,   103,   104,
     105,   105,   106,   106,   107,   108,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     110,   110,   110,   110,   111,   111,   111,   111,   111,   111,
     112,   112,   112,   112,   113,   114,   114,   115,   115,   116,
     116,   117,   117,   118,   118,   119,   119,   120,   120,   120,
     120,   121,   122,   122,   122,   122,   123,   123,   124,   124,
     124,   124,   125,   125,   125,   125,   125,   125,   125,   125,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     0,     2,     1,     2,     4,     4,
       3,     2,     2,     1,     3,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     4,     3,     1,     3,
       3,     3,     0,     1,     3,     1,     2,     2,     3,     3,
       4,     2,     1,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     7,     0,     2,     7,    10,     6,     6,
       1,     3,     1,     3,     5,     3,     3,     3,     4,     2,
       3,     3,     4,     2,     5,     5,     5,     5,     6,     6,
       4,     4,     6,     6,     5,     5,     5,     5,     4,     4,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     6,     5,     8,     2,     3,     2,     2,     3,     4,
       3,     1,     3,     1,     1,     1,     1,     3,     5,     6,
       8,     2,     3,     3,     1,     1,     2,     2,     3,     3,
       3,     3,     3,     1,     2,     2,     2,     2,     2,     2,
       4,     1,     3,     6,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
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
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 4: /* TK_PR_FLOAT  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 5: /* TK_PR_BOOL  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 6: /* TK_PR_CHAR  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 7: /* TK_PR_STRING  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 8: /* TK_PR_IF  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 9: /* TK_PR_THEN  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 10: /* TK_PR_ELSE  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 11: /* TK_PR_WHILE  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 12: /* TK_PR_DO  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 13: /* TK_PR_INPUT  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 14: /* TK_PR_OUTPUT  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 15: /* TK_PR_RETURN  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 16: /* TK_PR_CONST  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 17: /* TK_PR_STATIC  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 18: /* TK_PR_FOREACH  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 19: /* TK_PR_FOR  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 20: /* TK_PR_SWITCH  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 21: /* TK_PR_CASE  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 22: /* TK_PR_BREAK  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 23: /* TK_PR_CONTINUE  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 24: /* TK_PR_CLASS  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 25: /* TK_PR_PRIVATE  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 26: /* TK_PR_PUBLIC  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 27: /* TK_PR_PROTECTED  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 28: /* TK_OC_LE  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 29: /* TK_OC_GE  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 30: /* TK_OC_EQ  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 31: /* TK_OC_NE  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 32: /* TK_OC_AND  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 33: /* TK_OC_OR  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 34: /* TK_OC_SL  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 35: /* TK_OC_SR  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 36: /* TK_OC_FORWARD_PIPE  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 37: /* TK_OC_BASH_PIPE  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 38: /* TK_LIT_INT  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 39: /* TK_LIT_FLOAT  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 40: /* TK_LIT_FALSE  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 41: /* TK_LIT_TRUE  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 42: /* TK_LIT_CHAR  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 43: /* TK_LIT_STRING  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 44: /* TK_IDENTIFICADOR  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 45: /* TOKEN_ERRO  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 46: /* ','  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 47: /* ';'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 48: /* ':'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 49: /* '('  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 50: /* ')'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 51: /* '['  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 52: /* ']'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 53: /* '{'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 54: /* '}'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 55: /* '+'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 56: /* '-'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 57: /* '|'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 58: /* '?'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 59: /* '*'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 60: /* '/'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 61: /* '<'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 62: /* '>'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 63: /* '='  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 64: /* '!'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 65: /* '&'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
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

    case 66: /* '%'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2247 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 67: /* '#'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2261 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 68: /* '^'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2275 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 69: /* '.'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2289 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 70: /* '$'  */
#line 197 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2303 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 72: /* programa  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2313 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 74: /* componentes  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2323 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 75: /* componente  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2333 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 76: /* depoisDeIdent  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2343 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 77: /* fechaVarOuFunc  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2353 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 78: /* encapsulamento  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2363 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 79: /* tiposPrimitivos  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2373 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 80: /* tipo  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2383 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 81: /* static  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2393 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 82: /* tipoConst  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2403 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 83: /* literais  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2413 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 84: /* novoTipo  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2423 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 85: /* listaCampos  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2433 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 86: /* list  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2443 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 87: /* campo  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2453 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 88: /* tamanhoVetor  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2463 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 89: /* args  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2473 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 90: /* parameters  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2483 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 91: /* parameter  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2493 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 92: /* funcName  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2503 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 93: /* funcArgs  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2513 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 94: /* blocoComandos  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2523 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 95: /* comando  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2533 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 96: /* comandos  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2543 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 97: /* comandoSimples  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2553 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 98: /* comandosSemVirgula  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2563 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 99: /* ifThenElse  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2573 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 100: /* optElse  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2583 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 101: /* foreach  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2593 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 102: /* for  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2603 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 103: /* while_do  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2613 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 104: /* do_while  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2623 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 105: /* foreachList  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2633 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 106: /* forList  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2643 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 107: /* switch  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2653 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 108: /* case  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2663 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 109: /* localVarDefinition  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2673 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 110: /* negativeOrPositiveIdentifier  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2683 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 111: /* negativeOrPositiveLiteral  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2693 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 112: /* assignment  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2703 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 113: /* input  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2713 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 114: /* output  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2723 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 115: /* continueOutput  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2733 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 116: /* funcCall  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2743 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 117: /* argsCall  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2753 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 118: /* argCall  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2763 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 119: /* shiftOp  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2773 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 120: /* shift  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2783 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 121: /* return  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2793 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 122: /* expression  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2803 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 123: /* infiniteQuestionMarks  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2813 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 124: /* pipe  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2823 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 125: /* parenthesisOrOperand  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2833 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 126: /* operands  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2843 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 127: /* operators  */
#line 206 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2853 "parser.tab.c" /* yacc.c:1257  */
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
#line 231 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast); arvore = (yyval.ast); 
		parsingSucceded = TRUE;
		closeTable(); // fecha escopo global
	}
#line 3121 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 239 "parser/parser.y" /* yacc.c:1646  */
    {initTable();}
#line 3127 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 243 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3133 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 244 "parser/parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3139 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 247 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3145 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 248 "parser/parser.y" /* yacc.c:1646  */
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
#line 3243 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 342 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		//funcName tem 2 formas possíveis:
		// 1) head = tipoPrimitivo, kids[0] = nome da func
		// 2) head = TK_PR_STATIC, kids[0] = tipo, kids[1] = nome DA FUNC		
		int kid = 0;
		if((yyvsp[-3].ast)->kidsNumber == 2){
			kid = 1;
		}
			
		addArgsToSymbol((yyvsp[-3].ast)->kids[kid]->token->value.str, currentArgs);
		//printArgs($1->kids[kid]->token->value.str);
		clearCurrentArgs();
		closeTable();
		
	}
#line 3266 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 363 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3277 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 369 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3287 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 374 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3296 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 378 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3305 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 384 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3311 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 385 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		closeTable();
	}
#line 3321 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 394 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3327 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 395 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3333 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 396 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3339 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 397 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3345 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 400 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3351 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 401 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3357 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 402 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3363 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 403 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3369 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 404 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3375 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 407 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3381 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 408 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3387 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 411 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3393 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 412 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3399 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 415 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3405 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 416 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3411 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 419 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3417 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 420 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3423 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 421 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3429 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 422 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3435 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 423 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3441 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 424 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3447 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 429 "parser/parser.y" /* yacc.c:1646  */
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
#line 3463 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 441 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3473 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 448 "parser/parser.y" /* yacc.c:1646  */
    {adicionaCampo(criaCampo((yyvsp[0].ast))); (yyval.ast) = (yyvsp[0].ast);}
#line 3479 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 449 "parser/parser.y" /* yacc.c:1646  */
    {		
		adicionaCampo(criaCampo((yyvsp[-2].ast)));

		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3491 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 458 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3501 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 467 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3511 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 475 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3517 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 476 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3523 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 479 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		
		adicionaArg(criaArg((yyvsp[-2].ast)));

		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));

	}
#line 3537 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 488 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); adicionaArg(criaArg((yyvsp[0].ast)));}
#line 3543 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 491 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		//tipo const = TK_PR_CONST tipo || tipo
		int flag = 0;
		struct node* aux = (yyvsp[-1].ast);
		if ((yyvsp[-1].ast)->kidsNumber==2){
			flag = CONST;
			aux = (yyvsp[-1].ast)->kids[0];
		}
		int type = getType(aux);
		if (type == USER){
			int isUsr = isUserType(aux->token->value.str);
			if(isUsr!=TRUE) exit(isUsr);
			int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType(aux), 0, FALSE, flag);		
			if(addSymb!=0) exit(addSymb);
		}	
		else{	
			int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, type, NULL, 0, FALSE, flag);		
			if(addSymb!=0) exit(addSymb);
		}
	}
#line 3569 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 516 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, TRUE, 0);		
		if(addSymb!=0) exit(addSymb);
		saveFunc((yyvsp[0].valor_lexico)->value.str);	
	}
#line 3581 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 523 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[-1].ast));	
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int type = getType((yyvsp[-1].ast));
		if(type == USER){
			int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyvsp[-1].ast)), 0, TRUE, STATIC);
			if(addSymb!=0) exit(addSymb);
		}
		else{
			int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, type, NULL, 0, TRUE, STATIC);
			if(addSymb!=0) exit(addSymb);
		}
		saveFunc((yyvsp[0].valor_lexico)->value.str);	

	}
#line 3602 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 543 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[-1].ast));
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3612 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 555 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		closeTable();                     //Fecha escopo local
	}
#line 3623 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 563 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 3629 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 564 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3635 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 567 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3641 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 568 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3647 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 573 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3653 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 574 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3659 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 575 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3665 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 576 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3671 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 577 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3677 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 582 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3683 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 583 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3689 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 584 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3695 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 585 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3701 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 586 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3707 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 587 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3713 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 588 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3719 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 589 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3725 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 590 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3731 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 591 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3737 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 592 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3743 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 593 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3749 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 594 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3755 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 598 "parser/parser.y" /* yacc.c:1646  */
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
#line 3774 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 614 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3780 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 615 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3786 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 618 "parser/parser.y" /* yacc.c:1646  */
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
#line 3802 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 635 "parser/parser.y" /* yacc.c:1646  */
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
#line 3825 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 656 "parser/parser.y" /* yacc.c:1646  */
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
#line 3843 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 671 "parser/parser.y" /* yacc.c:1646  */
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
#line 3861 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 688 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3867 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 689 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3877 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 696 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3883 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 697 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3893 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 705 "parser/parser.y" /* yacc.c:1646  */
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
#line 3910 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 719 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3920 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 729 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = isUserType((yyvsp[-1].valor_lexico)->value.str);
		if (isUsr !=TRUE) exit(isUsr);
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)->kids[0]), 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 3934 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 738 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = isUserType((yyvsp[-1].valor_lexico)->value.str);
		if (isUsr !=TRUE) exit(isUsr);
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)->kids[0]), 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
#line 3948 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 747 "parser/parser.y" /* yacc.c:1646  */
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
#line 3964 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 758 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = isUserType((yyvsp[-1].valor_lexico)->value.str);
		if (isUsr !=TRUE) exit(isUsr);
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)), 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
		
	}
#line 3978 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 767 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 3990 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 774 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
		
	}
#line 4003 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 782 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 4016 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 790 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
	}
#line 4027 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 797 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
		
	}
#line 4042 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 807 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 4057 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 817 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
#line 4072 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 827 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
#line 4087 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 837 "parser/parser.y" /* yacc.c:1646  */
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
#line 4102 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 847 "parser/parser.y" /* yacc.c:1646  */
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
#line 4117 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 857 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
	}
#line 4130 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 865 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
	}
#line 4143 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 874 "parser/parser.y" /* yacc.c:1646  */
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
#line 4158 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 884 "parser/parser.y" /* yacc.c:1646  */
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
#line 4173 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 894 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 4187 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 903 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb!=0) exit(addSymb);
	}
#line 4201 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 912 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
#line 4215 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 921 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
#line 4229 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 930 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, 0);
		if(addSymb!=0) exit(addSymb);
	}
#line 4242 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 938 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb!=0) exit(addSymb);
	}
#line 4255 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 948 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4264 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 952 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4273 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 956 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4282 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 960 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4291 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 967 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4300 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 971 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4309 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 975 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4318 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 979 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4327 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 983 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4336 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 987 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4345 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 995 "parser/parser.y" /* yacc.c:1646  */
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
		//printCurrentOperands();
		clearCurrentOperands();
	}
#line 4364 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1009 "parser/parser.y" /* yacc.c:1646  */
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
#line 4389 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1029 "parser/parser.y" /* yacc.c:1646  */
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
#line 4410 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1045 "parser/parser.y" /* yacc.c:1646  */
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
#line 4441 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1073 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[0].ast)->token->tokenType!=IDS) exit(ERR_WRONG_PAR_INPUT);
		int isVar = isVariable((yyvsp[0].ast)->token->value.str);
		if(isVar!=TRUE) exit(ERR_VARIABLE);	
	}
#line 4452 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1086 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[-1].ast)->type != INT && (yyvsp[-1].ast)->type != FLOAT && (yyvsp[-1].ast)->token->literType!=STRING)
			exit(ERR_WRONG_PAR_OUTPUT);
	}
#line 4464 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1093 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[0].ast)->type != INT && (yyvsp[0].ast)->type != FLOAT && (yyvsp[0].ast)->token->literType!=STRING)
			exit(ERR_WRONG_PAR_OUTPUT);
	}
#line 4475 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1101 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[0].ast)->type != INT && (yyvsp[0].ast)->type != FLOAT && (yyvsp[0].ast)->token->literType!=STRING)
			exit(ERR_WRONG_PAR_OUTPUT);
	}
#line 4486 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1107 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[-1].ast)->type != INT && (yyvsp[-1].ast)->type != FLOAT && (yyvsp[-1].ast)->token->literType!=STRING)
			exit(ERR_WRONG_PAR_OUTPUT);
	}
#line 4498 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1116 "parser/parser.y" /* yacc.c:1646  */
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
#line 4513 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1126 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isFunc = isFunction((yyvsp[-2].valor_lexico)->value.str);
		if(isFunc!=TRUE) exit(isFunc);
		int correctArgs = verifyArguments((yyvsp[-2].valor_lexico)->value.str, NULL);
		if(correctArgs != TRUE) exit(correctArgs);
	}
#line 4527 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1137 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1138 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4543 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1145 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);
		parseOperands((yyvsp[0].ast));
		int correctOperands =  coercion(NONE, (yyvsp[0].ast));
		printf("tipo da expressao: %d\n", (yyvsp[0].ast)->type);
		if (correctOperands != 0) exit(correctOperands);
		printf("tipo da expressao: %d\n", (yyvsp[0].ast)->type);
		clearCurrentOperands();
	}
#line 4556 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1153 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4562 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1156 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4568 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1157 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4574 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1159 "parser/parser.y" /* yacc.c:1646  */
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
#line 4591 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1171 "parser/parser.y" /* yacc.c:1646  */
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
#line 4612 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1187 "parser/parser.y" /* yacc.c:1646  */
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
#line 4637 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1207 "parser/parser.y" /* yacc.c:1646  */
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
#line 4668 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1237 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int verifRet = verifyReturn((yyvsp[0].ast));
		if (verifRet!=TRUE) exit(verifRet);	
	}
#line 4678 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1245 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4688 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1250 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4698 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1255 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4704 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1256 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4710 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1259 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 4716 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1260 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 4722 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1263 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4732 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1268 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4742 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1273 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4752 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1278 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4762 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1286 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4772 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1291 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4778 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1292 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4784 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1293 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4790 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1294 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4796 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1295 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4802 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1296 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4808 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1297 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 4814 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1300 "parser/parser.y" /* yacc.c:1646  */
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
#line 4832 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1313 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));
		int isVar = isVariable((yyvsp[0].valor_lexico)->value.str);
		if (isVar != TRUE) exit(isVar);
	}
#line 4842 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1318 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoCampo((yyvsp[0].valor_lexico), (yyvsp[-2].valor_lexico)->value.str));
		int isUsr = isUserVar((yyvsp[-2].valor_lexico)->value.str);
		if(isUsr!=TRUE) exit(isUsr);
		int hasF = hasField((yyvsp[-2].valor_lexico)->value.str, (yyvsp[0].valor_lexico)->value.str);
		if(hasF != TRUE) exit(hasF);
	}
#line 4856 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1327 "parser/parser.y" /* yacc.c:1646  */
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
#line 4880 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1346 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4886 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1347 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4892 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1348 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4898 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1349 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4904 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1350 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4910 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1351 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4916 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1352 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4922 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1353 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4928 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1356 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4934 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1357 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4940 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1358 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4946 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1359 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4952 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1360 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4958 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1361 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4964 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1362 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4970 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1363 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4976 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1364 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4982 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1365 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4988 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1366 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4994 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1367 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5000 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1368 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5006 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1369 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5012 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1370 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5018 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1371 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5024 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 5028 "parser.tab.c" /* yacc.c:1646  */
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
#line 1374 "parser/parser.y" /* yacc.c:1906  */



