/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "ccompiler.y" /* yacc.c:339  */


#include "heading.h"
#include <string.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stack>


#define DeclList 9527
#define DeclListP 9528
#define Decl 9529
#define VarDecl 9530
#define VarDeclP 9531
#define FunDecl 9532
#define VarDeclList 9533

/* 
 * Mips register simulator
 */
struct Register {
	int v[2];
	int a[4];
	int t[10];
	int s[8];
	int k[2];
};

struct Register mips_reg;

void initRegs(); //initialize the mips_reg above
void releaseReg(string reg); //remove registers from avaliable lists
string getReg(char c); //get register from avaliable lists

/* Symbol table */
typedef struct var_information{
	int type; /* 1 for int, 2 FOR char */
	int size;
	int isArray; 
	int isFunction;
	string id;
}clearsym;

typedef struct decl_node_information{
	int type; /* 1 for int, 2 FOR char */
	int size;
	int isArray; 
	int isFunction;
}symbol;

/* Symbol table container*/
vector<clearsym> fun_table;
vector<clearsym> var_table;
vector<clearsym> func_param_table;

/* Look-up */
int look_up_var(string str); /* Find a var sym by str, and return its index */
int look_up_fuc(string str); /* Find a fuc sym by stt, and return its index */


/*
 * AST Node Structure
 */
typedef struct ast{

	struct ast* l;
	struct ast* r;
	struct ast* stmt;//use for loop or while
	int node_type;
	int val;
	symbol* sym; //use for recognize a var/func
	string *array_index;//it might be a var or a pure num Kappa.
	string *id;
	string *debug;
}ast;

typedef struct ast_val{
	string id;
	string index;
}ast_val;

ast* new_ast(int type, ast* l, ast* r, int val, string id);
ast* new_ast(int type, ast* l, ast* r, string id, string debug);
ast* new_ast(int type, ast* l, ast* r, int val);
ast* new_ast(int type, ast* l, ast* r, string debug);
ast* new_stmt_ast(int type, ast* l, ast* r, ast* stmt, string debug);

void print_ast(ast* t);
ast_val evaluate_exp(ast* t);

/*  Save Load method */
void store(string name, string reg, string &append_to); // store Reg's val into ID.

//for load type, we return the reg we store for name/id
string loadInt(string i, string &append_to);  // load an int into registers, return the saving regs
string loadVar(string a, string &append_to); // load a int variable into registers
string loadVarByte(string a,string &append_to); //load a char variable into registers
string loadArrByte(string id, string index, string &append_to);
string loadArr(string id, string index, string &append_to);//load array[index]'s value
string loadArrAddr(string id,string index, string &append_to);//load array[index]'s address
string loadId(ast_val value,string& append_to); // a function combine with above.


/* FILE STREAM */
ofstream debug;
ofstream mips;

/* container for and Operand */
stack<string> operator_stack;
stack<string> operand_stack;

/* DATA & TEXT SECTION */
string data = ".data\n";
string function_text = ".text\n\tjal main\n";

/* Operator operation*/
string equal(string rv, string lv, string lindex, string rindex);
string op(int op, string lv, string rv, string lindex, string rindex);
ast_val ury(int op,ast_val value);

/* PRINT AND READ FUNCTION */
void print(string id);
void read(string id);

int parseId(string id);//check the id is 1:num 2:var 3:array 4:reg 5:function(TODO)

int yylex(void);
int yyerror(const char *s) ;

/* Use FOR RECORD :) */

string cur_scope = "";//use for scope_var.
string cur_loop = "";

int if_else_count = 0;
int while_loop_count = 0;

/* If-else stmt operation */
void if_else(ast *t);

/* while operation */
void while_stmt(ast *t);

/* Return operation */
void return_stmt(ast_val ret_val);

/* operation for declaration */
void decl_var(clearsym sym);
void decl_fuc();
void symbol_table_insertion(string id, symbol* sym);

/* Function operation */
void write_a_param(string id);
void push_function_argument(ast_val value);


#line 226 "ccompiler.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "ccompiler.tab.h".  */
#ifndef YY_YY_CCOMPILER_TAB_H_INCLUDED
# define YY_YY_CCOMPILER_TAB_H_INCLUDED
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
    INT = 258,
    CHAR = 259,
    RETURN = 260,
    IF = 261,
    WHILE = 262,
    ELSE = 263,
    BREAK = 264,
    PRINT = 265,
    READ = 266,
    EQ = 267,
    NEQ = 268,
    GT = 269,
    LT = 270,
    GET = 271,
    LET = 272,
    AND = 273,
    OR = 274,
    ID = 275,
    MYCHAR = 276,
    NUM = 277
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 161 "ccompiler.y" /* yacc.c:355  */


	struct ast* tree;
	string* str;
	int test;
	int type;	/* 1 FOR INT, 2 FOR CHAR */
	int isArray;/* 0 FOR NOT, 1 FOR TRUE */
	int val;
	int cond;/* 1: EQ 2:NEQ 3:GT 4:LT 5:GET 6:LET 7:AND 8:OR */

#line 300 "ccompiler.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CCOMPILER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 315 "ccompiler.tab.c" /* yacc.c:358  */

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   125

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  116

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   277

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,     2,     2,     2,     2,     2,
      32,    33,    26,    23,    34,    24,     2,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    29,
       2,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    30,     2,    31,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,    36,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   202,   202,   215,   220,   226,   255,   258,   265,   278,
     287,   301,   309,   313,   319,   322,   328,   334,   338,   344,
     360,   361,   365,   372,   375,   381,   387,   390,   394,   399,
     407,   412,   416,   421,   426,   431,   436,   444,   447,   452,
     455,   461,   464,   469,   472,   478,   481,   487,   492,   499,
     502,   508,   515,   518,   524,   525,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "CHAR", "RETURN", "IF", "WHILE",
  "ELSE", "BREAK", "PRINT", "READ", "EQ", "NEQ", "GT", "LT", "GET", "LET",
  "AND", "OR", "ID", "MYCHAR", "NUM", "'+'", "'-'", "'!'", "'*'", "'/'",
  "'='", "';'", "'['", "']'", "'('", "')'", "','", "'{'", "'}'", "$accept",
  "Program", "DeclList", "DeclListP", "Decl", "VarDecl", "VarDeclP",
  "FunDecl", "VarDeclList", "ParamDeclList", "ParamDeclListTail",
  "ParamDeclListTailP", "ParamDecl", "ParamDeclP", "Block", "Type",
  "StmtList", "StmtListP", "Stmt", "Expr", "ExprIdTail", "ExprArrayTail",
  "ExprP", "ExprList", "ExprListTail", "ExprListTailP", "UnaryOp", "BinOp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,    43,    45,    33,    42,    47,    61,    59,
      91,    93,    40,    41,    44,   123,   125
};
# endif

