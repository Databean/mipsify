%code requires {

#include "Declaration.h"
#include "Expression.h"
#include "Statement.h"
#include "Type.h"
#include "Parser.h"
#include "Util.h"

extern Program* program_out;

}

%locations
%define parse.lac full
%error-verbose

%{
#include "Parser.h"
#include "scanner.h"
#include <string>
#include <iostream>
#include "Type.h"

%}

//%parse-param {Program*& out}

%union {
	char* cstr;
	std::string* ident;
	std::string* strConst;
	unsigned int intConst;
	Type* type;
	std::vector<Declaration*>* declareList;
	Declaration* declare;
	ConstantExpression* constant;
	std::vector<FunctionParameter*>* paramList;
	FunctionParameter* param;
	std::vector<StructMember*>* structMemberList;
	StructMember* structMember;
	StatementBlock* statementBlock;
	Statement* statement;
	std::vector<Statement*>* statementList;
	Expression* expression;
	std::vector<Expression*>* expressionList;
}

%type <type> type
%type <cstr> root
%type <declareList> root_declare_list
%type <declare> root_declare
%type <constant> constant
%type <paramList> param_list non_empty_param_list
%type <param> param
%type <structMemberList> struct_list
%type <structMember> struct_member;
%type <statementBlock> statement_block
%type <statementList> statement_list
%type <statement> statement
%type <expression> expression
%type <expressionList> argument_list non_empty_argument_list

%token <ident> T_IDENT
%token <strConst> T_STR_CONST
%token <intConst> T_INT_CONST
%token T_IF T_ELSE T_FOR T_WHILE T_DO T_SIZEOF
%token T_INT_TYPE T_STRING_TYPE T_VOID_TYPE T_STRUCT
%token T_RETURN T_SWITCH T_CASE T_DEFAULT T_BREAK T_CONTINUE
%token T_BOOL_OR T_BOOL_AND
%token T_LEFT_SHIFT T_RIGHT_SHIFT T_PLUS_EQUALS T_MINUS_EQUALS 
%token T_STAR_EQUALS T_DIV_EQUALS T_MOD_EQUALS T_EQUAL 
%token T_LESS_OR_EQUAL T_GREATER_OR_EQUAL T_NOT_EQUAL
%token T_BIT_OR_EQUALS T_BIT_AND_EQUALS T_BIT_XOR_EQUALS
%token T_BIT_NOT_EQUALS T_ARROW T_LEFT_SHIFT_EQUALS
%token T_RIGHT_SHIFT_EQUALS T_PLUS_PLUS T_MINUS_MINUS
%token T_UNTERM_STRING T_UNTERM_COMMENT

/* tokens for precedence */
%token PREC_ADDRESS PREC_DEREFERENCE PREC_UNARY_MINUS PREC_UNARY_PLUS
%token PREC_SUFFIX_PLUS_PLUS PREC_SUFFIX_MINUS_MINUS
%token PREC_PREFIX_PLUS_PLUS PREC_PREFIX_MINUS_MINUS
%token PREC_APPLICATION

/* lowest precedence */
%left ','
%right T_BIT_AND_EQUALS T_BIT_XOR_EQUALS T_BIT_OR_EQUALS
%right T_LEFT_SHIFT_EQUALS T_RIGHT_SHIFT_EQUALS
%right T_STAR_EQUALS T_DIV_EQUALS T_MOD_EQUALS
%right T_PLUS_EQUALS T_MINUS_EQUALS
%right '='
%left T_BOOL_OR
%left T_BOOL_AND
%left '|'
%left '^'
%left '&'
%left T_EQUAL T_NOT_EQUAL
%left '>' T_GREATER_OR_EQUAL
%left '<' T_LESS_OR_EQUAL
%left T_LEFT_SHIFT T_RIGHT_SHIFT
%left '+' '-'
%left '*' '/' '%'
%right PREC_ADDRESS
%right PREC_DEREFERENCE
%right '!' '~'
%right PREC_UNARY_PLUS PREC_UNARY_MINUS
%right PREC_PREFIX_PLUS_PLUS PREC_PREFIX_MINUS_MINUS
%right T_PLUS_PLUS T_MINUS_MINUS
%left T_ARROW
%left '.'
%left '['
%left PREC_APPLICATION
%left PREC_SUFFIX_PLUS_PLUS PREC_SUFFIX_MINUS_MINUS
%nonassoc T_IF
%nonassoc T_ELSE
/* highest precedence */



