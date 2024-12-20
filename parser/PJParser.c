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
#line 7 "PJParser.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <util/general.h>
#include <util/symtab.h>
#include <util/symtab_stack.h>
#include <util/string_utils.h>
#include <util/dlink.h>
#include <errno.h> // Added

#define SYMTABLE_SIZE 100


// ---------- MY MACROS --------------



// For Types
#define TYPE_LONGINT_ARR 0
#define TYPE_LONGINT_ARR_2D 1
#define TYPE_LONGINT_STD 2
#define TYPE_BOOL_ARR 3
#define TYPE_BOOL_ARR_2D 4
#define TYPE_BOOL_STD 5
#define TYPE_FLOAT_ARR 6
#define TYPE_FLOAT_ARR_2D 7
#define TYPE_FLOAT_STD 8

#define PSEUDOTYPE_STRING 6
#define PSEUDOTYPE_CONSTANT 7

#define DATA_SIZE 4


// For symbol tables
#define SYMTAB_TYPE_FIELD "type"
#define SYMTAB_OFFSET_FIELD "offset"
#define SYMTAB_SCLASS_FIELD "storage_class"
#define SYMTAB_VALUE_FIELD  "value"

// Storage Classes
#define BASE_ADDR 0
#define GLOBAL 1
#define STACK 2
#define HEAP 3

// Random
#define TEMP_STR_LEN 256
#define REG_STR 6
#define PADDING 5



// --------------- BEHAVIOR CONTROL MACROS -------------------

/* delete or comment out the line below after you have a good grasp of Project 1. It will turn off all printf statements that print the grammar rules */ 
//#define PROJECT1
/* uncomment the below line if you want all output to be put in the file provided as a program arg */
#define FILE_OUTPUT
// uncomment the below line if you want a symtable printout
//#define DEBUG_SYMTABLE

/*********************EXTERNAL DECLARATIONS***********************/

EXTERN(void,yyerror,(char*));
EXTERN(int,yylex,(void));

char *fileindex;

extern int yylineno;
extern char *yytext;
extern FILE *yyin;

SymTable global_symTab;
SymtabStack symStack;

// Reg 'Checked-Out' Array
u_int32_t reg_out_arr[12];

// ------------ VARS -------------

// Stores the dimension details of an array
struct ArrayDim {
	int dim_num, dim1_l, dim1_r, dim1_s, dim2_l, dim2_r, dim2_s;
};

// Func Management Vars
u_int16_t isFunc;
u_int32_t loc_nmemb;
int loc_sp;

const static char *frame_lvl_name = "flevel";
u_int16_t frame_lvl; // Value in frame_lvl is assigned to the next frame



// Global Pointer Vars
unsigned int glob_nmemb;

// DLink vars
DLinkList *iList;
DLinkList *dataList;
DLinkList *assList;
DLinkList *rStack;
DLinkList *funcList;

// 		- list atoms
const static char *dataList_atom = "Read-Only Data List";
const static char *iList_atom = "Instruction List";
const static char *assList_atom = "Final Assembly Instruction List";
const static char *idList_atom = "DeclList Identifiers";

// 		- init strings
const static char *dataList_init_string = ".section\t.rodata\n";
char *iList_init_string = ".text\n\t\t.globl main\n\t\t.type main,@function\nmain:\tnop\n\t\tpushq %rbp\n\t\tmovq %rsp, %rbp\n";


// global readonly mem vars
const static char *string_add_format = "\t\t.string_const%d: .string \"%s\"\n";
const static char *string_ref = ".string_const%d";
const static unsigned int string_add_format_size = 35; // This includes the digit %d
const static char *gp_add_format = "\t\t.comm _gp, %d, %d\n"; // This includes both digits
const static char *scanf_format = "\t\t.string_const0: .string \"%d\"\n";
const static char *newline_printf_format = "\t\t.string_const1: .string \"%c\"\n";
const static unsigned int gp_add_format_size = 35;

//const static char *scanf_data = "\t\t.x: .long 0";


// RStack vars
const static char *rStack_atom = "Register Stack";
const unsigned int reg_count = 12;


// Instruction strings
const static char *str_printf_string = "\t\tleaq .string_const%d(%%rip), %%rdi\n\t\tleaq .string_const%d(%%rip), %%rsi\n\t\tmovl $0, %%eax\n\t\tcall printf@PLT\n";
const static char *str_printf_nl = "\t\tleaq .string_const1(%rip), %rdi\n\t\tmovl $10, %esi\n\t\tmovl $0, %eax\n\t\tcall printf@PLT\n";
const static char *str_printf_int = "\t\tleaq .string_const%d(%%rip), %%rdi\n\t\tmovl %s, %%esi\n\t\tmovl $0, %%eax\n\t\tcall printf@PLT\n";

const static char *str_scanf = "\t\tleaq .string_const0(%%rip), %%rdi\n\t\tmovq %s, %%rsi\n\t\tmovl $0, %%eax\n\t\tcall scanf@PLT\n";
const static char *str_scanf_loc = "\t\tleaq .string_const0(%rip), %rdi\n\t\tmovq .x(%rip), %rsi\n\t\tmovl $0, %eax\n\t\tcall scanf@PLT\n";

const static char *str_assign = "\t\tmovl %s, (%s)\n";

const static char *str_loadVar = "\t\tleaq _gp(%%rip), %s\n\t\taddq $%u, %s\n";
const static char *str_loadVarValue = "\t\tmovl (%s), %s\n";
const static char *str_loadImm = "\t\tmovl $%d, %s\n";
const static char *str_addReg = "\t\taddl %s, %s\n";
const static char *str_multReg = "\t\timull %s, %s\n";
const static char *str_divReg = "\t\tmovl %s, %%eax\n\t\tcdq\n\t\tidivl %s\n\t\tmovl %%eax, %s\n";
const static char *str_not = "\t\tmovl $0x00000001, %%edx\n\t\tnotl %s\n\t\tandl %%edx, %s\n";
const static char *str_or = "\t\torl %s, %s\n";
const static char *str_and = "\t\tandl %s, %s\n";
const static char *str_sub = "\t\tsubl %s, %s\n";
const static char *str_gt_or_lt = "\t\tcmpl %s, %s\n\t\tmovl $0, %s\n\t\tmovl $1, %s\n\t\tcmovg %s, %s\n";
const static char *str_ge_or_le = "\t\tcmpl %s, %s\n\t\tmovl $0, %s\n\t\tmovl $1, %s\n\t\tcmovg %s, %s\n\t\tcmove %s, %s\n";
const static char *str_eq = "\t\tcmpl %s, %s\n\t\tmovl $0, %s\n\t\tmovl $1, %s\n\t\tcmove %s, %s\n";
const static char *str_neq = "\t\tcmpl %s, %s\n\t\tmovl $0, %s\n\t\tmovl $1, %s\n\t\tcmovne %s, %s\n";

const static char *str_loadImm_64 = "\t\tmovq $%d, %s\n";
const static char *str_addReg_64 = "\t\taddq %s, %s\n";
const static char *str_sub_64 = "\t\tsubq %s, %s\n";

const static char *str_32To64 = "\t\tmovslq %s, %s\n";


// const static char *str_not_jump = "\t\tmovl $-1, %s\n\t\ttestl %s, %s\n\t\tje .L%d\n";
// const static char *str_end_if = "\t\tjmp .L%d\n.L%d: nop\n";


const static char *str_label = ".L%d: nop\n";
const static char *str_test = "\t\ttestl %s, %s\n";
const static char *str_jumpeq = "\t\tje .L%d\n";
const static char *str_jump = "\t\tjmp .L%d\n";

// function ins
const static char *str_func_label = "%s:\n";
// In the future, this should push the containing function as the access link
const static char *str_func_prologue = "\t\tpushq %rbp\n\t\tmovq %rsp, %rbp\n\t\tsubq $4, %rsp\n";
const static char *str_func_init_local = "\t\tsubq $%d, %%rsp\n";
const static char *str_func_epilogue = "\t\tleave\n\t\tret\n";
const static char *str_func_return_val = "\t\tmovl %s, %%eax\n";
const static char *str_push_reg = "\t\tpushq %s\n";
const static char *str_pop_reg = "\t\tpopq %s\n";
const static char *str_call_func = "\t\tmovq $0, %%rax\n\t\tcall %s\n";
const static char *str_move_return = "\t\tmovl %%eax, %s\n";
// local version of loadVar
const static char *str_loadVar_loc = "\t\tmovq %%rbp, %s\n\t\taddq $%d, %s\n";

// End of program epilogue
const static char *str_end_program = "\t\tmovl $60, %eax\n\t\tmovl $0, %edi\n\t\tsyscall\n";

// 		- dynamic
static unsigned int next_str_sym_id;

// Control Labels
static int label_num = 0;



// ------------ FUNCTION DECLARATIONS -------------

// SymTab declarations
static void setType(char *name, int type, u_int16_t global);

static int getType(char *name);

static Generic getValue(char *name);

static void setValue(char *name, Generic value, u_int16_t global);

static void setOffset(char *name, int offset, u_int16_t global);

static int getOffset(char *name);

static void setSClass(char *name, int s_class, u_int16_t global);

static int getSClass(char *name);

static void initStringSym (char *str);

static void initVarSym (char *name, int type);


// DLink declarations

static void dataList_init ();

static void dataList_addStringConst (char *name);

static void dataList_addGlobalPointer (unsigned int nmemb, unsigned int size);

static void iList_init ();

static void add_instructions (char *ins);


// rStack declarations

static void rStack_init ();

static unsigned int pop_reg ();

static void push_reg (unsigned int reg);

static char *regToStr (char *reg_str, unsigned int reg, bool is64);


// Instruction declarations

static void ins_loadVar (char *name, unsigned int mem_reg);

static void ins_loadVarValue (unsigned int mem_reg, unsigned int reg);

static void ins_loadImm (int imm, unsigned int reg);

static void ins_addReg (unsigned int reg1, unsigned int reg2);

static void ins_subReg (unsigned int min_reg, unsigned int sub_reg);

static void ins_multReg (unsigned int reg1, unsigned int reg2);

static void ins_divReg (unsigned int dividend_reg, unsigned int divisor_reg);

static void ins_and (unsigned int reg1, unsigned int reg2);

static void ins_or (unsigned int reg1, unsigned int reg2);

static void ins_not (unsigned reg);

static void ins_gt (unsigned int reg1, unsigned int reg2);

static void ins_ge (unsigned int reg1, unsigned int reg2);

static void ins_lt (unsigned int reg1, unsigned int reg2);

static void ins_le (unsigned int reg1, unsigned int reg2);

