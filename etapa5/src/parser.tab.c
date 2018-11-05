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
#include "../include/parser.tab.h" 
#include "../include/iloc.h"
#include "../include/naming.h"
#include "../include/util.h"

int yylex(void);
extern int get_line_number(void);

int yyerror (char const *s){
	printf("%s, on line %d\n", s, get_line_number());
	return -1;
}

extern void* arvore;

extern Fields *currentFields;
extern Args *currentArgs;
extern char *currentFunc;

extern int yylex_destroy  (void); 

////////////////////////////////////////////////////////////////////////////////
/// Variáveis firstID e secondID usadas quando um componente de uma entrada  ///
/// válida da gramática começa com dois identificadores. Elas são            ///
/// necessárias, pois não se sabe se o componente é uma variável global ou   ///
/// uma função de tipos de usuário, no entanto, para que não exista          ///
/// conflitos gramáticais, foi necessário criar regras que processassem um   ///
/// identificador e depois diferenciassem se é uma função ou variável global ///
/// mas essas regras não teriam acesso aos identificadores já processados    ///
/// portanto os nodos da ast correspondentes a esses identificadores devem   ///
/// são salvos nessas variáveis para que o processamento adequado para cada  ///
/// caso seja possível                                                       ///
//////////////////////////////////////////////////////////////////////////////// 
struct node* firstID;
struct node* secondID;

////////////////////////////////////////////////////////////////////////////////
/// Variável inpPipe usada para salvar o nodo de uma expressão de pipe que   ///
/// será passado para uma função, é necessário para fazer a correta          ///
/// verificação de tipos dos argumentos da chamada de função com os          ///
/// parâmetros formais da função                                             ///
////////////////////////////////////////////////////////////////////////////////
struct node* inpPipe;


int parsingSucceded = FALSE;
int returnError = 1;
Node *nodeNotAdded = NULL;
char *identifierError;
extern Node *danglingNodes;
//necessários para casos especiais na verificação de expressões
int isInput = FALSE;
int isReturn = FALSE;

//Retorna constante representando o tipo, o nodo da ast passado deve ser ou da
//regra tipo, ou da regra tipoPrimitivo
int getType(struct node* type){
	if (strcmp(type->token->value.str, "int") == 0) return INT;
	if (strcmp(type->token->value.str, "float") == 0) return FLOAT;
	if (strcmp(type->token->value.str, "char") == 0) return CHAR;
	if (strcmp(type->token->value.str, "bool") == 0) return BOOL;
	if (strcmp(type->token->value.str, "string") == 0) return STRING;
	return USER;
}

//opera sobre regra tipo obtém o nome do tipo de usuário
char* getUserType(struct node* type){
	if (getType(type) != USER){
		return NULL;
	}
	else return type->token->value.str;
}

int verifyArguments(char* symbol, struct node* argsCall){
	Hash* func = getSymbol(symbol);
	int argsNum = func->argsNum;
	if(argsCall == NULL){ // chamada de função sem argumentos
		if (argsNum == 0) return TRUE;
		return ERR_MISSING_ARGS;
	}
	if(argsNum == 0){ // argsCall não é nulo mas a função exige 0 argumentos
		return ERR_EXCESS_ARGS;
	}
	/* estrutura de argsCall:
		* Cabeça = NULL -> facilita verificação de excesso ou falta de argumentos
		* kids[0], kids[2], kids[4], ..., kids[(argsNum - 1) * 2] -> argCall ->
			contém expressão que representa o argumento
		* kids[1], kids[3], kids[5], ..., kids[(argsNum-1)*2 - 1] -> vírgula
	*/
	if(argsCall->kidsNumber < 2*argsNum -1) return ERR_MISSING_ARGS;
	if(argsCall->kidsNumber > 2*argsNum -1) return ERR_EXCESS_ARGS;
	int currentArg = 0;	
	for(int i = 0; i <= ((argsNum-1)* 2); i+=2){
		
		if (argsCall->kids[i] != NULL)
			if (argsCall->kids[i]->token == NULL || 
				(!(argsCall->kids[i]->token->tokenType == SPEC_CHAR || 
				   argsCall->kids[i]->token->value.c == '.')) )
			{		
				
				int correctOperands =  coercion(func->args[currentArg]->argType, argsCall->kids[i]);
				if (correctOperands != 0){ return ERR_WRONG_TYPE_ARGS; }
				
			}else{ // verifica argumentos em uma expressão em pipe
				if(inpPipe==NULL) return ERR_WRONG_TYPE_ARGS;
				else{
					Hash* inPipeFunc = getSymbol(inpPipe->token->value.str);
					if (inPipeFunc->type != func->args[currentArg]->argType){
						return ERR_WRONG_TYPE_ARGS;
					} 

				}
			}
		currentArg++;
	}
	return TRUE;
}

//age sobre regra negativeOrPositiveIdentifier para obter o identificador 
//que é a folha da regra
char* getIdFromNegOrPosId(struct node* negOrPosId){
	
	struct node* aux = negOrPosId;
	do{
		aux = aux->kids[0];
	}while(aux->token->tokenType != IDS);
	return aux->token->value.str;
}



#line 206 "parser.tab.c" /* yacc.c:339  */

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
    TK_OC_SL = 283,
    TK_OC_SR = 284,
    TK_OC_FORWARD_PIPE = 285,
    TK_OC_BASH_PIPE = 286,
    TK_LIT_INT = 287,
    TK_LIT_FLOAT = 288,
    TK_LIT_FALSE = 289,
    TK_LIT_TRUE = 290,
    TK_LIT_CHAR = 291,
    TK_LIT_STRING = 292,
    TK_IDENTIFICADOR = 293,
    TOKEN_ERRO = 294,
    TK_OC_OR = 295,
    TK_OC_AND = 296,
    TK_OC_EQ = 297,
    TK_OC_NE = 298,
    TK_OC_LE = 299,
    TK_OC_GE = 300,
    UMINUS = 301,
    UPLUS = 302,
    UPOINTER = 303,
    UADDRESS = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 143 "parser/parser.y" /* yacc.c:355  */

	struct lexval* valor_lexico;
	struct node* ast;