#define YYPACT_NINF -96

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-96)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      11,   -96,   -96,     3,   -96,    11,   -12,   -96,   -96,   -23,
     -96,    -1,    11,   -96,   -96,   -96,   -21,    -8,   -96,   -22,
       6,     1,     0,    11,   -96,     4,   -96,    11,   -96,   -96,
       8,   -96,    11,    22,    20,   -96,   -96,    28,    13,    17,
      14,    36,    39,    60,    98,   -96,   -96,   -96,    28,   -96,
      26,    22,    34,    28,    -6,    35,    28,    28,   -96,    37,
      38,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,    28,    28,    28,   -96,   -96,    28,   -96,
      47,   -96,   -96,   -96,   -96,   -96,   -96,   -96,    48,    49,
     -96,   -96,   -96,    54,    55,    58,   -96,   -96,    98,    22,
      22,    81,    28,   -96,    98,   -96,    61,   -96,    28,   -96,
     -96,   -96,   -96,    22,   -96,   -96
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    23,    24,     0,     2,     4,     0,     1,     3,     0,
       9,     0,    15,     5,     6,     7,     0,     0,    14,    18,
       0,     0,     0,     0,    16,    21,    10,    13,    11,    17,
       0,    19,    13,     0,     0,    20,    12,     0,     0,     0,
       0,     0,     0,    48,    48,    54,    55,    28,     0,    34,
       0,    27,     0,     0,     0,     0,     0,     0,    31,     0,
       0,    60,    61,    62,    63,    64,    65,    66,    67,    56,
      57,    58,    59,     0,     0,    50,    40,    41,     0,    38,
       0,    22,    26,    25,    29,    37,     8,    30,     0,     0,
      35,    36,    44,     0,    53,     0,    49,    47,    48,     0,
       0,    48,     0,    51,    48,    39,     0,    33,     0,    43,
      45,    52,    42,     0,    46,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -96,   -96,    63,   -96,   -96,   -96,    16,   -96,    69,   -96,
      79,   -96,   -96,   -96,    84,   -10,    52,   -96,   -95,   -37,
     -96,   -96,   -43,   -96,    18,   -96,   -96,   -96
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    13,    32,    14,    15,    33,    17,
      18,    24,    19,    31,    49,     6,    50,    83,    51,    52,
      76,   109,    77,    95,    96,   103,    53,    78
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      55,    79,    20,     7,   106,   107,    10,    11,     9,    12,
      21,    80,    23,    20,     1,     2,    85,    34,   115,    88,
      89,    16,    34,    10,    11,    22,    25,    37,    38,    39,
      26,    40,    41,    42,    30,    27,    92,    93,    94,    35,
      54,    97,    43,    58,    44,    56,    45,    46,    43,    57,
      44,    47,    45,    46,    48,   105,    59,    27,   110,    60,
      48,   112,    81,    84,    87,    94,    90,    91,     8,   113,
      86,   114,    61,    62,    63,    64,    65,    66,    67,    68,
      98,    99,   100,    69,    70,   101,    71,    72,    73,   102,
      74,   104,    75,    61,    62,    63,    64,    65,    66,    67,
      68,    36,    29,    82,    69,    70,    28,    71,    72,   108,
      61,    62,    63,    64,    65,    66,    67,    68,     0,     0,
     111,    69,    70,     0,    71,    72
};

static const yytype_int8 yycheck[] =
{
      37,    44,    12,     0,    99,   100,    29,    30,    20,    32,
      31,    48,    34,    23,     3,     4,    53,    27,   113,    56,
      57,    22,    32,    29,    30,    33,    20,     5,     6,     7,
      29,     9,    10,    11,    30,    35,    73,    74,    75,    31,
      20,    78,    20,    29,    22,    32,    24,    25,    20,    32,
      22,    29,    24,    25,    32,    98,    20,    35,   101,    20,
      32,   104,    36,    29,    29,   102,    29,    29,     5,     8,
      54,   108,    12,    13,    14,    15,    16,    17,    18,    19,
      33,    33,    33,    23,    24,    31,    26,    27,    28,    34,
      30,    33,    32,    12,    13,    14,    15,    16,    17,    18,
      19,    32,    23,    51,    23,    24,    22,    26,    27,    28,
      12,    13,    14,    15,    16,    17,    18,    19,    -1,    -1,
     102,    23,    24,    -1,    26,    27
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    38,    39,    40,    52,     0,    39,    20,
      29,    30,    32,    41,    43,    44,    22,    46,    47,    49,
      52,    31,    33,    34,    48,    20,    29,    35,    51,    47,
      30,    50,    42,    45,    52,    31,    45,     5,     6,     7,
       9,    10,    11,    20,    22,    24,    25,    29,    32,    51,
      53,    55,    56,    63,    20,    56,    32,    32,    29,    20,
      20,    12,    13,    14,    15,    16,    17,    18,    19,    23,
      24,    26,    27,    28,    30,    32,    57,    59,    64,    59,
      56,    36,    53,    54,    29,    56,    43,    29,    56,    56,
      29,    29,    56,    56,    56,    60,    61,    56,    33,    33,
      33,    31,    34,    62,    33,    59,    55,    55,    28,    58,
      59,    61,    59,     8,    56,    55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    41,    41,    42,    43,
      43,    44,    45,    45,    46,    46,    47,    48,    48,    49,
      50,    50,    51,    52,    52,    53,    54,    54,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    56,    56,    56,
      56,    57,    57,    57,    57,    58,    58,    59,    59,    60,
      60,    61,    62,    62,    63,    63,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     1,     1,     3,     1,
       4,     4,     2,     0,     1,     0,     2,     2,     0,     3,
       2,     0,     4,     1,     1,     2,     1,     0,     1,     2,
       3,     2,     7,     5,     1,     3,     3,     2,     2,     4,
       2,     1,     4,     4,     2,     1,     2,     2,     0,     1,
       0,     2,     2,     0,     1,     1,     1,     1,     1,     1,
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
  YYUSE (yytype);
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
#line 202 "ccompiler.y" /* yacc.c:1646  */
    {
		mips.open("mips.s");
		debug.open("debug.txt");
		initRegs();

		(yyval.tree) = new_ast(9526,(yyvsp[0].tree),NULL,"Program -> DeclList");
		evaluate_exp((yyval.tree));
		mips << data << function_text;
		//debugLog << "[Program]:Into Main Program. Find a Declaration" << endl;
	}
#line 1480 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 215 "ccompiler.y" /* yacc.c:1646  */
    {
	
		(yyval.tree) = new_ast(9527,(yyvsp[-1].tree),(yyvsp[0].tree),"DeclList -> DeclListP DeclList");

	}
#line 1490 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 220 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = new_ast('F',NULL,NULL,"DeclList -> Empty");
	}
#line 1498 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 226 "ccompiler.y" /* yacc.c:1646  */
    {

		//cout << "[TEST]98989898989898989898998" << endl;
		(yyval.tree) = new_ast(9528,(yyvsp[0].tree),NULL,*(yyvsp[-1].str),"DeclListP -> Type ID");
		//ok, we already have decl information from $3
		
		if((yyval.tree)->sym != NULL)
		{
			//there is a var_sym
			(yyval.tree)->sym = new symbol;
			(yyval.tree)->sym->isArray = (yyvsp[0].tree)->sym->isArray;
			(yyval.tree)->sym->isFunction = (yyvsp[0].tree)->sym->isFunction;
			(yyval.tree)->sym->type = (yyvsp[-2].type);
		}
		else
		{
			//there is a fun_sym
			(yyval.tree)->sym = new symbol;
			(yyval.tree)->sym->type = (yyvsp[-2].type);
			(yyval.tree)->sym->isFunction = 1;
			(yyval.tree)->sym->isArray = 0;
			(yyval.tree)->l->id = new string(*(yyvsp[-1].str));
			(yyval.tree)->l->sym = (yyval.tree)->sym;
		}
		//cout << "[TESTEEEEEEEE]98989898989898989898998" << endl;
	}
#line 1529 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 255 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 1537 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 258 "ccompiler.y" /* yacc.c:1646  */
    {
	
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 1546 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 265 "ccompiler.y" /* yacc.c:1646  */
    {

		//cout <<endl<<endl<< "87878787878787877888"  << endl << endl <<endl;
		(yyval.tree) = new_ast(9531,(yyvsp[0].tree),NULL,*(yyvsp[-1].str),"VarDecl-> Type ID varDeclP");
		(yyval.tree)->sym = new symbol;
		(yyval.tree)->sym->type = (yyvsp[-2].type);
		(yyval.tree)->sym->isArray = (yyvsp[0].tree)->sym->isArray;
		(yyval.tree)->sym->isFunction = 0 ;
		(yyval.tree)->sym->size = (yyvsp[0].tree)->sym->size;
	}
#line 1561 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 278 "ccompiler.y" /* yacc.c:1646  */
    {
		/* Get a varaible declaration */
		
		(yyval.tree) = new_ast('F',NULL,NULL,"VarDeclP -> ;");
		(yyval.tree)->sym = new symbol;
		(yyval.tree)->sym->isArray = 0;
		(yyval.tree)->sym->size = 0;
		
 	}
#line 1575 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 287 "ccompiler.y" /* yacc.c:1646  */
    {
		/* Get a array declaration */
		(yyval.tree) = new_ast('F',NULL,NULL,"VarDeclP -> [NUM]");
		(yyval.tree)->sym = new symbol;
		(yyval.tree)->sym->isArray = 1;
		(yyval.tree)->sym->size = (yyvsp[-2].val);

		if((yyval.tree)->sym->size < 0){
			cout << "[ERROR]: INVALID SIZE OF AN ARRAY: " << (yyvsp[-2].val) << endl;
		}
	}
#line 1591 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 301 "ccompiler.y" /* yacc.c:1646  */
    {
		//evaluate this function
		
		(yyval.tree) = new_ast(9529,(yyvsp[-2].tree),(yyvsp[0].tree),"FunDecl -> ( ParaDeclList ) Block");
	}
#line 1601 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 309 "ccompiler.y" /* yacc.c:1646  */
    {
	
		(yyval.tree) = new_ast(9530,(yyvsp[-1].tree),(yyvsp[0].tree),"VarDeclList -> VarDecl VarDeclList");
	 }
#line 1610 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 313 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = new_ast('F',NULL,NULL,"VarDeclList -> empty");
	}