static void ins_eq (unsigned int reg1, unsigned int reg2);

static void ins_neq (unsigned int reg1, unsigned int reg2);

static void ins_printf_string (char *fstr, char *str);

static void ins_printf_int (char *str, unsigned int reg);

static void ins_printf_newline ();

static void ins_scanf (unsigned int reg);

static void ins_assign (unsigned int mem_reg, unsigned int reg);

static void dumpDList (DLinkList *list);

static void ins_label (unsigned int label_index);

static void ins_test (unsigned int const_reg, unsigned int cond_reg);

static void ins_jumpeq (unsigned label_index);

static void ins_jump (unsigned label_index);

static void ins_loadImm_64 (int imm, unsigned int reg);

static void ins_addReg_64 (unsigned int reg1, unsigned int reg2);

static void ins_subReg_64 (unsigned int reg1, unsigned int reg2);

static void ins_32To64 (unsigned int reg);

static void load_1dim_arr(char *name, unsigned int i_reg, unsigned int res_addr_reg);

static void load_2dim_arr(char *name, unsigned int i_reg, unsigned int j_reg, unsigned int res_addr_reg);

static void initArraySym (char *name, int type, int dim1_l, int dim1_r, int dim2_l, int dim2_r);



// Compound Instructions

static void start_control (unsigned int const_reg, unsigned int cond_reg, unsigned int label_index);

static void end_control (unsigned int end_ifelse_label_index, unsigned int start_else_label_index);

// Util Declarations

static void addStringConst (char *str);

static char *removeQuotes (char *temp_str, char *str);

static unsigned int genLabel ();

static u_int16_t isGlobal (char *name);

static void ins_end_program ();

// Function, Stack, and Scope Declarations
static SymTable push_scope ();

static SymTable pop_scope ();

static void kill_scope (SymTable scope_symTab);

static void ins_func_label (char *str);

static void ins_func_prologue();

static void ins_func_epilogue();

static void ins_func_init_local ();

static void ins_func_ret_val (int ret_reg);

static void ins_func_call(char *func_name, unsigned int ret_reg);





#line 428 "PJParser.c" /* yacc.c:339  */

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
   by #include "PJParser.h".  */
#ifndef YY_YY_PJPARSER_H_INCLUDED
# define YY_YY_PJPARSER_H_INCLUDED
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
    T_AND = 258,
    T_ELSE = 259,
    T_FLOAT = 260,
    T_FOR = 261,
    T_IF = 262,
    T_LONGINT = 263,
    T_BOOLEAN = 264,
    T_PROGRAM = 265,
    T_FUNCTION = 266,
    T_NOT = 267,
    T_OR = 268,
    T_READ = 269,
    T_WHILE = 270,
    T_WRITE = 271,
    T_WRITELN = 272,
    T_BEGIN = 273,
    T_END = 274,
    T_VAR = 275,
    T_DO = 276,
    T_ARRAY = 277,
    T_EXIT = 278,
    T_THEN = 279,
    T_LE = 280,
    T_LT = 281,
    T_GE = 282,
    T_GT = 283,
    T_EQ = 284,
    T_NE = 285,
    T_ASSIGN = 286,
    T_COMMA = 287,
    T_SEMICOLON = 288,
    T_COLON = 289,
    T_LBRACKET = 290,
    T_RBRACKET = 291,
    T_LPAREN = 292,
    T_RPAREN = 293,
    T_PLUS = 294,
    T_TIMES = 295,
    T_IDENTIFIER = 296,
    T_DIV = 297,
    T_STRING = 298,
    T_INTNUM = 299,
    T_FLOATNUM = 300,
    T_MINUS = 301,
    T_DOT = 302,
    T_DOTDOT = 303,
    T_OF = 304,
    T_TRUE = 305,
    T_FALSE = 306
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 369 "PJParser.y" /* yacc.c:355  */
 
	int ival;
	char *sval;
	struct DLinkList_struct *dll;
	int *iarrval;

#line 527 "PJParser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PJPARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 544 "PJParser.c" /* yacc.c:358  */

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   179

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  163

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   445,   445,   471,   479,   488,   495,   502,   526,   552,
     566,   579,   586,   595,   604,   613,   624,   650,   678,   688,
     698,   708,   720,   727,   734,   749,   760,   775,   783,   789,
     795,   801,   807,   814,   822,   836,   844,   854,   867,   884,
     895,   913,   925,   939,   977,  1023,  1031,  1039,  1046,  1055,
    1068,  1076,  1082,  1091,  1098,  1112,  1127,  1142,  1157,  1171,
    1187,  1194,  1208,  1222,  1238,  1245,  1259,  1273,  1290,  1306,
    1313,  1324,  1333,  1344,  1357,  1372,  1393,  1399,  1413,  1427,
    1441
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_AND", "T_ELSE", "T_FLOAT", "T_FOR",
  "T_IF", "T_LONGINT", "T_BOOLEAN", "T_PROGRAM", "T_FUNCTION", "T_NOT",
  "T_OR", "T_READ", "T_WHILE", "T_WRITE", "T_WRITELN", "T_BEGIN", "T_END",
  "T_VAR", "T_DO", "T_ARRAY", "T_EXIT", "T_THEN", "T_LE", "T_LT", "T_GE",
  "T_GT", "T_EQ", "T_NE", "T_ASSIGN", "T_COMMA", "T_SEMICOLON", "T_COLON",
  "T_LBRACKET", "T_RBRACKET", "T_LPAREN", "T_RPAREN", "T_PLUS", "T_TIMES",
  "T_IDENTIFIER", "T_DIV", "T_STRING", "T_INTNUM", "T_FLOATNUM", "T_MINUS",
  "T_DOT", "T_DOTDOT", "T_OF", "T_TRUE", "T_FALSE", "$accept", "Program",
  "ProgramHeadAndProcedures", "ProgramHead", "Decls", "DeclList",
  "IdentifierList", "Type", "StandardType", "ArrayType", "Dim",
  "Procedures", "ProcedureDecl", "ProcedureHead", "FunctionDecl",
  "ProcedureBody", "Statement", "Assignment", "IfStatement", "TestAndThen",
  "Test", "WhileStatement", "WhileExpr", "WhileToken", "IOStatement",
  "OutputFormat", "WriteToken", "ExitStatement", "CompoundStatement",
  "StatementList", "Expr", "AddExpr", "MulExpr", "Factor", "Variable",
  "Constant", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

#define YYPACT_NINF -93

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-93)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,   -17,    33,     9,   -93,    -3,   -93,     3,   -10,    25,
      28,    43,    17,   -93,   -93,   -93,    23,     5,   -93,   -93,
     -93,   -93,    43,   -93,    45,   -93,   -93,   -11,    16,   -93,
      24,   -93,     9,    28,    44,   -93,    43,    43,   -21,   -93,
     -93,    13,   -93,   -93,    87,    62,   125,    10,     1,   -93,
     -93,   -93,    67,    43,    43,    92,   125,    27,   -93,     3,
      43,    80,   -93,    93,   -93,   -93,    44,    29,   -93,    71,
      96,   -93,     3,     3,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    97,    77,    91,     3,
     102,   115,   -93,   125,     4,   -93,    42,    84,    20,   -93,
     -93,   -93,   -93,    10,    10,    10,    10,    10,    10,     1,
       1,     1,   -93,   -93,   -93,   -93,   -93,    43,   -93,   -93,
      94,    99,   108,   -93,   -93,   -93,   114,    20,   -93,   113,
     129,   -93,   -93,   103,   -93,   -93,   -93,   -93,   130,    35,
     -93,   -93,   -93,   116,   121,   -25,    46,   118,    35,   119,
     -93,   123,    78,   133,     4,   -93,   -93,   126,   122,   -93,
     -93,     4,   -93
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    23,     0,     1,     0,     0,     3,
       6,     0,     0,    41,    47,    48,     0,    73,    52,    28,
      29,    30,     0,    31,     0,    32,    33,     0,     0,     2,
       0,    22,     0,     6,     0,     4,     0,     0,    73,    78,
      76,     0,    79,    80,    36,     0,    38,    53,    60,    64,
      68,    69,     0,     0,     0,     0,    40,     0,    50,     0,
       0,     0,    24,     0,    25,     9,     5,     0,    70,     0,
       0,    77,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,    46,    51,    34,     0,    27,     0,     0,     0,    72,
      71,    35,    37,    56,    57,    58,    59,    54,    55,    61,
      62,    63,    67,    65,    66,    42,    49,     0,    74,    39,
       0,     0,     0,    15,    13,    14,     0,     0,    10,     0,
       0,    11,    12,     0,    45,    44,    43,    26,     0,     0,
       7,    75,     8,     0,     0,     0,     0,     0,     0,     0,
      18,     0,     0,     0,     0,    20,    19,     0,     0,    16,
      21,     0,    17
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -93,   -93,   -93,   -93,   139,   -93,   107,    47,   -92,   -93,
      31,   -93,   -93,   -93,   -93,   -93,   -14,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,   -93,    85,   -93,   -93,     2,   -93,
     -22,    82,    30,   -33,    -6,   -93
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    35,    66,    67,   130,   131,   132,
     145,     9,    31,    32,    33,    62,    18,    19,    20,    44,
      45,    21,    55,    22,    23,   121,    24,    25,    26,    27,
      46,    47,    48,    49,    50,    51
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      56,    28,   126,    68,    83,     8,     1,   148,    58,   123,
      11,   149,   124,   125,    54,    69,    70,    12,    13,    14,
      15,     7,    59,    80,     5,   123,    16,     7,   124,   125,
      10,    87,    88,     6,    63,    91,    30,    29,    93,    36,
      54,    84,   129,    85,    17,    92,    86,    60,    34,    81,
     112,   113,   114,    28,    52,    36,    82,    71,   101,   102,
      53,    97,   159,    98,    37,    61,    28,    28,    38,   162,
      90,    39,    40,    41,    97,   119,   127,    42,    43,   143,
      37,   144,    57,    28,    38,    65,    73,    39,    40,    41,
     150,    72,   151,    42,    43,   133,    74,    75,    76,    77,
      78,    79,    74,    75,    76,    77,    78,    79,    17,    99,
     109,   110,   111,    89,    94,   116,    74,    75,    76,    77,
      78,    79,   156,   117,   157,   128,    95,   118,    74,    75,
      76,    77,    78,    79,   100,   115,   120,   135,   134,   141,
      74,    75,    76,    77,    78,    79,   136,   137,   139,   120,
      74,    75,    76,    77,    78,    79,   103,   104,   105,   106,
     107,   108,   140,   142,   146,   147,   152,   155,   154,   158,
     160,   161,    64,    96,   138,     0,   122,     0,     0,   153
};

