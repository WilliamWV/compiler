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



#line 202 "parser.tab.c" /* yacc.c:339  */

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
#line 139 "parser/parser.y" /* yacc.c:355  */

	struct lexval* valor_lexico;
	struct node* ast;

#line 293 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 310 "parser.tab.c" /* yacc.c:358  */

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
#define YYLAST   716

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  194
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  327

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
       2,     2,     2,    61,     2,    64,    67,    63,    62,     2,
      49,    50,    68,    69,    46,    55,    66,    70,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    47,
      58,    60,    59,    57,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    51,     2,    52,    65,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,    56,    54,     2,     2,     2,     2,
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
       0,   288,   288,   296,   300,   301,   310,   314,   318,   319,
     407,   427,   433,   438,   442,   448,   449,   457,   466,   467,
     468,   469,   472,   473,   474,   475,   476,   479,   480,   483,
     484,   487,   488,   491,   492,   493,   494,   495,   496,   501,
     512,   519,   520,   529,   538,   546,   547,   550,   559,   562,
     587,   594,   614,   626,   636,   643,   644,   647,   648,   653,
     654,   655,   656,   657,   662,   663,   664,   665,   666,   667,
     668,   669,   670,   671,   672,   673,   674,   678,   692,   693,
     696,   713,   732,   745,   760,   766,   776,   777,   785,   797,
     807,   816,   825,   836,   845,   852,   860,   868,   875,   893,
     910,   929,   944,   963,   978,   996,  1010,  1026,  1038,  1053,
    1064,  1082,  1093,  1108,  1120,  1125,  1132,  1137,  1147,  1152,
    1159,  1166,  1171,  1178,  1189,  1204,  1224,  1241,  1268,  1277,
    1285,  1300,  1316,  1322,  1331,  1341,  1352,  1356,  1363,  1368,
    1371,  1372,  1374,  1384,  1398,  1414,  1440,  1450,  1454,  1489,
    1523,  1524,  1527,  1528,  1532,  1535,  1540,  1545,  1550,  1558,
    1563,  1564,  1570,  1576,  1582,  1583,  1584,  1587,  1600,  1618,
    1629,  1649,  1650,  1651,  1652,  1653,  1654,  1655,  1658,  1662,
    1663,  1664,  1665,  1666,  1667,  1668,  1669,  1670,  1671,  1672,
    1673,  1674,  1675,  1676,  1677
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
  "';'", "':'", "'('", "')'", "'['", "']'", "'{'", "'}'", "'-'", "'|'",
  "'?'", "'<'", "'>'", "'='", "'!'", "'&'", "'%'", "'#'", "'^'", "'.'",
  "'$'", "'*'", "'+'", "'/'", "$accept", "programa", "scopeOpenner",
  "componentes", "idThatCanBeFuncType", "idThatCanBeFuncName",
  "componente", "depoisDeIdent", "fechaVarOuFunc", "userTypeFunc",
  "encapsulamento", "tiposPrimitivos", "tipo", "static", "tipoConst",
  "literais", "novoTipo", "listaCampos", "list", "campo", "tamanhoVetor",
  "args", "parameters", "parameter", "funcName", "funcArgs",
  "blocoComandos", "blocoSemEscopo", "comando", "comandos",
  "comandoSimples", "comandosSemVirgula", "ifThenElse", "optElse",
  "foreach", "for", "while_do", "do_while", "foreachList", "forList",
  "switch", "case", "localVarDefinition", "negativeOrPositiveIdentifier",
  "negativeOrPositiveLiteral", "assignment", "input", "inputHelper",
  "output", "continueOutput", "funcCall", "argsCall", "argCall", "shiftOp",
  "shift", "return", "returnHelper", "expression", "infiniteQuestionMarks",
  "savePipe", "pipe", "parenthesisOrOperand", "operands", "operators", YY_NULLPTR
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
      41,    91,    93,   123,   125,    45,   124,    63,    60,    62,
      61,    33,    38,    37,    35,    94,    46,    36,    42,    43,
      47
};
# endif

#define YYPACT_NINF -215

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-215)))

