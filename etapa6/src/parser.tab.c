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


int expressionCoercion(Node *ss, Node *s1, struct lexval *s2, Node *s3){
	if(s2->tokenType == SPEC_CHAR){
			if(s2->value.c == '+' || s2->value.c == '%' || s2->value.c == '/' || s2->value.c == '*' || s2->value.c == '-' || s2->value.c == '^'){
				int coercion = arithmeticCoercion(ss, s1, s3);
				return coercion;
			}
			else if(s2->value.c == '|' || s2->value.c == '&'){
				int coercion = bitwiseCoercion(ss, s1, s3);
				return coercion;
			}
			else if(s2->value.c == '<' || s2->value.c == '>'){
				int coercion = arithRelationalCoercion(ss, s1, s3);
				return coercion;
			}
		}
		else if(s2->tokenType == COMP_OPER){
			if(strcmp(s2->value.str, "<=") == 0 || strcmp(s2->value.str, ">=") == 0){
				int coercion = arithRelationalCoercion(ss, s1, s3);
				return coercion;
			}
			else if(strcmp(s2->value.str, "&&") == 0 || strcmp(s2->value.str, "||") == 0){
				int coercion = logicCoercion(ss, s1, s3);
				return coercion;
			}
			else if(strcmp(s2->value.str, "==") == 0 || strcmp(s2->value.str, "!=") == 0){
				int coercion = relationalCoercion(ss, s1, s3);
				return coercion;
			}
		}
}



#line 238 "parser.tab.c" /* yacc.c:339  */

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
    UNARY = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 175 "parser/parser.y" /* yacc.c:355  */

	struct lexval* valor_lexico;
	struct node* ast;

#line 330 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 347 "parser.tab.c" /* yacc.c:358  */

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
#define YYLAST   733

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  189
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  337

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,     2,    66,    71,    60,    50,     2,
      67,    68,    59,    57,    40,    58,    42,    61,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    45,    46,
      54,    41,    56,    65,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    69,     2,    70,    62,     2,     2,     2,     2,     2,
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
      55,    63
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   340,   340,   366,   370,   371,   383,   387,   391,   392,
     480,   529,   535,   540,   544,   550,   551,   559,   568,   569,
     570,   571,   574,   575,   576,   577,   578,   581,   582,   585,
     586,   589,   590,   593,   594,   595,   596,   597,   598,   603,
     614,   621,   622,   631,   640,   648,   649,   652,   661,   664,
     689,   707,   738,   750,   761,   769,   770,   773,   774,   779,
     780,   781,   782,   783,   788,   789,   790,   791,   792,   793,
     794,   795,   796,   797,   798,   799,   800,   804,   857,   858,
     865,   882,   901,   952,   991,   997,  1007,  1008,  1016,  1028,
    1038,  1048,  1058,  1070,  1080,  1088,  1097,  1106,  1114,  1133,
    1151,  1171,  1187,  1207,  1223,  1242,  1257,  1274,  1287,  1303,
    1315,  1334,  1346,  1362,  1375,  1380,  1387,  1392,  1402,  1407,
    1414,  1421,  1426,  1433,  1444,  1471,  1491,  1508,  1535,  1544,
    1552,  1567,  1583,  1589,  1598,  1648,  1674,  1679,  1687,  1692,
    1695,  1696,  1698,  1708,  1722,  1738,  1764,  1774,  1778,  1779,
    1780,  1781,  1782,  1799,  1813,  1820,  1829,  1847,  1866,  1875,
    1899,  1923,  1932,  1941,  1960,  1979,  1998,  2017,  2036,  2057,
    2080,  2098,  2099,  2106,  2109,  2114,  2119,  2124,  2132,  2145,
    2168,  2179,  2199,  2205,  2206,  2207,  2208,  2209,  2210,  2224
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
  "'+'", "'-'", "'*'", "'%'", "'/'", "'^'", "UNARY", "'!'", "'?'", "'#'",
  "'('", "')'", "'['", "']'", "'$'", "$accept", "programa", "scopeOpenner",
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
  "shift", "return", "returnHelper", "expression", "savePipe", "pipe",
  "operands", YY_NULLPTR
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
      37,    47,    94,   301,    33,    63,    35,    40,    41,    91,
      93,    36
};
# endif

#define YYPACT_NINF -229

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-229)))