static const yytype_int16 yycheck[] =
{
      22,     7,    94,    36,     3,     3,    10,    32,    19,     5,
       7,    36,     8,     9,    35,    37,    37,    14,    15,    16,
      17,    18,    33,    13,    41,     5,    23,    18,     8,     9,
      33,    53,    54,     0,    32,    57,    11,    47,    60,    12,
      35,    40,    22,    42,    41,    59,    52,    31,    20,    39,
      83,    84,    85,    59,    37,    12,    46,    44,    72,    73,
      37,    32,   154,    34,    37,    41,    72,    73,    41,   161,
      43,    44,    45,    46,    32,    89,    34,    50,    51,    44,
      37,    46,    37,    89,    41,    41,    24,    44,    45,    46,
      44,     4,    46,    50,    51,   117,    25,    26,    27,    28,
      29,    30,    25,    26,    27,    28,    29,    30,    41,    38,
      80,    81,    82,    21,    34,    38,    25,    26,    27,    28,
      29,    30,    44,    32,    46,    41,    33,    36,    25,    26,
      27,    28,    29,    30,    38,    38,    34,    38,    44,    36,
      25,    26,    27,    28,    29,    30,    38,    33,    35,    34,
      25,    26,    27,    28,    29,    30,    74,    75,    76,    77,
      78,    79,    33,    33,    48,    44,    48,    44,    49,    36,
      44,    49,    33,    66,   127,    -1,    91,    -1,    -1,   148
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    53,    54,    55,    41,     0,    18,    80,    63,
      33,     7,    14,    15,    16,    17,    23,    41,    68,    69,
      70,    73,    75,    76,    78,    79,    80,    81,    86,    47,
      11,    64,    65,    66,    20,    56,    12,    37,    41,    44,
      45,    46,    50,    51,    71,    72,    82,    83,    84,    85,
      86,    87,    37,    37,    35,    74,    82,    37,    19,    33,
      31,    41,    67,    80,    56,    41,    57,    58,    85,    82,
      37,    44,     4,    24,    25,    26,    27,    28,    29,    30,
      13,    39,    46,     3,    40,    42,    86,    82,    82,    21,
      43,    82,    68,    82,    34,    33,    58,    32,    34,    38,
      38,    68,    68,    83,    83,    83,    83,    83,    83,    84,
      84,    84,    85,    85,    85,    38,    38,    32,    36,    68,
      34,    77,    77,     5,     8,     9,    60,    34,    41,    22,
      59,    60,    61,    82,    44,    38,    38,    33,    59,    35,
      33,    36,    33,    44,    46,    62,    48,    44,    32,    36,
      44,    46,    48,    62,    49,    44,    44,    46,    36,    60,
      44,    49,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    55,    56,    56,    57,    57,    58,
      58,    59,    59,    60,    60,    60,    61,    61,    62,    62,
      62,    62,    63,    63,    64,    65,    66,    67,    68,    68,
      68,    68,    68,    68,    69,    70,    70,    71,    72,    73,
      74,    75,    76,    76,    76,    77,    77,    78,    78,    79,
      80,    81,    81,    82,    82,    82,    82,    82,    82,    82,
      83,    83,    83,    83,    84,    84,    84,    84,    85,    85,
      85,    85,    85,    86,    86,    86,    87,    87,    87,    87,
      87
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     4,     2,     0,     4,     5,     1,
       3,     1,     1,     1,     1,     1,     6,     8,     3,     4,
       4,     5,     2,     0,     2,     2,     5,     2,     1,     1,
       1,     1,     1,     1,     3,     4,     2,     3,     1,     4,
       1,     1,     4,     5,     5,     2,     0,     1,     1,     4,
       3,     3,     1,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     1,     3,     3,     3,     1,     1,
       2,     3,     3,     1,     4,     6,     1,     2,     1,     1,
       1
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
#line 446 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Program : ProgramHeadAndProcedures CompoundStatement T_DOT\n");		
		  #endif

		  // Add a global pointer (note, whenever we start using multiple types, this will have to be changed)
		  dataList_addGlobalPointer(glob_nmemb, DATA_SIZE);

		  // End of program
		  ins_end_program();


		  // Combine dataList and iList into assList and print out instructions
		  dlinkJoin(assList, dataList, iList);
		  dlinkJoin(assList, assList, funcList);
		  DLinkNode *node = dlinkHead(assList);
		  #ifndef NO_ASM_OUT
		  while (node != NULLNODE) {
			fprintf(stdout, "%s", (char*)dlinkNodeAtom(node));
			node = dlinkNext(node);
		  }
		  #endif
        }
#line 1767 "PJParser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 472 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "ProgramHeadAndProcedures : ProgramHead Procedure\n");		
		  #endif
		}
#line 1777 "PJParser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 480 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "ProgramHead : T_PROGRAM T_IDENTIFIER T_SEMICOLON Decls \n");		
		  #endif
		}
#line 1787 "PJParser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 489 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Decls : T_VAR DeclList\n");		
		  #endif
		}
#line 1797 "PJParser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 495 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Decls : \n");		
		  #endif
		}
#line 1807 "PJParser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 503 "PJParser.y" /* yacc.c:1646  */
    {   
		  #ifdef PROJECT1
		  fprintf(stderr, "DeclList : IdentifierList T_COLON Type T_SEMICOLON\n");
		  #endif
		  // Enter all the globals into the symbol table
		  DLinkNode *node = dlinkHead((yyvsp[-3].dll));
		  int *type_def = (yyvsp[-1].iarrval);
		  while (node != NULLNODE) {
			char *name = (char*)dlinkNodeAtom(node);
			if ((type_def[0] == TYPE_LONGINT_STD) || (type_def[0] == TYPE_BOOL_STD) || (type_def[0] == TYPE_FLOAT_STD)) {
				initVarSym(name, type_def[0]);
			} else {
				initArraySym(name, type_def[0], type_def[1], type_def[2], type_def[3], type_def[4]);
			}

			node = dlinkNext(node);
		  }
		  // We free temp int array
		  free(type_def);
		  // DLinkList is no longer needed so we free it
		  dlinkFreeNodes((yyvsp[-3].dll));
		  dlinkListFree((yyvsp[-3].dll));
		}
#line 1835 "PJParser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 527 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "DeclList : DeclList IdentifierList T_COLON Type T_SEMICOLON\n");
		  #endif
		  // Enter all the globals into the symbol table
		  DLinkNode *node = dlinkHead((yyvsp[-3].dll));
		  int *type_def = (yyvsp[-1].iarrval);
		  while (node != NULLNODE) {
			char *name = (char*)dlinkNodeAtom(node);
			if ((type_def[0] == TYPE_LONGINT_STD) || (type_def[0] == TYPE_BOOL_STD) || (type_def[0] == TYPE_FLOAT_STD)) {
				initVarSym(name, type_def[0]);
			} else {
				initArraySym(name, type_def[0], type_def[1], type_def[2], type_def[3], type_def[4]);
			}

			node = dlinkNext(node);
		  }
		  // We free temp int array
		  free(type_def);
		  // DLinkList is no longer needed so we freee it
		  dlinkFreeNodes((yyvsp[-3].dll));
		  dlinkListFree((yyvsp[-3].dll));
		}
#line 1863 "PJParser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 553 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "IdentifierList : T_IDENTIFIER\n");
		  #endif
		  // Create a DLinkList and put the identifier in the list
		  DLinkList *idList;
		  DLinkNode *node;
		  idList = dlinkListAlloc((Generic*)idList_atom);
		  node = dlinkNodeAlloc((Generic*)(yyvsp[0].sval));
		  dlinkAppend(idList, node);
		  (yyval.dll) = idList;

		}
#line 1881 "PJParser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 567 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "IdentifierList : IdentifierList T_COMMA T_IDENTIFIER\n");
		  #endif
		  // Add the indentifier (string) to the current DLinkList
		  DLinkNode *node;
		  node = dlinkNodeAlloc((Generic*)(yyvsp[0].sval));
		  dlinkAppend((yyvsp[-2].dll), node);
		  (yyval.dll) = (yyvsp[-2].dll);
		}
#line 1896 "PJParser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 580 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Type : StandardType\n");		
		  #endif
		  (yyval.iarrval) = (yyvsp[0].iarrval);
		}
#line 1907 "PJParser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 587 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Type : ArrayType\n");		
		  #endif
  		  (yyval.iarrval) = (yyvsp[0].iarrval);
	 	}
#line 1918 "PJParser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 596 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "StandardType : T_LONGINT\n");		
		  #endif
		  int *type = malloc(sizeof(int));
		  type[0] = TYPE_LONGINT_STD;
		  (yyval.iarrval) = type;
		}
#line 1931 "PJParser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 605 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "StandardType : T_BOOLEAN\n");		
		  #endif
		  int *type = malloc(sizeof(int));
		  type[0] = TYPE_BOOL_STD;
		  (yyval.iarrval) = type;
		}
#line 1944 "PJParser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 614 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "StandardType : T_FLOAT\n");
		  #endif
		  int *type = malloc(sizeof(int));
		  type[0] = TYPE_FLOAT_STD;
		  (yyval.iarrval) = type;
		}
#line 1957 "PJParser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 625 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "ArrayType : T_ARRAY T_LBRACKET Dim T_RBRACKET T_OF StandardType\n");		
		  #endif

		  int type = *((yyvsp[0].iarrval));

		  int *arr = malloc(sizeof(int)*5);
		  int *prev_arr = (yyvsp[-3].iarrval);
		  arr[1] = prev_arr[0];
		  arr[2] = prev_arr[1];
		  free(prev_arr);
		  arr[3] = 1;
		  arr[4] = 1;

		  // Return a value associated with the datatype of the array
		  if (type == TYPE_LONGINT_STD) {
			arr[0] = TYPE_LONGINT_ARR;
		  } else if (type == TYPE_BOOL_STD) {
			arr[0] = TYPE_BOOL_ARR;
		  } else {
			arr[0] = TYPE_FLOAT_ARR;
		  }
		  (yyval.iarrval) = arr;
		}