#line 301 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 318 "parser.tab.c" /* yacc.c:358  */

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
#define YYLAST   674

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  182
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  324

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    67,     2,    69,    74,    60,    50,     2,
      70,    71,    59,    57,    40,    58,    42,    61,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    45,    46,
      54,    41,    56,    68,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    72,     2,    73,    62,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,    49,    43,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    47,    48,    51,    52,    53,
      55,    63,    64,    65,    66
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   308,   308,   316,   320,   321,   330,   334,   338,   339,
     427,   447,   453,   458,   462,   468,   469,   477,   486,   487,
     488,   489,   492,   493,   494,   495,   496,   499,   500,   503,
     504,   507,   508,   511,   512,   513,   514,   515,   516,   521,
     532,   539,   540,   549,   558,   566,   567,   570,   579,   582,
     607,   614,   634,   646,   656,   663,   664,   667,   668,   673,
     674,   675,   676,   677,   682,   683,   684,   685,   686,   687,
     688,   689,   690,   691,   692,   693,   694,   698,   712,   713,
     716,   733,   752,   765,   780,   786,   796,   797,   805,   817,
     827,   836,   845,   856,   865,   872,   880,   888,   895,   913,
     930,   949,   964,   983,   998,  1016,  1030,  1046,  1058,  1073,
    1084,  1102,  1113,  1128,  1140,  1145,  1152,  1157,  1167,  1172,
    1179,  1186,  1191,  1198,  1209,  1225,  1245,  1262,  1289,  1298,
    1306,  1321,  1337,  1343,  1352,  1362,  1373,  1377,  1384,  1389,
    1392,  1393,  1395,  1405,  1419,  1435,  1461,  1471,  1475,  1510,
    1545,  1580,  1615,  1650,  1685,  1720,  1755,  1800,  1835,  1870,
    1905,  1940,  1977,  2012,  2047,  2048,  2055,  2058,  2063,  2068,
    2073,  2081,  2094,  2113,  2124,  2144,  2150,  2151,  2152,  2153,
    2154,  2155,  2158
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
  "TK_OC_SL", "TK_OC_SR", "TK_OC_FORWARD_PIPE", "TK_OC_BASH_PIPE",
  "TK_LIT_INT", "TK_LIT_FLOAT", "TK_LIT_FALSE", "TK_LIT_TRUE",
  "TK_LIT_CHAR", "TK_LIT_STRING", "TK_IDENTIFICADOR", "TOKEN_ERRO", "','",
  "'='", "'.'", "'}'", "'{'", "':'", "';'", "TK_OC_OR", "TK_OC_AND", "'|'",
  "'&'", "TK_OC_EQ", "TK_OC_NE", "TK_OC_LE", "'<'", "TK_OC_GE", "'>'",
  "'+'", "'-'", "'*'", "'%'", "'/'", "'^'", "UMINUS", "UPLUS", "UPOINTER",
  "UADDRESS", "'!'", "'?'", "'#'", "'('", "')'", "'['", "']'", "'$'",
  "$accept", "programa", "scopeOpenner", "componentes",
  "idThatCanBeFuncType", "idThatCanBeFuncName", "componente",
  "depoisDeIdent", "fechaVarOuFunc", "userTypeFunc", "encapsulamento",
  "tiposPrimitivos", "tipo", "static", "tipoConst", "literais", "novoTipo",
  "listaCampos", "list", "campo", "tamanhoVetor", "args", "parameters",
  "parameter", "funcName", "funcArgs", "blocoComandos", "blocoSemEscopo",
  "comando", "comandos", "comandoSimples", "comandosSemVirgula",
  "ifThenElse", "optElse", "foreach", "for", "while_do", "do_while",
  "foreachList", "forList", "switch", "case", "localVarDefinition",
  "negativeOrPositiveIdentifier", "negativeOrPositiveLiteral",
  "assignment", "input", "inputHelper", "output", "continueOutput",
  "funcCall", "argsCall", "argCall", "shiftOp", "shift", "return",
  "returnHelper", "expression", "savePipe", "pipe", "operands", YY_NULLPTR
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
      44,    61,    46,   125,   123,    58,    59,   295,   296,   124,
      38,   297,   298,   299,    60,   300,    62,    43,    45,    42,
      37,    47,    94,   301,   302,   303,   304,    33,    63,    35,
      40,    41,    91,    93,    36
};
# endif

#define YYPACT_NINF -227

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-227)))

#define YYTABLE_NINF -167

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -227,     5,   266,  -227,  -227,  -227,  -227,  -227,  -227,   288,
      -4,  -227,  -227,    19,   266,     0,  -227,  -227,  -227,  -227,
       4,   -45,   288,  -227,    17,     8,  -227,    10,    42,  -227,
    -227,     9,  -227,    44,    20,    28,    24,  -227,  -227,  -227,
    -227,  -227,   288,   152,    48,  -227,  -227,  -227,   121,    58,
      76,  -227,  -227,  -227,     9,    87,   288,  -227,   107,    79,
    -227,   112,   190,  -227,   122,  -227,    44,    48,  -227,  -227,
    -227,  -227,   152,    92,    94,   123,   226,   307,   302,   108,
     130,   160,  -227,  -227,    91,  -227,   195,   171,  -227,   190,
     173,   172,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,  -227,   211,  -227,   179,  -227,  -227,   212,    53,
      69,  -227,  -227,  -227,  -227,   226,   226,   215,  -227,  -227,
    -227,  -227,  -227,  -227,   -35,   226,   146,   514,    69,  -227,
     193,   198,   316,   199,   201,   210,   226,   204,  -227,  -227,
    -227,   226,   149,   226,   228,   226,   190,   206,   214,  -227,
    -227,  -227,   226,   226,   239,   239,   239,   239,   389,   414,
     208,   226,   244,   439,   226,   226,   226,   226,   226,   226,
     226,   226,   226,   226,   226,   226,   226,   226,   226,   226,
     226,  -227,  -227,   231,   247,   248,  -227,   236,   252,   464,
    -227,   548,  -227,  -227,   -31,  -227,   548,   308,     3,   548,
     255,   131,   295,   548,   548,   232,  -227,  -227,  -227,  -227,
     294,   304,   226,   335,  -227,  -227,   514,   563,   577,   590,
     602,   612,   612,   277,   277,   277,   277,   111,   111,   262,
     262,   262,   262,   341,  -227,   264,   368,   226,   123,   209,
    -227,   -11,   226,   226,  -227,  -227,   -26,  -227,  -227,  -227,
    -227,  -227,  -227,  -227,  -227,   197,   242,  -227,  -227,  -227,
     123,   123,   489,   251,  -227,  -227,  -227,  -227,  -227,   377,
    -227,  -227,  -227,  -227,   -24,   548,  -227,  -227,   226,   303,
     226,   548,   548,   131,   226,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,  -227,  -227,  -227,   332,  -227,  -227,   305,  -227,
    -227,  -227,  -227,   226,   123,   548,    36,   548,  -227,   532,
     123,  -227,  -227,   548,  -227,   226,   226,   131,  -227,   548,
     548,   -20,   123,  -227
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     4,     1,    22,    23,    24,    25,    26,     0,
       0,     6,     2,     0,     4,     0,     8,     3,    28,    27,
       0,     0,     0,     7,     0,    17,     9,     0,    30,     5,
      50,     0,    51,    18,     0,     0,     0,    15,    14,     3,
      13,    29,     0,    45,     0,    19,    20,    21,     0,     0,
      41,    39,    12,    44,     0,     0,     0,    32,     0,     0,
      46,    48,     3,    10,     0,    40,    18,     0,    11,    31,
      49,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    68,    69,     0,     3,     0,     0,    76,     3,
       0,     0,    59,    71,    62,    63,    72,    73,    74,    56,
      64,    65,    66,     0,    60,   166,    67,    70,     0,     0,
      75,    43,    42,    16,    47,     0,     0,     0,   175,   176,
     178,   177,   179,   180,   172,     0,   181,   131,   182,   164,
       0,     0,     0,     0,     0,     0,     0,     0,   140,   141,
      93,     0,     0,     0,     0,     0,     3,     0,    97,    58,
      54,    55,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   130,    91,    95,     0,     0,    90,    94,     0,     0,
      89,   124,   139,   135,     0,   136,   138,     0,     0,   142,
       0,   129,     0,   128,   146,     0,   167,   169,   168,   170,
       0,     0,     0,     0,   173,   165,   132,   153,   152,   154,
     155,   156,   157,   159,   160,   158,   161,   162,   163,   150,
     151,   149,   148,     0,    92,    96,     0,     0,     0,     0,
     134,     0,     0,     0,    53,    86,     0,   166,    33,    34,
      35,    36,    37,    38,   104,     0,     0,   112,   105,   113,
       0,     0,     0,   171,   133,   100,   110,   101,   111,     0,
      98,   108,    99,   109,     0,    84,    88,   137,     0,     0,
       0,   126,   143,   129,     0,   122,   123,   117,   116,   121,
     119,   120,   115,   114,   118,    78,    82,    83,     0,   102,
     106,   103,   107,     0,     0,   125,     0,   144,    87,     0,
       0,    77,   174,    85,    80,     0,     0,   129,    79,   127,
     145,     0,     0,    81
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -227,  -227,    33,   330,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,    -2,    -1,  -227,  -227,  -226,  -227,  -227,   280,  -227,
    -227,  -227,   275,  -227,  -227,   296,   -72,   281,  -227,   -85,
    -227,  -195,  -227,  -227,  -227,  -227,  -227,  -227,  -227,    34,
    -227,  -227,  -227,  -188,    32,  -227,  -227,  -227,  -227,   133,
     -61,  -227,   132,  -183,  -227,  -227,  -227,   -63,  -227,   -60,
    -227
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    86,    12,    13,    25,    14,    26,    38,    39,
      48,    19,    57,    42,    58,   257,    16,    34,    49,    50,
      28,    59,    60,    61,    17,    44,    88,    63,    89,    90,
      91,    92,    93,   311,    94,    95,    96,    97,   274,   246,
      98,    99,   100,   258,   259,   101,   102,   103,   104,   181,
     126,   194,   195,   145,   106,   107,   108,   196,   109,   128,
     129
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      15,   105,   110,   117,   149,     3,   245,   266,    20,   239,
     271,    27,    15,   127,   283,   243,   303,   138,   139,   284,
     283,    35,     4,     5,     6,     7,     8,    33,   105,   110,
     278,   138,   139,     2,    21,   142,    22,   161,    30,   162,
     240,    55,    32,   300,   242,   267,    64,   304,   272,    36,
      31,   322,   158,   159,    37,    69,    40,    23,   280,    41,
      87,   200,   163,   279,   138,   139,    51,   288,   293,    45,
      46,    47,    54,   189,    52,   131,   134,   315,   191,    43,
     197,   301,   199,   154,   155,   105,   110,    87,   308,   203,
     204,    24,    62,   206,   207,   208,   209,    53,   213,   156,
     157,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   146,   138,
     139,    66,   245,   316,     4,     5,     6,     7,     8,   140,
     185,    65,   141,    68,     4,     5,     6,     7,     8,    73,
     247,   110,    74,    75,    87,    70,  -147,    77,    78,   262,
      71,    80,    72,    82,    83,     4,     5,     6,     7,     8,
     111,   142,   115,   143,   116,   144,   276,    85,    56,    84,
     177,   178,   179,   180,   275,    85,  -166,  -166,   135,   281,
     282,   118,   119,   120,   121,   122,   123,   124,   295,   296,
      18,   192,   137,     4,     5,     6,     7,     8,    73,    87,
     136,    74,    75,  -129,    76,  -147,    77,    78,    79,   148,
      80,    81,    82,    83,   147,   305,   150,   307,   151,   125,
     193,   309,   247,   110,   152,   -61,   160,   153,    84,   285,
     286,   182,   314,   -57,    85,   287,   183,   186,   318,   187,
     313,   118,   119,   120,   121,   122,   123,   124,   188,   190,
     323,   192,   319,   320,   255,   256,   247,   110,   118,   119,
     120,   121,   122,   123,   124,   268,   198,   202,   273,     4,
       5,     6,     7,     8,   290,   291,   201,   205,   212,   125,
     292,    87,   214,     9,   233,   234,   235,   289,   294,   236,
      10,     4,     5,     6,     7,     8,   125,   237,   244,   255,
     256,   302,   142,   260,    11,     4,     5,     6,     7,     8,
       4,     5,     6,     7,     8,    87,   261,   269,   132,     4,
       5,     6,     7,     8,   180,   298,    18,   248,   249,   250,
     251,   252,   253,   254,   175,   176,   177,   178,   179,   180,
     133,   306,   310,   312,    29,   130,   112,   114,   113,   264,
      67,   321,   255,   256,   184,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   277,     0,   248,   249,   250,   251,   252,   253,   265,
       0,   241,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   255,   256,
     248,   249,   250,   251,   252,   253,   270,     0,   263,   248,
     249,   250,   251,   252,   253,   299,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   255,   256,     0,     0,     0,
       0,     0,     0,     0,   255,   256,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,     0,     0,     0,     0,     0,     0,     0,     0,
     210,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,     0,     0,     0,
       0,     0,     0,     0,     0,   211,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,     0,     0,     0,     0,     0,     0,     0,     0,
     215,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,     0,     0,     0,
       0,     0,     0,     0,     0,   238,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,     0,     0,   164,     0,     0,     0,     0,     0,
     297,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   317,     0,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180
};