#define YYTABLE_NINF -174

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -229,    16,   337,  -229,  -229,  -229,  -229,  -229,  -229,   102,
      -4,  -229,  -229,     3,   337,     1,  -229,  -229,  -229,  -229,
       4,   -18,   102,  -229,    42,    37,  -229,    39,    61,  -229,
    -229,    22,  -229,    32,    47,    52,    33,  -229,  -229,  -229,
    -229,  -229,   102,   178,    86,  -229,  -229,  -229,   407,    62,
      93,  -229,  -229,  -229,    22,   101,   102,  -229,   110,    81,
    -229,   111,   152,  -229,   114,  -229,    32,    86,  -229,  -229,
    -229,  -229,   178,    94,   104,   133,   301,   138,   314,   113,
     119,   146,  -229,  -229,     2,  -229,   169,   151,  -229,   152,
     148,   153,  -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,
    -229,  -229,  -229,   184,  -229,   154,  -229,  -229,   183,    -5,
      18,  -229,  -229,  -229,  -229,   301,   301,   192,  -229,  -229,
    -229,  -229,  -229,  -229,    68,   301,   301,   301,   301,   301,
     301,   301,    80,   397,    18,  -229,   166,   173,   307,   177,
     185,   189,   301,   175,  -229,  -229,  -229,   301,   222,   301,
     193,   301,   152,   165,   168,  -229,  -229,  -229,   301,   301,
     195,   195,   195,   195,   464,   486,   170,   301,   200,  -229,
    -229,  -229,  -229,  -229,  -229,   508,   301,   301,   301,   301,
     301,   301,   301,   301,   301,   301,   301,   301,   301,   301,
     301,   301,   301,  -229,  -229,  -229,   186,   212,   214,  -229,
     208,   223,   530,  -229,   593,  -229,  -229,   -23,  -229,   593,
     416,    53,   593,   224,   202,   344,   593,   593,   204,  -229,
    -229,  -229,  -229,   266,   262,   301,   440,  -229,  -229,   397,
     611,   628,   644,   659,   373,   373,   668,   668,   668,   668,
     182,   182,   -30,   -30,   -30,   -30,   351,  -229,   225,   358,
     301,   133,   265,  -229,     9,   301,   301,  -229,  -229,   -21,
    -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,   315,   367,
    -229,  -229,  -229,   133,   133,   552,   206,  -229,  -229,  -229,
    -229,  -229,   385,  -229,  -229,  -229,  -229,   -13,   593,  -229,
    -229,   301,   244,   301,   593,   593,   202,   301,  -229,  -229,
    -229,  -229,  -229,  -229,  -229,  -229,  -229,  -229,   273,  -229,
    -229,   246,  -229,  -229,  -229,  -229,   301,   133,   593,   105,
     593,  -229,   574,   133,  -229,  -229,   593,  -229,   301,   301,
     202,  -229,   593,   593,    -7,   133,  -229
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
      64,    65,    66,     0,    60,   173,    67,    70,     0,     0,
      75,    43,    42,    16,    47,     0,     0,     0,   182,   183,
     185,   184,   186,   187,   179,     0,     0,     0,     0,     0,
       0,     0,   188,   131,   189,   171,     0,     0,     0,     0,
       0,     0,     0,     0,   140,   141,    93,     0,     0,     0,
       0,     0,     3,     0,    97,    58,    54,    55,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   150,
     153,   152,   151,   154,   149,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   148,   130,    91,    95,     0,     0,    90,
      94,     0,     0,    89,   124,   139,   135,     0,   136,   138,
       0,     0,   142,     0,   129,     0,   128,   146,     0,   174,
     176,   175,   177,     0,     0,     0,     0,   180,   172,   132,
     160,   159,   161,   162,   163,   164,   166,   167,   165,   168,
     169,   170,   157,   158,   156,   155,     0,    92,    96,     0,
       0,     0,     0,   134,     0,     0,     0,    53,    86,     0,
     173,    33,    34,    35,    36,    37,    38,   104,     0,     0,
     112,   105,   113,     0,     0,     0,   178,   133,   100,   110,
     101,   111,     0,    98,   108,    99,   109,     0,    84,    88,
     137,     0,     0,     0,   126,   143,   129,     0,   122,   123,
     117,   116,   121,   119,   120,   115,   114,   118,    78,    82,
      83,     0,   102,   106,   103,   107,     0,     0,   125,     0,
     144,    87,     0,     0,    77,   181,    85,    80,     0,     0,
     129,    79,   127,   145,     0,     0,    81
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -229,  -229,     5,   271,  -229,  -229,  -229,  -229,  -229,  -229,
    -229,    -2,    14,  -229,  -229,  -228,  -229,  -229,   221,  -229,
    -229,  -229,   219,  -229,  -229,   238,   -72,   226,  -229,   -75,
    -229,  -199,  -229,  -229,  -229,  -229,  -229,  -229,  -229,   -26,
    -229,  -229,  -229,   -20,    27,  -229,  -229,  -229,  -229,    76,
     -61,  -229,    54,  -207,  -229,  -229,  -229,   -63,  -229,   -60,
    -229
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    86,    12,    13,    25,    14,    26,    38,    39,
      48,    19,    57,    42,    58,   270,    16,    34,    49,    50,
      28,    59,    60,    61,    17,    44,    88,    63,    89,    90,
      91,    92,    93,   324,    94,    95,    96,    97,   287,   259,
      98,    99,   100,   271,   272,   101,   102,   103,   104,   194,
     132,   207,   208,   151,   106,   107,   108,   209,   109,   134,
     135
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      15,   105,   110,   117,   256,     2,     4,     5,     6,     7,
       8,    27,    15,   133,   155,   258,     3,   252,   279,   296,
      22,   284,    31,    20,   297,   160,   161,   316,   105,   110,
     144,   145,   192,   296,    21,   193,    35,   144,   145,    30,
     146,    23,    32,   147,    54,   253,    64,   293,   162,   163,
     291,    33,   164,   165,   313,   317,    55,    45,    46,    47,
      87,   335,   169,   170,   171,   172,   173,   174,   175,   148,
      69,   149,    24,   150,    36,   137,   140,   213,    41,   202,
     292,   144,   145,    37,   204,    40,   210,    87,   212,    43,
     152,   105,   110,    51,   255,   216,   217,   321,    52,   219,
     220,   221,   222,    53,   226,     4,     5,     6,     7,     8,
    -173,  -173,   329,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
      62,   258,    65,   144,   145,   148,   198,   167,    66,   168,
      18,     4,     5,     6,     7,     8,   328,    68,    70,    71,
      87,    72,   111,   260,   110,     4,     5,     6,     7,     8,
      73,   115,   275,    74,    75,  -129,    76,  -147,    77,    78,
      79,   116,    80,    81,    82,    83,   136,    85,   143,   289,
     141,     4,     5,     6,     7,     8,   142,   288,   153,   154,
      84,   156,   294,   295,    56,   -57,    85,   158,   159,   157,
     -61,   308,   309,   166,   195,     4,     5,     6,     7,     8,
      73,   196,    87,    74,    75,   199,    18,  -147,    77,    78,
     203,   215,    80,   200,    82,    83,   280,   201,   318,   285,
     320,   211,   214,   218,   322,   260,   110,   225,   227,   246,
      84,   189,   190,   191,   192,   327,    85,   193,   301,   306,
     247,   331,   248,   326,   118,   119,   120,   121,   122,   123,
     124,   249,   314,   336,   205,   332,   333,   257,   250,   260,
     110,   148,   125,   281,   274,   273,   286,   311,   282,   126,
     127,   128,   319,   323,   325,    29,   129,   112,   130,   131,
     206,   114,    67,   113,    87,   302,   307,   118,   119,   120,
     121,   122,   123,   124,   334,   277,   290,   205,     0,   315,
       4,     5,     6,     7,     8,   125,     0,     4,     5,     6,
       7,     8,   126,   127,   128,     0,     0,     0,    87,   129,
     138,   130,   131,   118,   119,   120,   121,   122,   123,   124,
       4,     5,     6,     7,     8,   197,     0,   298,   299,     0,
       0,   125,   139,   300,     9,     0,     0,     0,   126,   127,
     128,    10,     0,     0,     0,   129,     0,   130,   131,     0,
       0,     0,   268,   269,     0,    11,   261,   262,   263,   264,
     265,   266,   267,   261,   262,   263,   264,   265,   266,   278,
     261,   262,   263,   264,   265,   266,   283,     0,     0,   303,
     304,   268,   269,     0,     0,   305,     0,     0,   268,   269,
       4,     5,     6,     7,     8,   268,   269,   261,   262,   263,
     264,   265,   266,   312,   268,   269,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,     0,   176,   193,     0,
       0,     0,   268,   269,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
       0,     0,   193,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,     0,
       0,   193,     0,     0,     0,     0,   254,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,     0,     0,   193,     0,     0,     0,     0,
     276,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,     0,     0,   193,
       0,     0,   223,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,     0,
       0,   193,     0,     0,   224,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,     0,     0,   193,     0,     0,   228,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,     0,     0,   193,     0,     0,   251,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,     0,     0,   193,     0,   330,
     310,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,     0,     0,   193,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,     0,     0,   193,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,     0,     0,   193,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,     0,     0,   193,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,     0,     0,   193,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,     0,     0,   193,   187,   188,   189,   190,   191,
     192,     0,     0,   193
};