#line 1618 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 319 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = new_ast(9533,(yyvsp[0].tree),NULL,"ParamDeclList -> ParamDeclListTail");
	}
#line 1626 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 322 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = new_ast('F',NULL,NULL,"ParamDeclList -> Empty"); 
	}
#line 1634 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 328 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = new_ast(9534,(yyvsp[-1].tree),(yyvsp[0].tree),"ParamDeclListTail -> ParamDecl ParamDeclListTailP");
	}
#line 1642 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 334 "ccompiler.y" /* yacc.c:1646  */
    {
		
		(yyval.tree) = (yyvsp[0].tree);//pass another paramDecl,if there has one.
	}
#line 1651 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 338 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = new_ast(9538,NULL,NULL,"ParamDeclListTail -> Empty");
	}
#line 1659 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 344 "ccompiler.y" /* yacc.c:1646  */
    {

		(yyval.tree) = new_ast(9535,NULL,NULL,*(yyvsp[-1].str),"ParamDecl -> Type ID ParamDeclP");
		
		clearsym sym;
		sym.id = *(yyvsp[-1].str);
		sym.type = (yyvsp[-2].type);
		sym.isArray = (yyvsp[0].isArray);
		sym.isFunction = 0;
		sym.size = 0;
		var_table.push_back(sym);
		decl_var(sym);
	}
#line 1677 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 360 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.isArray) = 1; /* array type. */}
#line 1683 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 361 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.isArray) = 0;   /* nope. */}
#line 1689 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 365 "ccompiler.y" /* yacc.c:1646  */
    {
	 	(yyval.tree) = new_ast(9532,(yyvsp[-2].tree),(yyvsp[-1].tree),"Block -> { VarDeclList StmtList }");

	 }
#line 1698 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 372 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.type) = 1;
	}
#line 1706 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 375 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.type) = 2;
	}
#line 1714 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 381 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = new_ast('T',(yyvsp[-1].tree),(yyvsp[0].tree),"StmtList->Stmt StmtListP");
	}
#line 1722 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 387 "ccompiler.y" /* yacc.c:1646  */
    { 
		(yyval.tree) = (yyvsp[0].tree) ;
	}
#line 1730 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 390 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.tree) = new_ast('F',NULL,NULL,"Empty","StmtListP-> Empty"); }
#line 1736 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 394 "ccompiler.y" /* yacc.c:1646  */
    { /* NO Work */
		//I want to say that but i can't...
		//it also need a empty node to do something
		(yyval.tree) = new_ast('F',NULL,NULL,"Empty","Stmt->;");
	}
#line 1746 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 399 "ccompiler.y" /* yacc.c:1646  */
    {
	
		(yyval.tree) = new_ast('X',(yyvsp[-1].tree),NULL,"Stmt-> Expr;");
		
		//cout << "[Stmt -> ;]: This exp can conclude to " << val.id << endl;
		//releaseReg(val.id);
		
	}
#line 1759 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 407 "ccompiler.y" /* yacc.c:1646  */
    {
	
		(yyval.tree) = new_ast('Q',(yyvsp[-1].tree),NULL,"Empty","Stmt-> RETURN Expr");
	
	}
#line 1769 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 412 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = new_ast('C',NULL,NULL,"Break","Stmt-> Break");
		
	}
#line 1778 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 416 "ccompiler.y" /* yacc.c:1646  */
    {
	
		(yyval.tree) = new_stmt_ast('G',(yyvsp[-4].tree), (yyvsp[-2].tree), (yyvsp[0].tree), "Stmt->IF ELSE");
	
	}
#line 1788 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 421 "ccompiler.y" /* yacc.c:1646  */
    {
	
		(yyval.tree) = new_ast('W',(yyvsp[-2].tree),(yyvsp[0].tree),"Stmt-> While stmt");
	
	}
#line 1798 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 426 "ccompiler.y" /* yacc.c:1646  */
    {
	
		(yyval.tree) = (yyvsp[0].tree);// Block pass~
	
	}
#line 1808 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 431 "ccompiler.y" /* yacc.c:1646  */
    {
	
		(yyval.tree) = new_ast('P',NULL,NULL,*(yyvsp[-1].str),"Stmt-> Print "+*(yyvsp[-1].str));
	
	}
#line 1818 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 436 "ccompiler.y" /* yacc.c:1646  */
    {

		(yyval.tree) = new_ast('R',NULL,NULL,*(yyvsp[-1].str),"Stmt-> Read "+*(yyvsp[-1].str));

	}
#line 1828 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 444 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = new_ast((yyvsp[-1].cond),(yyvsp[0].tree),NULL,"Expr -> Unary Expr");
	}
#line 1836 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 447 "ccompiler.y" /* yacc.c:1646  */
    {
		stringstream s;
		s << (yyvsp[-1].val);
		(yyval.tree) = new_ast('N',(yyvsp[0].tree),NULL,s.str(),"Expr -> NUM ExprP");
	}
#line 1846 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 452 "ccompiler.y" /* yacc.c:1646  */
    { 
		(yyval.tree) = new_ast('B',(yyvsp[-2].tree),(yyvsp[0].tree),"Expr -> ( EXpr ) ExprP");
	}
#line 1854 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 455 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = new_ast('I',(yyvsp[0].tree),NULL,*(yyvsp[-1].str),"Expr -> ID ExprIdTail");
	}
#line 1862 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 461 "ccompiler.y" /* yacc.c:1646  */
    { 
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 1870 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 464 "ccompiler.y" /* yacc.c:1646  */
    { 
	
		(yyval.tree) = new_ast(9536,(yyvsp[-2].tree),(yyvsp[0].tree),"ExprIdTail -> ( ExprList ) ExprP");
	
	}
#line 1880 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 469 "ccompiler.y" /* yacc.c:1646  */
    { 
		(yyval.tree) = new_ast('L',(yyvsp[-2].tree),(yyvsp[0].tree),"ExprIdTail -> [Expr] ExprArrayIdTail");
	}
#line 1888 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 472 "ccompiler.y" /* yacc.c:1646  */
    { 
		(yyval.tree) = new_ast('A',(yyvsp[0].tree),NULL,"ExprIdTail -> = Expr");
	}
#line 1896 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 478 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 1904 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 481 "ccompiler.y" /* yacc.c:1646  */
    { 
		(yyval.tree) = new_ast('A',(yyvsp[0].tree),NULL,"ExprIdTail -> = Expr");
	}
#line 1912 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 487 "ccompiler.y" /* yacc.c:1646  */
    {

		(yyval.tree) = new_ast((yyvsp[-1].cond),(yyvsp[0].tree),NULL,"ExprP -> BinOp Expr");
		cout << "[ExprP-BinOp] Meet an Operator " << (yyvsp[-1].cond) << endl;
	}
#line 1922 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 492 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = new_ast('E',NULL,NULL,"ExprP -> Empty");
		cout << "[Expr-empty] Get a expr end Kappa" << endl; 
	}
#line 1931 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 499 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 1939 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 502 "ccompiler.y" /* yacc.c:1646  */
    {
		
	}
#line 1947 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 508 "ccompiler.y" /* yacc.c:1646  */
    {
	
		(yyval.tree) = new_ast(9537,(yyvsp[-1].tree),(yyvsp[0].tree),"ExprListTail -> ExprListTailP");
	}
#line 1956 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 515 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 1964 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 518 "ccompiler.y" /* yacc.c:1646  */
    {
		(yyval.tree) = new_ast('F',NULL,NULL,"ExprListTailP -> Empty");
	}
#line 1972 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 524 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 14;}
#line 1978 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 525 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 15;}
#line 1984 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 529 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 10;}
#line 1990 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 530 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 11; }
#line 1996 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 531 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 12; }
#line 2002 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 532 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 13; }
#line 2008 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 533 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 1; }
#line 2014 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 534 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 2; }
#line 2020 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 535 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 3; }
#line 2026 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 536 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 4; }
#line 2032 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 537 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 5; }
#line 2038 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 538 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 6; }
#line 2044 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 539 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 7; }
#line 2050 "ccompiler.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 540 "ccompiler.y" /* yacc.c:1646  */
    { (yyval.cond) = 8; }