static const yytype_int16 yycheck[] =
{
       2,    62,    62,    75,    89,     0,   201,   233,     9,    40,
     236,    13,    14,    76,    40,   198,    40,    28,    29,    45,
      40,    22,     3,     4,     5,     6,     7,    72,    89,    89,
      41,    28,    29,     0,    38,    70,    17,    72,    38,    74,
      71,    42,    38,   269,    41,   233,    48,    71,   236,    32,
      17,    71,   115,   116,    46,    56,    46,    38,   241,    17,
      62,   146,   125,    74,    28,    29,    46,   255,   256,    25,
      26,    27,    39,   136,    46,    77,    78,    41,   141,    70,
     143,   269,   145,    30,    31,   146,   146,    89,   283,   152,
     153,    72,    44,   154,   155,   156,   157,    73,   161,    30,
      31,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,    85,    28,
      29,    45,   317,   306,     3,     4,     5,     6,     7,    38,
     132,    73,    41,    46,     3,     4,     5,     6,     7,     8,
     201,   201,    11,    12,   146,    38,    15,    16,    17,   212,
      71,    20,    40,    22,    23,     3,     4,     5,     6,     7,
      38,    70,    70,    72,    70,    74,   238,    44,    16,    38,
      59,    60,    61,    62,   237,    44,    30,    31,    70,   242,
     243,    32,    33,    34,    35,    36,    37,    38,   260,   261,
      38,    42,    32,     3,     4,     5,     6,     7,     8,   201,
      70,    11,    12,    13,    14,    15,    16,    17,    18,    38,
      20,    21,    22,    23,    19,   278,    43,   280,    46,    70,
      71,   284,   283,   283,    13,    46,    11,    15,    38,    32,
      33,    38,   304,    43,    44,    38,    38,    38,   310,    38,
     303,    32,    33,    34,    35,    36,    37,    38,    38,    45,
     322,    42,   315,   316,    57,    58,   317,   317,    32,    33,
      34,    35,    36,    37,    38,   233,    38,    53,   236,     3,
       4,     5,     6,     7,    32,    33,    70,    38,    70,    70,
      38,   283,    38,    17,    53,    38,    38,   255,   256,    53,
      24,     3,     4,     5,     6,     7,    70,    45,    43,    57,
      58,   269,    70,     9,    38,     3,     4,     5,     6,     7,
       3,     4,     5,     6,     7,   317,    12,    53,    16,     3,
       4,     5,     6,     7,    62,    74,    38,    32,    33,    34,
      35,    36,    37,    38,    57,    58,    59,    60,    61,    62,
      38,    38,    10,    38,    14,    38,    66,    72,    67,   216,
      54,   317,    57,    58,    38,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,   239,    -1,    32,    33,    34,    35,    36,    37,    38,
      -1,    73,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    57,    58,
      32,    33,    34,    35,    36,    37,    38,    -1,    73,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    58,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      71,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    76,    77,     0,     3,     4,     5,     6,     7,    17,
      24,    38,    78,    79,    81,    86,    91,    99,    38,    86,
      87,    38,    17,    38,    72,    80,    82,    86,    95,    78,
      38,    77,    38,    72,    92,    87,    32,    46,    83,    84,
      46,    17,    88,    70,   100,    25,    26,    27,    85,    93,
      94,    46,    46,    73,    77,    87,    16,    87,    89,    96,
      97,    98,    44,   102,    86,    73,    45,   100,    46,    87,
      38,    71,    40,     8,    11,    12,    14,    16,    17,    18,
      20,    21,    22,    23,    38,    44,    77,    86,   101,   103,
     104,   105,   106,   107,   109,   110,   111,   112,   115,   116,
     117,   120,   121,   122,   123,   125,   129,   130,   131,   133,
     134,    38,    93,   102,    97,    70,    70,   101,    32,    33,
      34,    35,    36,    37,    38,    70,   125,   132,   134,   135,
      38,    86,    16,    38,    86,    70,    70,    32,    28,    29,
      38,    41,    70,    72,    74,   128,    77,    19,    38,   104,
      43,    46,    13,    15,    30,    31,    30,    31,   132,   132,
      11,    72,    74,   132,    40,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,   124,    38,    38,    38,    86,    38,    38,    38,   132,
      45,   132,    42,    71,   126,   127,   132,   132,    38,   132,
     104,    70,    53,   132,   132,    38,   125,   125,   125,   125,
      71,    71,    70,   132,    38,    71,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,    53,    38,    38,    53,    45,    71,    40,
      71,    73,    41,   128,    43,   106,   114,   125,    32,    33,
      34,    35,    36,    37,    38,    57,    58,    90,   118,   119,
       9,    12,   132,    73,   124,    38,    90,   118,   119,    53,
      38,    90,   118,   119,   113,   132,   101,   127,    41,    74,
     128,   132,   132,    40,    45,    32,    33,    38,   118,   119,
      32,    33,    38,   118,   119,   101,   101,    71,    74,    38,
      90,   118,   119,    40,    71,   132,    38,   132,   106,   132,
      10,   108,    38,   132,   101,    41,   128,    45,   101,   132,
     132,   114,    71,   101
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    77,    78,    78,    79,    80,    81,    81,
      81,    82,    82,    82,    82,    83,    83,    84,    85,    85,
      85,    85,    86,    86,    86,    86,    86,    87,    87,    88,
      88,    89,    89,    90,    90,    90,    90,    90,    90,    91,
      92,    93,    93,    94,    95,    96,    96,    97,    97,    98,
      99,    99,   100,   101,   102,   103,   103,   104,   104,   105,
     105,   105,   105,   105,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   107,   108,   108,
     109,   110,   111,   112,   113,   113,   114,   114,   115,   116,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   118,   118,   118,   118,   119,   119,
     119,   119,   119,   119,   120,   120,   120,   120,   121,   122,
     123,   123,   124,   124,   125,   125,   126,   126,   127,   127,
     128,   128,   129,   129,   129,   129,   130,   131,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   133,   134,   134,   134,
     134,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     0,     2,     1,     1,     1,     2,
       4,     4,     3,     2,     2,     1,     4,     0,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     2,     1,     1,     1,     1,     1,     1,     1,     4,
       3,     1,     3,     3,     3,     0,     1,     3,     1,     2,
       2,     3,     3,     4,     3,     2,     1,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     7,     0,     2,
       7,    10,     6,     6,     1,     3,     1,     3,     5,     3,
       3,     3,     4,     2,     3,     3,     4,     2,     5,     5,
       5,     5,     6,     6,     4,     4,     6,     6,     5,     5,
       5,     5,     4,     4,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     6,     5,     8,     3,     0,
       3,     2,     2,     3,     4,     3,     1,     3,     1,     1,
       1,     1,     3,     5,     6,     8,     3,     0,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     3,     1,     3,     3,     3,
       3,     4,     1,     3,     6,     1,     1,     1,     1,     1,
       1,     1,     1
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
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1470 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 4: /* TK_PR_FLOAT  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1484 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 5: /* TK_PR_BOOL  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1498 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 6: /* TK_PR_CHAR  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1512 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 7: /* TK_PR_STRING  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1526 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 8: /* TK_PR_IF  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1540 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 9: /* TK_PR_THEN  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1554 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 10: /* TK_PR_ELSE  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1568 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 11: /* TK_PR_WHILE  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1582 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 12: /* TK_PR_DO  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1596 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 13: /* TK_PR_INPUT  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1610 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 14: /* TK_PR_OUTPUT  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1624 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 15: /* TK_PR_RETURN  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1638 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 16: /* TK_PR_CONST  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1652 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 17: /* TK_PR_STATIC  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1666 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 18: /* TK_PR_FOREACH  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1680 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 19: /* TK_PR_FOR  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1694 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 20: /* TK_PR_SWITCH  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1708 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 21: /* TK_PR_CASE  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1722 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 22: /* TK_PR_BREAK  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1736 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 23: /* TK_PR_CONTINUE  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1750 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 24: /* TK_PR_CLASS  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1764 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 25: /* TK_PR_PRIVATE  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1778 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 26: /* TK_PR_PUBLIC  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1792 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 27: /* TK_PR_PROTECTED  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1806 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 28: /* TK_OC_SL  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1820 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 29: /* TK_OC_SR  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1834 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 30: /* TK_OC_FORWARD_PIPE  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1848 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 31: /* TK_OC_BASH_PIPE  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1862 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 32: /* TK_LIT_INT  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1876 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 33: /* TK_LIT_FLOAT  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1890 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 34: /* TK_LIT_FALSE  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1904 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 35: /* TK_LIT_TRUE  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1918 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 36: /* TK_LIT_CHAR  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1932 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 37: /* TK_LIT_STRING  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1946 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 38: /* TK_IDENTIFICADOR  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1960 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 39: /* TOKEN_ERRO  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1974 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 40: /* ','  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1988 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 41: /* '='  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2002 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 42: /* '.'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2016 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 43: /* '}'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2030 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 44: /* '{'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2044 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 45: /* ':'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2058 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 46: /* ';'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2072 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 47: /* TK_OC_OR  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2086 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 48: /* TK_OC_AND  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2100 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 49: /* '|'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2114 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 50: /* '&'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2128 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 51: /* TK_OC_EQ  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2142 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 52: /* TK_OC_NE  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2156 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 53: /* TK_OC_LE  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2170 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 54: /* '<'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2184 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 55: /* TK_OC_GE  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2198 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 56: /* '>'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2212 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 57: /* '+'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2226 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 58: /* '-'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2240 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 59: /* '*'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2254 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 60: /* '%'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2268 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 61: /* '/'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2282 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 62: /* '^'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2296 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 63: /* UMINUS  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2310 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 64: /* UPLUS  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2324 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 65: /* UPOINTER  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2338 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 66: /* UADDRESS  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2352 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 67: /* '!'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2366 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 68: /* '?'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2380 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 69: /* '#'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2394 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 70: /* '('  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2408 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 71: /* ')'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2422 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 72: /* '['  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2436 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 73: /* ']'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2450 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 74: /* '$'  */
#line 274 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2464 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 76: /* programa  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2474 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 78: /* componentes  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2484 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 79: /* idThatCanBeFuncType  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2494 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 80: /* idThatCanBeFuncName  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2504 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 81: /* componente  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2514 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 82: /* depoisDeIdent  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2524 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 83: /* fechaVarOuFunc  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2534 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 85: /* encapsulamento  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2544 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 86: /* tiposPrimitivos  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2554 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 87: /* tipo  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2564 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 88: /* static  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2574 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 89: /* tipoConst  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2584 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 90: /* literais  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2594 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 91: /* novoTipo  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2604 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 92: /* listaCampos  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2614 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 93: /* list  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2624 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 94: /* campo  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2634 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 95: /* tamanhoVetor  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2644 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 96: /* args  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2654 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 97: /* parameters  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2664 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 98: /* parameter  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2674 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 99: /* funcName  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2684 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 100: /* funcArgs  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2694 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 101: /* blocoComandos  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2704 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 102: /* blocoSemEscopo  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2714 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 103: /* comando  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2724 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 104: /* comandos  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2734 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 105: /* comandoSimples  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2744 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 106: /* comandosSemVirgula  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2754 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 107: /* ifThenElse  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2764 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 108: /* optElse  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2774 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 109: /* foreach  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2784 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 110: /* for  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2794 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 111: /* while_do  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2804 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 112: /* do_while  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2814 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 113: /* foreachList  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2824 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 114: /* forList  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2834 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 115: /* switch  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2844 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 116: /* case  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2854 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 117: /* localVarDefinition  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2864 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 118: /* negativeOrPositiveIdentifier  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2874 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 119: /* negativeOrPositiveLiteral  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2884 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 120: /* assignment  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2894 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 121: /* input  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2904 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 123: /* output  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2914 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 124: /* continueOutput  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2924 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 125: /* funcCall  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2934 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 126: /* argsCall  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2944 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 127: /* argCall  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2954 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 128: /* shiftOp  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2964 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 129: /* shift  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2974 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 130: /* return  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2984 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 132: /* expression  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2994 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 133: /* savePipe  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 3004 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 134: /* pipe  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 3014 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 135: /* operands  */
#line 283 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 3024 "parser.tab.c" /* yacc.c:1257  */
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
#line 308 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast); arvore = (yyval.ast); 
		parsingSucceded = TRUE;
		closeTable(); // fecha escopo global
	}