static const yytype_int16 yycheck[] =
{
       2,    62,    62,    75,   211,     0,     3,     4,     5,     6,
       7,    13,    14,    76,    89,   214,     0,    40,   246,    40,
      17,   249,    17,     9,    45,    30,    31,    40,    89,    89,
      28,    29,    62,    40,    38,    65,    22,    28,    29,    38,
      38,    38,    38,    41,    39,    68,    48,   254,    30,    31,
      41,    69,   115,   116,   282,    68,    42,    25,    26,    27,
      62,    68,   125,   126,   127,   128,   129,   130,   131,    67,
      56,    69,    69,    71,    32,    77,    78,   152,    17,   142,
      71,    28,    29,    46,   147,    46,   149,    89,   151,    67,
      85,   152,   152,    46,    41,   158,   159,   296,    46,   160,
     161,   162,   163,    70,   167,     3,     4,     5,     6,     7,
      30,    31,   319,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
      44,   330,    70,    28,    29,    67,   138,    69,    45,    71,
      38,     3,     4,     5,     6,     7,    41,    46,    38,    68,
     152,    40,    38,   214,   214,     3,     4,     5,     6,     7,
       8,    67,   225,    11,    12,    13,    14,    15,    16,    17,
      18,    67,    20,    21,    22,    23,    38,    44,    32,   251,
      67,     3,     4,     5,     6,     7,    67,   250,    19,    38,
      38,    43,   255,   256,    16,    43,    44,    13,    15,    46,
      46,   273,   274,    11,    38,     3,     4,     5,     6,     7,
       8,    38,   214,    11,    12,    38,    38,    15,    16,    17,
      45,    53,    20,    38,    22,    23,   246,    38,   291,   249,
     293,    38,    67,    38,   297,   296,   296,    67,    38,    53,
      38,    59,    60,    61,    62,   317,    44,    65,   268,   269,
      38,   323,    38,   316,    32,    33,    34,    35,    36,    37,
      38,    53,   282,   335,    42,   328,   329,    43,    45,   330,
     330,    67,    50,   246,    12,     9,   249,    71,    53,    57,
      58,    59,    38,    10,    38,    14,    64,    66,    66,    67,
      68,    72,    54,    67,   296,   268,   269,    32,    33,    34,
      35,    36,    37,    38,   330,   229,   252,    42,    -1,   282,
       3,     4,     5,     6,     7,    50,    -1,     3,     4,     5,
       6,     7,    57,    58,    59,    -1,    -1,    -1,   330,    64,
      16,    66,    67,    32,    33,    34,    35,    36,    37,    38,
       3,     4,     5,     6,     7,    38,    -1,    32,    33,    -1,
      -1,    50,    38,    38,    17,    -1,    -1,    -1,    57,    58,
      59,    24,    -1,    -1,    -1,    64,    -1,    66,    67,    -1,
      -1,    -1,    57,    58,    -1,    38,    32,    33,    34,    35,
      36,    37,    38,    32,    33,    34,    35,    36,    37,    38,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    32,
      33,    57,    58,    -1,    -1,    38,    -1,    -1,    57,    58,
       3,     4,     5,     6,     7,    57,    58,    32,    33,    34,
      35,    36,    37,    38,    57,    58,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    -1,    40,    65,    -1,
      -1,    -1,    57,    58,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    -1,    65,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    70,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      70,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    65,
      -1,    -1,    68,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    65,    -1,    -1,    68,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    -1,    65,    -1,    -1,    68,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    -1,    -1,    65,    -1,    -1,    68,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    -1,    -1,    65,    -1,    45,
      68,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    65,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    -1,    -1,    65,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    -1,    -1,    65,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    -1,    65,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    65,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    -1,    65,    57,    58,    59,    60,    61,
      62,    -1,    -1,    65
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    73,    74,     0,     3,     4,     5,     6,     7,    17,
      24,    38,    75,    76,    78,    83,    88,    96,    38,    83,
      84,    38,    17,    38,    69,    77,    79,    83,    92,    75,
      38,    74,    38,    69,    89,    84,    32,    46,    80,    81,
      46,    17,    85,    67,    97,    25,    26,    27,    82,    90,
      91,    46,    46,    70,    74,    84,    16,    84,    86,    93,
      94,    95,    44,    99,    83,    70,    45,    97,    46,    84,
      38,    68,    40,     8,    11,    12,    14,    16,    17,    18,
      20,    21,    22,    23,    38,    44,    74,    83,    98,   100,
     101,   102,   103,   104,   106,   107,   108,   109,   112,   113,
     114,   117,   118,   119,   120,   122,   126,   127,   128,   130,
     131,    38,    90,    99,    94,    67,    67,    98,    32,    33,
      34,    35,    36,    37,    38,    50,    57,    58,    59,    64,
      66,    67,   122,   129,   131,   132,    38,    83,    16,    38,
      83,    67,    67,    32,    28,    29,    38,    41,    67,    69,
      71,   125,    74,    19,    38,   101,    43,    46,    13,    15,
      30,    31,    30,    31,   129,   129,    11,    69,    71,   129,
     129,   129,   129,   129,   129,   129,    40,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    65,   121,    38,    38,    38,    83,    38,
      38,    38,   129,    45,   129,    42,    68,   123,   124,   129,
     129,    38,   129,   101,    67,    53,   129,   129,    38,   122,
     122,   122,   122,    68,    68,    67,   129,    38,    68,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,    53,    38,    38,    53,
      45,    68,    40,    68,    70,    41,   125,    43,   103,   111,
     122,    32,    33,    34,    35,    36,    37,    38,    57,    58,
      87,   115,   116,     9,    12,   129,    70,   121,    38,    87,
     115,   116,    53,    38,    87,   115,   116,   110,   129,    98,
     124,    41,    71,   125,   129,   129,    40,    45,    32,    33,
      38,   115,   116,    32,    33,    38,   115,   116,    98,    98,
      68,    71,    38,    87,   115,   116,    40,    68,   129,    38,
     129,   103,   129,    10,   105,    38,   129,    98,    41,   125,
      45,    98,   129,   129,   111,    68,    98
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    72,    73,    74,    75,    75,    76,    77,    78,    78,
      78,    79,    79,    79,    79,    80,    80,    81,    82,    82,
      82,    82,    83,    83,    83,    83,    83,    84,    84,    85,
      85,    86,    86,    87,    87,    87,    87,    87,    87,    88,
      89,    90,    90,    91,    92,    93,    93,    94,    94,    95,
      96,    96,    97,    98,    99,   100,   100,   101,   101,   102,
     102,   102,   102,   102,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   104,   105,   105,
     106,   107,   108,   109,   110,   110,   111,   111,   112,   113,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   115,   115,   115,   115,   116,   116,
     116,   116,   116,   116,   117,   117,   117,   117,   118,   119,
     120,   120,   121,   121,   122,   122,   123,   123,   124,   124,
     125,   125,   126,   126,   126,   126,   127,   128,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   130,   131,   131,   131,   131,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132
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
       1,     1,     3,     5,     6,     8,     3,     0,     2,     2,
       2,     2,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     1,     3,     3,     3,     3,     4,     1,
       3,     6,     1,     1,     1,     1,     1,     1,     1,     1
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
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1514 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 4: /* TK_PR_FLOAT  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1528 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 5: /* TK_PR_BOOL  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1542 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 6: /* TK_PR_CHAR  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1556 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 7: /* TK_PR_STRING  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1570 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 8: /* TK_PR_IF  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1584 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 9: /* TK_PR_THEN  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1598 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 10: /* TK_PR_ELSE  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1612 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 11: /* TK_PR_WHILE  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1626 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 12: /* TK_PR_DO  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1640 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 13: /* TK_PR_INPUT  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1654 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 14: /* TK_PR_OUTPUT  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1668 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 15: /* TK_PR_RETURN  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1682 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 16: /* TK_PR_CONST  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1696 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 17: /* TK_PR_STATIC  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1710 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 18: /* TK_PR_FOREACH  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1724 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 19: /* TK_PR_FOR  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1738 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 20: /* TK_PR_SWITCH  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1752 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 21: /* TK_PR_CASE  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1766 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 22: /* TK_PR_BREAK  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1780 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 23: /* TK_PR_CONTINUE  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1794 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 24: /* TK_PR_CLASS  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1808 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 25: /* TK_PR_PRIVATE  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1822 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 26: /* TK_PR_PUBLIC  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1836 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 27: /* TK_PR_PROTECTED  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1850 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 28: /* TK_OC_SL  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1864 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 29: /* TK_OC_SR  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1878 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 30: /* TK_OC_FORWARD_PIPE  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1892 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 31: /* TK_OC_BASH_PIPE  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1906 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 32: /* TK_LIT_INT  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1920 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 33: /* TK_LIT_FLOAT  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1934 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 34: /* TK_LIT_FALSE  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1948 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 35: /* TK_LIT_TRUE  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1962 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 36: /* TK_LIT_CHAR  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1976 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 37: /* TK_LIT_STRING  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 1990 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 38: /* TK_IDENTIFICADOR  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2004 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 39: /* TOKEN_ERRO  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2018 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 40: /* ','  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2032 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 41: /* '='  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2046 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 42: /* '.'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2060 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 43: /* '}'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2074 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 44: /* '{'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2088 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 45: /* ':'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2102 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 46: /* ';'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2116 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 47: /* TK_OC_OR  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2130 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 48: /* TK_OC_AND  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2144 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 49: /* '|'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2158 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 50: /* '&'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2172 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 51: /* TK_OC_EQ  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2186 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 52: /* TK_OC_NE  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2200 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 53: /* TK_OC_LE  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2214 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 54: /* '<'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2228 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 55: /* TK_OC_GE  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2242 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 56: /* '>'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2256 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 57: /* '+'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2270 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 58: /* '-'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2284 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 59: /* '*'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2298 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 60: /* '%'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2312 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 61: /* '/'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2326 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 62: /* '^'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2340 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 63: /* UNARY  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2354 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 64: /* '!'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2368 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 65: /* '?'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2382 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 66: /* '#'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2396 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 67: /* '('  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2410 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 68: /* ')'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2424 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 69: /* '['  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2438 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 70: /* ']'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2452 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 71: /* '$'  */
#line 306 "parser/parser.y" /* yacc.c:1257  */
      { /* Nao podemos desalocar os tokens aqui, precisamos apenas da liberaDanglingScanner();
		Se tentarmos fazer algo aqui, acabamos tentando desalocar alguns tokens mais de uma vez.
		Minha conclusao eh de que o token, apesar de ter ocorrido erro no parsing, eh posto em um nodo
		por alguma das acoes que foram finalizadas antes de se achar o erro. Com isso, acabariamos
		tentando desalocar o mesmo token tanto aqui quanto no destrutor de <ast>.
		OBS.: liberaDanglingParser() desaloca os nodos criados no parser que nao sao adicionados
		      à arvore, assim como os tokens presentes nesses nodos. Ai que mora o problema de
		      tentar liberar o mesmo token mais de uma vez se fizessemos algo no destrutor atual.
	  */}
#line 2466 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 73: /* programa  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2476 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 75: /* componentes  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2486 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 76: /* idThatCanBeFuncType  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2496 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 77: /* idThatCanBeFuncName  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2506 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 78: /* componente  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2516 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 79: /* depoisDeIdent  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2526 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 80: /* fechaVarOuFunc  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2536 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 82: /* encapsulamento  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2546 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 83: /* tiposPrimitivos  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2556 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 84: /* tipo  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2566 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 85: /* static  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2576 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 86: /* tipoConst  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2586 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 87: /* literais  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2596 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 88: /* novoTipo  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2606 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 89: /* listaCampos  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2616 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 90: /* list  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2626 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 91: /* campo  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2636 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 92: /* tamanhoVetor  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2646 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 93: /* args  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2656 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 94: /* parameters  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2666 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 95: /* parameter  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2676 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 96: /* funcName  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2686 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 97: /* funcArgs  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2696 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 98: /* blocoComandos  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2706 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 99: /* blocoSemEscopo  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2716 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 100: /* comando  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2726 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 101: /* comandos  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2736 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 102: /* comandoSimples  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2746 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 103: /* comandosSemVirgula  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2756 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 104: /* ifThenElse  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2766 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 105: /* optElse  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2776 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 106: /* foreach  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2786 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 107: /* for  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2796 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 108: /* while_do  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2806 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 109: /* do_while  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2816 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 110: /* foreachList  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2826 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 111: /* forList  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2836 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 112: /* switch  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2846 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 113: /* case  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2856 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 114: /* localVarDefinition  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2866 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 115: /* negativeOrPositiveIdentifier  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2876 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 116: /* negativeOrPositiveLiteral  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2886 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 117: /* assignment  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2896 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 118: /* input  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2906 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 120: /* output  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2916 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 121: /* continueOutput  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2926 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 122: /* funcCall  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2936 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 123: /* argsCall  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2946 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 124: /* argCall  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2956 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 125: /* shiftOp  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2966 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 126: /* shift  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2976 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 127: /* return  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2986 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 129: /* expression  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 2996 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 130: /* savePipe  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 3006 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 131: /* pipe  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 3016 "parser.tab.c" /* yacc.c:1257  */
        break;

    case 132: /* operands  */
#line 315 "parser/parser.y" /* yacc.c:1257  */
      {
	if(parsingSucceded == FALSE){
		liberaDanglingParser(((*yyvaluep).ast));
	}
}
#line 3026 "parser.tab.c" /* yacc.c:1257  */
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
#line 340 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast); arvore = (yyval.ast); 
		parsingSucceded = TRUE;
		int rfpAndRspInit = 0;
		int rbssInit = 0; //não sei que valor tem que ser aqui
		ILOC_LIST* start = createILOCList();
		Hash* mainContent = getSymbol("main");
		if (mainContent != NULL || mainContent->isFunction == FALSE){		
			createOperation(start, LOADI, "loadI", (void*) &rfpAndRspInit, "rfp", NULL, ARG1_IMED);
			createOperation(start, LOADI, "loadI", (void*) &rfpAndRspInit, "rsp", NULL, ARG1_IMED);
			createOperation(start, LOADI, "loadI", (void*) &rbssInit, "rbss", NULL, ARG1_IMED);
			createOperation(start, JUMPI, "jumpI", mainContent->label, NULL, NULL, 0);
			
			ILOC_LIST* halt = createILOCList();
			createOperation(halt, HALT, "halt", NULL, NULL, NULL, 0);
			(yyval.ast)->opList = concatILOC(start, (yyval.ast)->opList);
			(yyval.ast)->opList = concatILOC((yyval.ast)->opList, halt);
		}
		else{
			returnError = MAIN_NOT_DEFINED; nodeNotAdded = NULL; YYABORT;
		}
		closeTable(); // fecha escopo global
	}
