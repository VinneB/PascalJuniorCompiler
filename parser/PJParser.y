/*******************************************************/
/*                     PascalJunior Parser             */
/*                                                     */
/*******************************************************/

/*********************DEFINITIONS***********************/
%{
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




%}
// yyval union vars
%union { 
	int ival;
	char *sval;
	struct DLinkList_struct *dll;
	int *iarrval;
}

%defines

%start Program

%token T_AND
%token T_ELSE
%token T_FLOAT
%token T_FOR
%token T_IF 		
%token T_LONGINT
%token T_BOOLEAN
%token T_PROGRAM	 
%token T_FUNCTION
%token T_NOT 		
%token T_OR 		
%token T_READ
%token T_WHILE
%token T_WRITE
%token T_WRITELN
%token T_BEGIN
%token T_END
%token T_VAR
%token T_DO
%token T_ARRAY
%token T_EXIT
%token T_THEN
%token T_LE
%token T_LT
%token T_GE
%token T_GT
%token T_EQ
%token T_NE
%token T_ASSIGN
%token T_COMMA
%token T_SEMICOLON
%token T_COLON
%token T_LBRACKET
%token T_RBRACKET
%token T_LPAREN
%token T_RPAREN
%token T_PLUS
%token T_TIMES
%token T_IDENTIFIER
%token T_DIV
%token T_STRING	
%token T_INTNUM
%token T_FLOATNUM
%token T_MINUS
%token T_DOT
%token T_DOTDOT
%token T_OF
%token T_TRUE
%token T_FALSE

// ----------- TYPES -------------
%type <ival> T_INTNUM WriteToken Constant Factor MulExpr AddExpr Expr OutputFormat Variable Test TestAndThen WhileToken WhileExpr
%type <sval> T_STRING T_IDENTIFIER
%type <dll> IdentifierList
%type <iarrval> Dim ArrayType StandardType Type
// -------------------------------

%left T_LT T_LE T_GT T_GE T_NE T_EQ
%left T_PLUS T_MINUS T_OR
%left T_TIMES T_DIV T_AND
%left T_NOT

%%
/***********************PRODUCTIONS****************************/

Program 	: ProgramHeadAndProcedures CompoundStatement T_DOT
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
		;

ProgramHeadAndProcedures : ProgramHead Procedures 
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "ProgramHeadAndProcedures : ProgramHead Procedure\n");		
		  #endif
		}
		;

ProgramHead 	: T_PROGRAM T_IDENTIFIER T_SEMICOLON Decls 
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "ProgramHead : T_PROGRAM T_IDENTIFIER T_SEMICOLON Decls \n");		
		  #endif
		}
	    	;

       
Decls 		: T_VAR DeclList
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Decls : T_VAR DeclList\n");		
		  #endif
		}
      		|
    	{
		  #ifdef PROJECT1
		  fprintf(stderr, "Decls : \n");		
		  #endif
		}
	  	;
	  
DeclList 	: IdentifierList T_COLON Type T_SEMICOLON
		{   
		  #ifdef PROJECT1
		  fprintf(stderr, "DeclList : IdentifierList T_COLON Type T_SEMICOLON\n");
		  #endif
		  // Enter all the globals into the symbol table
		  DLinkNode *node = dlinkHead($1);
		  int *type_def = $3;
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
		  dlinkFreeNodes($1);
		  dlinkListFree($1);
		}
		| DeclList IdentifierList T_COLON Type T_SEMICOLON
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "DeclList : DeclList IdentifierList T_COLON Type T_SEMICOLON\n");
		  #endif
		  // Enter all the globals into the symbol table
		  DLinkNode *node = dlinkHead($2);
		  int *type_def = $4;
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
		  dlinkFreeNodes($2);
		  dlinkListFree($2);
		}
		;
		 