#line 3292 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 316 "parser/parser.y" /* yacc.c:1646  */
    {initTable();}
#line 3298 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 320 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3304 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 321 "parser/parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3310 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 330 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); firstID = (yyval.ast);}
#line 3316 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 334 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); secondID = (yyval.ast);}
#line 3322 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 338 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3328 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 339 "parser/parser.y" /* yacc.c:1646  */
    { // Regra introduzida para resolver conflitos
		(yyval.ast) = (yyvsp[-1].ast); 
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
				int isUsr = verifyUse((yyvsp[0].ast)->kids[3]->token->value.str, UTN);
				if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
				int addSymb = addSymbol(
					(yyvsp[-1].ast)->token, NATUREZA_IDENTIFICADOR, USER, getUserType((yyvsp[0].ast)->kids[3]),
					(yyvsp[0].ast)->kids[0]->token->value.i, FALSE, flag
				);
				if (addSymb!=0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else{
				int addSymb = addSymbol(
					(yyvsp[-1].ast)->token, NATUREZA_IDENTIFICADOR, type, NULL, (yyvsp[0].ast)->kids[0]->token->value.i, 
					FALSE, flag 
				);
				if (addSymb!=0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if ((yyvsp[0].ast)->kids[0]->token->value.c == '('){ //
			//trata função 
			// só precisa adicionar os argumentos, nome da função já foi adicionado em userTypeFunc
			addArgsToSymbol((yyvsp[0].ast)->token->value.str, currentArgs);
			clearCurrentArgs();
		}
		else{
			//trata variável global
			//Existem diferentes variações:
			//var global com tipos primitivos não estático -> head = tipoPrimitivo, kids[0] = ';'
			//var global estatica -> head = TK_PR_STATIC, kids[0] = tipo, kids[1] = ';'
			//var global não estática com tipo de usuário -> head = tipodeUser, kids[0] = ';'
			
			if ((yyvsp[0].ast)->kidsNumber == 2){
				//var global estática
				int type = getType((yyvsp[0].ast)->kids[0]);				
				if (type == USER){
					int isUsr = verifyUse((yyvsp[0].ast)->kids[0]->token->value.str, UTN);
					if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
					int addSymb = addSymbol(
						(yyvsp[-1].ast)->token, NATUREZA_IDENTIFICADOR, USER, 
						getUserType((yyvsp[0].ast)->kids[0]), 0, FALSE, STATIC
					);
					if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
					if (addSymb!=0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
				}
				else{
					int addSymb = addSymbol(
						(yyvsp[-1].ast)->token, NATUREZA_IDENTIFICADOR, type, 
						NULL, 0, FALSE, STATIC
					);
					if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}		
				}
				
			}else{
				int type = getType((yyvsp[0].ast));
				if (type == USER){
					int isUsr = verifyUse((yyvsp[0].ast)->token->value.str, UTN);
					if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
					int addSymb = addSymbol((yyvsp[-1].ast)->token, NATUREZA_IDENTIFICADOR, USER, getUserType((yyvsp[0].ast)), 0, FALSE, 0);
					if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
				}
				else{
					int addSymb = addSymbol((yyvsp[-1].ast)->token, NATUREZA_IDENTIFICADOR, type, NULL, 0, FALSE, 0);
					if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
				}
			}
		}
	}
#line 3420 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 427 "parser/parser.y" /* yacc.c:1646  */
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
		clearCurrentArgs();
		closeTable();
		
	}
#line 3442 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 447 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3453 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 453 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3463 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 458 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3472 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 462 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3481 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 468 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3487 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 469 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		closeTable();
	}
#line 3497 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 477 "parser/parser.y" /* yacc.c:1646  */
    {
		int isUsr = verifyUse(firstID->token->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; YYABORT;}
		int addSymb = addSymbol(secondID->token, NATUREZA_IDENTIFICADOR, USER, getUserType(firstID), 0, TRUE, 0);
		if(addSymb != 0){ returnError = addSymb; YYABORT;}
		saveFunc(secondID->token->value.str);
	}
#line 3509 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 486 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3515 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 487 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3521 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 488 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3527 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 489 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 492 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3539 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 493 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3545 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 494 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3551 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 495 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3557 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 496 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3563 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 499 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3569 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 500 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3575 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 503 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3581 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 504 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3587 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 507 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 508 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3599 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 511 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = INT; }
#line 3605 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 512 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = FLOAT; }
#line 3611 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 513 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = BOOL; }
#line 3617 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 514 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = BOOL; }
#line 3623 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 515 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = CHAR; }
#line 3629 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 516 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = STRING; }
#line 3635 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 521 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, USER, NULL, 0, FALSE, 0);		
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		addFieldsToSymbol((yyvsp[-2].valor_lexico)->value.str, currentFields);
		clearCurrentFields();
	}