#line 2056 "ccompiler.tab.c" /* yacc.c:1646  */
    break;


#line 2060 "ccompiler.tab.c" /* yacc.c:1646  */
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
#line 542 "ccompiler.y" /* yacc.c:1906  */


/* Print and read operation */

void print(string id)
{
		//IT MUST BE PRINT A VARAIBLE , NOT A FUC
		int is_var = look_up_var(id);
		function_text.append("\n\t#Print"+id+"\n");
				
		if(is_var != -1)
		{
			string target_reg = "";
			
			if(var_table[is_var].type == 1)//int
				target_reg = loadVar(var_table[is_var].id, function_text); // load  var into target_reg
			else//char
				target_reg = loadVarByte(var_table[is_var].id, function_text);//load char into target_reg
			
			cout << "[LOAD] Load " << var_table[is_var].id << "'s value into" << target_reg << endl;
			function_text.append("\tmove $a0, "+target_reg+"\n"); // move the value from target_reg to $a0
			releaseReg(target_reg); // release the reg from loadVar.
			if(var_table[is_var].type == 1)
				function_text.append("\tli $v0, 1\n"); //int
			else
				function_text.append("\tli $v0, 11\n"); //print a char
			//TODO ERROR (OUT OF BOUND) OCCUR AS PRINT A STRING
			function_text.append("\tsyscall\n");
		}
		else
		{
			cout << "[Stmt-PRINT]: A wrong symbol detected " << id << endl;
		}
}

void read(string id)
{
		//IT MUST BE PRINT A VARAIBLE , NOT A FUC, but maybe an array header(For a string)
		int is_var = look_up_var(id);
		function_text.append("\n\t#Read"+id+"\n");
		
		if(is_var != -1)
		{
			if(var_table[is_var].type == 1)
			{
				//read a int into a VAR , and VAR.isArray must be 0.
				if(var_table[is_var].isArray)
					cout << "[WTF?] : You want to store an integer into a array header ?" << endl;

				function_text.append("\tli $v0, 5\n");//read an integer~
				function_text.append("\tsyscall\n");//~store into v0
				
				cout << "[READ] : Store $v0 into " << var_table[is_var].id << endl ;
				store(var_table[is_var].id, "$v0", function_text);
			}
			else
			{
				//read a char OR chars into a VAR.
				function_text.append("\tli $v0, 12\n");//read an char or string~
				
				int size = var_table[is_var].size;
				stringstream s ;
				s << size;
				
				string tp_reg = loadInt(s.str(),function_text);
				string tp_reg2 = getReg('t');
				
				function_text.append("\tla "+tp_reg2+", "+id+"\n");//save the address of ID to tp_reg2
				function_text.append("\tmove $a0, "+tp_reg2+"\n"); // move the buffer to a0
				function_text.append("\tmove $a1, "+tp_reg+"\n"); // move the lens to a1
				function_text.append("\tsyscall\n");//~store into v0

				cout << "[READ] : Store $v0 into " << var_table[is_var].id << endl ;
				store(var_table[is_var].id, "$v0", function_text);
			}
		}
		else
		{
			cout << "[Stmt-READ]: A wrong symbol detected " << id << endl;
		}
} 


/* Load And Store command */
/* store register value into variable name */
void store(string id, string reg, string &append_to)
{
	//store src dest
	append_to.append("\tsw "+reg+", "+id+"\n");
}

//load an int into registers, return the saving regs
string loadInt(string i,string &append_to) 
{
	string reg = getReg('t');
	append_to.append("\tli "+reg+", "+i+"\n");
	return reg;
}

//load a variable into registers, and return the saving regs
string loadVar(string a,string &append_to) 
{

	string reg = getReg('t');
	append_to.append("\tla "+reg+", "+a+"\n"); //load the id address.

	string reg1 = getReg('t');
	append_to.append("\tlw "+reg1+", 0("+reg+")\n"); //load word by address mode.

	releaseReg(reg);
	return reg1;
}

string loadVarByte(string a,string &append_to) 
{

	string reg = getReg('t');
	append_to.append("\tla "+reg+", "+a+"\n"); //load the id address.

	string reg1 = getReg('t');
	append_to.append("\tlb "+reg1+", 0("+reg+")\n"); //load word by address mode.

	releaseReg(reg);
	return reg1;
}

string loadArrByte(string id, string index, string &append_to)
{
	//TODO maybe no used.
	return "1";
}
string loadArr(string id, string index, string &append_to)
{
	
	function_text.append("\t#Load "+id+"[ "+index+" ]\n\n");
	
	string index_reg = "";
	int index_is_reg = 0;
	int id_type = parseId(index);
	
	switch(id_type)
	{
		case 1://num
			index_reg = loadInt(index,function_text); //Arr [ num ]: nice.
			break;
		case 2://var
			index_reg = loadVar(index,function_text); //Arr[ idX ]: Sure, is int var.
			break;
		case 3://array impossible case
			//index_reg = loadArr(index,function_text); //Arr[Arr[]]: recursive lol
			break;
		case 4://reg nice.
			index_reg = index;
			index_is_reg = 1;
			break;
		case 5://TODO function
			break;
	}
	
	/* Load the array header address */
	string header_reg = getReg('t');
	function_text.append("\n\t#Load Array"+id+"[ " + index_reg + " ]\n");
	function_text.append("\tla "+header_reg+", "+id+"\n");
	
	/* Move from Attay[0] to Array[index] */
	function_text.append("\tadd "+index_reg+", "+index_reg+", "+index_reg+"\n");//4 bytes is equal
	function_text.append("\tadd "+index_reg+", "+index_reg+", "+index_reg+"\n");//to 1 word
	function_text.append("\tadd "+header_reg+", "+index_reg+","+header_reg+"\n");
	
	//[WARNING]: NOT SURE.
	if(index_is_reg == 0)//if is 1,that reg might be use out of this function.
		releaseReg(index_reg);
	
	header_reg = "0("+header_reg+")";
	
	return header_reg;
}

string loadArrAddr(string id,string index, string &append_to)
{

	function_text.append("\t#Load Address of "+id+"[ "+index+" ]\n\n");
	
	string index_reg = "";
	//int index_is_reg = 0;
	int id_type = parseId(index);
	
	switch(id_type)
	{
		case 1://num
			index_reg = loadInt(index,function_text); //Arr [ num ]: nice.
			break;
		case 2://var
			index_reg = loadVar(index,function_text); //Arr[ idX ]: Sure, is int var.
			break;
		case 3://array impossible case
			//index_reg = loadArr(index,function_text); //Arr[Arr[]]: recursive lol
			break;
		case 4://reg nice.
			index_reg = index;
			//index_is_reg = 1;
			break;
		case 5://TODO function
			break;
	}
	
	/* Load the array header address */
	string header_reg = getReg('t');
	function_text.append("\n\t#Load Array"+id+"[ " + index_reg + " ]\n");
	function_text.append("\tla "+header_reg+", "+id+"\n");
	
	/* Move from Attay[0] to Array[index] */
	function_text.append("\tadd "+index_reg+", "+index_reg+", "+index_reg+"\n");//4 bytes is equal
	function_text.append("\tadd "+index_reg+", "+index_reg+", "+index_reg+"\n");//to 1 word
	function_text.append("\tadd "+header_reg+", "+index_reg+", "+header_reg+"\n");
	
	//[WARNING]: NOT SURE.
	//if(index_is_reg == 0)//if is 1,that reg might be use out of this function.
	releaseReg(index_reg);
	
	return header_reg;
}

string loadId(ast_val value,string& append_to)
{
	string res_tp_reg = "" ;
	string tp_reg = "";
	

	switch(parseId(value.id))
	{
		case 1: // num, load Num;
			res_tp_reg = loadInt(value.id,function_text) ;
			break;	
	
		case 2: // var, load its value
			res_tp_reg = loadVar(value.id,function_text) ;
			break;
	
		case 3: // array, load its value
			tp_reg = loadArr(value.id,value.index,function_text); // get something like 0($tx)
			res_tp_reg = getReg('t'); 
			function_text.append("\tlw "+res_tp_reg+", "+tp_reg+"\n");
			releaseReg(tp_reg);
			break;
		
		case 4: // reg, might from an operations' result
		 	res_tp_reg = value.id;
			break;
		
		case 5: //RECURSIVE function, but I think it might  occur for my ast processing.
	
			cout << "[WTF?]: A recurrsive , How can it be !" << endl;
			exit(1);
		
			break;
	}
	
	return res_tp_reg;

}