#line 3312 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 366 "parser/parser.y" /* yacc.c:1646  */
    {initTable();}
#line 3318 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 370 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3324 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 371 "parser/parser.y" /* yacc.c:1646  */
    { 
		(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->opList = concatILOC((yyvsp[-1].ast)->opList, (yyvsp[0].ast)->opList);
	}
#line 3333 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 383 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); firstID = (yyval.ast);}
#line 3339 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 387 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); secondID = (yyval.ast);}
#line 3345 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 391 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3351 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 392 "parser/parser.y" /* yacc.c:1646  */
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
#line 3443 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 480 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		argsSize();
		//funcName tem 2 formas possíveis:
		// 1) head = tipoPrimitivo, kids[0] = nome da func
		// 2) head = TK_PR_STATIC, kids[0] = tipo, kids[1] = nome DA FUNC		
		int kid = 0;
		if((yyvsp[-3].ast)->kidsNumber == 2){
			kid = 1;
		}
			
		addArgsToSymbol((yyvsp[-3].ast)->kids[kid]->token->value.str, currentArgs);
		clearCurrentArgs();		

		Hash* funcContent = getSymbol((yyvsp[-3].ast)->kids[0]->token->value.str);
		int sizeLocalVars = funcContent->sizeOfLocalVars;
		createOperation((yyvsp[-3].ast)->opList, I2I, "i2i", "rsp", "rfp", NULL, 0);
		createOperation((yyvsp[-3].ast)->opList, ADDI, "addI", "rsp", (void*) &(sizeLocalVars), "rsp", ARG2_IMED);
		int funcArgs = funcContent->argsNum;
		for(int i = 0; i<funcArgs; i++){
			int currentLoadPos = i*4+12;
			int currentStorePos = i*4+12+4*funcArgs;			
			char* tempReg = getNewRegister();
			createOperation((yyvsp[-3].ast)->opList, LOADAI, "loadAI", "rfp", (void*) &currentLoadPos, tempReg, ARG2_IMED);
			createOperation((yyvsp[-3].ast)->opList, STOREAI, "storeAI", tempReg, "rfp", (void*) &currentStorePos, ARG3_IMED);
		}
		(yyval.ast)->opList = concatILOC((yyvsp[-3].ast)->opList, (yyvsp[0].ast)->opList);
		char* tempRegZero = getNewRegister();
		int zero = 0;
		char* tempRegQuatro = getNewRegister();
		int quatro = 4;
		char* tempRegOito = getNewRegister();
		int oito = 8;
		if(strcmp("main", (yyvsp[-3].ast)->kids[0]->token->value.str) != 0){
			createOperation((yyval.ast)->opList, LOADAI, "loadAI", "rfp", (void*) &zero, tempRegZero, ARG2_IMED);
			createOperation((yyval.ast)->opList, LOADAI, "loadAI", "rfp", (void*) &quatro, tempRegQuatro, ARG2_IMED);
			createOperation((yyval.ast)->opList, LOADAI, "loadAI", "rfp", (void*) &oito, tempRegOito, ARG2_IMED);
			createOperation((yyval.ast)->opList, I2I, "i2i", tempRegQuatro, "rsp", NULL, 0);
			createOperation((yyval.ast)->opList, I2I, "i2i", tempRegOito, "rfp", NULL, 0);
			createOperation((yyval.ast)->opList, JUMP, "jump", tempRegZero, NULL, NULL, 0);
		}
		closeTable();
		
	}
#line 3494 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 529 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3505 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 535 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3515 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 540 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3524 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 544 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 550 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3539 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 551 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		closeTable();
	}
#line 3549 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 559 "parser/parser.y" /* yacc.c:1646  */
    {
		int isUsr = verifyUse(firstID->token->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; YYABORT;}
		int addSymb = addSymbol(secondID->token, NATUREZA_IDENTIFICADOR, USER, getUserType(firstID), 0, TRUE, 0);
		if(addSymb != 0){ returnError = addSymb; YYABORT;}
		saveFunc(secondID->token->value.str);
	}
#line 3561 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 568 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3567 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 569 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3573 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 570 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3579 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 571 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3585 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 574 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3591 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 575 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3597 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 576 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3603 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 577 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3609 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 578 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3615 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 581 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3621 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 582 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3627 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 585 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3633 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 586 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3639 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 589 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));}
#line 3645 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 590 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3651 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 593 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = INT; }
#line 3657 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 594 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = FLOAT; }
#line 3663 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 595 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = BOOL; }
#line 3669 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 596 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = BOOL; }
#line 3675 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 597 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = CHAR; }
#line 3681 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 598 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = STRING; }
#line 3687 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 603 "parser/parser.y" /* yacc.c:1646  */
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
#line 3702 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 614 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3712 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 621 "parser/parser.y" /* yacc.c:1646  */
    {adicionaCampo(criaCampo((yyvsp[0].ast))); (yyval.ast) = (yyvsp[0].ast);}
#line 3718 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 622 "parser/parser.y" /* yacc.c:1646  */
    {		
		adicionaCampo(criaCampo((yyvsp[-2].ast)));

		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 3730 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 631 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3740 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 640 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3750 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 648 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3756 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 649 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3762 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 652 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		
		adicionaArg(criaArg((yyvsp[-2].ast)));

		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));

	}
#line 3776 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 661 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); adicionaArg(criaArg((yyvsp[0].ast)));}
#line 3782 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 664 "parser/parser.y" /* yacc.c:1646  */
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
#line 3808 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 689 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast);
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, TRUE, 0);		
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}	
		saveFunc((yyvsp[0].valor_lexico)->value.str);	
		Hash* funcContent = getSymbol((yyvsp[0].valor_lexico)->value.str);
		if(funcContent!=NULL){
			int labSize = strlen(funcContent->label);
			char* lab = (char*) aloca(sizeof(char) * (labSize + 3));
			strcpy(lab+1, funcContent->label); // copia label a partir da segunda posicao da string...
			lab[0] = '\n';			// pois a primeira posicao ira receber um '\n'
			lab[labSize+1] = ':';
			lab[labSize+2] = '\0';
			createOperation((yyval.ast)->opList, LAB, lab, NULL, NULL, NULL, 0);
		
		}
	}
#line 3831 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 707 "parser/parser.y" /* yacc.c:1646  */
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
		Hash* funcContent = getSymbol((yyvsp[0].valor_lexico)->value.str);
		if(funcContent!=NULL){
			int labSize = strlen(funcContent->label);
			char* lab = (char*) aloca(sizeof(char) * (labSize + 3));
			strcpy(lab+1, funcContent->label);
			lab[0] = 'Z';
			lab[labSize+1] = ':';
			lab[labSize+2] = '\0';
			createOperation((yyval.ast)->opList, LAB, lab, NULL, NULL, NULL, 0);
		
		}

	}
#line 3863 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 738 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[-1].ast));
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 3873 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 750 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->opList = (yyvsp[-1].ast)->opList;
		closeTable();                     //Fecha escopo local
	}
#line 3885 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 761 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[-1].ast));
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->opList = (yyvsp[-1].ast)->opList;
	}