#line 1987 "PJParser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 651 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "ArrayType : T_ARRAY T_LBRACKET Dim T_COMMA Dim T_RBRACKET T_OF StandardType\n");		
		  #endif

		  int type = *((yyvsp[0].iarrval));

		  int *arr = malloc(sizeof(int)*5);
		  int *prev_arr1 = (yyvsp[-5].iarrval);
		  int *prev_arr2 = (yyvsp[-3].iarrval);
		  arr[1] = prev_arr1[0]; arr[2] = prev_arr1[1];
		  arr[3] = prev_arr2[0]; arr[4] = prev_arr2[1];
		  free(prev_arr1);
		  free(prev_arr2);

		  // Return a value associated with the datatype of the array
		  if (type == TYPE_LONGINT_STD) {
			arr[0] = TYPE_LONGINT_ARR_2D;
		  } else if (type == TYPE_BOOL_STD) {
			arr[0] = TYPE_BOOL_ARR_2D;
		  } else {
			arr[0] = TYPE_FLOAT_ARR_2D;
		  }
		  (yyval.iarrval) = arr;
		}
#line 2017 "PJParser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 679 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Dim : T_INTNUM T_DOTDOT T_INTNUM\n");		
		  #endif
		  int *arr = malloc(sizeof(int)*2);
		  arr[0] = (yyvsp[-2].ival);
		  arr[1] = (yyvsp[0].ival);
		  (yyval.iarrval) = arr;
		}
#line 2031 "PJParser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 689 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Dim : T_INTNUM T_DOTDOT T_INTNUM\n");		
		  #endif
		  int *arr = malloc(sizeof(int)*2);
		  arr[0] = -(yyvsp[-2].ival);
		  arr[1] = (yyvsp[0].ival);
		  (yyval.iarrval) = arr;
		}
#line 2045 "PJParser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 699 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Dim : T_INTNUM T_DOTDOT T_INTNUM\n");		
		  #endif
		  int *arr = malloc(sizeof(int)*2);
		  arr[0] = (yyvsp[-3].ival);
		  arr[1] = -(yyvsp[0].ival);
		  (yyval.iarrval) = arr; 
		}
#line 2059 "PJParser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 709 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Dim : T_INTNUM T_DOTDOT T_INTNUM\n");		
		  #endif
		  int *arr = malloc(sizeof(int)*2);
		  arr[0] = -(yyvsp[-3].ival);
		  arr[1] = -(yyvsp[0].ival);
		  (yyval.iarrval) = arr;
		}
#line 2073 "PJParser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 721 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Procedures : Procedures ProcedureDecl\n");		
		  #endif
		}
#line 2083 "PJParser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 727 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Procedures :\n");		
		  #endif
		}
#line 2093 "PJParser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 735 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "ProcedureDecl : ProcedureHead ProcedureBody\n");		
		  #endif
		  if (isFunc) {
			SymTable sym_tab = pop_scope();
			if ((int)SymGetField(sym_tab, (char *)frame_lvl_name, SYMTAB_OFFSET_FIELD) == 1) {
				isFunc = 0;
			}
			kill_scope(sym_tab);
		  }
		}
#line 2110 "PJParser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 750 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "ProcedureHead : FunctionDecl Decls\n");		
		  #endif
		  ins_func_init_local();
		  loc_nmemb = 0;
		  loc_sp = 0;
		}
#line 2123 "PJParser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 761 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "FunctionDecl : T_FUNCTION T_IDENTIFIER T_COLON StandardType T_SEMICOLON\n");		
		  #endif
		  isFunc = 1;
		  loc_nmemb = 0;
		  loc_sp = -4;
		  push_scope();
		  ins_func_label((yyvsp[-3].sval));
		  ins_func_prologue();

		}
#line 2140 "PJParser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 776 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "ProcedureBody : CompoundStatement T_SEMICOLON\n");		
		  #endif
		}
#line 2150 "PJParser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 784 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Statement : Assignment\n");		
		  #endif
		}
#line 2160 "PJParser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 790 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Statement : IfStatement\n");		
		  #endif
		}
#line 2170 "PJParser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 796 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Statement : WhileStatement\n");		
		  #endif
		}
#line 2180 "PJParser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 802 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Statement : IOStatement\n");		
		  #endif
		}
#line 2190 "PJParser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 808 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Statement : ExitStatement\n");		
		  #endif

		}
#line 2201 "PJParser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 815 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Statement : CompoundStatement\n");		
		  #endif
		}
#line 2211 "PJParser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 823 "PJParser.y" /* yacc.c:1646  */
    { 
		  #ifdef PROJECT1
		  fprintf(stderr, "Assignment : Variable T_ASSIGN Expr\n");		
		  #endif
		  ins_assign((yyvsp[-2].ival), (yyvsp[0].ival));

		  // This is the end of this statement so we push both regs
		  push_reg((yyvsp[0].ival));
		  push_reg((yyvsp[-2].ival));

		}
#line 2227 "PJParser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 837 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "IfStatement : T_IF TestAndThen T_ELSE Statement\n");		
		  #endif

		  ins_label((yyvsp[-2].ival));
		}
#line 2239 "PJParser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 845 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "IfStatement : T_IF TestAndThen\n");		
		  #endif

		  ins_label((yyvsp[0].ival));
		}
#line 2251 "PJParser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 855 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "TestAndThen : Test T_THEN Statement\n");		
		  #endif

		  unsigned int label_index = genLabel();
		  end_control(label_index, (yyvsp[-2].ival));

		  (yyval.ival) = label_index;
	    }
#line 2266 "PJParser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 868 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Test : Expr \n");	
		  #endif
		  unsigned int const_reg = pop_reg();
		  unsigned int label_index = genLabel();

		  start_control(const_reg, (yyvsp[0].ival), label_index);

		  push_reg(const_reg);
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = label_index;
		}
#line 2285 "PJParser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 885 "PJParser.y" /* yacc.c:1646  */
    {
		  // WhileToken - label index for top of loop
		  // WhileExpr - label index for loop escape
		  #ifdef PROJECT1
		  fprintf(stderr, "WhileStatement : WhileToken WhileExpr T_DO Statement\n");		
		  #endif
		  end_control((yyvsp[-3].ival), (yyvsp[-2].ival));
		}
#line 2298 "PJParser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 896 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "WhileExpr : Expr \n");		
		  #endif

		  unsigned int const_reg = pop_reg();
		  unsigned int label_index = genLabel();

		  start_control(const_reg, (yyvsp[0].ival), label_index);

		  push_reg(const_reg);
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = label_index;
		}
#line 2318 "PJParser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 914 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "WhileToken : T_WHILE\n");		
		  #endif
		  unsigned int label_index = genLabel();
		  ins_label(label_index);

		  (yyval.ival) = label_index;
		}
#line 2332 "PJParser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 926 "PJParser.y" /* yacc.c:1646  */
    { 
		  #ifdef PROJECT1
		  fprintf(stderr, "IOStatement : T_READ T_LPAREN Variable T_RPAREN\n");		
		  #endif
		  
		  // Generate a scanf instruction
		  ins_scanf((yyvsp[-1].ival));

		  // No longer need this register
		  push_reg((yyvsp[-1].ival));


		}
#line 2350 "PJParser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 940 "PJParser.y" /* yacc.c:1646  */
    { 
		  #ifdef PROJECT1
		  fprintf(stderr, "IOStatement : WriteToken T_LPAREN Expr OutputFormat T_RPAREN\n");		
		  #endif

		  // FORMAT STRING SECTION

		  // Generate format string for print statement (newline and outputformat)
		  char fStr[8];
		  if ((yyvsp[-1].ival)) {
			if (snprintf(fStr, 8, "%%%dd", (yyvsp[-1].ival)) < 0) {
				perror("IOStatement");
				exit(1);
			}
		  } else {
			strcpy(fStr, "%d");
		  }

		  // Add format string to global Symbol Table and dataList if not already there
		  if (SymQueryIndex(global_symTab, fStr) == SYM_INVALID_INDEX) {
		  	addStringConst(fStr);
		  }

		  // INSTRUCTION SECTION

		  // Add printf instruction that outputs the provided string formatted
		  ins_printf_int(fStr, (yyvsp[-2].ival));
		  if ((yyvsp[-4].ival)) {
			ins_printf_newline();
		  }

		  // No longer needed
		  push_reg((yyvsp[-2].ival));

		  

		}
#line 2392 "PJParser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 978 "PJParser.y" /* yacc.c:1646  */
    { 
		  #ifdef PROJECT1
		  fprintf(stderr, "IOStatement : WriteToken T_LPAREN T_STRING OutputFormat T_RPAREN\n");		
		  #endif

		  // CONSTANT STRING SECTION

		  // Remove quotes
		  char temp_str[TEMP_STR_LEN];
		  removeQuotes(temp_str, (yyvsp[-2].sval));
		  
		  // Add T_STRING to global Symbol Table and dataList if not already there
		  if (SymQueryIndex(global_symTab, temp_str) == SYM_INVALID_INDEX) {
		  	addStringConst(temp_str);
		  }

		  // FORMAT STRING SECTION

		  // Generate format string for print statement (newline and outputformat)
		  char fStr[8];
		  if ((yyvsp[-1].ival)) {
			if (snprintf(fStr, 8, "%%%ds", (yyvsp[-1].ival)) < 0) {
				perror("IOStatement");
			}
		  } else {
			strcpy(fStr, "%s");
		  }

		  // Add format string to global Symbol Table and dataList if not already there
		  if (SymQueryIndex(global_symTab, fStr) == SYM_INVALID_INDEX) {
		  	addStringConst(fStr);
		  }


		  // INSTRUCTION SECTION

		  // Add printf instruction that outputs the provided string formatted
		  ins_printf_string(fStr, temp_str);
		  if ((yyvsp[-4].ival)) {
			ins_printf_newline();
		  }

		}
#line 2440 "PJParser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1024 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "OutputFormat : T_COLON T_INTNUM\n");		
		  #endif
		  (yyval.ival) = (yyvsp[0].ival);
		}
#line 2451 "PJParser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1031 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "OutputFormat : \n");		
		  #endif
		  (yyval.ival) = 0;
		}
#line 2462 "PJParser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1040 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "WriteToken : T_WRITE\n");		
		  #endif
		  (yyval.ival) = 0;
		}
#line 2473 "PJParser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1047 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "WriteToken : T_WRITELN\n");		
		  #endif
		  (yyval.ival) = 1;
		}
#line 2484 "PJParser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1056 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "ExitStatement : T_EXIT T_LPAREN Expr T_RPAREN\n");		
		  #endif
		  if (isFunc) {
			ins_func_ret_val((yyvsp[-1].ival));
			ins_func_epilogue();
			push_reg((yyvsp[-1].ival));
		  }
		}
#line 2499 "PJParser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1069 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "CompoundStatement : T_BEGIN StatementList T_END\n");		
		  #endif
		}
#line 2509 "PJParser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1077 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "StatementList : StatementList T_SEMICOLON Statement\n");		
		  #endif
		}
