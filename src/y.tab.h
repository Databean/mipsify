/* A Bison parser, made by GNU Bison 3.0.1.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "parser.y" /* yacc.c:1909  */


#include "Declaration.h"
#include "Expression.h"
#include "Statement.h"
#include "Type.h"
#include "Parser.h"
#include "Util.h"

extern Program* program_out;


#line 57 "y.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_IDENT = 258,
    T_STR_CONST = 259,
    T_INT_CONST = 260,
    T_IF = 261,
    T_ELSE = 262,
    T_FOR = 263,
    T_WHILE = 264,
    T_DO = 265,
    T_SIZEOF = 266,
    T_INT_TYPE = 267,
    T_STRING_TYPE = 268,
    T_VOID_TYPE = 269,
    T_STRUCT = 270,
    T_RETURN = 271,
    T_SWITCH = 272,
    T_CASE = 273,
    T_DEFAULT = 274,
    T_BREAK = 275,
    T_CONTINUE = 276,
    T_BOOL_OR = 277,
    T_BOOL_AND = 278,
    T_LEFT_SHIFT = 279,
    T_RIGHT_SHIFT = 280,
    T_PLUS_EQUALS = 281,
    T_MINUS_EQUALS = 282,
    T_STAR_EQUALS = 283,
    T_DIV_EQUALS = 284,
    T_MOD_EQUALS = 285,
    T_EQUAL = 286,
    T_LESS_OR_EQUAL = 287,
    T_GREATER_OR_EQUAL = 288,
    T_NOT_EQUAL = 289,
    T_BIT_OR_EQUALS = 290,
    T_BIT_AND_EQUALS = 291,
    T_BIT_XOR_EQUALS = 292,
    T_BIT_NOT_EQUALS = 293,
    T_ARROW = 294,
    T_LEFT_SHIFT_EQUALS = 295,
    T_RIGHT_SHIFT_EQUALS = 296,
    T_PLUS_PLUS = 297,
    T_MINUS_MINUS = 298,
    T_UNTERM_STRING = 299,
    T_UNTERM_COMMENT = 300,
    PREC_ADDRESS = 301,
    PREC_DEREFERENCE = 302,
    PREC_UNARY_MINUS = 303,
    PREC_UNARY_PLUS = 304,
    PREC_SUFFIX_PLUS_PLUS = 305,
    PREC_SUFFIX_MINUS_MINUS = 306,
    PREC_PREFIX_PLUS_PLUS = 307,
    PREC_PREFIX_MINUS_MINUS = 308,
    PREC_APPLICATION = 309
  };
#endif
/* Tokens.  */
#define T_IDENT 258
#define T_STR_CONST 259
#define T_INT_CONST 260
#define T_IF 261
#define T_ELSE 262
#define T_FOR 263
#define T_WHILE 264
#define T_DO 265
#define T_SIZEOF 266
#define T_INT_TYPE 267
#define T_STRING_TYPE 268
#define T_VOID_TYPE 269
#define T_STRUCT 270
#define T_RETURN 271
#define T_SWITCH 272
#define T_CASE 273
#define T_DEFAULT 274
#define T_BREAK 275
#define T_CONTINUE 276
#define T_BOOL_OR 277
#define T_BOOL_AND 278
#define T_LEFT_SHIFT 279
#define T_RIGHT_SHIFT 280
#define T_PLUS_EQUALS 281
#define T_MINUS_EQUALS 282
#define T_STAR_EQUALS 283
#define T_DIV_EQUALS 284
#define T_MOD_EQUALS 285
#define T_EQUAL 286
#define T_LESS_OR_EQUAL 287
#define T_GREATER_OR_EQUAL 288
#define T_NOT_EQUAL 289
#define T_BIT_OR_EQUALS 290
#define T_BIT_AND_EQUALS 291
#define T_BIT_XOR_EQUALS 292
#define T_BIT_NOT_EQUALS 293
#define T_ARROW 294
#define T_LEFT_SHIFT_EQUALS 295
#define T_RIGHT_SHIFT_EQUALS 296
#define T_PLUS_PLUS 297
#define T_MINUS_MINUS 298
#define T_UNTERM_STRING 299
#define T_UNTERM_COMMENT 300
#define PREC_ADDRESS 301
#define PREC_DEREFERENCE 302
#define PREC_UNARY_MINUS 303
#define PREC_UNARY_PLUS 304
#define PREC_SUFFIX_PLUS_PLUS 305
#define PREC_SUFFIX_MINUS_MINUS 306
#define PREC_PREFIX_PLUS_PLUS 307
#define PREC_PREFIX_MINUS_MINUS 308
#define PREC_APPLICATION 309

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 29 "parser.y" /* yacc.c:1909  */

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

#line 197 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