#line 3650 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 532 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3660 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 539 "parser/parser.y" /* yacc.c:1646  */
    {adicionaCampo(criaCampo((yyvsp[0].ast))); (yyval.ast) = (yyvsp[0].ast);}
#line 3666 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 540 "parser/parser.y" /* yacc.c:1646  */
    {		
		adicionaCampo(criaCampo((yyvsp[-2].ast)));

		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3678 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 549 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3688 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 558 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3698 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 566 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3704 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 567 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3710 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 570 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		
		adicionaArg(criaArg((yyvsp[-2].ast)));

		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));

	}
#line 3724 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 579 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); adicionaArg(criaArg((yyvsp[0].ast)));}
#line 3730 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 582 "parser/parser.y" /* yacc.c:1646  */
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
			int isUsr = verifyUse(aux->token->value.str, UTN);
			if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
			int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType(aux), 0, FALSE, flag);		
			if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		}	
		else{	
			int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, type, NULL, 0, FALSE, flag);		
			if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		}
	}
#line 3756 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 607 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, TRUE, 0);		
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		saveFunc((yyvsp[0].valor_lexico)->value.str);	
	}
#line 3768 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 614 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[-1].ast));	
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int type = getType((yyvsp[-1].ast));
		if(type == USER){
			int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyvsp[-1].ast)), 0, TRUE, STATIC);
			if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		}
		else{
			int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, type, NULL, 0, TRUE, STATIC);
			if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		}
		saveFunc((yyvsp[0].valor_lexico)->value.str);	

	}