#line 3896 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 769 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 3902 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 770 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3908 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 773 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 3914 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 774 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), (yyvsp[0].ast)); (yyval.ast)->opList = concatILOC((yyvsp[-1].ast)->opList, (yyvsp[0].ast)->opList);}
#line 3920 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 779 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3926 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 780 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3932 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 781 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3938 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 782 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3944 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 783 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3950 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 788 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3956 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 789 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); /*printListOfOperations($$->opList);*/}
#line 3962 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 790 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3968 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 791 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3974 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 792 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3980 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 793 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 3986 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 794 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 3992 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 795 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); /*printListOfOperations($$->opList);*/}
#line 3998 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 796 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); /*printListOfOperations($$->opList);*/}
#line 4004 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 797 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); /*printListOfOperations($$->opList);*/}
#line 4010 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 798 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4016 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 799 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4022 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 800 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4028 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 804 "parser/parser.y" /* yacc.c:1646  */
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
		
		char *newLabelT = getNewLabel();
		patch((yyvsp[-4].ast)->opList, newLabelT, (yyvsp[-4].ast)->trueList);		
		int lenT = strlen(newLabelT);
		char *newLabelTCopy = aloca((lenT+2)*sizeof(char));
		strcpy(newLabelTCopy, newLabelT);
		newLabelTCopy[lenT] = ':';
		newLabelTCopy[lenT+1] = '\0';
		ILOC_LIST* tempT = createILOCList();
		createOperation(tempT, LAB, newLabelTCopy, NULL, NULL, NULL, 0);

		char *newLabelAfterF = getNewLabel();		
		int lenAfterF = strlen(newLabelAfterF);
		char *newLabelAfterFCopy = aloca((lenAfterF+2)*sizeof(char));
		strcpy(newLabelAfterFCopy, newLabelAfterF);
		newLabelAfterFCopy[lenAfterF] = ':';
		newLabelAfterFCopy[lenAfterF+1] = '\0';
		ILOC_LIST* tempAfterF = createILOCList();
		createOperation(tempAfterF, LAB, newLabelAfterFCopy, NULL, NULL, NULL, 0);

		ILOC_LIST* ignoreF = createILOCList();
		createOperation(ignoreF, JUMPI, "jumpI", newLabelAfterF, NULL, NULL, 0);

		char *newLabelF = getNewLabel();
		patch((yyvsp[-4].ast)->opList, newLabelF, (yyvsp[-4].ast)->falseList);		
		int lenF = strlen(newLabelF);
		char *newLabelFCopy = aloca((lenF+2)*sizeof(char));
		strcpy(newLabelFCopy, newLabelF);
		newLabelFCopy[lenF] = ':';
		newLabelFCopy[lenF+1] = '\0';
		ILOC_LIST* tempF = createILOCList();
		createOperation(tempF, LAB, newLabelFCopy, NULL, NULL, NULL, 0);
		
		(yyval.ast)->opList = concatILOC((yyvsp[-4].ast)->opList, tempT);
		(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[-1].ast)->opList);
		(yyval.ast)->opList = concatILOC((yyval.ast)->opList, ignoreF);
		(yyval.ast)->opList = concatILOC((yyval.ast)->opList, tempF);
		(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[0].ast)->opList);		
		(yyval.ast)->opList = concatILOC((yyval.ast)->opList, tempAfterF);
	}
#line 4084 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 857 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo(NULL);}
#line 4090 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 858 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->opList = (yyvsp[0].ast)->opList;
	}
#line 4100 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 865 "parser/parser.y" /* yacc.c:1646  */
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
#line 4116 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 882 "parser/parser.y" /* yacc.c:1646  */
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
#line 4137 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 901 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-4].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-3].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int correctOperands =  coercion(BOOL, (yyvsp[-3].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	
		char *newLabelT = getNewLabel();
		patch((yyvsp[-3].ast)->opList, newLabelT, (yyvsp[-3].ast)->trueList);		
		int lenT = strlen(newLabelT);
		char *newLabelTCopy = aloca((lenT+2)*sizeof(char));
		strcpy(newLabelTCopy, newLabelT);
		newLabelTCopy[lenT] = ':';
		newLabelTCopy[lenT+1] = '\0';
		ILOC_LIST* tempT = createILOCList();
		createOperation(tempT, LAB, newLabelTCopy, NULL, NULL, NULL, 0);

		char *newLabelF = getNewLabel();
		patch((yyvsp[-3].ast)->opList, newLabelF, (yyvsp[-3].ast)->falseList);		
		int lenF = strlen(newLabelF);
		char *newLabelFCopy = aloca((lenF+2)*sizeof(char));
		strcpy(newLabelFCopy, newLabelF);
		newLabelFCopy[lenF] = ':';
		newLabelFCopy[lenF+1] = '\0';
		ILOC_LIST* tempF = createILOCList();
		createOperation(tempF, LAB, newLabelFCopy, NULL, NULL, NULL, 0);

		char *newLabelWhile = getNewLabel();
		int lenWhile = strlen(newLabelWhile);
		char *newLabelWhileCopy = aloca((lenWhile+2)*sizeof(char));
		strcpy(newLabelWhileCopy, newLabelWhile);
		newLabelWhileCopy[lenWhile] = ':';
		newLabelWhileCopy[lenWhile+1] = '\0';
		ILOC_LIST* tempWhile = createILOCList();
		createOperation(tempWhile, LAB, newLabelWhileCopy, NULL, NULL, NULL, 0);

		ILOC_LIST* tempGoto = createILOCList();		
		createOperation(tempGoto, JUMPI, "jumpI", newLabelWhile, NULL, NULL, 0);
		
		(yyval.ast)->opList = concatILOC(tempWhile, (yyvsp[-3].ast)->opList);
		(yyval.ast)->opList = concatILOC((yyval.ast)->opList, tempT);
		(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[0].ast)->opList);
		(yyval.ast)->opList = concatILOC((yyval.ast)->opList, tempGoto);
		(yyval.ast)->opList = concatILOC((yyval.ast)->opList, tempF);		

	}
#line 4191 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 952 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-5].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-4].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));

		int correctOperands =  coercion(BOOL, (yyvsp[-1].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	
		char *newLabelT = getNewLabel();
		patch((yyvsp[-1].ast)->opList, newLabelT, (yyvsp[-1].ast)->trueList);		
		int lenT = strlen(newLabelT);
		char *newLabelTCopy = aloca((lenT+2)*sizeof(char));
		strcpy(newLabelTCopy, newLabelT);
		newLabelTCopy[lenT] = ':';
		newLabelTCopy[lenT+1] = '\0';
		ILOC_LIST* tempT = createILOCList();
		createOperation(tempT, LAB, newLabelTCopy, NULL, NULL, NULL, 0);

		char *newLabelF = getNewLabel();
		patch((yyvsp[-1].ast)->opList, newLabelF, (yyvsp[-1].ast)->falseList);		
		int lenF = strlen(newLabelF);
		char *newLabelFCopy = aloca((lenF+2)*sizeof(char));
		strcpy(newLabelFCopy, newLabelF);
		newLabelFCopy[lenF] = ':';
		newLabelFCopy[lenF+1] = '\0';
		ILOC_LIST* tempF = createILOCList();
		createOperation(tempF, LAB, newLabelFCopy, NULL, NULL, NULL, 0);

		(yyval.ast)->opList = concatILOC(tempT, (yyvsp[-4].ast)->opList);
		(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[-1].ast)->opList);
		(yyval.ast)->opList = concatILOC((yyval.ast)->opList, tempF);		
	}
#line 4231 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 991 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);

		int correctOperands =  coercion(NONE, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4242 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 997 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));

		int correctOperands =  coercion(NONE, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4255 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1007 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);}
#line 4261 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1008 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 4271 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1016 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-4].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-3].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int correctOperands =  coercion(INT, (yyvsp[-2].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4286 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1028 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
	}
#line 4296 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1038 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = verifyUse((yyvsp[-1].valor_lexico)->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)->kids[0]), 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
		updateLocalVarSize(identifierSize((yyvsp[0].valor_lexico)->value.str));
	}
#line 4311 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1048 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = verifyUse((yyvsp[-1].valor_lexico)->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)->kids[0]), 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
		updateLocalVarSize(identifierSize((yyvsp[0].valor_lexico)->value.str));	
	}
#line 4326 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1058 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = verifyUse((yyvsp[-1].valor_lexico)->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)->kids[1]), 0, FALSE, STATIC + CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
		updateLocalVarSize(identifierSize((yyvsp[0].valor_lexico)->value.str));	
		
	}
#line 4343 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1070 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isUsr = verifyUse((yyvsp[-1].valor_lexico)->value.str, UTN);
		if (isUsr!=TRUE){ returnError = isUsr; nodeNotAdded = (yyval.ast); YYABORT;}
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, USER, getUserType((yyval.ast)), 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
		updateLocalVarSize(identifierSize((yyvsp[0].valor_lexico)->value.str));		
		
	}