#define YYTABLE_NINF -155

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -215,    20,   203,  -215,  -215,  -215,  -215,  -215,  -215,   251,
     -17,  -215,  -215,    33,   203,   -12,  -215,  -215,  -215,  -215,
       3,    16,   251,  -215,    48,    43,  -215,    78,   110,  -215,
    -215,    83,  -215,   171,    87,   101,    97,  -215,  -215,  -215,
    -215,  -215,   251,   139,    98,  -215,  -215,  -215,   182,   102,
     108,  -215,  -215,  -215,    83,   113,   251,  -215,   124,   128,
    -215,   144,   159,  -215,   149,  -215,   171,    98,  -215,  -215,
    -215,  -215,   139,   145,   150,   151,   615,   272,   227,   153,
     156,   173,  -215,  -215,   -25,  -215,   195,   174,  -215,   159,
     161,   170,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,   206,  -215,   175,  -215,  -215,   208,    17,
      59,  -215,  -215,  -215,  -215,   615,   615,   210,  -215,  -215,
    -215,  -215,  -215,  -215,    86,   615,   615,   615,   615,   615,
     615,   615,   104,   234,   167,    59,   172,  -215,   184,   193,
     368,   196,   200,   201,   615,   191,  -215,  -215,  -215,   551,
     615,   615,   202,   615,   159,   199,   221,  -215,  -215,  -215,
     615,   615,   207,   207,   207,   207,   277,   293,   219,   615,
     225,   336,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,   615,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,   615,  -215,  -215,  -215,
     222,   226,   228,  -215,   224,   233,   352,  -215,  -215,  -215,
     -16,  -215,   518,   395,   518,     9,   518,   229,   106,   393,
     518,   518,   236,  -215,  -215,  -215,  -215,   273,   274,   615,
     438,  -215,  -215,   234,   167,   172,   436,  -215,   259,   499,
     615,   151,   583,  -215,    14,   615,   615,  -215,  -215,    18,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,    13,    92,
    -215,  -215,  -215,   151,   151,   454,   231,  -215,  -215,  -215,
    -215,  -215,   647,  -215,  -215,  -215,  -215,    15,   518,  -215,
    -215,   615,   244,   615,   518,   518,   106,   615,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,   281,  -215,
    -215,   250,  -215,  -215,  -215,  -215,   615,   151,   518,    28,
     518,  -215,   497,   151,  -215,  -215,   518,  -215,   615,   615,
     106,  -215,   518,   518,    39,   151,  -215
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
      64,    65,    66,     0,    60,   154,    67,    70,     0,     0,
      75,    43,    42,    16,    47,     0,     0,     0,   171,   172,
     174,   173,   175,   176,   168,     0,     0,     0,     0,     0,
       0,     0,   177,   131,   151,   178,   150,   160,     0,     0,
       0,     0,     0,     0,     0,     0,   140,   141,    93,     0,
       0,     0,     0,     0,     3,     0,    97,    58,    54,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   161,   163,   165,   166,   164,   162,   192,   191,
     189,   190,   185,   186,     0,   180,   187,   193,   194,   188,
     183,   184,   181,   179,   182,   130,     0,   153,   152,    91,
      95,     0,     0,    90,    94,     0,     0,    89,   135,   139,
       0,   136,   138,     0,   124,     0,   142,     0,   129,     0,
     128,   146,     0,   155,   157,   156,   158,     0,     0,     0,
       0,   169,   159,   132,   149,   148,     0,    92,    96,     0,
       0,     0,     0,   134,     0,     0,     0,    53,    86,     0,
     154,    33,    34,    35,    36,    37,    38,   104,     0,     0,
     112,   105,   113,     0,     0,     0,   167,   133,   100,   110,
     101,   111,     0,    98,   108,    99,   109,     0,    84,    88,
     137,     0,     0,     0,   126,   143,   129,     0,   119,   120,
     115,   114,   118,   122,   123,   117,   116,   121,    78,    82,
      83,     0,   102,   106,   103,   107,     0,     0,   125,     0,
     144,    87,     0,     0,    77,   170,    85,    80,     0,     0,
     129,    79,   127,   145,     0,     0,    81
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -215,  -215,     6,   286,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,    -2,    -1,  -215,  -215,  -214,  -215,  -215,   235,  -215,
    -215,  -215,   239,  -215,  -215,   258,   -72,   246,  -215,   -82,
    -215,  -213,  -215,  -215,  -215,  -215,  -215,  -215,  -215,    -6,
    -215,  -215,  -215,  -180,  -139,  -215,  -215,  -215,  -215,    82,
     -61,  -215,    75,  -211,  -215,  -215,  -215,   -45,   123,  -215,
     -60,  -113,  -215,  -215
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    86,    12,    13,    25,    14,    26,    38,    39,
      48,    19,    57,    42,    58,   260,    16,    34,    49,    50,
      28,    59,    60,    61,    17,    44,    88,    63,    89,    90,
      91,    92,    93,   314,    94,    95,    96,    97,   277,   249,
      98,    99,   100,   261,   262,   101,   102,   103,   104,   195,
     132,   210,   211,   153,   106,   107,   108,   212,   134,   109,
     135,   136,   137,   196
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      15,   105,   110,   117,   246,   248,     2,   157,    20,   146,
     147,    27,    15,   172,   173,   174,   175,   176,   177,   148,
       3,    35,   269,    31,   149,   274,   150,    21,   105,   110,
     242,   133,    30,   283,   243,   151,     4,     5,     6,     7,
       8,    55,   152,   146,   147,    54,    64,    32,   146,   147,
      22,   288,   289,   162,   163,    69,   270,   290,   303,   275,
      87,   306,   146,   147,   286,   307,   287,    33,   258,   245,
     166,   167,   217,   311,   281,   139,   142,    23,   291,   296,
     171,   282,   259,   235,    24,   286,    36,    87,   318,   325,
      37,   154,   304,   105,   110,   164,   165,   271,   319,   206,
     276,   223,   224,   225,   226,   213,   214,   248,   216,     4,
       5,     6,     7,     8,    73,   220,   221,    74,    75,   292,
     297,  -147,    77,    78,   230,    40,    80,    41,    82,    83,
     293,   294,    43,   305,    51,   149,   295,   169,   202,   233,
    -154,  -154,     4,     5,     6,     7,     8,   258,    52,    53,
      84,    62,    87,   170,    65,    56,    66,   250,   110,    85,
      68,   259,     4,     5,     6,     7,     8,    73,    70,   279,
      74,    75,  -129,    76,  -147,    77,    78,    79,    71,    80,
      81,    82,    83,    18,   265,     4,     5,     6,     7,     8,
      72,   298,   299,   111,   115,   278,    45,    46,    47,   116,
     284,   285,   143,    84,    85,   144,     4,     5,     6,     7,
       8,   145,    85,   -57,   155,   158,    87,   159,   156,   160,
       9,   168,   -61,   161,   197,   250,   110,    10,   199,   198,
       4,     5,     6,     7,     8,   317,   308,   200,   310,   207,
     203,   321,   312,   140,   204,   205,   215,    11,   218,   219,
     236,   222,   239,   326,     4,     5,     6,     7,     8,   250,
     110,   316,   178,   179,   180,   181,   182,   183,   229,   231,
     237,   141,   238,   322,   323,     4,     5,     6,     7,     8,
     184,   240,   263,   247,    87,   149,   264,   272,   309,   185,
     186,   313,   187,   188,   315,    18,   189,   190,   301,   191,
      29,   112,   192,   193,   194,   178,   179,   180,   181,   182,
     183,   114,    67,   113,   324,   267,   138,   280,    87,   234,
       0,   178,   179,   180,   181,   182,   183,   227,     0,     0,
       0,     0,   185,   186,     0,   187,   188,     0,     0,   189,
     190,     0,   191,   228,     0,   192,   193,   194,   185,   186,
       0,   187,   188,     0,     0,   189,   190,     0,   191,     0,
       0,   192,   193,   194,   178,   179,   180,   181,   182,   183,
       0,     4,     5,     6,     7,     8,     0,     0,     0,     0,
     178,   179,   180,   181,   182,   183,   232,     0,     0,     0,
       0,   185,   186,     0,   187,   188,     0,     0,   189,   190,
       0,   191,   241,     0,   192,   193,   194,   185,   186,     0,
     187,   188,   201,     0,   189,   190,     0,   191,     0,     0,
     192,   193,   194,   178,   179,   180,   181,   182,   183,     0,
       0,   251,   252,   253,   254,   255,   256,   257,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   244,   258,     0,
     185,   186,     0,   187,   188,     0,     0,   189,   190,     0,
     191,     0,   259,   192,   193,   194,   178,   179,   180,   181,
     182,   183,     0,     0,   251,   252,   253,   254,   255,   256,
     268,     0,   178,   179,   180,   181,   182,   183,     0,     0,
     266,   258,     0,   185,   186,     0,   187,   188,     0,     0,
     189,   190,     0,   191,   300,   259,   192,   193,   194,   185,
     186,     0,   187,   188,     0,     0,   189,   190,     0,   191,
       0,     0,   192,   193,   194,   178,   179,   180,   181,   182,
     183,     0,     0,     0,     0,     0,     0,   251,   252,   253,
     254,   255,   256,   273,     0,   320,   178,   179,   180,   181,
     182,   183,   185,   186,   258,   187,   188,     0,     0,   189,
     190,     0,   191,     0,     0,   192,   193,   194,   259,     0,
       0,     0,     0,   185,   186,     0,   187,   188,     0,     0,
     189,   190,     0,   191,     0,     0,   192,   193,   194,   118,
     119,   120,   121,   122,   123,   124,     0,     0,     0,     0,
     125,   208,     0,     0,     0,     0,   126,     0,     0,     0,
       0,     0,   127,   128,     0,   129,     0,   209,     0,   130,
     131,   118,   119,   120,   121,   122,   123,   124,     0,     0,
       0,     0,   125,     0,     0,     0,     0,     0,   126,     0,
       0,     0,     0,     0,   127,   128,     0,   129,     0,   209,
       0,   130,   131,   118,   119,   120,   121,   122,   123,   124,
       0,     0,     0,     0,   125,     0,     0,     0,     0,     0,
     126,     0,     0,     0,     0,     0,   127,   128,     0,   129,
       0,     0,     0,   130,   131,   251,   252,   253,   254,   255,
     256,   302,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   258,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   259
};

