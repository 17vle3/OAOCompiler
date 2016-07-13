%{

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

%}

%union{

	struct ast* tree;
	string* str;
	int test;
	int type;	/* 1 FOR INT, 2 FOR CHAR */
	int isArray;/* 0 FOR NOT, 1 FOR TRUE */
	int val;
	int cond;/* 1: EQ 2:NEQ 3:GT 4:LT 5:GET 6:LET 7:AND 8:OR */
}
/* Termainal sybmol */

%token <str> INT CHAR RETURN IF WHILE ELSE BREAK PRINT READ

%token <cond> EQ NEQ GT LT GET LET
%token <type> AND OR
%token <str> ID MYCHAR
%token <val> NUM

%left <str> '+' '-' '!'
%left <str> '*' '/'
%right <str> '='
/* Non-terminal symbol */

%type <tree> Program DeclList DeclListP
%type <tree> VarDeclList
%type <tree> VarDeclP VarDecl Decl
%type <tree> FunDecl

%type <tree> ParamDeclList ParamDeclListTail ParamDeclListTailP ParamDecl
%type <isArray> ParamDeclP

/* TYPE=1 -> INT ; TYPE=2 -> CHAR */
%type <type> Type
%type <tree> StmtList StmtListP Stmt Block
%type <tree> Expr ExprIdTail ExprArrayTail ExprP ExprList ExprListTail ExprListTailP
%type <cond> BinOp UnaryOp

%%

Program	
	: DeclList {
		mips.open("mips.s");
		debug.open("debug.txt");
		initRegs();

		$$ = new_ast(9526,$1,NULL,"Program -> DeclList");
		evaluate_exp($$);
		mips << data << function_text;
		//debugLog << "[Program]:Into Main Program. Find a Declaration" << endl;
	}
	;

DeclList
	: DeclListP DeclList {
	
		$$ = new_ast(9527,$1,$2,"DeclList -> DeclListP DeclList");

	}
	| /* empty */ {
		$$ = new_ast('F',NULL,NULL,"DeclList -> Empty");
	}
	;

DeclListP 
	: Type ID Decl {

		$$ = new_ast(9528,$3,NULL,*$2,"DeclListP -> Type ID");
		//ok, we already have decl information from $3
		
		if($$->sym != NULL)
		{
			//there is a var_sym
			$$->sym = new symbol;
			$$->sym->isArray = $3->sym->isArray;
			$$->sym->isFunction = $3->sym->isFunction;
			$$->sym->type = $1;
		}
		else
		{
			//there is a fun_sym
			$$->sym = new symbol;
			$$->sym->type = $1;
			$$->sym->isFunction = 1;
			$$->sym->isArray = 0;
			$$->l->id = new string(*$2);
			$$->l->sym = $$->sym;
		}
	}
	;

Decl
	: VarDeclP {
		$$ = $1;
	}
	| FunDecl {
	
		$$ = $1;
	}
	;

VarDecl /* DONE */
	: Type ID VarDeclP {

		$$ = new_ast(9531,$3,NULL,*$2,"VarDecl-> Type ID varDeclP");
		$$->sym = new symbol;
		$$->sym->type = $1;
		$$->sym->isArray = $3->sym->isArray;
		$$->sym->isFunction = 0 ;
		$$->sym->size = $3->sym->size;
	}
	;

VarDeclP /* DONE */
	: ';' {
		/* Get a varaible declaration */
		
		$$ = new_ast('F',NULL,NULL,"VarDeclP -> ;");
		$$->sym = new symbol;
		$$->sym->isArray = 0;
		$$->sym->size = 0;
		
 	}
	| '[' NUM ']' ';' {
		/* Get a array declaration */
		$$ = new_ast('F',NULL,NULL,"VarDeclP -> [NUM]");
		$$->sym = new symbol;
		$$->sym->isArray = 1;
		$$->sym->size = $2;

		if($$->sym->size < 0){
			cout << "[ERROR]: INVALID SIZE OF AN ARRAY: " << $2 << endl;
		}
	}
	;

FunDecl /* TODO */
	: '(' ParamDeclList ')' Block {
		//evaluate this function
		
		$$ = new_ast(9529,$2,$4,"FunDecl -> ( ParaDeclList ) Block");
	}
	;

VarDeclList /* DONE */
	: VarDecl VarDeclList {
	
		$$ = new_ast(9530,$1,$2,"VarDeclList -> VarDecl VarDeclList");
	 }
	| /* empty */ {
		$$ = new_ast('F',NULL,NULL,"VarDeclList -> empty");
	}
	;

ParamDeclList /*TODO */
	: ParamDeclListTail {
		$$ = new_ast(9533,$1,NULL,"ParamDeclList -> ParamDeclListTail");
	}
	| /* empty */ {
		$$ = new_ast('F',NULL,NULL,"ParamDeclList -> Empty"); 
	}
	;

ParamDeclListTail
	: ParamDecl ParamDeclListTailP {
		$$ = new_ast(9534,$1,$2,"ParamDeclListTail -> ParamDecl ParamDeclListTailP");
	}
	;

ParamDeclListTailP 
	: ',' ParamDeclListTail {
		
		$$ = $2;//pass another paramDecl,if there has one.
	}
	| /* empty */ {
		$$ = new_ast(9538,NULL,NULL,"ParamDeclListTail -> Empty");
	}
	;