/* AST Operation */
ast* new_ast(int type, ast* l, ast* r,string debug)
{
	ast *t = new ast;
	
	if(t == NULL)
	{
		cout << "[WTF?] NO SPACE TO BUILD AN AST" << endl;
		exit(1);
	}

	t->node_type = type;
	t->l = l;
	t->r = r;
	t->id = NULL;
	t->debug = new string(debug);
	t->stmt = NULL;
	
	return t;
}

ast* new_ast(int type, ast* l, ast* r, int val)
{
	ast *t = new ast;
	
	if(t == NULL)
	{
		cout << "[WTF?] NO SPACE TO BUILD AN AST" << endl;
		exit(1);
	}

	t->node_type = type;
	t->l = l;
	t->r = r;
	t->val = val;
	t->id = NULL;
	t->stmt = NULL;

	return t;
}

ast* new_ast(int type, ast* l, ast* r, string id, string debug)
{
	ast *t = new ast;
	
	if(t == NULL)
	{
		cout << "[WTF?] NO SPACE TO BUILD AN AST" << endl;
		exit(1);
	}

	t->node_type = type;
	t->l = l;
	t->r = r;
	t->id = new string(id);
	t->debug = new string(debug);
	t->stmt = NULL;

	return t;
}

ast* new_ast(int type, ast* l, ast* r, int val, string id)
{
	ast *t = new ast;
	
	if(t == NULL)
	{
		cout << "[WTF?] NO SPACE TO BUILD AN AST" << endl;
		exit(1);
	}

	t->node_type = type;
	t->l = l;
	t->r = r;
	t->val = val;
	t->id = new string(id);
	t->stmt = NULL;
	
	return t;
}

ast* new_stmt_ast(int type, ast* l, ast* r, ast* stmt, string debug)
{
	ast *t = new ast;
	
	if(t == NULL)
	{
		cout << "[WTF?] NO SPACE TO BUILD AN AST" << endl;
		exit(1);
	}
	t->node_type = type;
	t->l = l;
	t->r = r;
	t->stmt = stmt;
	t->debug = new string(debug);
	t->id = NULL;
	
	//cout << "[AST_IF_ELSE] : " << (char)t->node_type << endl; 

	return t;
}

void print_ast(ast* t)
{
	if(t == NULL)
	{
		cout << "[AST]: An empty Tree Node" << endl;
		debug << "[AST]: An empty Tree Node" << endl;		
	}
	else
	{
		if(t->id != NULL )
		{
			cout << "[AST]: " << *(t->debug) << " with ID: " << *(t->id) << endl;
			debug << "[AST]: " << *(t->debug) << " with ID: " << *(t->id) << endl;			
		}
		else
		{
			cout << "[AST]: " << *(t->debug) << " And No ID" << endl;
			debug << "[AST]: " << *(t->debug) << " And No ID" << endl;			
		}

	}
	//cout << "****************  AST ****************" << endl;
}

ast_val evaluate_exp(ast* t)
{
	ast_val value;
	value.id = "";
	value.index = "";
	clearsym s;
	
	ast_val tpval;
	tpval.id = "";
	tpval.index = "";
		
	string arrLeftIndex = "0";
	string arrRightIndex = "0";
	string arrIndex = "0";
	
	int tid = 0;
	int tid2 = 0;
	
	if(t == NULL)
	{
		cout << "[WTF?]: A NULL AST" << endl;
		exit(1);
	}

	//string ls,rs,stmt;
	print_ast(t);

	switch(t->node_type)
	{
		/* inherit principle 
		 * 1.if production have a ExprP
		 *   than ExprP's id or val = parents' id or val.
		 * 2.IdTail founded.
		 */
		case 9526: /* Start */
			evaluate_exp(t->l);
			break;
		case 9527: /* DeclList -> DeclListP DeclList*/ 
			evaluate_exp(t->l);
			//insert this time decl to symbol table.
			evaluate_exp(t->r);
		
			break;
		
		case 9528: /* DeclListP -> Type ID Decl */


			evaluate_exp(t->l);//check if var or func

			if(t->l->sym != NULL && t->l->sym->isFunction != 1)
			{
				s.type = t->sym->type;
				s.isArray = t->sym->isArray;
				s.isFunction = 0;
				s.size = t->sym->size;
				s.id = *(t->id);
				symbol_table_insertion(s.id,t->sym);
				decl_var(s);
			}
			else
			{		
				//pass func's id and type to FunDecl(9529)
				decl_fuc();
				//there is a func
			}
		
		 	break;
		 	
		case 9529: /* FunDecl -> paprlist Block*/
		
			symbol_table_insertion(*(t->id),t->sym);//wtite the function title
		 	evaluate_exp(t->l);//write the arguments
		 	
		 	/* Important !! Must free $aX after write the param */
		 	releaseReg("$a0");
			releaseReg("$a1");
			releaseReg("$a2");
			releaseReg("$a3");
		 	
		 	evaluate_exp(t->r);//main bodyee
		 	
		 	break;

		case 9530: /* VarDeclList -> VarDecl VarDeclList */
			evaluate_exp(t->l);
			evaluate_exp(t->r);
			break;
		
		case 9531:/* VarDecl -> Type ID VarDeclP */
		
			s.id = *(t->id);
			s.type = t->sym->type;
			s.isArray = t->sym->isArray;
			s.isFunction = t->sym->isFunction;
			s.size = t->sym->size;
		
			decl_var(s);
			break;
		
		case 9532:/* Block -> { VarDeclList StmtList } */
			evaluate_exp(t->l);
			evaluate_exp(t->r);
			break;
			
		case 9533:/* ParamDeclList -> ParamDeclListTail */	
			
			evaluate_exp(t->l);
			
			break;
		
		case 9534:/* ParamDeclListTail -> ParamDecl ParamDeclListTailP*/
		
			evaluate_exp(t->l);//write one info (goto 9535)
			evaluate_exp(t->r);//check if have some param
			
			break;
			
		case 9535:/* ParamDecl -> Type ID ParamDeclP */
			write_a_param(*(t->id));
					
			break;	
			
		case 9536: /* ExprIdTail -> ( ExprList ) ExprP */
		
			//before call the function, we must push argument to $aX
			evaluate_exp(t->l);
			
			//now ,we call call function	
			function_text.append("\tjal "+*(t->id)+"\n");
			
			//then ,store the return value, REMEMBER TO FREE AFTER USE IT!
			value.id = getReg('t');
			function_text.append("\tmove "+value.id+", $v0\n");
			
			break;
		
		case 9537:/* ExprListTail -> Expr ExprListTailP*/
		
			value = evaluate_exp(t->l);//get the argument.
			
			function_text.append("\t#call with argument "+value.id+"\n");
			push_function_argument(value);
			evaluate_exp(t->r);//check if have some argument
			break;			
			
		case 9538:/* ExprListTailP -> empty */
		
			/* Well done, we deal with all argument */
			/* now just free all reg registers */
			
			releaseReg("$a0");
			releaseReg("$a1");
			releaseReg("$a2");
			releaseReg("$a3");	
			
			break;
		case 15: /* ! */
			//TODO is error
			value = evaluate_exp(t->l);			
			value = ury(15,value);
			break;
		case 14: /* - */
			//TODO is error
			value = evaluate_exp(t->l); 
			value = ury(14,value);
			break;
		case 13: /* / */
		case 12: /* * */ 
		case 11: /* - */
		case 10: /* + */
		case 8:  /* || */
		case 7:  /* && */
		case 6:  /* <= */
		case 5:  /* >= */
		case 4:  /* < */
		case 3:  /* > */
		case 2:  /* != */
		case 1:  /* == */

			/* consider as same case: exprival BinOp Expr */
			tpval = evaluate_exp(t->l);//ger Expr
			cout << "/**************** OP TIME ****************/" << endl;

			tid = look_up_var(*(t->id));
			tid2= look_up_var(tpval.id);
			
			
			if( tid != -1 && var_table[tid].isArray )
			{
				arrLeftIndex = *(t->array_index);
				cout << "lr with index " << arrLeftIndex;
			}
			if( tid2!= -1 && var_table[tid2].isArray)
			{
				arrRightIndex = tpval.index;
				cout << "rr with index " << arrRightIndex;
			}

			value.id = op(t->node_type, *(t->id) ,tpval.id, arrLeftIndex, arrRightIndex);

			cout << "[DO-OP #"<< t->node_type <<"]: lr is " << *(t->id) << " rv is " << tpval.id <<" store in "<< value.id << endl ;

	
			break;
		case 'A':/* ExprIdTail = Expr */
			
			tpval = evaluate_exp(t->l);
			cout << "[Do-ASSIGN] lr is " << *(t->id) << " rr is " << tpval.id;
			
			tid = look_up_var(*(t->id));
			tid2= look_up_var(tpval.id);
			
			if( tid != -1 && var_table[tid].isArray )
			{
				arrLeftIndex = *(t->array_index);
				cout << "lr with index " << arrLeftIndex;
			}
			if( tid2!= -1 && var_table[tid2].isArray)
			{
				arrRightIndex = tpval.index;
				cout << "rr with index " << arrRightIndex;
			}
			cout << endl;
			value.id = equal(*(t->id),tpval.id,arrLeftIndex,arrRightIndex);
			
			break;
		case 'B':/* {Exp} ExprP */
			
			tpval = evaluate_exp(t->l); // we do stmt in block first.
			
			t->r->id = new string(tpval.id); // then assgin the result as right tree's Kappa.
			t->r->array_index = new string(tpval.index);
			value = evaluate_exp(t->r);//eval left tree, i.e Expr
			//t->id = new string(reg);
			
			break;
		case 'N':/* NUM ExprP */
			t->l->id = t->id; // ival
			value = evaluate_exp(t->l);
			break;
		case 'I':/* ID ExprIdTail */
			t->l->id = t->id ; // ival again
 			value = evaluate_exp(t->l);
			break;
		case 'E':/* Empty node */
		
			value.id = *(t->id);/* bottom up pass my id Kappa*/
			
			tid = look_up_var(value.id);
			if(tid != -1 && var_table[tid].isArray == 1)
				value.index = *(t->array_index);/* bottom up pass my index */
				
			break;
		case 'L':/* '[' Expr ']' ExprArrayTail*/
		
			tpval = evaluate_exp(t->l); // eval the Expr to get the array index.
			t->r->array_index = new string(tpval.id) ; // ival the array_index.
			t->r->id = t->id ; // we also need to pass the array id Kappa
			value = evaluate_exp(t->r);
			
			//REMEMBER WE MUST CLEAN THE REG FOR ARRAY INDEX
			//WAIT UNTIL IT'S ALL OVER
			break;
		case 'F':/* Stmt -> ; */
			// NO WORK dude.
			break;
		case 'G':/* Stmt -> If expr stmt else stmt */
		
			if_else(t);
			//cout <<"[IF]" <<endl;
			// ls = *(t->l->debug);
			// rs = *(t->r->debug);
			// stmt = *(t->stmt->debug);
			
			//cout <<"[87878787]" << ls << endl;
			//cout <<"[87878787]" << rs << endl;
			//cout <<"[87878787]" << stmt << endl;
			
			break;
		case 'K':/* Block -> varList StmtList */
			
			value = evaluate_exp(t->l);
			
			break;
		case 'U':
		
			break;
		case 'X': /* Stmt -> Exp ;*/
			
			value = evaluate_exp(t->l);
			cout << "[EXP X SEC]: This Expression can conclude to " << value.id << endl;
			break;
		case 'P': /* Print id */
			print(*(t->id));
			break;
		case 'R': /* Read id */
			read(*(t->id));
			break;
		case 'T': /* StmtList -> Stmt StmtListP */
			tpval = evaluate_exp(t->l);
			releaseReg(tpval.id);
				
			value = evaluate_exp(t->r);
			releaseReg(value.id);	
		
			break;
		case 'W': /* WHILE '(' Expr ')' Stmt */	
			while_stmt(t);
			
			break;
		case 'C': /* Stmt -> Break */
			function_text.append("\t#break time\n");	
			function_text.append("\tj "+cur_loop+"\n");
			
			break;
		case 'Q': /* Stmt -> Return Expr*/
			
			value = evaluate_exp(t->l);
			return_stmt(value);
			break;
		default:
			//char c = t->node_type;
			cout << "[WTF?]: How can you make this node type ? ->" << t->node_type << endl;
	}

	return value;
}
/* Reg Operation */
//function to set up the register allocation
void initRegs() 
{

	for(int i = 0; i < 10; i++)
		mips_reg.t[i] = 0; // temp

	for(int i = 0; i < 8; i++)
		mips_reg.s[i] = 0; // static

	for(int i = 0; i < 4; i++)
	{
		mips_reg.a[i] = 0; // arg
		//cout << mips_reg.a[i] << endl;
	}	
	for(int i = 0; i < 2; i++)
	{
		mips_reg.v[i] = 0; // sys
		mips_reg.k[i] = 0; //
	}
}