%%

root:
		root_declare_list										{ $$ = NULL; program_out = new Program(@$, *$1); delete $1; }
	;

root_declare_list:
		root_declare_list root_declare							{ $$ = $1; $1->push_back($2); }
	|															{ $$ = new std::vector<Declaration*>(); }
	;

root_declare:
		type T_IDENT '(' param_list ')' ';'						{ $$ = new FunctionPrototype(@$, $1, *$2, *$4); delete $2; delete $4; }
	|	type T_IDENT '(' param_list ')' statement_block			{ $$ = new FunctionDeclaration(@$, $1, *$2, *$4, $6); delete $2; delete $4; }
	|	type T_IDENT ';'										{ $$ = new GlobalVarDeclaration(@$, $1, *$2); delete $2; }
	|	type T_IDENT '[' T_INT_CONST ']' ';'					{ $$ = new GlobalArrayDeclaration(@$, $1, *$2, $4); delete $2; }
	|	type T_IDENT '=' constant ';'							{ $$ = new GlobalVarDeclarationInit(@$, $1, *$2, $4); delete $2; }
	|	T_STRUCT T_IDENT '{' struct_list '}' ';'				{ $$ = new StructDeclaration(@$, *$2, *$4); delete $2; delete $4; }
	|	T_STRUCT T_IDENT ';'									{ $$ = new StructPredeclaration(@$, *$2); delete $2; }
	;

constant:
		T_INT_CONST												{ $$ = new IntConstantExpression(@$, $1); }
	|	T_STR_CONST												{ $$ = new StringConstantExpression(@$, *$1); delete $1; }
	;

param_list:
		non_empty_param_list									{ $$ = $1; }
	|															{ $$ = new std::vector<FunctionParameter*>(); }
	;

non_empty_param_list:
		non_empty_param_list ',' param							{ $$ = $1; $1->push_back($3); }
	|	param													{ $$ = new std::vector<FunctionParameter*>({$1}); }
	;

param:
		type T_IDENT											{ $$ = new FunctionParameter(@$, $1, *$2); delete $2; }
	;

struct_list:
		struct_list struct_member ';'							{ $$ = $1; $1->push_back($2); }
	|															{ $$ = new std::vector<StructMember*>(); }
	;

struct_member:
		type T_IDENT											{ $$ = new StructMember(@$, $1, *$2); delete $2; }
	;

type:
		type '*'												{ $$ = new PointerType($1); }
	|	T_STRUCT T_IDENT										{ $$ = new StructType(*$2); delete $2; }
	|	T_INT_TYPE												{ $$ = new IntType(); }
	|	T_VOID_TYPE												{ $$ = new VoidType(); }
	|	T_STRING_TYPE											{ $$ = new StringType(); }
	;

statement_block:
		'{' statement_list '}'									{ $$ = new StatementBlock(@$, *$2); delete $2; }
	;

statement_list:
		statement_list statement								{ $$ = $1; $1->push_back($2); }
	|															{ $$ = new std::vector<Statement*>(); }
	;