IdentifierList 	: T_IDENTIFIER
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "IdentifierList : T_IDENTIFIER\n");
		  #endif
		  // Create a DLinkList and put the identifier in the list
		  DLinkList *idList;
		  DLinkNode *node;
		  idList = dlinkListAlloc((Generic*)idList_atom);
		  node = dlinkNodeAlloc((Generic*)$1);
		  dlinkAppend(idList, node);
		  $$ = idList;

		}
	       	| IdentifierList T_COMMA T_IDENTIFIER
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "IdentifierList : IdentifierList T_COMMA T_IDENTIFIER\n");
		  #endif
		  // Add the indentifier (string) to the current DLinkList
		  DLinkNode *node;
		  node = dlinkNodeAlloc((Generic*)$3);
		  dlinkAppend($1, node);
		  $$ = $1;
		}

// Type uses two bytes of the int type for type identification [NA NA isArray(bool) StdType]
Type 		: StandardType
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Type : StandardType\n");		
		  #endif
		  $$ = $1;
		}
	 	| ArrayType
	 	{
		  #ifdef PROJECT1
		  fprintf(stderr, "Type : ArrayType\n");		
		  #endif
  		  $$ = $1;
	 	}
	 	;

StandardType 	: T_LONGINT
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "StandardType : T_LONGINT\n");		
		  #endif
		  int *type = malloc(sizeof(int));
		  type[0] = TYPE_LONGINT_STD;
		  $$ = type;
		} 
		| T_BOOLEAN
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "StandardType : T_BOOLEAN\n");		
		  #endif
		  int *type = malloc(sizeof(int));
		  type[0] = TYPE_BOOL_STD;
		  $$ = type;
		}
		| T_FLOAT
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "StandardType : T_FLOAT\n");
		  #endif
		  int *type = malloc(sizeof(int));
		  type[0] = TYPE_FLOAT_STD;
		  $$ = type;
		}
		;
			
ArrayType 	: T_ARRAY T_LBRACKET Dim T_RBRACKET T_OF StandardType
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "ArrayType : T_ARRAY T_LBRACKET Dim T_RBRACKET T_OF StandardType\n");		
		  #endif

		  int type = *($6);

		  int *arr = malloc(sizeof(int)*5);
		  int *prev_arr = $3;
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
		  $$ = arr;
		}
		| T_ARRAY T_LBRACKET Dim T_COMMA Dim T_RBRACKET T_OF StandardType
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "ArrayType : T_ARRAY T_LBRACKET Dim T_COMMA Dim T_RBRACKET T_OF StandardType\n");		
		  #endif

		  int type = *($8);

		  int *arr = malloc(sizeof(int)*5);
		  int *prev_arr1 = $3;
		  int *prev_arr2 = $5;
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
		  $$ = arr;
		}
		;

Dim 		: T_INTNUM T_DOTDOT T_INTNUM
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Dim : T_INTNUM T_DOTDOT T_INTNUM\n");		
		  #endif
		  int *arr = malloc(sizeof(int)*2);
		  arr[0] = $1;
		  arr[1] = $3;
		  $$ = arr;
		} 
		| T_MINUS T_INTNUM T_DOTDOT T_INTNUM
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Dim : T_INTNUM T_DOTDOT T_INTNUM\n");		
		  #endif
		  int *arr = malloc(sizeof(int)*2);
		  arr[0] = -$2;
		  arr[1] = $4;
		  $$ = arr;
		}
		| T_INTNUM T_DOTDOT T_MINUS T_INTNUM
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Dim : T_INTNUM T_DOTDOT T_INTNUM\n");		
		  #endif
		  int *arr = malloc(sizeof(int)*2);
		  arr[0] = $1;
		  arr[1] = -$4;
		  $$ = arr; 
		}
		| T_MINUS T_INTNUM T_DOTDOT T_MINUS T_INTNUM
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Dim : T_INTNUM T_DOTDOT T_INTNUM\n");		
		  #endif
		  int *arr = malloc(sizeof(int)*2);
		  arr[0] = -$2;
		  arr[1] = -$5;
		  $$ = arr;
		}
		;