//get register from avaliable lists

string getReg(char c) {

	string tmp;
	int i = 0;
	
	//based on which register type to get find one that is free, 0 = free, 1 = used
	switch (c) 
	{
		case 'v':
			for(i=0;i<2;i++) {
				if( mips_reg.v[i] == 0)
				{
					mips_reg.v[i] = 1;
					tmp = "$v"+to_string(i);
					break;
				}
			}
			break;
		case 'a':
			for(i=0;i<4;i++)
			{
			
				//cout << endl << endl<< "87878787878787878" << endl << endl;
				//cout << "Value of GODDAMN IT RA = " << cout << mips_reg.a[i] << endl;
				if(mips_reg.a[i] == 0)
				{
					mips_reg.a[i] = 1;
					tmp = "$a"+to_string(i);
					break;
				}
			}
			break;
		case 't':
			for(i=0;i<10;i++)
			{
				if(mips_reg.t[i] == 0)
				{
					mips_reg.t[i] = 1;
					tmp = "$t"+to_string(i);
					break;
				}
			}
			break;
		case 's':
			for(i=0;i<8;i++)
			{
				if(mips_reg.s[i] == 0)
				{
					mips_reg.s[i] = 1;
					tmp = "$s"+to_string(i);
					break;
				}
			}
			break;
		case 'k':
			for(i=0;i<2;i++)
			{
				if( mips_reg.k[i] == 0)
				{
					mips_reg.k[i] = 1;
					tmp = "$k"+to_string(i);
					break;
				}
			}
			break;
		default:
			cout << "[WTF?] Dude, there is no type '" << c << "' in mips structure" << endl;
	}
	return tmp;
}

//remove registers from avaliable lists
void releaseReg(string reg)
{

	//DEALING with Padding XX($XX);
	size_t lp_pos = reg.find("(");
	size_t rp_pos = reg.find(")");
	
	if(lp_pos != string::npos && rp_pos != string::npos)
	{
		
		reg = reg.substr(lp_pos+1, rp_pos-lp_pos-1);
		//cout <<"[Release REG]: " << reg << endl;
	}

	char t = reg[1];
	switch (t)
	{
		case 'v':
			mips_reg.v[stoi(reg.substr(2))] = 0;
			break;
		case 'a':
			mips_reg.a[stoi(reg.substr(2))] = 0;
			break;
		case 't':
			mips_reg.t[stoi(reg.substr(2))] = 0;
			break;
		case 's':
			mips_reg.s[stoi(reg.substr(2))] = 0;
			break;
		case 'k':
			mips_reg.k[stoi(reg.substr(2))] = 0;;
			break;
	}
}

int parseId(string id)
{
	int index = look_up_var(id);
	
	if(index != -1)
	{
		//is var
		if(var_table[index].isArray)
			return 3;
		else if(var_table[index].isFunction)
			return 5;
		else
			return 2;
	}
	else
	{
		size_t dollor_pos = id.find("$");
		if(dollor_pos == std::string::npos)
			return 1;//is numver
		else
			return 4;//is reg
	}	

}