#line 2519 "PJParser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1083 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "StatementList : Statement\n");		
		  #endif
		}
#line 2529 "PJParser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1092 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : AddExpr\n");		
		  #endif
		  (yyval.ival) = (yyvsp[0].ival); // No change needed
		}
#line 2540 "PJParser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1099 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : Expr T_EQ AddExpr\n");		
		  #endif
		  
		  // Add instruction: operand 1 is turned to pos if (operand 1 == operand 2)
		  ins_eq((yyvsp[-2].ival), (yyvsp[0].ival));

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = (yyvsp[-2].ival);
		}
#line 2558 "PJParser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1113 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : Expr T_NE AddExpr\n");		
		  #endif

		  // Add instruction: operand 1 is turned to pos if (operand 1 != operand 2)
		  ins_neq((yyvsp[-2].ival), (yyvsp[0].ival));

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = (yyvsp[-2].ival);

		}
#line 2577 "PJParser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1128 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : Expr T_LE AddExpr\n");		
		  #endif

		  // Add instruction: operand 1 is turned to pos if (operand 1 <= operand 2)
		  ins_le((yyvsp[-2].ival), (yyvsp[0].ival));

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = (yyvsp[-2].ival);

		}
#line 2596 "PJParser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1143 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : Expr T_LT AddExpr\n");		
		  #endif

		  // Add instruction: operand 1 is turned to pos if (operand 1 < operand 2)
		  ins_lt((yyvsp[-2].ival), (yyvsp[0].ival));

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = (yyvsp[-2].ival);

		}
#line 2615 "PJParser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1158 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : Expr T_GE AddExpr\n");		
		  #endif

		  // Add instruction: operand 1 is turned to pos if (operand 1 >= operand 2)
		  ins_ge((yyvsp[-2].ival), (yyvsp[0].ival));

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = (yyvsp[-2].ival);
		}
#line 2633 "PJParser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1172 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : Expr T_GT AddExpr\n");		
		  #endif

		  // Add instruction: operand 1 is turned to pos if (operand 1 > operand 2)
		  ins_gt((yyvsp[-2].ival), (yyvsp[0].ival));

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = (yyvsp[-2].ival);
		}
#line 2651 "PJParser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1188 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "AddExpr : MulExpr\n");		
		  #endif
		  (yyval.ival) = (yyvsp[0].ival); // No change needed
		}
#line 2662 "PJParser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1195 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "AddExpr : AddExpr T_OR MulExpr\n");		
		  #endif

		  // Add instruction to perform a bitwise OR operation operand 1 and operand 2
		  ins_or((yyvsp[-2].ival), (yyvsp[0].ival));

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = (yyvsp[-2].ival);
		}
#line 2680 "PJParser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1209 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "AddExpr : AddExpr T_PLUS MulExpr\n");		
		  #endif

		  // Add instruction to add our two operands
		  ins_addReg((yyvsp[-2].ival), (yyvsp[0].ival));

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = (yyvsp[-2].ival);
		}
#line 2698 "PJParser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1223 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "AddExpr : AddExpr T_MINUS MulExpr\n");		
		  #endif
		  
		  // Add instruction to subract the 2nd operand from the first
		  ins_subReg((yyvsp[-2].ival), (yyvsp[0].ival));

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = (yyvsp[-2].ival);
		}
#line 2716 "PJParser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1239 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "MulExpr : Factor\n");
		  #endif
		  (yyval.ival) = (yyvsp[0].ival); // No change necessary
        }
#line 2727 "PJParser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1246 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "MulExpr : MulExpr T_TIMES Factor\n");
		  #endif
		  
		  // Add instruction to multiply our two operands
		  ins_multReg((yyvsp[-2].ival), (yyvsp[0].ival));

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = (yyvsp[-2].ival);
		}
#line 2745 "PJParser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1260 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "MulExpr : MulExpr T_DIV Factor\n");		
		  #endif
		  
		  // Add instruction to divide operand 1 by operand 2
		  ins_divReg((yyvsp[-2].ival), (yyvsp[0].ival));

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = (yyvsp[-2].ival);
		}
#line 2763 "PJParser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1274 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "MulExpr : MulExpr T_AND Factor\n");		
		  #endif
		  
		  // Add instruction to bitwise AND operand 1 and operand 2
		  ins_and((yyvsp[-2].ival), (yyvsp[0].ival));

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = (yyvsp[-2].ival);
		}
#line 2781 "PJParser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1291 "PJParser.y" /* yacc.c:1646  */
    { 
		  #ifdef PROJECT1
		  fprintf(stderr, "Factor : Variable\n");		
		  #endif

		  // We pop a register to hold the value in the variable
		  unsigned int reg = pop_reg();

		  ins_loadVarValue((yyvsp[0].ival), reg);

		  // The mem_reg is no longer necessary so we push it
		  push_reg((yyvsp[0].ival));

		  (yyval.ival) = reg;
		}
#line 2801 "PJParser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1307 "PJParser.y" /* yacc.c:1646  */
    { 
		  #ifdef PROJECT1
		  fprintf(stderr, "Factor : Constant\n");		
		  #endif
		  (yyval.ival) = (yyvsp[0].ival); // No change necessary
		}
#line 2812 "PJParser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1314 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Factor : T_NOT Factor\n");		
		  #endif

		  // Add an instruction which inverts (NOT) the current register
		  ins_not((yyvsp[0].ival));

		  (yyval.ival) = (yyvsp[0].ival);
		}
#line 2827 "PJParser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1325 "PJParser.y" /* yacc.c:1646  */
    {					
		  #ifdef PROJECT1
		  fprintf(stderr, "Factor : T_IDENTIFIER T_LPAREN T_RPAREN\n");		
		  #endif
		  unsigned int ret_reg = pop_reg();
		  ins_func_call((yyvsp[-2].sval), ret_reg);
		  (yyval.ival) = ret_reg;
		}
#line 2840 "PJParser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1334 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Factor : T_LPAREN Expr T_RPAREN\n");		
		  #endif
		  (yyval.ival) = (yyvsp[-1].ival); // No change necessary
		}
#line 2851 "PJParser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1345 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Variable : T_IDENTIFIER\n");		
		  #endif
		  // Pop the necessary registers to load global memory
		  unsigned int mem_reg = pop_reg();

		  // Add Instructions
		  ins_loadVar((yyvsp[0].sval), mem_reg);

		  (yyval.ival) = mem_reg;
		}
#line 2868 "PJParser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1358 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Variable : T_IDENTIFIER T_LBRACKET Expr T_RBRACKET\n");		
		  #endif
		  // Pop the necessary registers to load global memory
		  unsigned int mem_reg = pop_reg();

		  // Add Instructions
		  load_1dim_arr((yyvsp[-3].sval), (yyvsp[-1].ival), mem_reg);

		  push_reg((yyvsp[-1].ival));

		  (yyval.ival) = mem_reg;
        }
#line 2887 "PJParser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1373 "PJParser.y" /* yacc.c:1646  */
    {
		  #ifdef PROJECT1
		  fprintf(stderr, "Variable  : T_IDENTIFIER T_LBRACKET Expr T_COMMA Expr T_RBRACKET\n");		
		  #endif

		  // Pop the necessary registers to load global memory
		  unsigned int mem_reg = pop_reg();

		  // Add Instructions
		  load_2dim_arr((yyvsp[-5].sval), (yyvsp[-3].ival), (yyvsp[-1].ival), mem_reg);

		  push_reg((yyvsp[-3].ival));
		  push_reg((yyvsp[-1].ival));

		  (yyval.ival) = mem_reg;

        }
#line 2909 "PJParser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1394 "PJParser.y" /* yacc.c:1646  */
    { 
		  #ifdef PROJECT1
		  fprintf(stderr, "Constant : T_FLOATNUM\n");	
		  #endif
		}
#line 2919 "PJParser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1400 "PJParser.y" /* yacc.c:1646  */
    {   
		  #ifdef PROJECT1
		  fprintf(stderr, "Constant : T_MINUS T_INTNUM\n");		
		  #endif

		  // Get free register
		  unsigned int reg = pop_reg();

		  // Load negative of constant value into register
		  ins_loadImm(-((yyvsp[0].ival)), reg);
		  
		  (yyval.ival) = reg;
		}
#line 2937 "PJParser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1414 "PJParser.y" /* yacc.c:1646  */
    { 
		  #ifdef PROJECT1
		  fprintf(stderr, "Constant : T_INTNUM\n");
		  #endif
		  
		  // Get free register
		  unsigned int reg = pop_reg();

		  // Load constant value into register
		  ins_loadImm((yyvsp[0].ival), reg);
		  
		  (yyval.ival) = reg;
		}
#line 2955 "PJParser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1428 "PJParser.y" /* yacc.c:1646  */
    { 
		  #ifdef PROJECT1
		  fprintf(stderr, "Constant : T_TRUE\n");		
		  #endif
		 
		  // Get free register
		  unsigned int reg = pop_reg();

		  // Load true (1) into register
		  ins_loadImm(1, reg);
		  
		  (yyval.ival) = reg;
		}
#line 2973 "PJParser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1442 "PJParser.y" /* yacc.c:1646  */
    { 
		  #ifdef PROJECT1
		  fprintf(stderr, "Constant : T_FALSE\n");		
		  #endif
		 
		  // Get free register
		  unsigned int reg = pop_reg();

		  // Load false (0) into register
		  ins_loadImm(0, reg);
		  
		  (yyval.ival) = reg;
		}
#line 2991 "PJParser.c" /* yacc.c:1646  */
    break;


#line 2995 "PJParser.c" /* yacc.c:1646  */
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
#line 1457 "PJParser.y" /* yacc.c:1906  */



/********************C ROUTINES *********************************/
void yyerror(char *s)
{
  fprintf(stderr,"%s: line %d, found %s: %s\n",fileindex,yylineno,yytext,s);
}

int yywrap() {
	return 1;
}

static void initialize(char* inputFileindex) {
	yyin = fopen(inputFileindex,"r");
        if (yyin == NULL) {
          fprintf(stderr,"Error: Could not open file %s\n",inputFileindex);
          exit(-1);
        }
// REDIRECT ALL STDOUT OUTPUT TO 'outputFileindex'
#ifdef FILE_OUTPUT
	char* dotChar = rindex(inputFileindex,'.');
	int endIndex = strlen(inputFileindex) - strlen(dotChar);
	char *outputFileindex = nssave(2,substr(inputFileindex,0,endIndex),".s");
	stdout = freopen(outputFileindex,"w",stdout);
        if (stdout == NULL) {
          fprintf(stderr,"Error: Could not open file %s\n",outputFileindex);
          exit(-1);
        }
#endif

	frame_lvl = 0;
	symStack = symtabStackInit();
	global_symTab = push_scope();

	// Initialize the instruction DLinkLists
	iList = dlinkListAlloc((Generic*)iList_atom);
	dataList = dlinkListAlloc((Generic*)dataList_atom);
	assList = dlinkListAlloc((Generic*)assList_atom);
	rStack = dlinkListAlloc((Generic*)rStack_atom);
	funcList = dlinkListAlloc((Generic*)rStack_atom);
	iList_init();
	dataList_init();
	rStack_init();
	// Nothing in funcList needs to be initialized
	glob_nmemb = 0;
	next_str_sym_id = 2;
	isFunc = 0;
}