Procedures 	: Procedures ProcedureDecl
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Procedures : Procedures ProcedureDecl\n");		
		  #endif
		}
	   	| 
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Procedures :\n");		
		  #endif
		}
	   	;

ProcedureDecl 	: ProcedureHead ProcedureBody
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
              	;

ProcedureHead 	: FunctionDecl Decls 
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "ProcedureHead : FunctionDecl Decls\n");		
		  #endif
		  ins_func_init_local();
		  loc_nmemb = 0;
		  loc_sp = 0;
		}
              	;

FunctionDecl 	: T_FUNCTION T_IDENTIFIER T_COLON StandardType T_SEMICOLON
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "FunctionDecl : T_FUNCTION T_IDENTIFIER T_COLON StandardType T_SEMICOLON\n");		
		  #endif
		  isFunc = 1;
		  loc_nmemb = 0;
		  loc_sp = -4;
		  push_scope();
		  ins_func_label($2);
		  ins_func_prologue();

		}
   	     	;
	      
ProcedureBody 	: CompoundStatement T_SEMICOLON
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "ProcedureBody : CompoundStatement T_SEMICOLON\n");		
		  #endif
		}
	      	;

Statement 	: Assignment
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Statement : Assignment\n");		
		  #endif
		}
          	| IfStatement
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Statement : IfStatement\n");		
		  #endif
		}
	  	| WhileStatement
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Statement : WhileStatement\n");		
		  #endif
		}
          	| IOStatement 
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Statement : IOStatement\n");		
		  #endif
		}
	  	| ExitStatement
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Statement : ExitStatement\n");		
		  #endif

		}
	  	| CompoundStatement
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Statement : CompoundStatement\n");		
		  #endif
		}
          	;

Assignment 	: Variable T_ASSIGN Expr
		{ 
		  #ifdef PROJECT1
		  fprintf(stderr, "Assignment : Variable T_ASSIGN Expr\n");		
		  #endif
		  ins_assign($1, $3);

		  // This is the end of this statement so we push both regs
		  push_reg($3);
		  push_reg($1);

		}
		;
 
IfStatement 	: T_IF TestAndThen T_ELSE Statement
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "IfStatement : T_IF TestAndThen T_ELSE Statement\n");		
		  #endif

		  ins_label($2);
		}
	    	| T_IF TestAndThen
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "IfStatement : T_IF TestAndThen\n");		
		  #endif

		  ins_label($2);
		}
  	    	;
				
TestAndThen	: Test T_THEN Statement
	   	{
		  #ifdef PROJECT1
		  fprintf(stderr, "TestAndThen : Test T_THEN Statement\n");		
		  #endif

		  unsigned int label_index = genLabel();
		  end_control(label_index, $1);

		  $$ = label_index;
	    }
		;
				
Test 		: Expr 
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Test : Expr \n");	
		  #endif
		  unsigned int const_reg = pop_reg();
		  unsigned int label_index = genLabel();

		  start_control(const_reg, $1, label_index);

		  push_reg(const_reg);
		  push_reg($1);

		  $$ = label_index;
		}
	 	;

WhileStatement 	: WhileToken WhileExpr T_DO Statement
		{
		  // WhileToken - label index for top of loop
		  // WhileExpr - label index for loop escape
		  #ifdef PROJECT1
		  fprintf(stderr, "WhileStatement : WhileToken WhileExpr T_DO Statement\n");		
		  #endif
		  end_control($1, $2);
		}
        ;
                
WhileExpr : 	Expr 
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "WhileExpr : Expr \n");		
		  #endif

		  unsigned int const_reg = pop_reg();
		  unsigned int label_index = genLabel();

		  start_control(const_reg, $1, label_index);

		  push_reg(const_reg);
		  push_reg($1);

		  $$ = label_index;
		}
		;
				
WhileToken	: T_WHILE
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "WhileToken : T_WHILE\n");		
		  #endif
		  unsigned int label_index = genLabel();
		  ins_label(label_index);

		  $$ = label_index;
		}
		;