ast_val ury(int op,ast_val value)
{
	//TODO SOME BUG
	
	//load the value's value
	string id = value.id;
	string res_tp_reg = "";
	string tp_reg = "";
	
	int id_type = parseId(id);
	cout <<endl<<endl<<endl;
	cout << "[ID Type]: " << id_type << endl;
	
	switch(id_type)
	{
		case 1: // num, load Num;
			res_tp_reg = loadInt(id,function_text) ;
			break;	
		
		case 2: // var, load its value
			res_tp_reg = loadVar(id,function_text) ;
			break;
		
		case 3: // array, load its value
			tp_reg = loadArr(id,value.index,function_text); //get address
			res_tp_reg = getReg('t');
			
			function_text.append("\tlw "+res_tp_reg+", "+tp_reg+"\n");
			
			releaseReg(tp_reg);						
			break;
			
		case 4: // reg, might from an operations' result
		 	res_tp_reg = id;
			break;
			
		case 5: //TODO function, but is it valid to do this? 
		
			break;
	}
	
	//it's op time
	
	switch(op)
	{
		case 15:/* ! */
		
			function_text.append("\t#do not with "+id+"\n");
			function_text.append("\tnot "+res_tp_reg+", "+res_tp_reg+"\n");
		
			break;
		case 14:/* - */
		
			function_text.append("\t#do neg with "+id+"\n");
			function_text.append("\tneg "+res_tp_reg+", "+res_tp_reg+"\n");		
		
			break;
	}
	
	/* Store the res_tp_reg back to value.id */
	
	ast_val return_val;
	return_val.id = "";
	return_val.index = "";
	
	switch(id_type)
	{
		case 1: // num like, -1 ,we just pass back res_tp_reg
			return_val.id = res_tp_reg;
			break;	
		
		case 2: // var, use store func
		
			store(id,res_tp_reg,function_text) ;
			return_val.id = value.id;
			releaseReg(res_tp_reg);
			
			break;
		
		case 3: // array, store back to an array
		
			tp_reg = loadArr(id,value.index,function_text); //get address
			function_text.append("\tsw "+res_tp_reg+", "+tp_reg+"\n");
			releaseReg(tp_reg);
			releaseReg(res_tp_reg);
			
			return_val.id = value.id;
			return_val.index = value.index;						
			
			break;
			
		case 4: // just pass it back
		 	return_val.id = res_tp_reg;
			break;
			
		case 5: //TODO function, but is it valid to do so? 
		
			break;
	}
	
	return return_val;
}

string op(int op, string lv, string rv, string left_index, string right_index) {

	string rreg = "";
	string lreg = "";
	string tp_reg = "";

	cout << "[IN OP] LV is " << lv << " RV is " << rv << endl; 
	//check id type of id, 1:num,2:var,3:array,4:reg,5:func
	int lv_type = parseId(lv);
	int rv_type = parseId(rv);

	/*
	 * The idea is that
	 * Always LOAD THE VALUE
	 * Left hand side and right hand side must be a value NOT AN ADDRESS (like ID,XX($XX) )
	 */
	 
	switch(lv_type)
	{
		case 1:
			function_text.append("\n\t#load int\n");
			lreg = loadInt(lv,function_text);
			break;
		case 2:
			function_text.append("\n\t#load Var\n");
			lreg = loadVar(lv,function_text);
			break;
		case 3:
			function_text.append("\n\t#load Array\n");
			lreg = loadArr(lv,left_index,function_text);//we get XX($X) here
			
			//but that guy is a name, we need to load its value
			tp_reg = getReg('t');
			function_text.append("\tlw "+tp_reg+", "+lreg+"\n");
			
			//K , we can free lreg and set lreg = tp_reg
			releaseReg(lreg);	
			lreg = tp_reg;
		
			break;
		case 4:
			function_text.append("\n\t#pass reg\n");
			lreg = lv; //that is, we pass a result regs from another op/
			break;
		case 5://TODO
			break;
	}
	
	switch(rv_type)
	{
		case 1:
			function_text.append("\n\t#load int\n");
			rreg = loadInt(rv,function_text);
			break;
		case 2:
			function_text.append("\n\t#load Var\n");
			rreg = loadVar(rv,function_text);
			break;
		case 3:
			function_text.append("\n\t#load Array\n");
			rreg = loadArr(rv,right_index,function_text); //we get XX($X) here
			
			//but that guy is a name, we need to load its value
			tp_reg = getReg('t');
			function_text.append("\tlw "+tp_reg+", "+rreg+"\n");
			
			//K , we can free lreg and set lreg = tp_reg
			releaseReg(rreg);	
			rreg = tp_reg;
			
			break;
		case 4:
			function_text.append("\n\t#pass reg\n");
			rreg = rv; //that is, we pass a result regs from another op
			break;
		case 5://TODO

			break;
	}

	string res_reg = getReg('t');

	//do the operation
	switch (op)
	{
		case 1://EQ
			function_text.append("\n\t#EQ "+lv+" "+rv+" store in "+res_reg+"\n");		
			function_text.append("\tseq "+res_reg+", "+lreg+", "+rreg+"\n");
			break;
		case 2://NEQ
			function_text.append("\n\t#NEQ "+lv+" "+rv+" store in "+res_reg+"\n");		
			function_text.append("\tsne "+res_reg+", "+lreg+", "+rreg+"\n");			
			break;	
		case 3:// >
			function_text.append("\n\t#GT "+lv+" "+rv+" store in "+res_reg+"\n");		
			function_text.append("\tsgt "+res_reg+", "+lreg+", "+rreg+"\n");			
			break;
		case 4:// <
			function_text.append("\n\t#LT "+lv+" "+rv+" store in "+res_reg+"\n");		
			function_text.append("\tslt "+res_reg+", "+lreg+", "+rreg+"\n");			
			break;			
		case 5:// >=
			function_text.append("\n\t#GET "+lv+" "+rv+" store in "+res_reg+"\n");		
			function_text.append("\tsge "+res_reg+", "+lreg+", "+rreg+"\n");			
			break;			
		case 6:// <=
			function_text.append("\n\t#LET "+lv+" "+rv+" store in "+res_reg+"\n");		
			function_text.append("\tsle "+res_reg+", "+lreg+", "+rreg+"\n");			
			break;			
		case 7:// &&
			function_text.append("\n\t#AND "+lv+" "+rv+" store in "+res_reg+"\n");		
			function_text.append("\tand "+res_reg+", "+lreg+", "+rreg+"\n");			
			break;			
		case 8:// ||
			function_text.append("\n\t#OR "+lv+" "+rv+" store in "+res_reg+"\n");		
			function_text.append("\tor "+res_reg+", "+lreg+", "+rreg+"\n");			
			break;						
		case 10://+
			function_text.append("\n\t#add "+lv+" "+rv+" store in "+res_reg+"\n");
			function_text.append("\tadd "+res_reg+", "+lreg+", "+rreg+"\n");
			break;
		case 11://-
			function_text.append("\n\t#sub "+lv+" "+rv+" store in "+res_reg+"\n");
			function_text.append("\tsub "+res_reg+", "+lreg+", "+rreg+"\n");
			break;
		case 12://*
			function_text.append("\n\t#mul "+lv+" "+rv+" store in "+res_reg+"\n");
			function_text.append("\tmul "+res_reg+", "+lreg+", "+rreg+"\n");
			break;
		case 13://div
			function_text.append("\n\t#div "+lv+" "+rv+" store in "+res_reg+"\n");
			function_text.append("\tdiv "+res_reg+", "+lreg+", "+rreg+"\n");
			break;
	}
	
	//op done, release reg
	releaseReg(lreg);
	releaseReg(rreg);

	return res_reg;
}