statement:
		expression ';'											{ $$ = $1; }
	|	type T_IDENT ';'										{ $$ = new VarDeclaration(@$, $1, *$2); delete $2; }
	|	type T_IDENT '=' expression ';'							{ $$ = new VarDeclarationInit(@$, $1, *$2, $4); delete $2; }
	|	type T_IDENT '[' T_INT_CONST ']' ';'					{ $$ = new ArrayDeclaration(@$, $1, *$2, $4); delete $2; }
	|	T_WHILE '(' expression ')' statement					{ $$ = new WhileStatement(@$, $3, $5); }
	|	T_DO statement T_WHILE '(' expression ')' ';'			{ $$ = new DoWhileStatement(@$, $2, $5); }
	|	T_FOR '(' expression ';' expression ';' expression ')' statement { $$ = new ForStatement(@$, $3, $5, $7, $9); }
	|	statement_block											{ $$ = $1; }
	|	T_IF '(' expression ')' statement %prec T_IF			{ $$ = new IfStatement(@$, $3, $5); }
	|	T_IF '(' expression ')' statement T_ELSE statement		{ $$ = new IfElseStatement(@$, $3, $5, $7); }
	|	T_BREAK ';'												{ $$ = new BreakStatement(@$); }
	|	T_CONTINUE ';'											{ $$ = new ContinueStatement(@$); }
	|	T_SWITCH '(' expression ')' '{' statement_list '}'		{ $$ = new SwitchStatement(@$, $3, *$6); delete $6; }
	|	T_CASE T_INT_CONST ':'									{ $$ = new CaseStatement(@$, $2); }
	|	T_DEFAULT ':'											{ $$ = new DefaultStatement(@$); }
	|	T_RETURN expression ';'									{ $$ = new ReturnStatement(@$, $2); }
	;