static const yytype_int16 yycheck[] =
{
       2,    62,    62,    75,   215,   218,     0,    89,     9,    34,
      35,    13,    14,   126,   127,   128,   129,   130,   131,    44,
       0,    22,   236,    17,    49,   239,    51,    44,    89,    89,
      46,    76,    44,   244,    50,    60,     3,     4,     5,     6,
       7,    42,    67,    34,    35,    39,    48,    44,    34,    35,
      17,    38,    39,    36,    37,    56,   236,    44,   272,   239,
      62,    46,    34,    35,    46,    50,    48,    51,    55,    60,
     115,   116,   154,   286,    60,    77,    78,    44,   258,   259,
     125,    67,    69,   196,    51,    46,    38,    89,    60,    50,
      47,    85,   272,   154,   154,    36,    37,   236,   309,   144,
     239,   162,   163,   164,   165,   150,   151,   320,   153,     3,
       4,     5,     6,     7,     8,   160,   161,    11,    12,   258,
     259,    15,    16,    17,   169,    47,    20,    17,    22,    23,
      38,    39,    49,   272,    47,    49,    44,    51,   140,   184,
      36,    37,     3,     4,     5,     6,     7,    55,    47,    52,
      44,    53,   154,    67,    52,    16,    48,   218,   218,    53,
      47,    69,     3,     4,     5,     6,     7,     8,    44,   241,
      11,    12,    13,    14,    15,    16,    17,    18,    50,    20,
      21,    22,    23,    44,   229,     3,     4,     5,     6,     7,
      46,   263,   264,    44,    49,   240,    25,    26,    27,    49,
     245,   246,    49,    44,    53,    49,     3,     4,     5,     6,
       7,    38,    53,    54,    19,    54,   218,    47,    44,    13,
      17,    11,    47,    15,    57,   286,   286,    24,    44,    57,
       3,     4,     5,     6,     7,   307,   281,    44,   283,    48,
      44,   313,   287,    16,    44,    44,    44,    44,    49,    28,
      28,    44,    28,   325,     3,     4,     5,     6,     7,   320,
     320,   306,    28,    29,    30,    31,    32,    33,    49,    44,
      44,    44,    44,   318,   319,     3,     4,     5,     6,     7,
      46,    48,     9,    54,   286,    49,    12,    28,    44,    55,
      56,    10,    58,    59,    44,    44,    62,    63,    67,    65,
      14,    66,    68,    69,    70,    28,    29,    30,    31,    32,
      33,    72,    54,    67,   320,   233,    44,   242,   320,   196,
      -1,    28,    29,    30,    31,    32,    33,    50,    -1,    -1,
      -1,    -1,    55,    56,    -1,    58,    59,    -1,    -1,    62,
      63,    -1,    65,    50,    -1,    68,    69,    70,    55,    56,
      -1,    58,    59,    -1,    -1,    62,    63,    -1,    65,    -1,
      -1,    68,    69,    70,    28,    29,    30,    31,    32,    33,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    33,    50,    -1,    -1,    -1,
      -1,    55,    56,    -1,    58,    59,    -1,    -1,    62,    63,
      -1,    65,    50,    -1,    68,    69,    70,    55,    56,    -1,
      58,    59,    44,    -1,    62,    63,    -1,    65,    -1,    -1,
      68,    69,    70,    28,    29,    30,    31,    32,    33,    -1,
      -1,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    55,    -1,
      55,    56,    -1,    58,    59,    -1,    -1,    62,    63,    -1,
      65,    -1,    69,    68,    69,    70,    28,    29,    30,    31,
      32,    33,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    -1,    28,    29,    30,    31,    32,    33,    -1,    -1,
      52,    55,    -1,    55,    56,    -1,    58,    59,    -1,    -1,
      62,    63,    -1,    65,    50,    69,    68,    69,    70,    55,
      56,    -1,    58,    59,    -1,    -1,    62,    63,    -1,    65,
      -1,    -1,    68,    69,    70,    28,    29,    30,    31,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    44,    -1,    48,    28,    29,    30,    31,
      32,    33,    55,    56,    55,    58,    59,    -1,    -1,    62,
      63,    -1,    65,    -1,    -1,    68,    69,    70,    69,    -1,
      -1,    -1,    -1,    55,    56,    -1,    58,    59,    -1,    -1,
      62,    63,    -1,    65,    -1,    -1,    68,    69,    70,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      49,    50,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    61,    62,    -1,    64,    -1,    66,    -1,    68,
      69,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    61,    62,    -1,    64,    -1,    66,
      -1,    68,    69,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    64,
      -1,    -1,    -1,    68,    69,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    69
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    72,    73,     0,     3,     4,     5,     6,     7,    17,
      24,    44,    74,    75,    77,    82,    87,    95,    44,    82,
      83,    44,    17,    44,    51,    76,    78,    82,    91,    74,
      44,    73,    44,    51,    88,    83,    38,    47,    79,    80,
      47,    17,    84,    49,    96,    25,    26,    27,    81,    89,
      90,    47,    47,    52,    73,    83,    16,    83,    85,    92,
      93,    94,    53,    98,    82,    52,    48,    96,    47,    83,
      44,    50,    46,     8,    11,    12,    14,    16,    17,    18,
      20,    21,    22,    23,    44,    53,    73,    82,    97,    99,
     100,   101,   102,   103,   105,   106,   107,   108,   111,   112,
     113,   116,   117,   118,   119,   121,   125,   126,   127,   130,
     131,    44,    89,    98,    93,    49,    49,    97,    38,    39,
      40,    41,    42,    43,    44,    49,    55,    61,    62,    64,
      68,    69,   121,   128,   129,   131,   132,   133,    44,    82,
      16,    44,    82,    49,    49,    38,    34,    35,    44,    49,
      51,    60,    67,   124,    73,    19,    44,   100,    54,    47,
      13,    15,    36,    37,    36,    37,   128,   128,    11,    51,
      67,   128,   132,   132,   132,   132,   132,   132,    28,    29,
      30,    31,    32,    33,    46,    55,    56,    58,    59,    62,
      63,    65,    68,    69,    70,   120,   134,    57,    57,    44,
      44,    44,    82,    44,    44,    44,   128,    48,    50,    66,
     122,   123,   128,   128,   128,    44,   128,   100,    49,    28,
     128,   128,    44,   121,   121,   121,   121,    50,    50,    49,
     128,    44,    50,   128,   129,   132,    28,    44,    44,    28,
      48,    50,    46,    50,    52,    60,   124,    54,   102,   110,
     121,    38,    39,    40,    41,    42,    43,    44,    55,    69,
      86,   114,   115,     9,    12,   128,    52,   120,    44,    86,
     114,   115,    28,    44,    86,   114,   115,   109,   128,    97,
     123,    60,    67,   124,   128,   128,    46,    48,    38,    39,
      44,   114,   115,    38,    39,    44,   114,   115,    97,    97,
      50,    67,    44,    86,   114,   115,    46,    50,   128,    44,
     128,   102,   128,    10,   104,    44,   128,    97,    60,   124,
      48,    97,   128,   128,   110,    50,    97
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    73,    74,    74,    75,    76,    77,    77,
      77,    78,    78,    78,    78,    79,    79,    80,    81,    81,
      81,    81,    82,    82,    82,    82,    82,    83,    83,    84,
      84,    85,    85,    86,    86,    86,    86,    86,    86,    87,
      88,    89,    89,    90,    91,    92,    92,    93,    93,    94,
      95,    95,    96,    97,    98,    99,    99,   100,   100,   101,
     101,   101,   101,   101,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   103,   104,   104,
     105,   106,   107,   108,   109,   109,   110,   110,   111,   112,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   114,   114,   114,   114,   115,   115,
     115,   115,   115,   115,   116,   116,   116,   116,   117,   118,
     119,   119,   120,   120,   121,   121,   122,   122,   123,   123,
     124,   124,   125,   125,   125,   125,   126,   127,   128,   128,
     128,   128,   129,   129,   130,   131,   131,   131,   131,   132,
     132,   132,   132,   132,   132,   132,   132,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134
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
       1,     1,     2,     2,     1,     3,     3,     3,     3,     3,
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
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1473 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 4: /* TK_PR_FLOAT  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1487 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 5: /* TK_PR_BOOL  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1501 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 6: /* TK_PR_CHAR  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1515 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 7: /* TK_PR_STRING  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1529 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 8: /* TK_PR_IF  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1543 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 9: /* TK_PR_THEN  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1557 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 10: /* TK_PR_ELSE  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1571 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 11: /* TK_PR_WHILE  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1585 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 12: /* TK_PR_DO  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1599 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 13: /* TK_PR_INPUT  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1613 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 14: /* TK_PR_OUTPUT  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1627 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 15: /* TK_PR_RETURN  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1641 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 16: /* TK_PR_CONST  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1655 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 17: /* TK_PR_STATIC  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1669 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 18: /* TK_PR_FOREACH  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1683 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 19: /* TK_PR_FOR  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1697 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 20: /* TK_PR_SWITCH  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1711 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 21: /* TK_PR_CASE  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1725 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 22: /* TK_PR_BREAK  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1739 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 23: /* TK_PR_CONTINUE  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1753 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 24: /* TK_PR_CLASS  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1767 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 25: /* TK_PR_PRIVATE  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1781 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 26: /* TK_PR_PUBLIC  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1795 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 27: /* TK_PR_PROTECTED  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1809 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 28: /* TK_OC_LE  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1823 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 29: /* TK_OC_GE  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1837 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 30: /* TK_OC_EQ  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1851 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 31: /* TK_OC_NE  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1865 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 32: /* TK_OC_AND  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1879 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 33: /* TK_OC_OR  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1893 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 34: /* TK_OC_SL  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1907 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 35: /* TK_OC_SR  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1921 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 36: /* TK_OC_FORWARD_PIPE  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1935 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 37: /* TK_OC_BASH_PIPE  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1949 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 38: /* TK_LIT_INT  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1963 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 39: /* TK_LIT_FLOAT  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1977 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 40: /* TK_LIT_FALSE  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1991 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 41: /* TK_LIT_TRUE  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2005 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 42: /* TK_LIT_CHAR  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2019 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 43: /* TK_LIT_STRING  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2033 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 44: /* TK_IDENTIFICADOR  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2047 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 45: /* TOKEN_ERRO  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2061 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 46: /* ','  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2075 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 47: /* ';'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2089 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 48: /* ':'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2103 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 49: /* '('  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2117 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 50: /* ')'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2131 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 51: /* '['  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2145 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 52: /* ']'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2159 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 53: /* '{'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2173 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 54: /* '}'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2187 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 55: /* '-'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2201 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 56: /* '|'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2215 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 57: /* '?'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2229 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 58: /* '<'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2243 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 59: /* '>'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2257 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 60: /* '='  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2271 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 61: /* '!'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2285 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 62: /* '&'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2299 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 63: /* '%'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2313 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 64: /* '#'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2327 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 65: /* '^'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2341 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 66: /* '.'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2355 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 67: /* '$'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2369 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 68: /* '*'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2383 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 69: /* '+'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2397 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 70: /* '/'  */
#line 254 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2411 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 72: /* programa  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2421 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 74: /* componentes  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2431 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 75: /* idThatCanBeFuncType  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2441 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 76: /* idThatCanBeFuncName  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2451 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 77: /* componente  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2461 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 78: /* depoisDeIdent  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2471 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 79: /* fechaVarOuFunc  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2481 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 81: /* encapsulamento  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2491 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 82: /* tiposPrimitivos  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2501 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 83: /* tipo  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2511 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 84: /* static  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2521 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 85: /* tipoConst  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2531 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 86: /* literais  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2541 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 87: /* novoTipo  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2551 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 88: /* listaCampos  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2561 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 89: /* list  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2571 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 90: /* campo  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2581 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 91: /* tamanhoVetor  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2591 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 92: /* args  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2601 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 93: /* parameters  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2611 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 94: /* parameter  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2621 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 95: /* funcName  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2631 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 96: /* funcArgs  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2641 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 97: /* blocoComandos  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2651 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 98: /* blocoSemEscopo  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2661 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 99: /* comando  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2671 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 100: /* comandos  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2681 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 101: /* comandoSimples  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2691 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 102: /* comandosSemVirgula  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2701 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 103: /* ifThenElse  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2711 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 104: /* optElse  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2721 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 105: /* foreach  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2731 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 106: /* for  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2741 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 107: /* while_do  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2751 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 108: /* do_while  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2761 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 109: /* foreachList  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2771 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 110: /* forList  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2781 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 111: /* switch  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2791 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 112: /* case  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2801 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 113: /* localVarDefinition  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2811 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 114: /* negativeOrPositiveIdentifier  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2821 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 115: /* negativeOrPositiveLiteral  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2831 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 116: /* assignment  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2841 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 117: /* input  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2851 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 119: /* output  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2861 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 120: /* continueOutput  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2871 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 121: /* funcCall  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2881 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 122: /* argsCall  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2891 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 123: /* argCall  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2901 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 124: /* shiftOp  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2911 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 125: /* shift  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2921 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 126: /* return  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2931 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 128: /* expression  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2941 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 129: /* infiniteQuestionMarks  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2951 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 130: /* savePipe  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2961 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 131: /* pipe  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2971 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 132: /* parenthesisOrOperand  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2981 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 133: /* operands  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2991 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 134: /* operators  */
#line 263 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 3001 "parser.tab.c" /* yacc.c:1257  */
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
#line 288 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast); arvore = (yyval.ast); 
		parsingSucceded = TRUE;
		closeTable(); // fecha escopo global
	}