IOStatement 	: T_READ T_LPAREN Variable T_RPAREN
		{ 
		  #ifdef PROJECT1
		  fprintf(stderr, "IOStatement : T_READ T_LPAREN Variable T_RPAREN\n");		
		  #endif
		  
		  // Generate a scanf instruction
		  ins_scanf($3);

		  // No longer need this register
		  push_reg($3);


		}
		| WriteToken T_LPAREN Expr OutputFormat T_RPAREN
		{ 
		  #ifdef PROJECT1
		  fprintf(stderr, "IOStatement : WriteToken T_LPAREN Expr OutputFormat T_RPAREN\n");		
		  #endif

		  // FORMAT STRING SECTION

		  // Generate format string for print statement (newline and outputformat)
		  char fStr[8];
		  if ($4) {
			if (snprintf(fStr, 8, "%%%dd", $4) < 0) {
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
		  ins_printf_int(fStr, $3);
		  if ($1) {
			ins_printf_newline();
		  }

		  // No longer needed
		  push_reg($3);

		  

		}
		| WriteToken T_LPAREN T_STRING OutputFormat T_RPAREN      
		{ 
		  #ifdef PROJECT1
		  fprintf(stderr, "IOStatement : WriteToken T_LPAREN T_STRING OutputFormat T_RPAREN\n");		
		  #endif

		  // CONSTANT STRING SECTION

		  // Remove quotes
		  char temp_str[TEMP_STR_LEN];
		  removeQuotes(temp_str, $3);
		  
		  // Add T_STRING to global Symbol Table and dataList if not already there
		  if (SymQueryIndex(global_symTab, temp_str) == SYM_INVALID_INDEX) {
		  	addStringConst(temp_str);
		  }

		  // FORMAT STRING SECTION

		  // Generate format string for print statement (newline and outputformat)
		  char fStr[8];
		  if ($4) {
			if (snprintf(fStr, 8, "%%%ds", $4) < 0) {
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
		  if ($1) {
			ins_printf_newline();
		  }

		}
		;

OutputFormat 	: T_COLON T_INTNUM
        	{
		  #ifdef PROJECT1
		  fprintf(stderr, "OutputFormat : T_COLON T_INTNUM\n");		
		  #endif
		  $$ = $2;
		} 
		|
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "OutputFormat : \n");		
		  #endif
		  $$ = 0;
		}
		;

WriteToken 	: T_WRITE
             	{
		  #ifdef PROJECT1
		  fprintf(stderr, "WriteToken : T_WRITE\n");		
		  #endif
		  $$ = 0;
		}
	    	| T_WRITELN
            	{
		  #ifdef PROJECT1
		  fprintf(stderr, "WriteToken : T_WRITELN\n");		
		  #endif
		  $$ = 1;
		}
                ;
			 
ExitStatement 	: T_EXIT T_LPAREN Expr T_RPAREN 
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "ExitStatement : T_EXIT T_LPAREN Expr T_RPAREN\n");		
		  #endif
		  if (isFunc) {
			ins_func_ret_val($3);
			ins_func_epilogue();
			push_reg($3);
		  }
		}
                ;

CompoundStatement : T_BEGIN StatementList T_END
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "CompoundStatement : T_BEGIN StatementList T_END\n");		
		  #endif
		}
                ;
                  
StatementList 	: StatementList T_SEMICOLON Statement
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "StatementList : StatementList T_SEMICOLON Statement\n");		
		  #endif
		}
		| Statement
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "StatementList : Statement\n");		
		  #endif
		}
		;

 