#line 4358 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1080 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
		updateLocalVarSize(identifierSize((yyvsp[0].valor_lexico)->value.str));	
	}
#line 4371 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1088 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
		updateLocalVarSize(identifierSize((yyvsp[0].valor_lexico)->value.str));	
		
	}
#line 4385 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1097 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, CONST + STATIC);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
		updateLocalVarSize(identifierSize((yyvsp[0].valor_lexico)->value.str));	
	}
#line 4399 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1106 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-1].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int addSymb = addSymbol((yyvsp[0].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-1].ast)), NULL, 0, FALSE, 0);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
		updateLocalVarSize(identifierSize((yyvsp[0].valor_lexico)->value.str));
	}
#line 4411 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1114 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));
		
	}
#line 4435 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1133 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));
		
	}
#line 4458 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1151 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));
	}
#line 4483 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1171 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));
	}
#line 4504 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1187 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));

	}
#line 4529 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1207 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));
	}
#line 4550 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1223 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));
	}
#line 4574 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1242 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));
	}
#line 4593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1257 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));
	}
#line 4615 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1274 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));
	}
#line 4633 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1287 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));
	}
#line 4654 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1303 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));
	}
#line 4671 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1315 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));	
	}
#line 4695 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1334 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));
	}
#line 4712 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1346 "parser/parser.y" /* yacc.c:1646  */
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
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));	
	}
#line 4733 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1362 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-3].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int addSymb = addSymbol((yyvsp[-2].valor_lexico), NATUREZA_IDENTIFICADOR, getType((yyvsp[-3].ast)), NULL, 0, FALSE, CONST);
		if(addSymb != 0){ returnError = addSymb; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctOperands =  coercion(getType((yyvsp[-3].ast)), (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT; }
		updateLocalVarSize(identifierSize((yyvsp[-2].valor_lexico)->value.str));
	}
#line 4749 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1375 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->type = (yyvsp[0].ast)->type;
	}
#line 4759 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1380 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));		
		(yyval.ast)->kids[0]->type = identifierType((yyvsp[0].valor_lexico)->value.str);
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4771 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1387 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->type = (yyvsp[0].ast)->type;
	}
#line 4781 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1392 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = identifierType((yyvsp[0].valor_lexico)->value.str);
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4793 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1402 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->type = (yyvsp[0].ast)->type;
	}
#line 4803 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1407 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = INT;
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4815 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1414 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = FLOAT;
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1421 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->type = (yyvsp[0].ast)->type;
	}
#line 4837 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1426 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = INT;
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4849 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1433 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		(yyval.ast)->kids[0]->type = FLOAT;
		int coercion = unaryArithCoercion((yyval.ast), (yyval.ast)->kids[0]);
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 4861 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1444 "parser/parser.y" /* yacc.c:1646  */
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
		//printListOfOperations($3->opList);
		//Geração de código 
		if((yyvsp[0].ast)->reg!=NULL){
			//Código de atribuição é o seguinte:
			// 1) Calcular expressão
			// 2) Cálcula endereço de variável 
			// 3) Armazena conteúdo do registrador da expressão nesse endereço
			(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[0].ast)->opList);
			char* address = calculateAddressOfVar((yyval.ast)->opList, (yyvsp[-2].valor_lexico)->value.str);
			createOperation((yyval.ast)->opList, STORE, "store", (yyvsp[0].ast)->reg, address, NULL, 0);
		}
		
	}
#line 4893 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1471 "parser/parser.y" /* yacc.c:1646  */
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
#line 4918 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1491 "parser/parser.y" /* yacc.c:1646  */
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
#line 4940 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1508 "parser/parser.y" /* yacc.c:1646  */
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
#line 4970 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1535 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[0].ast)->token->tokenType!=IDS){ returnError = ERR_WRONG_PAR_INPUT; nodeNotAdded = (yyval.ast); YYABORT;}	
		isInput = FALSE;
	}
#line 4980 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1544 "parser/parser.y" /* yacc.c:1646  */
    {isInput = TRUE;}
#line 4986 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1552 "parser/parser.y" /* yacc.c:1646  */
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
#line 5006 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1567 "parser/parser.y" /* yacc.c:1646  */
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
#line 5025 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1583 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[0].ast)->type != INT && (yyvsp[0].ast)->type != FLOAT && (yyvsp[0].ast)->token->literType!=STRING)
			{ returnError = ERR_WRONG_PAR_OUTPUT; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 5036 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1589 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		if((yyvsp[-1].ast)->type != INT && (yyvsp[-1].ast)->type != FLOAT && (yyvsp[-1].ast)->token->literType!=STRING)
			{ returnError = ERR_WRONG_PAR_OUTPUT; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 5048 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1598 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-3].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-2].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isFunc = verifyUse((yyvsp[-3].valor_lexico)->value.str, FUN);
		if (isFunc != TRUE){ returnError = isFunc; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctArgs = verifyArguments((yyvsp[-3].valor_lexico)->value.str, (yyvsp[-1].ast));
		if (correctArgs != TRUE){ returnError = correctArgs; nodeNotAdded = (yyval.ast); YYABORT;}
		// Na chamada da função deve antes se avaliar a expressão dos argumentos
		(yyval.ast)->opList = (yyvsp[-1].ast)->opList;
		//Gerar prólogo
		//1) Cálcular endereço de retorno com base no rpc
		// O endereço de retorno vai ser igual ao pc atual somado com a quantidade 
        // de instruções no prólogo que depende da quantidade de argumentos em argsCall
		// O endereço de retorno é dado por: rpc + 8 +nOfArgs
		// Uma vez que existem 8 instruções que sempre ocorrerão no prólogo e mais uma
		// para empilhar cada argumento
		Hash* funcContent = getSymbol((yyvsp[-3].valor_lexico)->value.str);		
		int funcArgs = funcContent->argsNum;
		int prologueSize = 7 + funcArgs;
		char* tempReg = getNewRegister();		
		createOperation((yyval.ast)->opList, ADDI, "addI", "rpc", (void*) &prologueSize, tempReg, ARG2_IMED);
		int zero = 0;
		createOperation((yyval.ast)->opList, STOREAI, "storeAI", tempReg, "rsp", (void*) &zero, ARG3_IMED);
		//2) Salvar vínculo dinâmico: rsp e rfp atual
		int quatro = 4;
		createOperation((yyval.ast)->opList, STOREAI, "storeAI", "rsp", "rsp", (void*) &quatro, ARG3_IMED);
		int oito = 8;
		createOperation((yyval.ast)->opList, STOREAI, "storeAI", "rfp", "rsp", (void*) &oito, ARG3_IMED);
		//3) Salvar vínculo estático: rfp e rsp de uma instância do pai estático, como existirão somente dois escopos pode armazenar zero
		createOperation((yyval.ast)->opList, LOADI, "loadI", (void*) &zero, tempReg, NULL, ARG1_IMED);
		int doze = 12;
		createOperation((yyval.ast)->opList, STOREAI, "storeAI", tempReg, "rsp", (void*) &doze, ARG3_IMED);
		//4) Empilha argumentos
		/* estrutura de argsCall:
		* Cabeça = NULL -> facilita verificação de excesso ou falta de argumentos
		* kids[0], kids[2], kids[4], ..., kids[(argsNum - 1) * 2] -> argCall ->
			contém expressão que representa o argumento
		* kids[1], kids[3], kids[5], ..., kids[(argsNum-1)*2 - 1] -> vírgula
	*/	
		for(int i = 0; i<funcArgs; i++){
			int currentPos = i*4+16;			
			createOperation((yyval.ast)->opList, STOREAI, "storeAI", (yyvsp[-1].ast)->kids[i*2]->reg, "rsp", (void*) &currentPos, ARG3_IMED);
		}
		//5) Atualiza rfp, atualiza rsp e desvia para a função
		createOperation((yyval.ast)->opList, JUMPI, "jumpI", funcContent->label, NULL, NULL, 0);
		//printf("TEST: localVarBegin = %d\n", localVarBegin($1->value.str));

	}
#line 5103 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1648 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));
		int isFunc = verifyUse((yyvsp[-2].valor_lexico)->value.str, FUN);
		if (isFunc != TRUE){ returnError = isFunc; nodeNotAdded = (yyval.ast); YYABORT;}
		int correctArgs = verifyArguments((yyvsp[-2].valor_lexico)->value.str, NULL);
		if (correctArgs != TRUE){ returnError = correctArgs; nodeNotAdded = (yyval.ast); YYABORT;}
		
		int prologueSize = 7;
		char* tempReg = getNewRegister();		
		createOperation((yyval.ast)->opList, ADDI, "addI", "rpc", (void*) &prologueSize, tempReg, ARG2_IMED);
		int zero = 0;
		createOperation((yyval.ast)->opList, STOREAI, "storeAI", tempReg, "rsp", (void*) &zero, ARG3_IMED);
		int quatro = 4;
		createOperation((yyval.ast)->opList, STOREAI, "storeAI", "rsp", "rsp", (void*) &quatro, ARG3_IMED);
		int oito = 8;
		createOperation((yyval.ast)->opList, STOREAI, "storeAI", "rfp", "rsp", (void*) &oito, ARG3_IMED);
		createOperation((yyval.ast)->opList, LOADI, "loadI", (void*) &zero, tempReg, NULL, ARG1_IMED);
		int doze = 12;
		createOperation((yyval.ast)->opList, STOREAI, "storeAI", tempReg, "rsp", (void*) &doze, ARG3_IMED);
		Hash* funcContent = getSymbol((yyvsp[-2].valor_lexico)->value.str);
		createOperation((yyval.ast)->opList, JUMPI, "jumpI", funcContent->label, NULL, NULL, 0);
	}