#line 3269 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 296 "parser/parser.y" /* yacc.c:1646  */
    {initTable();}
#line 3275 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 300 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3281 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 301 "parser/parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3287 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 310 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); firstID = (yyval.ast);}
#line 3293 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 314 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); secondID = (yyval.ast);}
#line 3299 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 318 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3305 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 319 "parser/parser.y" /* yacc.c:1646  */
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
#line 3397 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 407 "parser/parser.y" /* yacc.c:1646  */
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
#line 3419 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 427 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3430 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 433 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3440 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 438 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3449 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 442 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3458 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 448 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3464 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 449 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		closeTable();
	}
#line 3474 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 457 "parser/parser.y" /* yacc.c:1646  */
    {
		int isUsr = verifyUse(firstID->token->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; YYABORT;}
		int addSymb = addSymbol(secondID->token, NATUREZA_IDENTIFICADOR, USER, getUserType(firstID), 0, TRUE, 0);
		if(addSymb != 0){ returnError = addSymb; YYABORT;}
		saveFunc(secondID->token->value.str);
	}
#line 3486 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 466 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3492 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 467 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3498 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 468 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3504 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 469 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3510 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 472 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3516 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 473 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3522 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 474 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3528 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 475 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3534 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 476 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3540 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 479 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3546 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 480 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3552 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 483 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3558 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 484 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3564 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 487 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3570 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 488 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3576 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 491 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = INT; }
#line 3582 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 492 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = FLOAT; }
#line 3588 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 493 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = BOOL; }
#line 3594 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 494 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = BOOL; }
#line 3600 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 495 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = CHAR; }
#line 3606 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 496 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = STRING; }
#line 3612 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 501 "parser/parser.y" /* yacc.c:1646  */
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
#line 3627 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 512 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3637 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 519 "parser/parser.y" /* yacc.c:1646  */
    {adicionaCampo(criaCampo((yyvsp[0].ast))); (yyval.ast) = (yyvsp[0].ast);}