static void finalize() {
	// Free up the global symbol table
	SymTable sym_tab = pop_scope();
	kill_scope(sym_tab);


    fclose(yyin);
#ifdef FILE_OUTPUT
    fclose(stdout); //uncomment this line for Project 2
#endif
	// Free dlinkLists
	// [ don't need to free iList, dataList, and funcList node's because they're contents are in assList]
	dlinkFreeNodesAndAtoms(assList);
	dlinkFreeNodes(rStack);
	dlinkListFree(iList);
	dlinkListFree(dataList);
	dlinkListFree(assList);
	dlinkListFree(rStack);
	// SymTabStack is just a alias for DLinkList
	dlinkListFree((DLinkList *)funcList);
}

int main(int argc, char** argv)

{	
	fileindex = argv[1];
	initialize(fileindex);


	yyparse();
    
	finalize();
  
	return 0;
}

// Scope Management Functions

static SymTable push_scope () {
	SymTable scope_symTab = beginScope(symStack);
	// These are the symbol table fields I use for symbol tables
	SymInitField(scope_symTab, SYMTAB_TYPE_FIELD, (Generic)-1, NULL);
	SymInitField(scope_symTab, SYMTAB_OFFSET_FIELD, (Generic)-1, NULL);
	SymInitField(scope_symTab, SYMTAB_SCLASS_FIELD, (Generic)-1, NULL);
	SymInitField(scope_symTab, SYMTAB_VALUE_FIELD, (Generic)-1, NULL);

	setOffset((char *)frame_lvl_name, frame_lvl++, 0);
	return scope_symTab;
}

static SymTable pop_scope () {
	SymTable scope_symTab = endScope(symStack);
	// DEBUG
	#ifdef DEBUG_SYMTABLE
	SymDump(scope_symTab);
	#endif
	frame_lvl--;
	return scope_symTab;
}

static void kill_scope (SymTable scope_symTab) {
	SymKillField(scope_symTab,SYMTAB_TYPE_FIELD);
	SymKillField(scope_symTab,SYMTAB_OFFSET_FIELD);
	SymKillField(scope_symTab,SYMTAB_SCLASS_FIELD);
	SymKillField(scope_symTab,SYMTAB_VALUE_FIELD);
    SymKill(scope_symTab);
}

static void ins_func_label (char *str) {
	char temp_str[TEMP_STR_LEN];
	sprintf(temp_str, str_func_label, str);
	add_instructions(temp_str);
}

		  
static void ins_func_prologue() {
	add_instructions((char *)str_func_prologue);
}

static void ins_func_epilogue() {
	add_instructions((char *)str_func_epilogue);
}

static void ins_func_init_local () {
	char temp_str[TEMP_STR_LEN];
	sprintf(temp_str, str_func_init_local, loc_nmemb*DATA_SIZE);
	add_instructions(temp_str);
}

static void ins_func_ret_val (int ret_reg) {
	char temp_str[TEMP_STR_LEN];
	char ret_reg_str[REG_STR];
	regToStr(ret_reg_str, ret_reg, false);
	sprintf(temp_str, str_func_return_val, ret_reg_str);
	add_instructions(temp_str);
}

// Haven't implemented args yet.
static void ins_func_call(char *func_name, unsigned int ret_reg) {
	char temp_str[TEMP_STR_LEN];
	char reg_str[REG_STR];
	for (unsigned int i = 0; i < reg_count; i++) { // ret_reg is one larger than the highest register value in reg_arr
		if (reg_out_arr[i]) {
			regToStr(reg_str, i, true);
			sprintf(temp_str, str_push_reg, reg_str);
			add_instructions(temp_str);
		}
	}
	sprintf(temp_str, str_call_func, func_name);
	add_instructions(temp_str);
	for (int i = reg_count-1; i >= 0; i--) {
		if (reg_out_arr[i]) {
			regToStr(reg_str, (unsigned int)i, true);
			sprintf(temp_str, str_pop_reg, reg_str);
			add_instructions(temp_str);
		}
	}
	// At this point, the return value of the called function should be in %eax
	regToStr(reg_str, ret_reg, false);
	sprintf(temp_str, str_move_return, reg_str);
	add_instructions(temp_str);
	// The value returned from the called function should now be in ret_reg
}




// INSTRUCTIONS

static void ins_loadVar (char *name, unsigned int mem_reg) {
	char temp_str[TEMP_STR_LEN];
	int offset = getOffset(name);
	char mem_reg_str[REG_STR];
	if (isGlobal(name)) {
		regToStr(mem_reg_str, mem_reg, true);
		sprintf(temp_str, str_loadVar, mem_reg_str, offset, mem_reg_str);
		add_instructions(temp_str);
	} else {
		// Too be implemented: derefrecing access pointers (and access links)
		regToStr(mem_reg_str, mem_reg, true);
		sprintf(temp_str, str_loadVar_loc, mem_reg_str, offset, mem_reg_str);
		add_instructions(temp_str);
	}

}

static void ins_loadVarValue (unsigned int mem_reg, unsigned int reg) {
	char temp_str[TEMP_STR_LEN];
	char mem_reg_str[REG_STR];
	char reg_str[REG_STR];
	regToStr(mem_reg_str, mem_reg, true);
	regToStr(reg_str, reg, false);
	sprintf(temp_str, str_loadVarValue, mem_reg_str, reg_str);
	add_instructions(temp_str);
}

static void ins_loadImm_64 (int imm, unsigned int reg) {
	char temp_str[TEMP_STR_LEN];
	char reg_str[REG_STR];
	regToStr(reg_str, reg, true);
	sprintf(temp_str, str_loadImm_64, imm, reg_str);
	add_instructions(temp_str);
}

static void ins_loadImm (int imm, unsigned int reg) {
	char temp_str[TEMP_STR_LEN];
	char reg_str[REG_STR];
	regToStr(reg_str, reg, false);
	sprintf(temp_str, str_loadImm, imm, reg_str);
	add_instructions(temp_str);
}

static void ins_addReg (unsigned int reg1, unsigned int reg2) {
	char temp_str[TEMP_STR_LEN];
	char reg1_str[REG_STR];
	char reg2_str[REG_STR];
	regToStr(reg1_str, reg1, false);
	regToStr(reg2_str, reg2, false);
	sprintf(temp_str, str_addReg, reg2_str, reg1_str);
	add_instructions(temp_str);
}

static void ins_addReg_64 (unsigned int reg1, unsigned int reg2) {
	char temp_str[TEMP_STR_LEN];
	char reg1_str[REG_STR];
	char reg2_str[REG_STR];
	regToStr(reg1_str, reg1, true);
	regToStr(reg2_str, reg2, true);
	sprintf(temp_str, str_addReg_64, reg2_str, reg1_str);
	add_instructions(temp_str);
}

static void ins_subReg (unsigned int min_reg, unsigned int sub_reg) {
	char temp_str[TEMP_STR_LEN];
	char min_str[REG_STR];
	char sub_str[REG_STR];
	regToStr(min_str, min_reg, false);
	regToStr(sub_str, sub_reg, false);
	sprintf(temp_str, str_sub, sub_str, min_str);
	add_instructions(temp_str);
}

static void ins_subReg_64 (unsigned int reg1, unsigned int reg2) {
	char temp_str[TEMP_STR_LEN];
	char reg1_str[REG_STR];
	char reg2_str[REG_STR];
	regToStr(reg1_str, reg1, true);
	regToStr(reg2_str, reg2, true);
	sprintf(temp_str, str_sub_64, reg2_str, reg1_str);
	add_instructions(temp_str);
}

static void ins_multReg (unsigned int reg1, unsigned int reg2) {
	char temp_str[TEMP_STR_LEN];
	char reg1_str[REG_STR];
	char reg2_str[REG_STR];
	regToStr(reg1_str, reg1, false);
	regToStr(reg2_str, reg2, false);
	sprintf(temp_str, str_multReg, reg2_str, reg1_str);
	add_instructions(temp_str);
}

static void ins_divReg (unsigned int dividend_reg, unsigned int divisor_reg) {
	char temp_str[TEMP_STR_LEN];
	char divisor_str[REG_STR];
	char dividend_str[REG_STR];
	regToStr(divisor_str, divisor_reg, false);
	regToStr(dividend_str, dividend_reg, false);
	sprintf(temp_str, str_divReg, dividend_str, divisor_str, dividend_str);
	add_instructions(temp_str);
}

static void ins_not (unsigned reg) {
	char temp_str[TEMP_STR_LEN];
	char reg_str[REG_STR];
	regToStr(reg_str, reg, false);
	sprintf(temp_str, str_not, reg_str, reg_str);
	add_instructions(temp_str);
}

static void ins_and (unsigned int reg1, unsigned int reg2) {
	char temp_str[TEMP_STR_LEN];
	char reg1_str[REG_STR];
	char reg2_str[REG_STR];
	regToStr(reg1_str, reg1, false);
	regToStr(reg2_str, reg2, false);
	sprintf(temp_str, str_and, reg2_str, reg1_str);
	add_instructions(temp_str);
}

static void ins_or (unsigned int reg1, unsigned int reg2) {
	char temp_str[TEMP_STR_LEN];
	char reg1_str[REG_STR];
	char reg2_str[REG_STR];
	regToStr(reg1_str, reg1, false);
	regToStr(reg2_str, reg2, false);
	sprintf(temp_str, str_or, reg2_str, reg1_str);
	add_instructions(temp_str);
}

static void ins_gt (unsigned int reg1, unsigned int reg2) {
	char temp_str[TEMP_STR_LEN];
	char reg1_str[REG_STR];
	char reg2_str[REG_STR];
	regToStr(reg1_str, reg1, false);
	regToStr(reg2_str, reg2, false);
	sprintf(temp_str, str_gt_or_lt, reg2_str, reg1_str, reg1_str, reg2_str, reg2_str, reg1_str);
	add_instructions(temp_str);
}