#line 5132 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1674 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);	//tem cabeça NULL para facilitar verificação dos argumentos
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->opList = (yyvsp[0].ast)->opList;
	}
#line 5142 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1679 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		(yyval.ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyvsp[0].ast)->opList);
	}
#line 5153 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1687 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast);
		int correctOperands =  coercion(NONE, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
		
	}
#line 5163 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1692 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5169 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1695 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5175 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1696 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));}
#line 5181 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1698 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-2].valor_lexico)); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int isVar = verifyUse((yyvsp[-2].valor_lexico)->value.str, VAR);
		if (isVar != TRUE){ returnError = isVar; nodeNotAdded = (yyval.ast); YYABORT;}

		int correctOperands =  coercion(INT, (yyvsp[0].ast));
		if (correctOperands != 0){ returnError = correctOperands; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 5196 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1708 "parser/parser.y" /* yacc.c:1646  */
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
#line 5215 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1722 "parser/parser.y" /* yacc.c:1646  */
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
#line 5236 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1738 "parser/parser.y" /* yacc.c:1646  */
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
#line 5263 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1764 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int verifRet = verifyReturn((yyvsp[0].ast));
		if (verifRet != TRUE){ returnError = verifRet; nodeNotAdded = (yyval.ast); YYABORT;}
		isReturn = FALSE;
	}
#line 5274 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1774 "parser/parser.y" /* yacc.c:1646  */
    {isReturn = TRUE;}
#line 5280 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1778 "parser/parser.y" /* yacc.c:1646  */
    {/*printf("unario\n");*/ (yyval.ast) = (yyvsp[-1].ast); adicionaFilho((yyval.ast), criaNodo((yyvsp[0].valor_lexico)));}
#line 5286 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1779 "parser/parser.y" /* yacc.c:1646  */
    {/*printf("unario\n");*/ (yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast)); (yyval.ast)->type = (yyvsp[0].ast)->type;}
#line 5292 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1780 "parser/parser.y" /* yacc.c:1646  */
    {/*printf("unario\n");*/ (yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast)); (yyval.ast)->type = (yyvsp[0].ast)->type;}
#line 5298 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1781 "parser/parser.y" /* yacc.c:1646  */
    {/*printf("unario\n");*/ (yyval.ast) = criaNodo((yyvsp[-1].valor_lexico)); adicionaFilho((yyval.ast), (yyvsp[0].ast)); (yyval.ast)->type = (yyvsp[0].ast)->type;}
#line 5304 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1782 "parser/parser.y" /* yacc.c:1646  */
    {
		//printf("unario\n");
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int coercion = unaryArithCoercion((yyval.ast), (yyvsp[0].ast));
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
		//gera código inverte o sinal fazendo subtraindo de zero o valor do registrador
		if((yyvsp[0].ast)->reg!=NULL){
			(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[0].ast)->opList);
			(yyval.ast)->reg = getNewRegister();
			//rsubI   r1, c2  =>  r3    // r3 = c2 - r1
			int zero = 0;
			createOperation((yyval.ast)->opList, RSUBI, "rsubI", (yyvsp[0].ast)->reg, (void*) &zero, (yyval.ast)->reg, ARG2_IMED);
			//printf("Lista de operações na divisão:\n");
			//printILOCList($$->opList); 
		}
	}
#line 5326 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1799 "parser/parser.y" /* yacc.c:1646  */
    {
		//printf("unario\n");
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int coercion = unaryArithCoercion((yyval.ast), (yyvsp[0].ast));
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
		
		if((yyvsp[0].ast)->reg!=NULL){
			(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[0].ast)->opList);
			(yyval.ast)->reg = (yyvsp[0].ast)->reg; // apenas copia o registrador já que essa operação não muda o valor			
			//printf("Lista de operações na divisão:\n");
			//printILOCList($$->opList); 
		}
	}
#line 5345 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1813 "parser/parser.y" /* yacc.c:1646  */
    {
		//printf("unario\n");
		(yyval.ast) = criaNodo((yyvsp[-1].valor_lexico));
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		int coercion = unaryLogicCoercion((yyval.ast), (yyvsp[0].ast));
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
	}
#line 5357 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1820 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}					
	}
#line 5371 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1829 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
		
		if((yyvsp[-2].ast)->reg!=NULL && (yyvsp[0].ast)->reg!=NULL){
			(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[-2].ast)->opList);
			(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[0].ast)->opList);
			(yyval.ast)->reg = getNewRegister();
			createOperation((yyval.ast)->opList, DIV, "div", (yyvsp[-2].ast)->reg, (yyvsp[0].ast)->reg, (yyval.ast)->reg, 0);
			//printf("Lista de operações na divisão:\n");
			//printILOCList($$->opList); 
		}		
	}
#line 5394 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1847 "parser/parser.y" /* yacc.c:1646  */
    {
		//printf("mult\n");
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}	
		
		if((yyvsp[-2].ast)->reg!=NULL && (yyvsp[0].ast)->reg!=NULL){
			(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[-2].ast)->opList);
			(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[0].ast)->opList);
			(yyval.ast)->reg = getNewRegister();
			createOperation((yyval.ast)->opList, MULT, "mult", (yyvsp[-2].ast)->reg, (yyvsp[0].ast)->reg, (yyval.ast)->reg, 0); 
			//printf("Lista de operações na multiplicação:\n");
			//printILOCList($$->opList);
		}					
	}
#line 5418 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1866 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}				
	}
#line 5432 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1875 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}		
		
		char *newLabel = getNewLabel();
		patch((yyvsp[-2].ast)->opList, newLabel, (yyvsp[-2].ast)->trueList);
		(yyval.ast)->trueList = (yyvsp[0].ast)->trueList;
		concatenateLabelsList((yyval.ast)->falseList, (yyvsp[-2].ast)->falseList);
		concatenateLabelsList((yyval.ast)->falseList, (yyvsp[0].ast)->falseList);
		
		int len = strlen(newLabel);
		char *newLabelCopy = aloca((len+2)*sizeof(char));
		strcpy(newLabelCopy, newLabel);
		newLabelCopy[len] = ':';
		newLabelCopy[len+1] = '\0';
		createOperation((yyval.ast)->opList, LAB, newLabelCopy, NULL, NULL, NULL, 0);
		(yyval.ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyval.ast)->opList);
		(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[0].ast)->opList);				
	}
#line 5461 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1899 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
		
		char *newLabel = getNewLabel();
		patch((yyvsp[-2].ast)->opList, newLabel, (yyvsp[-2].ast)->falseList);
		(yyval.ast)->falseList = (yyvsp[0].ast)->falseList;
		concatenateLabelsList((yyval.ast)->trueList, (yyvsp[-2].ast)->trueList);
		concatenateLabelsList((yyval.ast)->trueList, (yyvsp[0].ast)->trueList);
		
		int len = strlen(newLabel);
		char *newLabelCopy = aloca((len+2)*sizeof(char));
		strcpy(newLabelCopy, newLabel);
		newLabelCopy[len] = ':';
		newLabelCopy[len+1] = '\0';
		createOperation((yyval.ast)->opList, LAB, newLabelCopy, NULL, NULL, NULL, 0);
		(yyval.ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyval.ast)->opList);
		(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[0].ast)->opList);
	}
#line 5490 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1923 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}				
	}
#line 5504 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1932 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}		
	}
#line 5518 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1941 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}		
		
		(yyval.ast)->reg = getNewRegister();
		char *trueLabel = getNewLabel();
		char *falseLabel = getNewLabel();
		addNewLabel((yyval.ast)->trueList, trueLabel);
		addNewLabel((yyval.ast)->falseList, falseLabel);
		createOperation((yyval.ast)->opList, CMP_EQ, "cmp_EQ", (yyvsp[-2].ast)->reg, (yyvsp[0].ast)->reg , (yyval.ast)->reg, 0);
		createOperation((yyval.ast)->opList, CBR, "cbr", (yyval.ast)->reg, trueLabel , falseLabel, 0);
		(yyvsp[-2].ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyvsp[0].ast)->opList);
		(yyval.ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyval.ast)->opList);
	}