ParamDecl 
	: Type ID ParamDeclP {

		$$ = new_ast(9535,NULL,NULL,*$2,"ParamDecl -> Type ID ParamDeclP");
		
		clearsym sym;
		sym.id = *$2;
		sym.type = $1;
		sym.isArray = $3;
		sym.isFunction = 0;
		sym.size = 0;
		var_table.push_back(sym);
		decl_var(sym);
	}
	;

ParamDeclP 
	: '[' ']' { $$ = 1; /* array type. */}
	| /* empty */ { $$ = 0;   /* nope. */}
	;

Block /* DONE */
	:'{' VarDeclList StmtList '}'{
	 	$$ = new_ast(9532,$2,$3,"Block -> { VarDeclList StmtList }");

	 }
	;

Type /* DONE */
	: INT {
		$$ = 1;
	}
	| CHAR {
		$$ = 2;
	}
	;

StmtList /* DONE */
	: Stmt StmtListP {
		$$ = new_ast('T',$1,$2,"StmtList->Stmt StmtListP");
	}
	;

StmtListP
	: StmtList { 
		$$ = $1 ;
	}
	| /* empty */ { $$ = new_ast('F',NULL,NULL,"Empty","StmtListP-> Empty"); }
	;

Stmt
	: ';' { /* NO Work */
		//I want to say that but i can't...
		//it also need a empty node to do something
		$$ = new_ast('F',NULL,NULL,"Empty","Stmt->;");
	}
	| Expr ';' {
	
		$$ = new_ast('X',$1,NULL,"Stmt-> Expr;");
		
		//cout << "[Stmt -> ;]: This exp can conclude to " << val.id << endl;
		//releaseReg(val.id);
		
	}
	| RETURN Expr ';' {
	
		$$ = new_ast('Q',$2,NULL,"Empty","Stmt-> RETURN Expr");
	
	}
	| BREAK ';' {
		$$ = new_ast('C',NULL,NULL,"Break","Stmt-> Break");
		
	}
	| IF '(' Expr ')' Stmt ELSE Stmt {
	
		$$ = new_stmt_ast('G',$3, $5, $7, "Stmt->IF ELSE");
	
	}
	| WHILE '(' Expr ')' Stmt {
	
		$$ = new_ast('W',$3,$5,"Stmt-> While stmt");
	
	}
	| Block {
	
		$$ = $1;// Block pass~
	
	}
	| PRINT ID ';' {
	
		$$ = new_ast('P',NULL,NULL,*$2,"Stmt-> Print "+*$2);
	
	}
	| READ ID ';' {

		$$ = new_ast('R',NULL,NULL,*$2,"Stmt-> Read "+*$2);

	}
	;

Expr
	: UnaryOp Expr {
		$$ = new_ast($1,$2,NULL,"Expr -> Unary Expr");
	}
	| NUM ExprP {
		stringstream s;
		s << $1;
		$$ = new_ast('N',$2,NULL,s.str(),"Expr -> NUM ExprP");
	}
	| '(' Expr ')' ExprP { 
		$$ = new_ast('B',$2,$4,"Expr -> ( EXpr ) ExprP");
	}
	| ID ExprIdTail {
		$$ = new_ast('I',$2,NULL,*$1,"Expr -> ID ExprIdTail");
	}
	;

ExprIdTail
	: ExprP { 
		$$ = $1;
	}
	| '(' ExprList ')' ExprP { 
	
		$$ = new_ast(9536,$2,$4,"ExprIdTail -> ( ExprList ) ExprP");
	
	}
	| '[' Expr ']' ExprArrayTail { 
		$$ = new_ast('L',$2,$4,"ExprIdTail -> [Expr] ExprArrayIdTail");
	}
	| '=' Expr { 
		$$ = new_ast('A',$2,NULL,"ExprIdTail -> = Expr");
	}
	;

ExprArrayTail
	: ExprP {
		$$ = $1;
	}
	| '=' Expr { 
		$$ = new_ast('A',$2,NULL,"ExprIdTail -> = Expr");
	}
	;

ExprP
	: BinOp Expr {

		$$ = new_ast($1,$2,NULL,"ExprP -> BinOp Expr");
		cout << "[ExprP-BinOp] Meet an Operator " << $1 << endl;
	}
	| /* empty */ {
		$$ = new_ast('E',NULL,NULL,"ExprP -> Empty");
		cout << "[Expr-empty] Get a expr end Kappa" << endl; 
	}
	;

ExprList
	: ExprListTail {
		$$ = $1;
	}
	| /* empty */ {
		
	}
	;

ExprListTail
	: Expr ExprListTailP {
	
		$$ = new_ast(9537,$1,$2,"ExprListTail -> ExprListTailP");
	}
	;

ExprListTailP
	: ',' ExprListTail {
		$$ = $2;
	}
	| /* empty */ {
		$$ = new_ast('F',NULL,NULL,"ExprListTailP -> Empty");
	}
	;

UnaryOp
	: '-' { $$ = 14;}
	| '!' { $$ = 15;}
	;

BinOp
	: '+' { $$ = 10;}
	| '-' { $$ = 11; }
	| '*' { $$ = 12; }
	| '/' { $$ = 13; }
	| EQ { $$ = 1; }
	| NEQ { $$ = 2; }
	| GT { $$ = 3; }
	| LT { $$ = 4; }
	| GET { $$ = 5; }
	| LET { $$ = 6; }
	| AND { $$ = 7; }
	| OR { $$ = 8; }
	;
%%

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
		
		case 5: //RECURSIVE function. NOT ALLOWED IN INPUT,so...
	
			cout << "[WTF?]: A recurrsive , That's not approve !" << endl;
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