Expr		: AddExpr
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : AddExpr\n");		
		  #endif
		  $$ = $1; // No change needed
		}
        | Expr T_EQ AddExpr
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : Expr T_EQ AddExpr\n");		
		  #endif
		  
		  // Add instruction: operand 1 is turned to pos if (operand 1 == operand 2)
		  ins_eq($1, $3);

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg($3);

		  $$ = $1;
		}
        | Expr T_NE AddExpr
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : Expr T_NE AddExpr\n");		
		  #endif

		  // Add instruction: operand 1 is turned to pos if (operand 1 != operand 2)
		  ins_neq($1, $3);

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg($3);

		  $$ = $1;

		}
        | Expr T_LE AddExpr
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : Expr T_LE AddExpr\n");		
		  #endif

		  // Add instruction: operand 1 is turned to pos if (operand 1 <= operand 2)
		  ins_le($1, $3);

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg($3);

		  $$ = $1;

		}
        | Expr T_LT AddExpr
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : Expr T_LT AddExpr\n");		
		  #endif

		  // Add instruction: operand 1 is turned to pos if (operand 1 < operand 2)
		  ins_lt($1, $3);

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg($3);

		  $$ = $1;

		}
        | Expr T_GE AddExpr
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : Expr T_GE AddExpr\n");		
		  #endif

		  // Add instruction: operand 1 is turned to pos if (operand 1 >= operand 2)
		  ins_ge($1, $3);

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg($3);

		  $$ = $1;
		}
        | Expr T_GT AddExpr
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Expr : Expr T_GT AddExpr\n");		
		  #endif

		  // Add instruction: operand 1 is turned to pos if (operand 1 > operand 2)
		  ins_gt($1, $3);

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg($3);

		  $$ = $1;
		}
                ;

AddExpr		: MulExpr
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "AddExpr : MulExpr\n");		
		  #endif
		  $$ = $1; // No change needed
		}
		| AddExpr T_OR MulExpr 
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "AddExpr : AddExpr T_OR MulExpr\n");		
		  #endif

		  // Add instruction to perform a bitwise OR operation operand 1 and operand 2
		  ins_or($1, $3);

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg($3);

		  $$ = $1;
		}
        | AddExpr T_PLUS MulExpr
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "AddExpr : AddExpr T_PLUS MulExpr\n");		
		  #endif

		  // Add instruction to add our two operands
		  ins_addReg($1, $3);

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg($3);

		  $$ = $1;
		}
        | AddExpr T_MINUS MulExpr
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "AddExpr : AddExpr T_MINUS MulExpr\n");		
		  #endif
		  
		  // Add instruction to subract the 2nd operand from the first
		  ins_subReg($1, $3);

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg($3);

		  $$ = $1;
		}
                ;

MulExpr		:  Factor
        {
		  #ifdef PROJECT1
		  fprintf(stderr, "MulExpr : Factor\n");
		  #endif
		  $$ = $1; // No change necessary
        }
	    | MulExpr T_TIMES Factor
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "MulExpr : MulExpr T_TIMES Factor\n");
		  #endif
		  
		  // Add instruction to multiply our two operands
		  ins_multReg($1, $3);

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg($3);

		  $$ = $1;
		}
        | MulExpr T_DIV Factor
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "MulExpr : MulExpr T_DIV Factor\n");		
		  #endif
		  
		  // Add instruction to divide operand 1 by operand 2
		  ins_divReg($1, $3);

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg($3);

		  $$ = $1;
		}	
		| MulExpr T_AND Factor 
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "MulExpr : MulExpr T_AND Factor\n");		
		  #endif
		  
		  // Add instruction to bitwise AND operand 1 and operand 2
		  ins_and($1, $3);

		  // The second operand register is no longer needed so we push it back on the rStack
		  push_reg($3);

		  $$ = $1;
		}	
                ;
		