#line 3789 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 634 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[-1].ast));
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3799 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 646 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		closeTable();                     //Fecha escopo local
	}
#line 3810 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 656 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[-1].ast));
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3820 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 663 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 3826 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 664 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3832 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 667 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3838 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 668 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3844 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 673 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3850 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 674 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3856 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 675 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3862 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 676 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3868 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 677 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3874 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 682 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3880 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 683 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3886 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 684 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3892 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 685 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3898 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 686 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3904 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 687 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3910 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 688 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3916 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 689 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3922 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 690 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3928 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 691 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3934 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 692 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3940 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 693 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3946 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 694 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3952 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 698 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-6].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-5].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-4].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));

		int correctOperands =  coercion(BOOL, (yyvsp[-4].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 3969 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 712 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3975 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 713 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3981 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 716 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-6].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-5].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVar = verifyUse((yyvsp[-4].valor_lexico)->value.str, VAR);
		if (isVar != TRUE){ returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 3997 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 733 "parser/parser.y" /* yacc.c:1646  */
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

		int correctOperands =  coercion(BOOL, (yyvsp[-4].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}

		closeTable();
	}
#line 4018 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 752 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));

		int correctOperands =  coercion(BOOL, (yyvsp[-3].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4034 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 765 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-4].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));

		int correctOperands =  coercion(BOOL, (yyvsp[-1].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4050 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 780 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);

		int correctOperands =  coercion(NONE, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4061 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 786 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));

		int correctOperands =  coercion(NONE, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4074 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 796 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4080 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 797 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4090 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 805 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int correctOperands =  coercion(INT, (yyvsp[-2].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4105 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 817 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4115 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 827 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = verifyUse((yyvsp[-1].valor_lexico)->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)->kids[0]), 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
	}
#line 4129 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 836 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = verifyUse((yyvsp[-1].valor_lexico)->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)->kids[0]), 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
	}
#line 4143 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 845 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = verifyUse((yyvsp[-1].valor_lexico)->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)->kids[1]), 0, FALSE, STATIC + CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		
	}
#line 4159 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 856 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = verifyUse((yyvsp[-1].valor_lexico)->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)), 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		
	}
#line 4173 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 865 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
	}
#line 4185 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 872 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		
	}
#line 4198 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 880 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
	}
#line 4211 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 888 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
	}
#line 4222 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 895 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoTipado((yyvsp[0].valor_lexico), identifierType((yyvsp[0].valor_lexico)->value.str)));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		int isVar = verifyUse((yyvsp[0].valor_lexico)->value.str, VAR);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyval.ast)->kids[3]);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
		if (getType((yyvsp[-3].ast)) == STRING){
			//atualiza tamanho
			updateStringSize((yyvsp[-2].valor_lexico)->value.str, (yyval.ast)->kids[3], IDENT, NULL);
		}
		
	}
#line 4245 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 913 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
				
		// o identificador é sempre o útimo filho desse nodo
		int isVar = verifyUse(getIdFromNegOrPosId((yyvsp[0].ast)), VAR);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
		
	}
#line 4267 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 930 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoTipado((yyvsp[0].valor_lexico), identifierType((yyvsp[0].valor_lexico)->value.str)));
		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		int isVar = verifyUse((yyvsp[0].valor_lexico)->value.str, VAR);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}

		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyval.ast)->kids[3]);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
		if (getType((yyvsp[-3].ast)) == STRING){
			//atualiza tamanho
			updateStringSize((yyvsp[-2].valor_lexico)->value.str, (yyval.ast)->kids[3], IDENT, NULL);
		}
	}
#line 4291 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 949 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		// o identificador é sempre o útimo filho desse nodo
		int isVar = verifyUse(getIdFromNegOrPosId((yyvsp[0].ast)), VAR);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
	}
#line 4311 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 964 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoTipado((yyvsp[0].valor_lexico), identifierType((yyvsp[0].valor_lexico)->value.str)));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		int isVar = verifyUse((yyvsp[0].valor_lexico)->value.str, VAR);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyval.ast)->kids[4]);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
		if (getType((yyvsp[-3].ast)) == STRING){
			//atualiza tamanho
			updateStringSize((yyvsp[-2].valor_lexico)->value.str, (yyval.ast)->kids[4], IDENT, NULL);
		}

	}
#line 4335 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 983 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		// o identificador é sempre o útimo filho desse nodo
		int isVar = verifyUse(getIdFromNegOrPosId((yyvsp[0].ast)), VAR);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
	}
#line 4355 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 998 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoTipado((yyvsp[0].valor_lexico), identifierType((yyvsp[0].valor_lexico)->value.str)));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		int isVar = verifyUse((yyvsp[0].valor_lexico)->value.str, VAR);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyval.ast)->kids[2]);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }

		
		if (getType((yyvsp[-3].ast)) == STRING){
			//atualiza tamanho
			updateStringSize((yyvsp[-2].valor_lexico)->value.str, (yyval.ast)->kids[2], IDENT, NULL);
		}
	}
#line 4378 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1016 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		// o identificador é sempre o útimo filho desse nodo
		int isVar = verifyUse(getIdFromNegOrPosId((yyvsp[0].ast)), VAR);
		if(isVar!=TRUE){returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
	}
#line 4396 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1030 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
		if (getType((yyvsp[-3].ast)) == STRING){
			//atualiza tamanho
			updateStringSize((yyvsp[-2].valor_lexico)->value.str, (yyvsp[0].ast), IDENT, NULL);
		}
	}
#line 4417 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1046 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
	}
#line 4434 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1058 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));		
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
		if (getType((yyvsp[-3].ast)) == STRING){
			//atualiza tamanho
			updateStringSize((yyvsp[-2].valor_lexico)->value.str, (yyvsp[0].ast), IDENT, NULL);
		}
	}
#line 4454 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1073 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
	}
#line 4470 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1084 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}

		

		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
		if (getType((yyvsp[-3].ast)) == STRING){
			//atualiza tamanho
			updateStringSize((yyvsp[-2].valor_lexico)->value.str, (yyvsp[0].ast), IDENT, NULL);
		}	
	}
#line 4493 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1102 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
	}
#line 4509 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1113 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}		

		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
		if (getType((yyvsp[-3].ast)) == STRING){
			//atualiza tamanho
			updateStringSize((yyvsp[-2].valor_lexico)->value.str, (yyvsp[0].ast), IDENT, NULL);
		}	
	}
#line 4529 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1128 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
	}
#line 4544 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1140 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->type = (yyvsp[0].ast)->type;
	}
#line 4554 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1145 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));		
		(yyval.ast)->kids[0]->type = identifierType((yyvsp[0].valor_lexico)->value.str);
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4566 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1152 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->type = (yyvsp[0].ast)->type;
	}
#line 4576 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1157 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = identifierType((yyvsp[0].valor_lexico)->value.str);
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4588 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1167 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->type = (yyvsp[0].ast)->type;
	}
#line 4598 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1172 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = INT;
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4610 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1179 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = FLOAT;
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4622 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1186 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->type = (yyvsp[0].ast)->type;
	}