expression:
		expression '=' expression								{ $$ = new AssignExpression(@$, $1, $3); }
	|	expression T_PLUS_EQUALS expression						{ $$ = new AssignExpression(@$, $1, new BinaryOperatorExpression(@3, $1->clone(), "+", $3)); }
	|	expression T_MINUS_EQUALS expression					{ $$ = new AssignExpression(@$, $1, new BinaryOperatorExpression(@3, $1->clone(), "-", $3)); }
	|	expression T_STAR_EQUALS expression						{ $$ = new AssignExpression(@$, $1, new BinaryOperatorExpression(@3, $1->clone(), "*", $3)); }
	|	expression T_DIV_EQUALS expression						{ $$ = new AssignExpression(@$, $1, new BinaryOperatorExpression(@3, $1->clone(), "/", $3)); }
	|	expression T_MOD_EQUALS expression						{ $$ = new AssignExpression(@$, $1, new BinaryOperatorExpression(@3, $1->clone(), "%", $3)); }
	|	expression T_BIT_AND_EQUALS expression					{ $$ = new AssignExpression(@$, $1, new BinaryOperatorExpression(@3, $1->clone(), "&", $3)); }
	|	expression T_BIT_OR_EQUALS expression					{ $$ = new AssignExpression(@$, $1, new BinaryOperatorExpression(@3, $1->clone(), "|", $3)); }
	|	expression T_BIT_XOR_EQUALS expression					{ $$ = new AssignExpression(@$, $1, new BinaryOperatorExpression(@3, $1->clone(), "^", $3)); }
	|	expression T_LEFT_SHIFT_EQUALS expression				{ $$ = new AssignExpression(@$, $1, new BinaryOperatorExpression(@3, $1->clone(), "<<", $3)); }
	|	expression T_RIGHT_SHIFT_EQUALS expression				{ $$ = new AssignExpression(@$, $1, new BinaryOperatorExpression(@3, $1->clone(), ">>", $3)); }
	|	expression T_PLUS_PLUS %prec PREC_SUFFIX_PLUS_PLUS		{ $$ = new UnaryAssignExpression(@$, $1, "++"); }
	|	T_PLUS_PLUS expression %prec PREC_PREFIX_PLUS_PLUS		{ $$ = new UnaryAssignExpression(@$, "++", $2); }
	|	expression T_MINUS_MINUS %prec PREC_SUFFIX_MINUS_MINUS	{ $$ = new UnaryAssignExpression(@$, $1, "--"); }
	|	T_MINUS_MINUS expression %prec PREC_PREFIX_MINUS_MINUS	{ $$ = new UnaryAssignExpression(@$, "--", $2); }
	|	constant												{ $$ = $1; }
	|	'(' expression ')'										{ $$ = $2; }
	|	T_IDENT '(' argument_list ')' %prec PREC_APPLICATION	{ $$ = new FunctionCallExpression(@$, *$1, *$3); delete $1; delete $3; }
	|	T_SIZEOF '(' type ')'									{ $$ = new SizeofExpression(@$, $3); }
	|	'!' expression											{ $$ = new UnaryOperatorExpression(@$, "!", $2); }
	|	'~' expression											{ $$ = new UnaryOperatorExpression(@$, "~", $2); }
	|	'+' expression %prec PREC_UNARY_PLUS					{ $$ = new UnaryOperatorExpression(@$, "+", $2); }
	|	'-' expression %prec PREC_UNARY_MINUS					{ $$ = new UnaryOperatorExpression(@$, "-", $2); }
	|	'*' expression %prec PREC_DEREFERENCE					{ $$ = new ArraySubscriptExpression(@$, $2, new IntConstantExpression(@2, 0)); }
	|	'&' expression %prec PREC_ADDRESS						{ $$ = new UnaryOperatorExpression(@$, "&", $2); }
	|	expression '+' expression								{ $$ = new BinaryOperatorExpression(@$, $1, "+", $3); }
	|	expression '-' expression								{ $$ = new BinaryOperatorExpression(@$, $1, "-", $3); }
	|	expression '*' expression								{ $$ = new BinaryOperatorExpression(@$, $1, "*", $3); }
	|	expression '/' expression								{ $$ = new BinaryOperatorExpression(@$, $1, "/", $3); }
	|	expression '%' expression								{ $$ = new BinaryOperatorExpression(@$, $1, "%", $3); }
	|	expression '&' expression								{ $$ = new BinaryOperatorExpression(@$, $1, "&", $3); }
	|	expression '|' expression								{ $$ = new BinaryOperatorExpression(@$, $1, "|", $3); }
	|	expression '^' expression								{ $$ = new BinaryOperatorExpression(@$, $1, "^", $3); }
	|	expression T_BOOL_AND expression						{ $$ = new BinaryOperatorExpression(@$, $1, "&&", $3); }
	|	expression T_BOOL_OR expression							{ $$ = new BinaryOperatorExpression(@$, $1, "||", $3); }
	|	expression T_LEFT_SHIFT expression						{ $$ = new BinaryOperatorExpression(@$, $1, "<<", $3); }
	|	expression T_RIGHT_SHIFT expression						{ $$ = new BinaryOperatorExpression(@$, $1, ">>", $3); }
	|	expression T_EQUAL expression							{ $$ = new BinaryOperatorExpression(@$, $1, "==", $3); }
	|	expression T_NOT_EQUAL expression						{ $$ = new BinaryOperatorExpression(@$, $1, "!=", $3); }
	|	expression '<' expression								{ $$ = new BinaryOperatorExpression(@$, $1, "<", $3); }
	|	expression '>' expression								{ $$ = new BinaryOperatorExpression(@$, $1, ">", $3); }
	|	expression T_LESS_OR_EQUAL expression					{ $$ = new BinaryOperatorExpression(@$, $1, "<=", $3); }
	|	expression T_GREATER_OR_EQUAL expression				{ $$ = new BinaryOperatorExpression(@$, $1, ">=", $3); }
	|	T_IDENT													{ $$ = new VarExpression(@$, *$1); delete $1; }
	|	expression '.' T_IDENT									{ $$ = new StructMemberExpression(@$, $1, *$3); delete $3; }
	|	expression T_ARROW T_IDENT								{ $$ = new StructMemberExpression(@$, $1, *$3); delete $3; }
	|	expression '[' expression ']'							{ $$ = new ArraySubscriptExpression(@$, $1, $3); }
	;

argument_list:
		non_empty_argument_list									{ $$ = $1; }
	|															{ $$ = new std::vector<Expression*>(); }
	;

non_empty_argument_list:
		non_empty_argument_list ',' expression					{ $$ = $1; $1->push_back($3); }
	|	expression												{ $$ = new std::vector<Expression*>({$1}); }
	;