#line 3643 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 520 "parser/parser.y" /* yacc.c:1646  */
    {		
		adicionaCampo(criaCampo((yyvsp[-2].ast)));

		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3655 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 529 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3665 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 538 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3675 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 546 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3681 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 547 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3687 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 550 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		
		adicionaArg(criaArg((yyvsp[-2].ast)));

		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));

	}
#line 3701 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 559 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); adicionaArg(criaArg((yyvsp[0].ast)));}
#line 3707 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 562 "parser/parser.y" /* yacc.c:1646  */
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
#line 3733 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 587 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, TRUE, 0);		
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		saveFunc((yyvsp[0].valor_lexico)->value.str);	
	}
#line 3745 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 594 "parser/parser.y" /* yacc.c:1646  */
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
#line 3766 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 614 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[-1].ast));
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3776 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 626 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		closeTable();                     //Fecha escopo local
	}
#line 3787 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 636 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[-1].ast));
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3797 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 643 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 3803 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 644 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3809 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 647 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3815 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 648 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3821 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 653 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 654 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3833 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 655 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3839 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 656 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3845 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 657 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3851 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 662 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3857 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 663 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3863 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 664 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3869 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 665 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3875 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 666 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3881 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 667 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3887 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 668 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3893 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 669 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3899 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 670 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3905 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 671 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3911 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 672 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3917 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 673 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3923 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 674 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3929 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 678 "parser/parser.y" /* yacc.c:1646  */
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
#line 3946 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 692 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3952 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 693 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3958 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 696 "parser/parser.y" /* yacc.c:1646  */
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
#line 3974 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 713 "parser/parser.y" /* yacc.c:1646  */
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
#line 3995 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 732 "parser/parser.y" /* yacc.c:1646  */
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
#line 4011 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 745 "parser/parser.y" /* yacc.c:1646  */
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
#line 4027 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 760 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);

		int correctOperands =  coercion(NONE, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4038 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 766 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));

		int correctOperands =  coercion(NONE, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4051 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 776 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4057 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 777 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4067 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 785 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int correctOperands =  coercion(INT, (yyvsp[-2].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4082 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 797 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4092 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 807 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = verifyUse((yyvsp[-1].valor_lexico)->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)->kids[0]), 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
	}
#line 4106 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 816 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = verifyUse((yyvsp[-1].valor_lexico)->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)->kids[0]), 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
	}