#line 5542 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1960 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}			
		
		(yyval.ast)->reg = getNewRegister();
		char *trueLabel = getNewLabel();
		char *falseLabel = getNewLabel();
		addNewLabel((yyval.ast)->trueList, trueLabel);
		addNewLabel((yyval.ast)->falseList, falseLabel);
		createOperation((yyval.ast)->opList, CMP_EQ, "cmp_NE", (yyvsp[-2].ast)->reg, (yyvsp[0].ast)->reg , (yyval.ast)->reg, 0);
		createOperation((yyval.ast)->opList, CBR, "cbr", (yyval.ast)->reg, trueLabel , falseLabel, 0);
		(yyvsp[-2].ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyvsp[0].ast)->opList);
		(yyval.ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyval.ast)->opList);			
	}
#line 5566 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1979 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}		
		
		(yyval.ast)->reg = getNewRegister();
		char *trueLabel = getNewLabel();
		char *falseLabel = getNewLabel();
		addNewLabel((yyval.ast)->trueList, trueLabel);
		addNewLabel((yyval.ast)->falseList, falseLabel);
		createOperation((yyval.ast)->opList, CMP_EQ, "cmp_GE", (yyvsp[-2].ast)->reg, (yyvsp[0].ast)->reg , (yyval.ast)->reg, 0);
		createOperation((yyval.ast)->opList, CBR, "cbr", (yyval.ast)->reg, trueLabel , falseLabel, 0);
		(yyvsp[-2].ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyvsp[0].ast)->opList);
		(yyval.ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyval.ast)->opList);		
	}
#line 5590 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1998 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}		
		
		(yyval.ast)->reg = getNewRegister();
		char *trueLabel = getNewLabel();
		char *falseLabel = getNewLabel();
		addNewLabel((yyval.ast)->trueList, trueLabel);
		addNewLabel((yyval.ast)->falseList, falseLabel);
		createOperation((yyval.ast)->opList, CMP_EQ, "cmp_LE", (yyvsp[-2].ast)->reg, (yyvsp[0].ast)->reg , (yyval.ast)->reg, 0);
		createOperation((yyval.ast)->opList, CBR, "cbr", (yyval.ast)->reg, trueLabel , falseLabel, 0);
		(yyvsp[-2].ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyvsp[0].ast)->opList);
		(yyval.ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyval.ast)->opList);		
	}
#line 5614 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 2017 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}		
		
		(yyval.ast)->reg = getNewRegister();
		char *trueLabel = getNewLabel();
		char *falseLabel = getNewLabel();
		addNewLabel((yyval.ast)->trueList, trueLabel);
		addNewLabel((yyval.ast)->falseList, falseLabel);
		createOperation((yyval.ast)->opList, CMP_EQ, "cmp_LT", (yyvsp[-2].ast)->reg, (yyvsp[0].ast)->reg , (yyval.ast)->reg, 0);
		createOperation((yyval.ast)->opList, CBR, "cbr", (yyval.ast)->reg, trueLabel , falseLabel, 0);
		(yyvsp[-2].ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyvsp[0].ast)->opList);
		(yyval.ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyval.ast)->opList);			
	}
#line 5638 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 2036 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}		
		
		(yyval.ast)->reg = getNewRegister();
		char *trueLabel = getNewLabel();
		char *falseLabel = getNewLabel();
		addNewLabel((yyval.ast)->trueList, trueLabel);
		addNewLabel((yyval.ast)->falseList, falseLabel);
		createOperation((yyval.ast)->opList, CMP_EQ, "cmp_GT", (yyvsp[-2].ast)->reg, (yyvsp[0].ast)->reg , (yyval.ast)->reg, 0);
		createOperation((yyval.ast)->opList, CBR, "cbr", (yyval.ast)->reg, trueLabel , falseLabel, 0);
		(yyvsp[-2].ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyvsp[0].ast)->opList);
		(yyval.ast)->opList = concatILOC((yyvsp[-2].ast)->opList, (yyval.ast)->opList);		
	}
#line 5662 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 2057 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
		//Se registrador de alguma das expressões for nulo significa que não foi
		//gerado código pra ela portanto não se pode realizar a soma
		if((yyvsp[-2].ast)->reg!=NULL && (yyvsp[0].ast)->reg!=NULL){
			//Para realizar uma operação precisamos:
			// 1) Realizar o processamento das subexpressões
			// 2) Criar registrador para conter resultado
			// 3) Realizar operação específica
			(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[-2].ast)->opList);
			(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[0].ast)->opList);
			(yyval.ast)->reg = getNewRegister();
			createOperation((yyval.ast)->opList, ADD, "add", (yyvsp[-2].ast)->reg, (yyvsp[0].ast)->reg, (yyval.ast)->reg, 0); 
			//printf("Lista de operações na adição:\n");
			//printILOCList($$->opList);
		}	
	}
#line 5690 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 2080 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo(NULL);
		adicionaFilho((yyval.ast), (yyvsp[-2].ast)); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
		
		int coercion = expressionCoercion((yyval.ast), (yyvsp[-2].ast), (yyvsp[-1].valor_lexico), (yyvsp[0].ast));		
		if(coercion!=0){ returnError = coercion; nodeNotAdded = (yyval.ast); YYABORT;}
		
		if((yyvsp[-2].ast)->reg!=NULL && (yyvsp[0].ast)->reg!=NULL){
			(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[-2].ast)->opList);
			(yyval.ast)->opList = concatILOC((yyval.ast)->opList, (yyvsp[0].ast)->opList);
			(yyval.ast)->reg = getNewRegister();
			createOperation((yyval.ast)->opList, SUB, "sub", (yyvsp[-2].ast)->reg, (yyvsp[0].ast)->reg, (yyval.ast)->reg, 0);
			//printf("Lista de operações na subtração:\n");
			//printILOCList($$->opList);
		}								
	}
#line 5713 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 2098 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); (yyval.ast)->type = (yyvsp[0].ast)->type;}
#line 5719 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 2099 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodoTipado((yyvsp[-2].valor_lexico), (yyvsp[-1].ast)->type); 
		adicionaFilho((yyval.ast), (yyvsp[-1].ast)); 
		adicionaFilho((yyval.ast), criaNodoTipado((yyvsp[0].valor_lexico), (yyvsp[-1].ast)->type));}
#line 5728 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 2106 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); inpPipe = (yyvsp[0].ast);}
#line 5734 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 2109 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 5744 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 2114 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 5754 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 2119 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 5764 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 2124 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[-2].ast); 
		adicionaFilho((yyval.ast), criaNodo((yyvsp[-1].valor_lexico))); 
		adicionaFilho((yyval.ast), (yyvsp[0].ast));
	}
#line 5774 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 2132 "parser/parser.y" /* yacc.c:1646  */
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
#line 5792 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 2145 "parser/parser.y" /* yacc.c:1646  */
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
		//geração de código		
		if((yyval.ast)->type == INT){
			(yyval.ast)->reg = loadVarToRegister((yyval.ast)->opList, (yyvsp[0].valor_lexico)->value.str);
		}

	}
#line 5820 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 2168 "parser/parser.y" /* yacc.c:1646  */
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
#line 5836 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 2179 "parser/parser.y" /* yacc.c:1646  */
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
#line 5861 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 2199 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = criaNodo((yyvsp[0].valor_lexico));
		(yyval.ast)->type = INT;
		(yyval.ast)->reg = getNewRegister();
		createOperation((yyval.ast)->opList, LOADI, "loadI", (void*) &((yyvsp[0].valor_lexico)->value.i), (yyval.ast)->reg, NULL, ARG1_IMED);
	}
#line 5872 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 2205 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = FLOAT;}
#line 5878 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 2206 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = BOOL;}
#line 5884 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 2207 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = BOOL;}
#line 5890 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 2208 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = CHAR;}
#line 5896 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 2209 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = criaNodo((yyvsp[0].valor_lexico)); (yyval.ast)->type = STRING;}
#line 5902 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 2210 "parser/parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = (yyvsp[0].ast);	
		(yyval.ast)->type = identifierType((yyval.ast)->token->value.str);
		(yyval.ast)->reg = getNewRegister();		
		Hash* funcContent = getSymbol((yyvsp[0].ast)->token->value.str);		
		int funcArgs = funcContent->argsNum;		
		int currentPos;
		for(int i = 0; i<funcArgs; i++){	
			 currentPos = i*4+16;
		}		
		createOperation((yyval.ast)->opList, LOADAI, "loadAI", "rsp", (void*) &currentPos, (yyval.ast)->reg, ARG2_IMED);		
	}
#line 5919 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 2224 "parser/parser.y" /* yacc.c:1646  */
    {(yyval.ast) = (yyvsp[0].ast); (yyval.ast)->type = identifierType((yyval.ast)->kids[(yyval.ast)->kidsNumber-1]->token->value.str);}
#line 5925 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 5929 "parser.tab.c" /* yacc.c:1646  */
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
#line 2228 "parser/parser.y" /* yacc.c:1906  */