static void ins_ge (unsigned int reg1, unsigned int reg2) {
	char temp_str[TEMP_STR_LEN];
	char reg1_str[REG_STR];
	char reg2_str[REG_STR];
	regToStr(reg1_str, reg1, false);
	regToStr(reg2_str, reg2, false);
	sprintf(temp_str, str_ge_or_le, reg2_str, reg1_str, reg1_str, reg2_str, reg2_str, reg1_str, reg2_str, reg1_str);
	add_instructions(temp_str);
}

static void ins_lt (unsigned int reg1, unsigned int reg2) {
	char temp_str[TEMP_STR_LEN];
	char reg1_str[REG_STR];
	char reg2_str[REG_STR];
	regToStr(reg1_str, reg1, false);
	regToStr(reg2_str, reg2, false);
	sprintf(temp_str, str_gt_or_lt, reg1_str, reg2_str, reg1_str, reg2_str, reg2_str, reg1_str);
	add_instructions(temp_str);
}

static void ins_le (unsigned int reg1, unsigned int reg2) {
	char temp_str[TEMP_STR_LEN];
	char reg1_str[REG_STR];
	char reg2_str[REG_STR];
	regToStr(reg1_str, reg1, false);
	regToStr(reg2_str, reg2, false);
	sprintf(temp_str, str_ge_or_le, reg1_str, reg2_str, reg1_str, reg2_str, reg2_str, reg1_str, reg2_str, reg1_str);
	add_instructions(temp_str);
}

static void ins_eq (unsigned int reg1, unsigned int reg2) {
	char temp_str[TEMP_STR_LEN];
	char reg1_str[REG_STR];
	char reg2_str[REG_STR];
	regToStr(reg1_str, reg1, false);
	regToStr(reg2_str, reg2, false);
	sprintf(temp_str, str_eq, reg2_str, reg1_str, reg1_str, reg2_str, reg2_str, reg1_str);
	add_instructions(temp_str);
}

static void ins_neq (unsigned int reg1, unsigned int reg2) {
	char temp_str[TEMP_STR_LEN];
	char reg1_str[REG_STR];
	char reg2_str[REG_STR];
	regToStr(reg1_str, reg1, false);
	regToStr(reg2_str, reg2, false);
	sprintf(temp_str, str_neq, reg2_str, reg1_str, reg1_str, reg2_str, reg2_str, reg1_str);
	add_instructions(temp_str);
}

static void ins_printf_string (char *fstr, char *str) {
	char temp_str[TEMP_STR_LEN];
	int offset1 = (int)getOffset(fstr);
	int offset2 = (int)getOffset(str);
	sprintf(temp_str, str_printf_string, offset1, offset2);
	add_instructions(temp_str);
}

static void ins_printf_int (char *str, unsigned int reg) {
	char temp_str[TEMP_STR_LEN];
	char reg_str[REG_STR];
	int offset = (int)getOffset(str);
	regToStr(reg_str, reg, false);
	sprintf(temp_str, str_printf_int, offset, reg_str);
	add_instructions(temp_str);
}

static void ins_printf_newline () {
	add_instructions((char *)str_printf_nl);
}

static void ins_scanf (unsigned int reg) {
	char temp_str[TEMP_STR_LEN];
	char reg_str[REG_STR];
	regToStr(reg_str, reg, true);
	sprintf(temp_str, str_scanf, reg_str);
	add_instructions(temp_str);
}

static void ins_assign (unsigned int mem_reg, unsigned int reg) {
	char temp_str[TEMP_STR_LEN];
	char mem_reg_str[REG_STR];
	char reg_str[REG_STR];
	regToStr(mem_reg_str, mem_reg, true);
	regToStr(reg_str, reg, false);
	sprintf(temp_str, str_assign, reg_str, mem_reg_str);
	add_instructions(temp_str);
}

static void ins_label (unsigned int label_index) {
	char temp_str[TEMP_STR_LEN];
	sprintf(temp_str, str_label, label_index);
	add_instructions(temp_str);
}

static void ins_test (unsigned int const_reg, unsigned int cond_reg) {
	char temp_str[TEMP_STR_LEN];
	char const_reg_str[REG_STR];
	char cond_reg_str[REG_STR];
	regToStr(const_reg_str, const_reg, false);
	regToStr(cond_reg_str, cond_reg, false);
	sprintf(temp_str, str_test, const_reg_str, cond_reg_str);
	add_instructions(temp_str);
}

static void ins_jumpeq (unsigned int label_index) {
	char temp_str[TEMP_STR_LEN];
	sprintf(temp_str, str_jumpeq, label_index);
	add_instructions(temp_str);
}

static void ins_jump (unsigned int label_index) {
	char temp_str[TEMP_STR_LEN];
	sprintf(temp_str, str_jump, label_index);
	add_instructions(temp_str);
}

static void ins_32To64 (unsigned int reg) {
	char temp_str[TEMP_STR_LEN];
	char reg32_str[REG_STR];
	char reg64_str[REG_STR];
	regToStr(reg32_str, reg, false);
	regToStr(reg64_str, reg, true);
	sprintf(temp_str, str_32To64, reg32_str, reg64_str);
	add_instructions(temp_str);
}

static void start_control (unsigned int const_reg, unsigned int cond_reg, unsigned int label_index) {
	// movl, test, je
	ins_loadImm(-1, const_reg);
	ins_test(const_reg, cond_reg);
	ins_jumpeq(label_index);
}


static void end_control (unsigned int end_ifelse_label_index, unsigned int start_else_label_index) {
	ins_jump(end_ifelse_label_index);
	ins_label(start_else_label_index);
}

static void load_1dim_arr(char *name, unsigned int i_reg, unsigned int res_addr_reg) {
	struct ArrayDim *dim = getValue(name);
	unsigned int offset = getOffset(name);
	unsigned int imm_reg = pop_reg();
	// Get array base pointer
	ins_loadVar(name, res_addr_reg);

	//ins_loadImm_64(dim->dim1_s*DATA_SIZE, imm_reg); // Load size of arr in imm_reg
	//ins_subReg_64(res_addr_reg, imm_reg); // Get to base of arr
	//ins_addReg_64(res_addr_reg, imm_reg); // Get to base of arr

	// Adjust i_reg value for start index
	ins_loadImm(dim->dim1_l, imm_reg); // Get start index of arr
	ins_subReg(i_reg, imm_reg); // Adjust i_reg
	// Turn index offset to addr offset
	ins_loadImm(DATA_SIZE, imm_reg);
	ins_multReg(i_reg, imm_reg);
	// Get address of value
	ins_32To64(i_reg); // Conversion to addr size
	ins_addReg_64(res_addr_reg, i_reg); // Put addr of val into res_addr_reg
	push_reg(imm_reg);
}

static void load_2dim_arr(char *name, unsigned int i_reg, unsigned int j_reg, unsigned int res_addr_reg) {
	struct ArrayDim *dim = getValue(name);
	unsigned int offset = getOffset(name);
	unsigned int imm_reg = pop_reg();
	// Get array base pointer
	ins_loadVar(name, res_addr_reg);
	//ins_loadImm_64((dim->dim2_s)*(dim->dim1_s)*DATA_SIZE, imm_reg); // Load size of arr in imm_reg
	//ins_subReg_64(res_addr_reg, imm_reg); // res_addr_reg <- base pointer
	// Adjust i_reg value for start index and move down i rows
	ins_loadImm(dim->dim1_l, imm_reg);
	ins_subReg(i_reg, imm_reg);
	ins_loadImm(dim->dim2_s, imm_reg);
	ins_multReg(i_reg, imm_reg);
	// Add adjusted j to i (i = i + j - dim2_l)
	ins_addReg(i_reg, j_reg);
	ins_loadImm(dim->dim2_l, imm_reg);
	ins_subReg(i_reg, imm_reg);
	// Turn index offset to addr offset
	ins_loadImm(DATA_SIZE, imm_reg);
	ins_multReg(i_reg, imm_reg);
	// Get address of value
	ins_32To64(i_reg);
	ins_addReg_64(res_addr_reg, i_reg);
	push_reg(imm_reg);

}

static void ins_end_program () {
	add_instructions((char*)str_end_program);
}

static void initStringSym (char *str) {
	char name[TEMP_STR_LEN];
	sprintf(name, string_ref, next_str_sym_id);
	setSClass(str, GLOBAL, 1);
	setType(str, PSEUDOTYPE_STRING, 1);
	setValue(str, name, 1); // .stringconst(num)
	setOffset(str, next_str_sym_id, 1);
	next_str_sym_id++;
}

static void initVarSym (char *name, int type) {
	if (!isFunc) {
		setType(name, type, 1);
		setSClass(name, GLOBAL, 1);
		setOffset(name, (glob_nmemb++*DATA_SIZE), 1);
	} else {
		setType(name, type, 0);
		setSClass(name, STACK, 0);
		setOffset(name, (loc_sp), 0);
		loc_nmemb++;
		loc_sp -= 4;
	}
}

// Put 1 in dim2_r and dim2_l if it's a one-dim array
static void initArraySym (char *name, int type, int dim1_l, int dim1_r, int dim2_l, int dim2_r) {
	int dim1_s = dim1_r - dim1_l + 1;
	int dim2_s = dim2_r - dim2_l + 1;

	// Record dimensions of array
	struct ArrayDim *dim_arr = malloc(sizeof(struct ArrayDim));
	if (!((dim2_l == 1) && (dim2_r == 1))) {
		// One dimensional
		dim_arr->dim_num = 2;
		dim_arr->dim2_l = dim2_l;
		dim_arr->dim2_r = dim2_r;
		dim_arr->dim2_s = dim2_s;
	} else {
		// Two dimensional
		dim_arr->dim_num = 1;
		dim_arr->dim2_l = 0;
		dim_arr->dim2_r = 0;
		dim_arr->dim2_s = 0;
	}
	dim_arr->dim1_l = dim1_l;
	dim_arr->dim1_r = dim1_r;
	dim_arr->dim1_s = dim1_s;

	if (!isFunc) {
		setType(name, type, 1);
		setSClass(name, GLOBAL, 1);
		// Set offset
		setOffset(name, (glob_nmemb*DATA_SIZE), 1);
		// Reserve space for the array
		glob_nmemb += (dim1_s*dim2_s);
		setValue(name, dim_arr, 1);
	} else {
		setType(name, type, 0);
		setSClass(name, STACK, 0);
		// Set offset
		// Reserve space for the array
		loc_nmemb += (dim1_s*dim2_s);
		loc_sp -= (dim1_s*dim2_s)*DATA_SIZE;
		setOffset(name, (loc_sp+4), 0);
		setValue(name, dim_arr, 0);
	}
}