#line 4120 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 825 "parser/parser.y" /* yacc.c:1646  */
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
#line 4136 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 836 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = verifyUse((yyvsp[-1].valor_lexico)->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)), 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		
	}
#line 4150 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 845 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
	}
#line 4162 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 852 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		
	}
#line 4175 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 860 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
	}
#line 4188 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 868 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
	}
#line 4199 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 875 "parser/parser.y" /* yacc.c:1646  */
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
#line 4222 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 893 "parser/parser.y" /* yacc.c:1646  */
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
#line 4244 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 910 "parser/parser.y" /* yacc.c:1646  */
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
#line 4268 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 929 "parser/parser.y" /* yacc.c:1646  */
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
#line 4288 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 944 "parser/parser.y" /* yacc.c:1646  */
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
#line 4312 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 963 "parser/parser.y" /* yacc.c:1646  */
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
#line 4332 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 978 "parser/parser.y" /* yacc.c:1646  */
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
#line 4355 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 996 "parser/parser.y" /* yacc.c:1646  */
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
#line 4373 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1010 "parser/parser.y" /* yacc.c:1646  */
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
#line 4394 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1026 "parser/parser.y" /* yacc.c:1646  */
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
#line 4411 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1038 "parser/parser.y" /* yacc.c:1646  */
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
#line 4431 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1053 "parser/parser.y" /* yacc.c:1646  */
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
#line 4447 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1064 "parser/parser.y" /* yacc.c:1646  */
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
#line 4470 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1082 "parser/parser.y" /* yacc.c:1646  */
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
#line 4486 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1093 "parser/parser.y" /* yacc.c:1646  */
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
#line 4506 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1108 "parser/parser.y" /* yacc.c:1646  */
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
#line 4521 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1120 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->type = (yyvsp[0].ast)->type;
	}