#line 4632 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1191 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = INT;
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4644 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1198 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = FLOAT;
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4656 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1209 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVar = verifyUse((yyvsp[-2].valor_lexico)->value.str, VAR);
		if (isVar != TRUE){ returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctOperands =  coercion(identifierType((yyvsp[-2].valor_lexico)->value.str), (yyvsp[0].ast));
		//printExpression($3);
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
		//printExpression($3);
		if(identifierType((yyvsp[-2].valor_lexico)->value.str) == STRING){
			//atualizar tamanho
			updateStringSize((yyvsp[-2].valor_lexico)->value.str, (yyvsp[0].ast), IDENT, NULL);			
		}
		printListOfOperations((yyvsp[0].ast)->opList);
	}
#line 4677 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1225 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVec = verifyUse((yyvsp[-5].valor_lexico)->value.str, VET);
		if (isVec!=TRUE){ returnError = isVec; nodeNotAdded = (yyval.ast); YYABORT;}
		
		int correctOperands =  coercion(INT, (yyvsp[-3].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}

		correctOperands =  coercion(identifierType((yyvsp[-5].valor_lexico)->value.str), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}

		if(identifierType((yyvsp[-5].valor_lexico)->value.str) == STRING){
			updateStringSize((yyvsp[-5].valor_lexico)->value.str, (yyvsp[0].ast), VECTOR, NULL);
		}
	}
#line 4702 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1245 "parser/parser.y" /* yacc.c:1646  */
    {//
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoCampo((yyvsp[-2].valor_lexico), (yyvsp[-4].valor_lexico)->value.str)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isUsr = verifyUse((yyvsp[-4].valor_lexico)->value.str, UTV);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int hasF = hasField((yyvsp[-4].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str);
		if (hasF!=TRUE){ returnError = hasF; nodeNotAdded = (yyval.ast); YYABORT;}
		
		int correctOperands =  coercion(fieldType((yyvsp[-4].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
		if (fieldType((yyvsp[-4].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str) == STRING){
			updateStringSize((yyvsp[-4].valor_lexico)->value.str, (yyvsp[0].ast), USR, (yyvsp[-2].valor_lexico)->value.str);
		}
	}
#line 4724 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1262 "parser/parser.y" /* yacc.c:1646  */
    {//
		(yyval.ast) = criaNodo((yyvsp[-7].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-6].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-5].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoCampo((yyvsp[-2].valor_lexico), (yyvsp[-7].valor_lexico)->value.str)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVec = verifyUse((yyvsp[-7].valor_lexico)->value.str, VET);
		if (isVec!=TRUE){ returnError = isVec; nodeNotAdded = (yyval.ast); YYABORT;}
		int isUsr = verifyUse((yyvsp[-7].valor_lexico)->value.str, UTV);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int hasF = hasField((yyvsp[-7].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str);
		if (hasF!=TRUE){ returnError = hasF; nodeNotAdded = (yyval.ast); YYABORT;}

		int correctOperands =  coercion(INT, (yyvsp[-5].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}

		correctOperands =  coercion(fieldType((yyvsp[-7].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
		if(fieldType((yyvsp[-7].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str) == STRING){
			updateStringSize((yyvsp[-7].valor_lexico)->value.str, (yyvsp[0].ast), VEC_USR, (yyvsp[-2].valor_lexico)->value.str);
		}
	}
#line 4754 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1289 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[0].ast)->token->tokenType!=IDS){ returnError = ERR_WRONG_PAR_INPUT; nodeNotAdded = (yyval.ast); YYABORT;}	
		isInput = FALSE;
	}
#line 4764 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1298 "parser/parser.y" /* yacc.c:1646  */
    {isInput = TRUE;}
#line 4770 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1306 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[-1].ast)->type == BOOL){
			int correctOperands =  coercion(INT, (yyvsp[-1].ast));
			if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
		}
		else{
			int correctOperands =  coercion(NONE, (yyvsp[-1].ast));
			if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
		}
		if((yyvsp[-1].ast)->type != INT && (yyvsp[-1].ast)->type != FLOAT && (yyvsp[-1].ast)->type != BOOL && (yyvsp[-1].ast)->token->literType!=STRING)
			{ returnError = ERR_WRONG_PAR_OUTPUT; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4790 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1321 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[0].ast)->type == BOOL){
			int correctOperands =  coercion(INT, (yyvsp[0].ast));
			if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
		}
		else{
			int correctOperands =  coercion(NONE, (yyvsp[0].ast));
			if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
		}
		if((yyvsp[0].ast)->type != INT && (yyvsp[0].ast)->type != FLOAT && (yyvsp[0].ast)->type != BOOL && (yyvsp[0].ast)->token->literType!=STRING)
			{ returnError = ERR_WRONG_PAR_OUTPUT; nodeNotAdded = (yyval.ast); YYABORT;}
		}
#line 4809 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1337 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[0].ast)->type != INT && (yyvsp[0].ast)->type != FLOAT && (yyvsp[0].ast)->token->literType!=STRING)
			{ returnError = ERR_WRONG_PAR_OUTPUT; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4820 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1343 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[-1].ast)->type != INT && (yyvsp[-1].ast)->type != FLOAT && (yyvsp[-1].ast)->token->literType!=STRING)
			{ returnError = ERR_WRONG_PAR_OUTPUT; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4832 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1352 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isFunc = verifyUse((yyvsp[-3].valor_lexico)->value.str, FUN);
		if (isFunc != TRUE){ returnError = isFunc; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctArgs = verifyArguments((yyvsp[-3].valor_lexico)->value.str, (yyvsp[-1].ast));
		if (correctArgs != TRUE){ returnError = correctArgs; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4847 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1362 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isFunc = verifyUse((yyvsp[-2].valor_lexico)->value.str, FUN);
		if (isFunc != TRUE){ returnError = isFunc; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctArgs = verifyArguments((yyvsp[-2].valor_lexico)->value.str, NULL);
		if (correctArgs != TRUE){ returnError = correctArgs; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4861 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1373 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);	//tem cabeça NULL para facilitar verificação dos argumentos
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4870 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1377 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4880 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1384 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);
		int correctOperands =  coercion(NONE, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
		
	}
#line 4890 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1389 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4896 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1392 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4902 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1393 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4908 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1395 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVar = verifyUse((yyvsp[-2].valor_lexico)->value.str, VAR);
		if (isVar != TRUE){ returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}

		int correctOperands =  coercion(INT, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4923 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1405 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico)));
		adicionaFilho((yyval.ast), criaNodoCampo((yyvsp[-2].valor_lexico), (yyvsp[-4].valor_lexico)->value.str));
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isUsr = verifyUse((yyvsp[-4].valor_lexico)->value.str, UTV);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int hasF = hasField((yyvsp[-4].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str);
		if (hasF!=TRUE){ returnError = hasF; nodeNotAdded = (yyval.ast); YYABORT;}

		int correctOperands =  coercion(INT, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4942 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1419 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico)));
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast));
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVec = verifyUse((yyvsp[-5].valor_lexico)->value.str, VET);
		if (isVec!=TRUE){ returnError = isVec; nodeNotAdded = (yyval.ast); YYABORT;}

		int correctOperands =  coercion(INT, (yyvsp[-3].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
		
		correctOperands =  coercion(INT, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4963 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1435 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-7].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-6].valor_lexico)));
		adicionaFilho((yyval.ast), (yyvsp[-5].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoCampo((yyvsp[-2].valor_lexico), (yyvsp[-7].valor_lexico)->value.str));
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVec = verifyUse((yyvsp[-7].valor_lexico)->value.str, VET);
		if (isVec!=TRUE){ returnError = isVec; nodeNotAdded = (yyval.ast); YYABORT;}
		int isUsr = verifyUse((yyvsp[-7].valor_lexico)->value.str, UTV);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int hasF = hasField((yyvsp[-7].valor_lexico)->value.str, (yyvsp[-2].valor_lexico)->value.str);
		if (hasF!=TRUE){ returnError = hasF; nodeNotAdded = (yyval.ast); YYABORT;}

		int correctOperands =  coercion(INT, (yyvsp[-5].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}

		correctOperands =  coercion(INT, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4990 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1461 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int verifRet = verifyReturn((yyvsp[0].ast));
		if (verifRet != TRUE){ returnError = verifRet; nodeNotAdded = (yyval.ast); YYABORT;}
		isReturn = FALSE;
	}
#line 5001 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1471 "parser/parser.y" /* yacc.c:1646  */
    {isReturn = TRUE;}
#line 5007 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1475 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}						
	}
#line 5047 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1510 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
	}
#line 5087 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1545 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}				
	}
#line 5127 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1580 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}		
	}