string equal(string lv, string rv, string left_index, string right_index) {

	//sw Rsrc address
	
	int id_type = parseId(rv);
	int lv_type = parseId(lv);
	
	string lreg = "";
	
	switch(lv_type)
	{
		case 1:
			cout << "[WTFS?]: Your assign's left value is A NUMBER" << endl;
			break;
		case 2:
			function_text.append("\n\t#load Var\n");
			// just pass the name, we don't use loadVar
			lreg = lv; //because loadVar is load value but not address.
			break;
		case 3:
			function_text.append("\n\t#load Array Address\n");
			lreg = loadArr(lv,left_index,function_text); 
			break;
		case 4:
			function_text.append("\n\t#pass reg\n");
			lreg = lv; //that is, we pass a result regs from another op/
			break;
		case 5://TODO
			break;
	}
	
	function_text.append("\n\t# Assign Lv:"+lreg+" Rv:"+rv+"\n");
	
	
	/* Dealing with right value type */
	if(id_type == 1)
	{
		string tp_reg = loadInt(rv,function_text);
		function_text.append("\tsw "+tp_reg+", "+lreg+"\n");
		releaseReg(tp_reg);
	}
	else
	{
		/* 2 case :  
		 * rv is a id. 
		 * rv is a reg. (like case'B')
		 */ 
		int index = 0;
		index = look_up_var(rv);
		if( index != -1 ) 
		{
			//cout << endl <<"LV is" << lv <<endl<< "87878787878787878787" << endl <<"Rv is" << rv <<endl <<endl;
			/* is a id */
			if(var_table[index].isArray == 1)
			{
				//I think it is impossible to get in here...
				//but better safe than sorry.
				string tp_reg = loadArr(rv,right_index,function_text);
				string tp_reg2 = getReg('t');
				function_text.append("\tlw "+tp_reg2+", "+tp_reg+"\n");
				function_text.append("\tsw "+tp_reg2+", "+lreg+"\n");
				releaseReg(tp_reg);
				releaseReg(tp_reg2);
			}
			else
			{
				/* normal varible */
				string tp_reg = loadVar(rv, function_text); //load value in rv to tp_reg
				function_text.append("\tsw "+tp_reg+", "+lreg+"\n"); //sw value in reg to lv
				releaseReg(tp_reg);
			}
		}
		else
		{
			//is a register
			function_text.append("\tsw "+rv+", "+lreg+"\n");
			releaseReg(rv);
		}
	}
	return lreg;
}


/* IF-ELSE AST operation */
void if_else(ast *t)
{

	//Structure : IF ( Expr ) Stmt ELSE Stmt 
	// Expr: l , Stmt: r, Stmt: stmt

	if_else_count += 1;//lol another if-else occur.
	
	int tp_count = if_else_count;
	stringstream s;
	s << tp_count;
	string tp_if_tag = s.str();
	
	//text.append(function_text);	//meet a new tag flush out the former block
	//function_text = "";
	
	
	//if res == 0 (i.e. 0=0 ,that is falase )-> goto ELSE, otherwise keep going
	function_text.append("\tbeqz "+evaluate_exp(t->l).id+", else"+tp_if_tag);
	evaluate_exp(t->r);
	
	//text.append(function_text);//meet a new tag flush out the former block
	//function_text = "";
	
	function_text.append("\tjal done"+tp_if_tag+"\nelse"+tp_if_tag+":\n");
	evaluate_exp(t->stmt);
	function_text.append("done"+tp_if_tag+":\n");
	
}

/* WHILE operation */
void while_stmt(ast *t) {

	//Structure : WHILE '(' Expr ')' Stmt 
	// Expr: l , Stmt: r
	
	while_loop_count += 1;
	stringstream s;
	s << while_loop_count;
	
	string current_loop_num = s.str();
	cur_loop = "whileEnd"+current_loop_num ; //is a global at record, use for easy break Kappa~ 
	
	function_text.append("while"+current_loop_num+": ");
	
	evaluate_exp(t->r); // write the loooooooop body
	
	//if you guys dont know what is 0=0, reference if_else kk.
	function_text.append("\tbeqz "+evaluate_exp(t->l).id+", whileEnd"+current_loop_num+"\n");//if 0==0 jump to while end
	function_text.append("\tj while"+current_loop_num+"\n");
	function_text.append("whileEnd"+current_loop_num+":\t");
}

void return_stmt(ast_val ret_val)
{
	/* we only RETURN A VALUE */
	/* so... */
	int ret_type = parseId(ret_val.id);
	
	string value_reg = getReg('v'); //ret_value only store in $v0,$v1
	string res_tp_reg = "" ;
	string tp_reg = "";
	
	switch(ret_type)
	{
		case 1: // num, load Num;
			res_tp_reg = loadInt(ret_val.id,function_text) ;
			break;	
		
		case 2: // var, load its value
			res_tp_reg = loadVar(ret_val.id,function_text) ;
			break;
		
		case 3: // array, load its value
			tp_reg = loadArr(ret_val.id,ret_val.index,function_text); //get address
			res_tp_reg = getReg('t');
			
			function_text.append("\tlw "+res_tp_reg+", "+tp_reg+"\n");
			
			releaseReg(tp_reg);						
			break;
			
		case 4: // reg, might from an operations' result
		 	res_tp_reg = ret_val.id;
			break;
			
		case 5: //TODO function 
		
			break;
	}
	
	if(cur_scope  == "idMain")
	{
		//exit the program
		function_text.append("\tli $v0, 10\n");
		function_text.append("\tsyscall\n");
	}
	else
	{
		function_text.append("\t#Return value\n");
		function_text.append("\tmove "+value_reg+", "+res_tp_reg+"\n");
		releaseReg(res_tp_reg);
		function_text.append("\tjr $ra\n");
	}
}


/* declare operation */

void decl_var(clearsym sym)
{
	clearsym tp ;

	tp.type = sym.type;
	tp.isArray = sym.isArray;
	tp.isFunction = 0;
	tp.size = sym.size;
	tp.id = sym.id;		

	cout << "[VarDecl]: Find a var" << tp.id << " with type" << tp.type << " isArray:" << tp.isArray << " with size :" << tp.size << endl;	
	
	var_table.push_back(tp);
	string name = tp.id; 
	
	if(tp.type == 1)
	{
		if(tp.isArray)
		{
			int size = tp.size;
			stringstream s;
			s << size;
			data.append("\t"+name+":\t.word 0:"+s.str()+"\n");
		}
		else
			data.append("\t"+name+":\t.word 0\n");
	}
	else
	{
		if(tp.isArray)
		{
			int size = tp.size;
			stringstream s;
			s << size;
			data.append("\t"+name+":\t.word "+s.str()+"\n");
		}
		else
			data.append("\t"+name+":\t.word 'a'\n");
	}
}

void symbol_table_insertion(string id, symbol* sym)
{
		//Do with declListP,
		//we push the decl ($3) to fun_table/var_table

		string name = string(id);
		//cout << endl<< "GGININDER" << endl;
		if(sym->isFunction == 1)
		{
			cur_scope = name;
			if( id == "idMain")
			{
				/* is in main function */
				function_text.append("main:\n");
			}
			else
			{
				/* TODO Another FUNCTION */
				function_text.append(name+":\n");
			}
			
			clearsym tp;
			tp.type = sym->type;
			tp.isFunction = 1;
			tp.isArray = 0;
			tp.size = 0;
			tp.id = name;
			fun_table.push_back(tp);
		}
		else
		{
			/* is an varaible */
			clearsym tp;
			tp.type = sym->type;
			tp.isFunction = 0;
			tp.isArray = sym->isArray;
			tp.size = sym->size;
			tp.id = name;
			var_table.push_back(tp);		
		}
}

void decl_fuc()
{

}

/* Look-up Operation */
int look_up_var(string str){
	
	size_t i;
	
	for( i = 0 ; i < var_table.size() ; i++)
		if( str == var_table[i].id )
			break;

	if( i != var_table.size())
	{
		//cout << "[LOOK-UP] : Find a reference symbol(var) " << var_table[i].id << endl;
		return i;
	} else
		return -1;

}
int look_up_fuc(string str){

	size_t i;
	for( i = 0 ; i < var_table.size() ; i++)
		if( str == fun_table[i].id )
			break;

	if( i != fun_table.size())
	{
		cout << "[LOOK-UP] : Find a reference symbol(fun) " << fun_table[i].id << endl;
		return i;
	} else
		return -1;
}


/* Function operation */
void write_a_param(string id)
{
	string reg = getReg('a');//get one argument register
	store(id, reg, function_text);// store value form id to that reg.
}

void push_function_argument(ast_val value)
{
	string reg = loadId(value,function_text);
	
	//store its value to argument register;
	string areg = getReg('a');
	
	if(areg.empty())
	{
		cout << "[WTF?] Too many argument, dude" << endl;
		exit(1);
	}
	else
	{
		cout << "[Argument] : store " << value.id << " into " << areg << endl;
		function_text.append("\tmove "+areg+", "+reg+"\n");
	}
	
}


/* yyerror debug method */
int yyerror(string s) {
	extern int yylineno;
	extern char **yytext;

	cerr << "ERROR: " << s << " at symbol \"" << yytext;
	cerr << "\" on line " << yylineno << endl;
	return 1;
}

int yyerror(const char *s) {
	return yyerror(string(s));
}

int yyerror() {
	return yyerror(string(""));
}