#line 4531 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1125 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));		
		(yyval.ast)->kids[0]->type = identifierType((yyvsp[0].valor_lexico)->value.str);
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4543 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1132 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->type = (yyvsp[0].ast)->type;
	}
#line 4553 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1137 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = identifierType((yyvsp[0].valor_lexico)->value.str);
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4565 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1147 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->type = (yyvsp[0].ast)->type;
	}
#line 4575 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1152 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = INT;
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4587 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1159 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = FLOAT;
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4599 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1166 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->type = (yyvsp[0].ast)->type;
	}
#line 4609 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1171 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = INT;
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4621 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1178 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = FLOAT;
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4633 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1189 "parser/parser.y" /* yacc.c:1646  */
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
	}
#line 4653 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1204 "parser/parser.y" /* yacc.c:1646  */
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
#line 4678 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1224 "parser/parser.y" /* yacc.c:1646  */
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
#line 4700 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1241 "parser/parser.y" /* yacc.c:1646  */
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
#line 4730 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1268 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[0].ast)->token->tokenType!=IDS){ returnError = ERR_WRONG_PAR_INPUT; nodeNotAdded = (yyval.ast); YYABORT;}	
		isInput = FALSE;
	}
#line 4740 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1277 "parser/parser.y" /* yacc.c:1646  */
    {isInput = TRUE;}
#line 4746 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1285 "parser/parser.y" /* yacc.c:1646  */
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
#line 4766 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1300 "parser/parser.y" /* yacc.c:1646  */
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
#line 4785 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1316 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[0].ast)->type != INT && (yyvsp[0].ast)->type != FLOAT && (yyvsp[0].ast)->token->literType!=STRING)
			{ returnError = ERR_WRONG_PAR_OUTPUT; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4796 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1322 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[-1].ast)->type != INT && (yyvsp[-1].ast)->type != FLOAT && (yyvsp[-1].ast)->token->literType!=STRING)
			{ returnError = ERR_WRONG_PAR_OUTPUT; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4808 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1331 "parser/parser.y" /* yacc.c:1646  */
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
#line 4823 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1341 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isFunc = verifyUse((yyvsp[-2].valor_lexico)->value.str, FUN);
		if (isFunc != TRUE){ returnError = isFunc; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctArgs = verifyArguments((yyvsp[-2].valor_lexico)->value.str, NULL);
		if (correctArgs != TRUE){ returnError = correctArgs; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4837 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1352 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);	//tem cabeça NULL para facilitar verificação dos argumentos
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4846 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1356 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4856 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1363 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);
		int correctOperands =  coercion(NONE, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
		
	}
#line 4866 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1368 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4872 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1371 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4878 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1372 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 4884 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1374 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVar = verifyUse((yyvsp[-2].valor_lexico)->value.str, VAR);
		if (isVar != TRUE){ returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}

		int correctOperands =  coercion(INT, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4899 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1384 "parser/parser.y" /* yacc.c:1646  */
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
#line 4918 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1398 "parser/parser.y" /* yacc.c:1646  */
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
#line 4939 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1414 "parser/parser.y" /* yacc.c:1646  */
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
#line 4966 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1440 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int verifRet = verifyReturn((yyvsp[0].ast));
		if (verifRet != TRUE){ returnError = verifRet; nodeNotAdded = (yyval.ast); YYABORT;}
		isReturn = FALSE;
	}
#line 4977 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1450 "parser/parser.y" /* yacc.c:1646  */
    {isReturn = TRUE;}
#line 4983 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1454 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		if((yyvsp[-1].ast)->token->tokenType == SPEC_CHAR){
			if((yyvsp[-1].ast)->token->value.c == '+' || (yyvsp[-1].ast)->token->value.c == '%' || (yyvsp[-1].ast)->token->value.c == '/' || (yyvsp[-1].ast)->token->value.c == '*' || (yyvsp[-1].ast)->token->value.c == '-' || (yyvsp[-1].ast)->token->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].ast)->token->value.c == '|' || (yyvsp[-1].ast)->token->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].ast)->token->value.c == '<' || (yyvsp[-1].ast)->token->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].ast)->token->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].ast)->token->value.str, "<=") == 0 || strcmp((yyvsp[-1].ast)->token->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].ast)->token->value.str, "&&") == 0 || strcmp((yyvsp[-1].ast)->token->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].ast)->token->value.str, "==") == 0 || strcmp((yyvsp[-1].ast)->token->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}				
	}