#line 5167 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1615 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}			
	}
#line 5207 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1650 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}		
	}
#line 5247 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1685 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}		
	}
#line 5287 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1720 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}		
	}
#line 5327 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1755 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}	
		
		(yyval.ast)->reg = getNewRegister();
		char *trueLabel = getNewLabel();
		char *falseLabel = getNewLabel();
		addNewLabel((yyval.ast)->trueList, trueLabel);
		addNewLabel((yyval.ast)->falseList, falseLabel);
		createOperation((yyval.ast)->opList, CMP_EQ, "cmp_EQ", (yyvsp[-2].ast)->reg, (yyvsp[0].ast)->reg , (yyval.ast)->reg);
		createOperation((yyval.ast)->opList, CBR, "cbr", (yyval.ast)->reg, trueLabel , falseLabel);
		(yyvsp[-2].ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyvsp[0].ast)->opList);
		(yyval.ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyval.ast)->opList);
	}
#line 5377 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1800 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}			
	}
#line 5417 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1835 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}		
	}
#line 5457 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1870 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}		
	}
#line 5497 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1905 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}		
	}
#line 5537 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1940 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}	
	}
#line 5577 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1977 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
	}
#line 5617 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 2012 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].valor_lexico)->tokenType == SPEC_CHAR){
			if((yyvsp[-1].valor_lexico)->value.c == '+' || (yyvsp[-1].valor_lexico)->value.c == '%' || (yyvsp[-1].valor_lexico)->value.c == '/' || (yyvsp[-1].valor_lexico)->value.c == '*' || (yyvsp[-1].valor_lexico)->value.c == '-' || (yyvsp[-1].valor_lexico)->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '|' || (yyvsp[-1].valor_lexico)->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].valor_lexico)->value.c == '<' || (yyvsp[-1].valor_lexico)->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].valor_lexico)->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].valor_lexico)->value.str, "<=") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "&&") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].valor_lexico)->value.str, "==") == 0 || strcmp((yyvsp[-1].valor_lexico)->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}						
	}
#line 5657 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 2047 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); (yyval.ast)->type = (yyvsp[0].ast)->type;}
#line 5663 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 2048 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodoTipado((yyvsp[-2].valor_lexico), (yyvsp[-1].ast)->type); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodoTipado((yyvsp[0].valor_lexico), (yyvsp[-1].ast)->type));}
#line 5672 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 2055 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); inpPipe = (yyvsp[0].ast);}
#line 5678 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 2058 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 5688 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 2063 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 5698 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 2068 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 5708 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 2073 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 5718 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 2081 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isVec = verifyUse((yyvsp[-3].valor_lexico)->value.str, VET);
		if (isVec!=TRUE){ returnError = isVec; nodeNotAdded = (yyval.ast); YYABORT;}
		
		int correctOperands =  coercion(INT, (yyvsp[-1].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}

		(yyval.ast)->type = identifierType((yyvsp[-3].valor_lexico)->value.str);
	}
#line 5736 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 2094 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));
		if(isInput == TRUE){
			int use = symbolUse((yyvsp[0].valor_lexico)->value.str);
			if(use != VET && use != VAR && use != UTV){returnError = ERR_WRONG_PAR_INPUT; nodeNotAdded = (yyval.ast); YYABORT;}
		}
		else if(isReturn == TRUE){
			int use = symbolUse((yyvsp[0].valor_lexico)->value.str);
			if(use == ERR_UNDECLARED){returnError = ERR_UNDECLARED; nodeNotAdded = (yyval.ast); YYABORT;}
			if(use != VAR && use!= UTV){returnError = ERR_WRONG_PAR_RETURN; nodeNotAdded = (yyval.ast); YYABORT;}
		}
		else{
			int isVar = verifyUse((yyvsp[0].valor_lexico)->value.str, VAR);
			if (isVar != TRUE){ returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}

		}
		(yyval.ast)->type = identifierType((yyvsp[0].valor_lexico)->value.str);

	}
#line 5760 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 2113 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoCampo((yyvsp[0].valor_lexico), (yyvsp[-2].valor_lexico)->value.str));
		int isUsr = verifyUse((yyvsp[-2].valor_lexico)->value.str, UTV);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int hasF = hasField((yyvsp[-2].valor_lexico)->value.str, (yyvsp[0].valor_lexico)->value.str);
		if (hasF!=TRUE){ returnError = hasF; nodeNotAdded = (yyval.ast); YYABORT;}

		(yyval.ast)->type = fieldType((yyvsp[-2].valor_lexico)->value.str, (yyvsp[0].valor_lexico)->value.str);
	}
#line 5776 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 2124 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico)));
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodoCampo((yyvsp[0].valor_lexico), (yyvsp[-5].valor_lexico)->value.str));
		int isVec = verifyUse((yyvsp[-5].valor_lexico)->value.str, VET);
		if (isVec!=TRUE){ returnError = isVec; nodeNotAdded = (yyval.ast); YYABORT;}
		int isUsr = verifyUse((yyvsp[-5].valor_lexico)->value.str, UTV);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int hasF = hasField((yyvsp[-5].valor_lexico)->value.str, (yyvsp[0].valor_lexico)->value.str);
		if (hasF!=TRUE){ returnError = hasF; nodeNotAdded = (yyval.ast); YYABORT;}

		int correctOperands =  coercion(INT, (yyvsp[-3].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}

		(yyval.ast)->type = fieldType((yyvsp[-5].valor_lexico)->value.str, (yyvsp[0].valor_lexico)->value.str);

	}
#line 5801 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 2144 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));
		(yyval.ast)->type = INT;
		(yyval.ast)->reg = getNewRegister();
		createOperation((yyval.ast)->opList, LOADI, "loadI", (void*) &((yyvsp[0].valor_lexico)->value.i), (yyval.ast)->reg, NULL);
	}
#line 5812 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 2150 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = FLOAT;}
#line 5818 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 2151 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = BOOL;}
#line 5824 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 2152 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = BOOL;}
#line 5830 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 2153 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = CHAR;}
#line 5836 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 2154 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = STRING;}
#line 5842 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 2155 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); (yyval.ast)->type = identifierType((yyval.ast)->token->value.str);}
#line 5848 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 2158 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); (yyval.ast)->type = identifierType((yyval.ast)->kids[(yyval.ast)->kidsNumber-1]->token->value.str);}
#line 5854 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 5858 "parser.tab.c" /* yacc.c:1646  */
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
#line 2162 "parser/parser.y" /* yacc.c:1906  */