// Instruction DLink Structure
// 		dataList contains readonly data: global vars, string constants
//		iList contains instructions to be exectuted
// Once the source file has been read, the two files are combined and
// printed

static void dataList_init () {
	char *_atom1;
	char *_atom2;
	char *_atom3;
	//char *_atom4;
	_atom1 = malloc(sizeof(char)*(strlen(dataList_init_string)+1));
	_atom2 = malloc(sizeof(char)*(strlen(scanf_format)+1));
	_atom3 = malloc(sizeof(char)*(strlen(newline_printf_format)+1));
	//_atom4 = malloc(sizeof(char)*(strlen(scanf_data)+1));
	strcpy(_atom1, dataList_init_string);
	strcpy(_atom2, scanf_format);
	strcpy(_atom3, newline_printf_format);
	//strcpy(_atom4, scanf_data);
	DLinkNode *node1 = dlinkNodeAlloc((Generic)_atom1);
	DLinkNode *node2 = dlinkNodeAlloc((Generic)_atom2);
	DLinkNode *node3 = dlinkNodeAlloc((Generic)_atom3);
	//DLinkNode *node4 = dlinkNodeAlloc((Generic)_atom4);
	dlinkAppend(dataList, node1);
	dlinkAppend(dataList, node2);
	dlinkAppend(dataList, node3);
	//dlinkAppend(dataList, node4);
}

/**
 *
 * Adds a string to the read-only constant section of assembly
 * @param atom: the string constant
 */
static void dataList_addStringConst (char *name) {
	char *_atom;
	_atom = malloc(sizeof(char)*(strlen((char*)name)+string_add_format_size+5));
	sprintf(_atom, string_add_format, getOffset(name), name);
	DLinkNode *node = dlinkNodeAlloc((Generic)_atom);
	dlinkAppend(dataList, node);
}

/**
 *
 * Adds the global pointer to the read-only constant section of assembly
 * @param nmemb: number of global vars
 * @param size: size of each global var
 */
static void dataList_addGlobalPointer (unsigned int nmemb, unsigned int size) {
	char *_atom;
	_atom = malloc(sizeof(char)*(gp_add_format_size+1));
	sprintf(_atom, gp_add_format, nmemb*size, size);
	DLinkNode *node = dlinkNodeAlloc((Generic)_atom);
	dlinkAppend(dataList, node);
}

static void iList_init () {
	char *_atom;
	_atom = malloc(sizeof(char)*(strlen(iList_init_string)+1));
	strcpy(_atom, iList_init_string);
	DLinkNode *node = dlinkNodeAlloc((Generic)_atom);
	dlinkAppend(iList, node);
}

static void add_instructions (char *ins) {
	char *_atom;
	_atom = malloc(sizeof(char)*(strlen(ins)+PADDING));
	strcpy(_atom, ins);
	DLinkNode *node = dlinkNodeAlloc((Generic)_atom);
	if (isFunc) {
		dlinkAppend(funcList, node);
	} else {
		dlinkAppend(iList, node);
	}
}

static void addStringConst (char *str) {
	initStringSym(str);
	dataList_addStringConst(str);
}

// rStack

static void rStack_init () {
	for (unsigned int i = 0; i < reg_count; i++) {
		DLinkNode *node = dlinkNodeAlloc((Generic)i);
		dlinkAppend(rStack, node);
	}
	memset(reg_out_arr, 0, reg_count);
}

static unsigned int pop_reg () {
	DLinkNode *head = dlinkHead(rStack);
	unsigned int ret_reg = (unsigned int)dlinkNodeAtom(head);
	reg_out_arr[ret_reg] = 1; // Mark the register that was popped
	dlinkRemove(head);
	dlinkFreeNode(head);
	return ret_reg;
}

static void push_reg (unsigned int reg) {
	reg_out_arr[reg] = 0; // Mark the register was pushed
	DLinkNode *node = dlinkNodeAlloc((Generic)reg);
	dlinkInsertBefore(node, dlinkHead(rStack));
}

// Note %eax and %edx are reserved for division
static char *regToStr (char *reg_str, unsigned int reg, bool is64) {
	if (is64) {
		switch (reg) {
			case 0: { strcpy(reg_str, "%rbx"); } break;
			case 1: { strcpy(reg_str, "%rcx"); } break;
			case 2: { strcpy(reg_str, "%r8"); } break;
			case 3: { strcpy(reg_str, "%r9"); } break;
			case 4: { strcpy(reg_str, "%r10"); } break;
			case 5: { strcpy(reg_str, "%r11"); } break;
			case 6: { strcpy(reg_str, "%r12"); } break;
			case 7: { strcpy(reg_str, "%r13"); } break;
			case 8: { strcpy(reg_str, "%r14"); } break;
			case 9: { strcpy(reg_str, "%r15"); } break;
			case 10: { strcpy(reg_str,"%rdi"); } break;
			case 11: { strcpy(reg_str,"%rsi"); } break;
		}
	} else {
		switch (reg) {
			case 0: { strcpy(reg_str, "%ebx"); } break;
			case 1: { strcpy(reg_str, "%ecx"); } break;
			case 2: { strcpy(reg_str, "%r8d"); } break;
			case 3: { strcpy(reg_str, "%r9d"); } break;
			case 4: { strcpy(reg_str, "%r10d"); } break;
			case 5: { strcpy(reg_str, "%r11d"); } break;
			case 6: { strcpy(reg_str, "%r12d"); } break;
			case 7: { strcpy(reg_str, "%r13d"); } break;
			case 8: { strcpy(reg_str, "%r14d"); } break;
			case 9: { strcpy(reg_str, "%r15d"); } break;
			case 10: { strcpy(reg_str, "%rdi"); } break;
			case 11: { strcpy(reg_str, "%rsi"); } break;
		}
	}
	return reg_str;
}


/*
	There are 5 fields in 'symTabs': name, value, type, offset, sclass
		- name: a unique identifier for each symbol
		- value: the integer associated with the symbol if applicable
		- type: the type of data structure that the symbol is
		- offset: in the case of variables, this indicates the memory pos of the value of the var
		- sclass: the place in memory where the variable is stored

	Additionally, there are 3 types of symbols stored in the symbol table: string, constant, variable
		- string: name, value, type
		- constant: name, value, type
		- variable: name, type, offset, sclass

*/



// VALUE
/**
 *
 * retrieve the value of a key
 *
 * @param index a int which is a key
 * @return the value of the key
 */

static Generic getValue(char *name)
{
  return SymGetField(findSymtab(symStack, name), name, SYMTAB_VALUE_FIELD);
}

/**
 *
 * Set the value for a key
 *
 * @param index a int which is a key
 * @param value the value of the key
 */

static void setValue(char *name, Generic value, u_int16_t global)
{

  if (global) {
	SymPutField(global_symTab, name, SYMTAB_VALUE_FIELD, (Generic)value);
  } else {
	SymPutField(currentSymtab(symStack), name, SYMTAB_VALUE_FIELD, (Generic)value);
  }
}

// TYPE
/**
 *
 * Set the type for a key
 *
 * @param index: a int which is a key
 * @param type: the type of the key
 */
static void setType(char *name, int type, u_int16_t global)
{

  if (global) {
	SymPutField(global_symTab, name, SYMTAB_TYPE_FIELD, (Generic)type);
  } else {
	SymPutField(currentSymtab(symStack), name, SYMTAB_TYPE_FIELD, (Generic)type);
  }
}

/**
 *
 * retrieve the type of a key
 *
 * @param index: a int which is a key
 * @return the type of the key
 */
static int getType(char *name)
{
  return (int)SymGetField(findSymtab(symStack, name), name, SYMTAB_TYPE_FIELD);
}

// OFFSET
/**
 *
 * Set the offset for a key
 *
 * @param index: a int which is a key
 * @param offset: the offset from storage class addr where the value of the object pointed to by 'index' is stored
 */
static void setOffset(char *name, int offset, u_int16_t global)
{

  if (global) {
	SymPutField(global_symTab, name, SYMTAB_OFFSET_FIELD, (Generic)offset);
  } else {
	SymPutField(currentSymtab(symStack), name, SYMTAB_OFFSET_FIELD, (Generic)offset);
  }
}

/**
 *
 * retrieve the offset of a keyB
 *
 * @param index: a int which is a key
 * @return the offset of the key
 */
static int getOffset(char *name)
{
  return (int)SymGetField(findSymtab(symStack, name), name, SYMTAB_OFFSET_FIELD);
}

// STORAGE CLASS
/**
 *
 * Set the storage class for a key
 *
 * @param index: a int which is a key
 * @param type: the section of  memory where the object is being stored
 */
static void setSClass(char *name, int s_class, u_int16_t global)
{
  if (global) {
	SymPutField(global_symTab, name, SYMTAB_SCLASS_FIELD, (Generic)s_class);
  } else {
	SymPutField(currentSymtab(symStack), name, SYMTAB_SCLASS_FIELD, (Generic)s_class);
  }
}

/**
 *
 * retrieve the storage class of a key
 *
 * @param index: a int which is a key
 * @return the storage class of the key
 */
static int getSClass(char *name)
{ 
	return (int)SymGetField(findSymtab(symStack, name), name, SYMTAB_SCLASS_FIELD);
}

// UTIL FUNCTIONS

/**
 *
 * removes the quotes around a str that is surrounded by quotes
 * NOTE: returned string must be freed
 *
 * @param str: a string surrounded by quotes
 * @return 'str' without quotes
 */
static char *removeQuotes (char *temp_str, char *str) {
	int i = 1;
	strcpy(temp_str, str);
	while (temp_str[i] != '\0') {
	temp_str[i-1] = temp_str[i];
	i++;
	}
	temp_str[i-2] = '\0';
	return temp_str;
}

// Generate a Label line
static unsigned int genLabel () {
	return label_num++;
}

// Debug
static void dumpDList (DLinkList *list) {
	DLinkNode *node = dlinkHead(list);
	while (node != NULLNODE) {
		fprintf(stderr, "atom:\n%s\n", (char*) node->atom);
		node = dlinkNext(node);
	}
}

static u_int16_t isGlobal (char *name) {
	SymTable sym_tab = findSymtab(symStack, name);
	if (sym_tab != NULL) {
		if ((int)SymGetField(sym_tab, name, SYMTAB_SCLASS_FIELD) == GLOBAL) {
			return 1;
		} else {
			return 0;
		}
	} else {
		fprintf(stderr, "Error: %s has not been initialized\n", name);
		exit(1);
	}
}

/******************END OF C ROUTINES**********************/