#line 5023 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1489 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));

		if((yyvsp[-1].ast)->token->tokenType == SPEC_CHAR){
			if((yyvsp[-1].ast)->token->value.c == '+' || (yyvsp[-1].ast)->token->value.c == '%' || (yyvsp[-1].ast)->token->value.c == '/' || (yyvsp[-1].ast)->token->value.c == '*' || (yyvsp[-1].ast)->token->value.c == '-' || (yyvsp[-1].ast)->token->value.c == '^'){
				int coercion = arithmeticCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].ast)->token->value.c == '|' || (yyvsp[-1].ast)->token->value.c == '&'){
				int coercion = bitwiseCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if((yyvsp[-1].ast)->token->value.c == '<' || (yyvsp[-1].ast)->token->value.c == '>'){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
		else if((yyvsp[-1].ast)->token->tokenType == COMP_OPER){
			if(strcmp((yyvsp[-1].ast)->token->value.str, "<=") == 0 || strcmp((yyvsp[-1].ast)->token->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].ast)->token->value.str, "&&") == 0 || strcmp((yyvsp[-1].ast)->token->value.str, "||") == 0){
				int coercion = logicCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
			else if(strcmp((yyvsp[-1].ast)->token->value.str, "==") == 0 || strcmp((yyvsp[-1].ast)->token->value.str, "!=") == 0){
				int coercion = relationalCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
			}
		}
	}
#line 5062 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1523 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); (yyval.ast)->type = (yyvsp[0].ast)->type;}
#line 5068 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1524 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); (yyval.ast)->type = (yyvsp[0].ast)->type;}
#line 5074 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1527 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 5080 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1528 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 5086 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1532 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); inpPipe = (yyvsp[0].ast);}
#line 5092 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1535 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 5102 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1540 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 5112 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1545 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 5122 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1550 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 5132 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1558 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodoTipado((yyvsp[-2].valor_lexico), (yyvsp[-1].ast)->type); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodoTipado((yyvsp[0].valor_lexico), (yyvsp[-1].ast)->type));
	}
#line 5142 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1563 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); (yyval.ast)->type = (yyvsp[0].ast)->type;}
#line 5148 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1564 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int coercion = unaryArithCoercion((yyval.ast), (yyvsp[0].ast));
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 5159 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1570 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int coercion = unaryArithCoercion((yyval.ast), (yyvsp[0].ast));
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 5170 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1576 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int coercion = unaryLogicCoercion((yyval.ast), (yyvsp[0].ast));
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 5181 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1582 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast)); (yyval.ast)->type = (yyvsp[0].ast)->type;}
#line 5187 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1583 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast)); (yyval.ast)->type = (yyvsp[0].ast)->type;}
#line 5193 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1584 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast)); (yyval.ast)->type = (yyvsp[0].ast)->type;}
#line 5199 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1587 "parser/parser.y" /* yacc.c:1646  */
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
#line 5217 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1600 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));
		if(isInput == TRUE){
			int use = symbolUse((yyvsp[0].valor_lexico)->value.str);
			if(use != VET && use != VAR && use != UTV){returnError = ERR_WRONG_PAR_INPUT; nodeNotAdded = (yyval.ast); YYABORT;}
		}
		else if(isReturn == TRUE){
			int use = symbolUse((yyvsp[0].valor_lexico)->value.str);
			if(use != VAR && use!= UTV){returnError = ERR_WRONG_PAR_RETURN; nodeNotAdded = (yyval.ast); YYABORT;}
		}
		else{
			int isVar = verifyUse((yyvsp[0].valor_lexico)->value.str, VAR);
			if (isVar != TRUE){ returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}

		}
		(yyval.ast)->type = identifierType((yyvsp[0].valor_lexico)->value.str);

	}
#line 5240 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1618 "parser/parser.y" /* yacc.c:1646  */
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
#line 5256 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1629 "parser/parser.y" /* yacc.c:1646  */
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
#line 5281 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1649 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = INT;}
#line 5287 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1650 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = FLOAT;}
#line 5293 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1651 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = BOOL;}
#line 5299 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1652 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = BOOL;}
#line 5305 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1653 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = CHAR;}
#line 5311 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1654 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = STRING;}
#line 5317 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1655 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); (yyval.ast)->type = identifierType((yyval.ast)->token->value.str);}
#line 5323 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1658 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); (yyval.ast)->type = identifierType((yyval.ast)->kids[(yyval.ast)->kidsNumber-1]->token->value.str);}
#line 5329 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1662 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5335 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1663 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5341 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1664 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5347 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1665 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5353 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1666 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5359 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1667 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5365 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1668 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5371 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1669 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5377 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1670 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5383 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1671 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5389 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1672 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5395 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1673 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5401 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1674 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5407 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1675 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5413 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1676 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5419 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1677 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5425 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 5429 "parser.tab.c" /* yacc.c:1646  */
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
#line 1680 "parser/parser.y" /* yacc.c:1906  */