Factor          : Variable
		{ 
		  #ifdef PROJECT1
		  fprintf(stderr, "Factor : Variable\n");		
		  #endif

		  // We pop a register to hold the value in the variable
		  unsigned int reg = pop_reg();

		  ins_loadVarValue($1, reg);

		  // The mem_reg is no longer necessary so we push it
		  push_reg($1);

		  $$ = reg;
		}
        | Constant
		{ 
		  #ifdef PROJECT1
		  fprintf(stderr, "Factor : Constant\n");		
		  #endif
		  $$ = $1; // No change necessary
		}
	    | T_NOT Factor
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Factor : T_NOT Factor\n");		
		  #endif

		  // Add an instruction which inverts (NOT) the current register
		  ins_not($2);

		  $$ = $2;
		}
        | T_IDENTIFIER T_LPAREN T_RPAREN
       		{					
		  #ifdef PROJECT1
		  fprintf(stderr, "Factor : T_IDENTIFIER T_LPAREN T_RPAREN\n");		
		  #endif
		  unsigned int ret_reg = pop_reg();
		  ins_func_call($1, ret_reg);
		  $$ = ret_reg;
		}
        | T_LPAREN Expr T_RPAREN
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Factor : T_LPAREN Expr T_RPAREN\n");		
		  #endif
		  $$ = $2; // No change necessary
		}
                ;  

 

Variable        : T_IDENTIFIER
		{
		  #ifdef PROJECT1
		  fprintf(stderr, "Variable : T_IDENTIFIER\n");		
		  #endif
		  // Pop the necessary registers to load global memory
		  unsigned int mem_reg = pop_reg();

		  // Add Instructions
		  ins_loadVar($1, mem_reg);

		  $$ = mem_reg;
		}
        | T_IDENTIFIER T_LBRACKET Expr T_RBRACKET    
       	{
		  #ifdef PROJECT1
		  fprintf(stderr, "Variable : T_IDENTIFIER T_LBRACKET Expr T_RBRACKET\n");		
		  #endif
		  // Pop the necessary registers to load global memory
		  unsigned int mem_reg = pop_reg();

		  // Add Instructions
		  load_1dim_arr($1, $3, mem_reg);

		  push_reg($3);

		  $$ = mem_reg;
        }
		| T_IDENTIFIER T_LBRACKET Expr T_COMMA Expr T_RBRACKET   
        {
		  #ifdef PROJECT1
		  fprintf(stderr, "Variable  : T_IDENTIFIER T_LBRACKET Expr T_COMMA Expr T_RBRACKET\n");		
		  #endif

		  // Pop the necessary registers to load global memory
		  unsigned int mem_reg = pop_reg();

		  // Add Instructions
		  load_2dim_arr($1, $3, $5, mem_reg);

		  push_reg($3);
		  push_reg($5);

		  $$ = mem_reg;

        }
                ;			       

        		       
Constant        : T_FLOATNUM    
		{ 
		  #ifdef PROJECT1
		  fprintf(stderr, "Constant : T_FLOATNUM\n");	
		  #endif
		}
		| T_MINUS T_INTNUM
		{   
		  #ifdef PROJECT1
		  fprintf(stderr, "Constant : T_MINUS T_INTNUM\n");		
		  #endif

		  // Get free register
		  unsigned int reg = pop_reg();

		  // Load negative of constant value into register
		  ins_loadImm(-($2), reg);
		  
		  $$ = reg;
		}
        	| T_INTNUM
		{ 
		  #ifdef PROJECT1
		  fprintf(stderr, "Constant : T_INTNUM\n");
		  #endif
		  
		  // Get free register
		  unsigned int reg = pop_reg();

		  // Load constant value into register
		  ins_loadImm($1, reg);
		  
		  $$ = reg;
		}
		| T_TRUE
		{ 
		  #ifdef PROJECT1
		  fprintf(stderr, "Constant : T_TRUE\n");		
		  #endif
		 
		  // Get free register
		  unsigned int reg = pop_reg();

		  // Load true (1) into register
		  ins_loadImm(1, reg);
		  
		  $$ = reg;
		}
		| T_FALSE
		{ 
		  #ifdef PROJECT1
		  fprintf(stderr, "Constant : T_FALSE\n");		
		  #endif
		 
		  // Get free register
		  unsigned int reg = pop_reg();

		  // Load false (0) into register
		  ins_loadImm(0, reg);
		  
		  $$ = reg;
		}
                ;

%%


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
