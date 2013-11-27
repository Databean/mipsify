/* A Bison parser, made by GNU Bison 3.0.1.  */

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
#define YYBISON_VERSION "3.0.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 18 "parser.y" /* yacc.c:339  */

#include "Parser.h"
#include "scanner.h"
#include <string>
#include <iostream>
#include "Type.h"


#line 75 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
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
#line 1 "parser.y" /* yacc.c:355  */


#include "Declaration.h"
#include "Expression.h"
#include "Statement.h"
#include "Type.h"
#include "Parser.h"
#include "Util.h"

extern Program* program_out;


#line 118 "y.tab.c" /* yacc.c:355  */

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
#line 29 "parser.y" /* yacc.c:355  */

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

#line 258 "y.tab.c" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 287 "y.tab.c" /* yacc.c:358  */

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


#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

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
# define YYCOPY_NEEDED 1
#endif


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   1431

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  208

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    67,     2,     2,     2,    66,    59,     2,
      71,    72,    64,    62,    55,    63,    69,    65,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    77,    73,
      61,    56,    60,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    70,     2,    74,    58,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    75,    57,    76,    68,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   123,   123,   127,   128,   132,   133,   134,   135,   136,
     137,   138,   142,   143,   147,   148,   152,   153,   157,   161,
     162,   166,   170,   171,   172,   173,   174,   178,   182,   183,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   256,   257,   261,   262
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_IDENT", "T_STR_CONST", "T_INT_CONST",
  "T_IF", "T_ELSE", "T_FOR", "T_WHILE", "T_DO", "T_SIZEOF", "T_INT_TYPE",
  "T_STRING_TYPE", "T_VOID_TYPE", "T_STRUCT", "T_RETURN", "T_SWITCH",
  "T_CASE", "T_DEFAULT", "T_BREAK", "T_CONTINUE", "T_BOOL_OR",
  "T_BOOL_AND", "T_LEFT_SHIFT", "T_RIGHT_SHIFT", "T_PLUS_EQUALS",
  "T_MINUS_EQUALS", "T_STAR_EQUALS", "T_DIV_EQUALS", "T_MOD_EQUALS",
  "T_EQUAL", "T_LESS_OR_EQUAL", "T_GREATER_OR_EQUAL", "T_NOT_EQUAL",
  "T_BIT_OR_EQUALS", "T_BIT_AND_EQUALS", "T_BIT_XOR_EQUALS",
  "T_BIT_NOT_EQUALS", "T_ARROW", "T_LEFT_SHIFT_EQUALS",
  "T_RIGHT_SHIFT_EQUALS", "T_PLUS_PLUS", "T_MINUS_MINUS",
  "T_UNTERM_STRING", "T_UNTERM_COMMENT", "PREC_ADDRESS",
  "PREC_DEREFERENCE", "PREC_UNARY_MINUS", "PREC_UNARY_PLUS",
  "PREC_SUFFIX_PLUS_PLUS", "PREC_SUFFIX_MINUS_MINUS",
  "PREC_PREFIX_PLUS_PLUS", "PREC_PREFIX_MINUS_MINUS", "PREC_APPLICATION",
  "','", "'='", "'|'", "'^'", "'&'", "'>'", "'<'", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'!'", "'~'", "'.'", "'['", "'('", "')'", "';'", "']'",
  "'{'", "'}'", "':'", "$accept", "root", "root_declare_list",
  "root_declare", "constant", "param_list", "non_empty_param_list",
  "param", "struct_list", "struct_member", "type", "statement_block",
  "statement_list", "statement", "expression", "argument_list",
  "non_empty_argument_list", YY_NULLPTR
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
     305,   306,   307,   308,   309,    44,    61,   124,    94,    38,
      62,    60,    43,    45,    42,    47,    37,    33,   126,    46,
      91,    40,    41,    59,    93,   123,   125,    58
};
# endif

#define YYPACT_NINF -68

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-68)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -68,     7,    29,   -68,   -68,   -68,   -68,     0,   -68,    -1,
     -67,   -35,   -68,   -68,   -68,    41,    14,   104,   -68,    74,
     -68,   -68,   -43,   -50,    30,    -6,    12,   -68,    26,    20,
      23,    28,   -68,    47,   -68,     6,   104,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,    94,    50,    53,    54,
      55,   242,    56,    80,    57,    96,    58,    60,    65,    80,
      80,    80,    80,    80,    80,    80,    80,    80,   -68,   -68,
      31,   -68,   -68,   349,    80,    80,    80,    80,   131,   104,
     401,    80,    64,   -68,   -68,   -68,   164,   164,   164,   164,
     164,   164,   164,   164,   609,   -33,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,   142,    80,    80,   -68,   -68,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,   149,    80,
     -68,   915,    82,   105,   660,   453,   711,    88,   -63,   -68,
     762,   -68,   -68,    80,   158,   -68,  1159,  1202,   151,   151,
    1062,  1062,  1013,  1013,  1013,  1314,  1361,  1326,  1314,   915,
     915,   915,   -68,   964,   964,  1111,  1215,  1258,  1271,  1326,
    1361,   159,   159,   164,   164,   164,   -68,   296,   -68,    80,
     242,    80,   242,    80,   -68,    89,   505,    92,   -68,   915,
     160,   557,   -68,   813,   -68,   -68,    95,   242,    80,   102,
     168,   -68,   -68,   864,   -68,   -68,   242,   -68
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    24,    26,    25,     0,     3,     0,
      23,     0,    22,    11,    20,     0,     0,    15,     7,     0,
      13,    12,     0,     0,     0,     0,    14,    17,     0,     0,
       0,     0,     9,     0,    23,     0,     0,    18,    10,    19,
      21,     8,     5,    29,     6,    16,     0,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    27,    61,
       0,    37,    28,     0,    94,     0,     0,     0,     0,     0,
       0,     0,     0,    44,    40,    41,    58,    60,    70,    67,
      68,    69,    65,    66,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      30,    96,     0,    93,     0,     0,     0,     0,     0,    45,
       0,    43,    62,     0,     0,    31,    80,    79,    81,    82,
      47,    48,    49,    50,    51,    83,    87,    88,    84,    53,
      52,    54,    91,    55,    56,    46,    77,    78,    76,    86,
      85,    71,    72,    73,    74,    75,    90,     0,    63,     0,
       0,     0,     0,     0,    64,     0,     0,     0,    92,    95,
      38,     0,    34,     0,    29,    32,     0,     0,     0,     0,
       0,    33,    39,     0,    35,    42,     0,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -68,   -68,   -68,   -68,   176,   -68,   -68,   156,   -68,   -68,
       3,   161,     1,   -51,   -49,   -68,   -68
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     8,    69,    25,    26,    27,    19,    30,
      70,    71,    46,    72,    73,   132,   133
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      78,    12,    11,    10,    80,     9,    13,     3,    14,   184,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    23,
      28,    15,    31,   143,    33,   131,   134,   135,   136,    37,
      32,    40,   140,    34,    95,    16,    17,   144,    18,    28,
     145,     4,     5,     6,     7,    20,    21,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,    12,   163,   164,    35,    36,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,    42,
     177,    43,   138,    47,    20,    21,     4,     5,     6,    24,
      12,    52,    12,    38,   186,    12,    39,    47,    20,    21,
      48,    82,    49,    50,    51,    52,     4,     5,     6,    24,
      53,    54,    55,    56,    57,    58,     4,     5,     6,    24,
      41,    74,    59,    60,    75,    76,    77,    79,    81,   190,
     189,   192,   191,    84,   193,    83,    59,    60,    85,    61,
     137,   141,    62,    63,    64,   162,   202,    65,    66,   203,
      29,    67,   176,    61,   178,   207,    62,    63,    64,   183,
     179,    65,    66,   187,   194,    67,   196,   197,   201,    43,
      68,    47,    20,    21,    48,   204,    49,    50,    51,    52,
       4,     5,     6,    24,    53,    54,    55,    56,    57,    58,
     112,    22,    45,   115,   116,   200,    44,     0,   112,     0,
       0,   115,   116,   112,     0,     0,   115,   116,     0,     0,
      59,    60,     0,   123,   124,   125,   126,   127,     0,     0,
     128,   129,     0,   125,   126,   127,     0,    61,   128,   129,
      62,    63,    64,   128,   129,    65,    66,     0,     0,    67,
       0,     0,     0,    43,   205,    47,    20,    21,    48,     0,
      49,    50,    51,    52,     4,     5,     6,    24,    53,    54,
      55,    56,    57,    58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    59,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,     0,    62,    63,    64,     0,     0,    65,
      66,     0,     0,    67,     0,     0,     0,    43,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,     0,   112,   113,   114,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,     0,     0,   128,   129,     0,     0,     0,
     188,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,     0,   112,   113,
     114,   115,   116,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,     0,     0,   128,   129,
       0,     0,   130,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,     0,
     112,   113,   114,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,     0,     0,
     128,   129,     0,     0,   139,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,     0,   112,   113,   114,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
       0,     0,   128,   129,     0,     0,   181,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,     0,   112,   113,   114,   115,   116,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,     0,     0,   128,   129,     0,     0,   195,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,     0,   112,   113,   114,   115,
     116,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,     0,   128,   129,     0,     0,
     198,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,     0,   112,   113,
     114,   115,   116,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,     0,     0,   128,   129,
       0,   142,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,     0,   112,
     113,   114,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,     0,     0,   128,
     129,     0,   180,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,     0,
     112,   113,   114,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,     0,     0,
     128,   129,     0,   182,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
       0,   112,   113,   114,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,     0,
       0,   128,   129,     0,   185,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,     0,   112,   113,   114,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
       0,     0,   128,   129,     0,   199,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,     0,   112,   113,   114,   115,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,     0,     0,   128,   129,     0,   206,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,     0,   112,   113,   114,   115,   116,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,     0,     0,   128,   129,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,     0,
       0,     0,     0,   112,   113,   114,   115,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,     0,     0,   128,   129,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,     0,     0,
       0,     0,   112,     0,     0,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
       0,     0,   128,   129,    96,    97,    98,    99,   100,   101,
       0,     0,     0,   105,   106,   107,   108,     0,     0,     0,
       0,   112,     0,     0,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,     0,
       0,   128,   129,    96,    97,    98,    99,     0,     0,     0,
       0,     0,   105,   106,   107,   108,     0,     0,     0,     0,
     112,     0,     0,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,     0,     0,
     128,   129,    97,    98,    99,     0,     0,     0,     0,     0,
     105,   106,   107,   108,     0,     0,     0,     0,   112,     0,
       0,   115,   116,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    98,    99,   128,   129,
       0,     0,     0,   105,   106,   107,   108,     0,     0,    98,
      99,   112,     0,     0,   115,   116,   105,   106,   107,   108,
       0,     0,     0,     0,   112,     0,     0,   115,   116,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,     0,
       0,   128,   129,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    98,    99,   128,   129,     0,     0,     0,   105,
     106,   107,   108,     0,     0,    98,    99,   112,     0,     0,
     115,   116,   105,   106,   107,   108,     0,     0,     0,     0,
     112,     0,     0,   115,   116,     0,     0,   120,   121,   122,
     123,   124,   125,   126,   127,     0,     0,   128,   129,     0,
       0,   121,   122,   123,   124,   125,   126,   127,    98,    99,
     128,   129,     0,     0,     0,     0,   106,   107,     0,     0,
      98,    99,     0,   112,     0,     0,   115,   116,   106,     0,
       0,     0,     0,     0,     0,   112,     0,     0,   115,   116,
       0,     0,     0,     0,   121,   122,   123,   124,   125,   126,
     127,     0,     0,   128,   129,    98,    99,   122,   123,   124,
     125,   126,   127,     0,     0,   128,   129,     0,     0,     0,
     112,     0,     0,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   123,   124,   125,   126,   127,     0,     0,
     128,   129
};

static const yytype_int16 yycheck[] =
{
      51,    64,     3,     3,    53,     2,    73,     0,    75,    72,
      59,    60,    61,    62,    63,    64,    65,    66,    67,     5,
      17,    56,    19,    56,    74,    74,    75,    76,    77,     3,
      73,     3,    81,     3,     3,    70,    71,    70,    73,    36,
      73,    12,    13,    14,    15,     4,     5,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,    64,   113,   114,    72,    55,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    73,
     129,    75,    79,     3,     4,     5,    12,    13,    14,    15,
      64,    11,    64,    73,   143,    64,    73,     3,     4,     5,
       6,     5,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    12,    13,    14,    15,
      73,    71,    42,    43,    71,    71,    71,    71,    71,   180,
     179,   182,   181,    73,   183,    77,    42,    43,    73,    59,
       9,    77,    62,    63,    64,     3,   197,    67,    68,   198,
      76,    71,     3,    59,    72,   206,    62,    63,    64,    71,
      55,    67,    68,     5,    75,    71,    74,     7,    73,    75,
      76,     3,     4,     5,     6,    73,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      39,    15,    36,    42,    43,   194,    35,    -1,    39,    -1,
      -1,    42,    43,    39,    -1,    -1,    42,    43,    -1,    -1,
      42,    43,    -1,    62,    63,    64,    65,    66,    -1,    -1,
      69,    70,    -1,    64,    65,    66,    -1,    59,    69,    70,
      62,    63,    64,    69,    70,    67,    68,    -1,    -1,    71,
      -1,    -1,    -1,    75,    76,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    -1,    -1,    62,    63,    64,    -1,    -1,    67,
      68,    -1,    -1,    71,    -1,    -1,    -1,    75,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    -1,    69,    70,    -1,    -1,    -1,
      74,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    69,    70,
      -1,    -1,    73,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      69,    70,    -1,    -1,    73,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    69,    70,    -1,    -1,    73,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    -1,    -1,    69,    70,    -1,    -1,    73,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    -1,    69,    70,    -1,    -1,
      73,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    -1,    -1,    69,    70,
      -1,    72,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    -1,    -1,    69,
      70,    -1,    72,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      69,    70,    -1,    72,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    69,    70,    -1,    72,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    69,    70,    -1,    72,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    39,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    69,    70,    -1,    72,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    -1,    -1,    69,    70,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    69,    70,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      -1,    -1,    69,    70,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    69,    70,    22,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    -1,    -1,
      69,    70,    23,    24,    25,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    24,    25,    69,    70,
      -1,    -1,    -1,    31,    32,    33,    34,    -1,    -1,    24,
      25,    39,    -1,    -1,    42,    43,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    42,    43,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    69,    70,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    24,    25,    69,    70,    -1,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    24,    25,    39,    -1,    -1,
      42,    43,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    42,    43,    -1,    -1,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    69,    70,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    24,    25,
      69,    70,    -1,    -1,    -1,    -1,    32,    33,    -1,    -1,
      24,    25,    -1,    39,    -1,    -1,    42,    43,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      66,    -1,    -1,    69,    70,    24,    25,    61,    62,    63,
      64,    65,    66,    -1,    -1,    69,    70,    -1,    -1,    -1,
      39,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,
      69,    70
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    79,    80,     0,    12,    13,    14,    15,    81,    88,
       3,     3,    64,    73,    75,    56,    70,    71,    73,    86,
       4,     5,    82,     5,    15,    83,    84,    85,    88,    76,
      87,    88,    73,    74,     3,    72,    55,     3,    73,    73,
       3,    73,    73,    75,    89,    85,    90,     3,     6,     8,
       9,    10,    11,    16,    17,    18,    19,    20,    21,    42,
      43,    59,    62,    63,    64,    67,    68,    71,    76,    82,
      88,    89,    91,    92,    71,    71,    71,    71,    91,    71,
      92,    71,     5,    77,    73,    73,    92,    92,    92,    92,
      92,    92,    92,    92,    92,     3,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    39,    40,    41,    42,    43,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    69,    70,
      73,    92,    93,    94,    92,    92,    92,     9,    88,    73,
      92,    77,    72,    56,    70,    73,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,     3,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,     3,    92,    72,    55,
      72,    73,    72,    71,    72,    72,    92,     5,    74,    92,
      91,    92,    91,    92,    75,    73,    74,     7,    73,    72,
      90,    73,    91,    92,    73,    76,    72,    91
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    80,    80,    81,    81,    81,    81,    81,
      81,    81,    82,    82,    83,    83,    84,    84,    85,    86,
      86,    87,    88,    88,    88,    88,    88,    89,    90,    90,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    93,    93,    94,    94
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     6,     6,     3,     6,     5,
       6,     3,     1,     1,     1,     0,     3,     1,     2,     3,
       0,     2,     2,     2,     1,     1,     1,     3,     2,     0,
       2,     3,     5,     6,     5,     7,     9,     1,     5,     7,
       2,     2,     7,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       2,     1,     3,     4,     4,     2,     2,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     3,     4,     1,     0,     3,     1
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
      YY_LAC_DISCARD ("YYBACKUP");                              \
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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

/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return 1 if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYSIZE_T *yycapacity, YYSIZE_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yytype_int16 **yybottom,
                      yytype_int16 *yybottom_no_free,
                      yytype_int16 **yytop, yytype_int16 *yytop_empty)
{
  YYSIZE_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYSIZE_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYSIZE_T yyalloc = 2 * yysize_new;
      yytype_int16 *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        (yytype_int16*) YYSTACK_ALLOC (yyalloc * sizeof *yybottom_new);
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                         \
do {                                                             \
  if (!yy_lac_established)                                       \
    {                                                            \
      YYDPRINTF ((stderr,                                        \
                  "LAC: initial context established for %s\n",   \
                  yytname[yytoken]));                            \
      yy_lac_established = 1;                                    \
      {                                                          \
        int yy_lac_status =                                      \
          yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken); \
        if (yy_lac_status == 2)                                  \
          goto yyexhaustedlab;                                   \
        if (yy_lac_status == 1)                                  \
          goto yyerrlab;                                         \
      }                                                          \
    }                                                            \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      if (yydebug)                                                       \
        YYFPRINTF (stderr, "LAC: initial context discarded due to "      \
                   Event "\n");                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return 2 if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yytype_int16 *yyesa, yytype_int16 **yyes,
        YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  yytype_int16 *yyes_prev = yyssp;
  yytype_int16 *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          yyrule = yydefact[*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      {
        YYSIZE_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
        if (yyesp != yyes_prev)
          {
            YYSIZE_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yylen -= yysize;
                yyesp = yyes_prev;
              }
          }
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      {
        int yystate;
        {
          int yylhs = yyr1[yyrule] - YYNTOKENS;
          yystate = yypgoto[yylhs] + *yyesp;
          if (yystate < 0 || YYLAST < yystate
              || yycheck[yystate] != *yyesp)
            yystate = yydefgoto[yylhs];
          else
            yystate = yytable[yystate];
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            *yyesp = yystate;
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return 2;
              }
            *++yyesp = yystate;
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


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
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store or if
   yy_lac returned 2.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyesa, yytype_int16 **yyes,
                YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
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
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          int yyx;

          for (yyx = 0; yyx < YYNTOKENS; ++yyx)
            if (yyx != YYTERROR && yyx != YYUNDEFTOK)
              {
                {
                  int yy_lac_status = yy_lac (yyesa, yyes, yyes_capacity,
                                              yyssp, yyx);
                  if (yy_lac_status == 2)
                    return 2;
                  if (yy_lac_status == 1)
                    continue;
                }
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
# if YYDEBUG
      else if (yydebug)
        YYFPRINTF (stderr, "No expected tokens.\n");
# endif
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

    yytype_int16 yyesa[20];
    yytype_int16 *yyes;
    YYSIZE_T yyes_capacity;

  int yy_lac_established = 0;
  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  yyes = yyesa;
  yyes_capacity = sizeof yyesa / sizeof *yyes;
  if (YYMAXDEPTH < yyes_capacity)
    yyes_capacity = YYMAXDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      YY_LAC_ESTABLISH;
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
  YY_LAC_DISCARD ("shift");

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
          case 2:
#line 123 "parser.y" /* yacc.c:1646  */
    { (yyval.cstr) = NULL; program_out = new Program((yyloc), *(yyvsp[0].declareList)); delete (yyvsp[0].declareList); }
#line 2086 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 127 "parser.y" /* yacc.c:1646  */
    { (yyval.declareList) = (yyvsp[-1].declareList); (yyvsp[-1].declareList)->push_back((yyvsp[0].declare)); }
#line 2092 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 128 "parser.y" /* yacc.c:1646  */
    { (yyval.declareList) = new std::vector<Declaration*>(); }
#line 2098 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 132 "parser.y" /* yacc.c:1646  */
    { (yyval.declare) = new FunctionPrototype((yyloc), (yyvsp[-5].type), *(yyvsp[-4].ident), *(yyvsp[-2].paramList)); delete (yyvsp[-4].ident); delete (yyvsp[-2].paramList); }
#line 2104 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 133 "parser.y" /* yacc.c:1646  */
    { (yyval.declare) = new FunctionDeclaration((yyloc), (yyvsp[-5].type), *(yyvsp[-4].ident), *(yyvsp[-2].paramList), (yyvsp[0].statementBlock)); delete (yyvsp[-4].ident); delete (yyvsp[-2].paramList); }
#line 2110 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 134 "parser.y" /* yacc.c:1646  */
    { (yyval.declare) = new GlobalVarDeclaration((yyloc), (yyvsp[-2].type), *(yyvsp[-1].ident)); delete (yyvsp[-1].ident); }
#line 2116 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 135 "parser.y" /* yacc.c:1646  */
    { (yyval.declare) = new GlobalArrayDeclaration((yyloc), (yyvsp[-5].type), *(yyvsp[-4].ident), (yyvsp[-2].intConst)); delete (yyvsp[-4].ident); }
#line 2122 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 136 "parser.y" /* yacc.c:1646  */
    { (yyval.declare) = new GlobalVarDeclarationInit((yyloc), (yyvsp[-4].type), *(yyvsp[-3].ident), (yyvsp[-1].constant)); delete (yyvsp[-3].ident); }
#line 2128 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 137 "parser.y" /* yacc.c:1646  */
    { (yyval.declare) = new StructDeclaration((yyloc), *(yyvsp[-4].ident), *(yyvsp[-2].structMemberList)); delete (yyvsp[-4].ident); delete (yyvsp[-2].structMemberList); }
#line 2134 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 138 "parser.y" /* yacc.c:1646  */
    { (yyval.declare) = new StructPredeclaration((yyloc), *(yyvsp[-1].ident)); delete (yyvsp[-1].ident); }
#line 2140 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 142 "parser.y" /* yacc.c:1646  */
    { (yyval.constant) = new IntConstantExpression((yyloc), (yyvsp[0].intConst)); }
#line 2146 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 143 "parser.y" /* yacc.c:1646  */
    { (yyval.constant) = new StringConstantExpression((yyloc), *(yyvsp[0].strConst)); delete (yyvsp[0].strConst); }
#line 2152 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 147 "parser.y" /* yacc.c:1646  */
    { (yyval.paramList) = (yyvsp[0].paramList); }
#line 2158 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 148 "parser.y" /* yacc.c:1646  */
    { (yyval.paramList) = new std::vector<FunctionParameter*>(); }
#line 2164 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 152 "parser.y" /* yacc.c:1646  */
    { (yyval.paramList) = (yyvsp[-2].paramList); (yyvsp[-2].paramList)->push_back((yyvsp[0].param)); }
#line 2170 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 153 "parser.y" /* yacc.c:1646  */
    { (yyval.paramList) = new std::vector<FunctionParameter*>({(yyvsp[0].param)}); }
#line 2176 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 157 "parser.y" /* yacc.c:1646  */
    { (yyval.param) = new FunctionParameter((yyloc), (yyvsp[-1].type), *(yyvsp[0].ident)); delete (yyvsp[0].ident); }
#line 2182 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 161 "parser.y" /* yacc.c:1646  */
    { (yyval.structMemberList) = (yyvsp[-2].structMemberList); (yyvsp[-2].structMemberList)->push_back((yyvsp[-1].structMember)); }
#line 2188 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 162 "parser.y" /* yacc.c:1646  */
    { (yyval.structMemberList) = new std::vector<StructMember*>(); }
#line 2194 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 166 "parser.y" /* yacc.c:1646  */
    { (yyval.structMember) = new StructMember((yyloc), (yyvsp[-1].type), *(yyvsp[0].ident)); delete (yyvsp[0].ident); }
#line 2200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 170 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new PointerType((yyvsp[-1].type)); }
#line 2206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 171 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new StructType(*(yyvsp[0].ident)); delete (yyvsp[0].ident); }
#line 2212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 172 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new IntType(); }
#line 2218 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 173 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new VoidType(); }
#line 2224 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 174 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new StringType(); }
#line 2230 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 178 "parser.y" /* yacc.c:1646  */
    { (yyval.statementBlock) = new StatementBlock((yyloc), *(yyvsp[-1].statementList)); delete (yyvsp[-1].statementList); }
#line 2236 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 182 "parser.y" /* yacc.c:1646  */
    { (yyval.statementList) = (yyvsp[-1].statementList); (yyvsp[-1].statementList)->push_back((yyvsp[0].statement)); }
#line 2242 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 183 "parser.y" /* yacc.c:1646  */
    { (yyval.statementList) = new std::vector<Statement*>(); }
#line 2248 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 187 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[-1].expression); }
#line 2254 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 188 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new VarDeclaration((yyloc), (yyvsp[-2].type), *(yyvsp[-1].ident)); delete (yyvsp[-1].ident); }
#line 2260 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 189 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new VarDeclarationInit((yyloc), (yyvsp[-4].type), *(yyvsp[-3].ident), (yyvsp[-1].expression)); delete (yyvsp[-3].ident); }
#line 2266 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 190 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ArrayDeclaration((yyloc), (yyvsp[-5].type), *(yyvsp[-4].ident), (yyvsp[-2].intConst)); delete (yyvsp[-4].ident); }
#line 2272 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 191 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new WhileStatement((yyloc), (yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2278 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 192 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new DoWhileStatement((yyloc), (yyvsp[-5].statement), (yyvsp[-2].expression)); }
#line 2284 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 193 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ForStatement((yyloc), (yyvsp[-6].expression), (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2290 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 194 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].statementBlock); }
#line 2296 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 195 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new IfStatement((yyloc), (yyvsp[-2].expression), (yyvsp[0].statement)); }
#line 2302 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 196 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new IfElseStatement((yyloc), (yyvsp[-4].expression), (yyvsp[-2].statement), (yyvsp[0].statement)); }
#line 2308 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 197 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new BreakStatement((yyloc)); }
#line 2314 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 198 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ContinueStatement((yyloc)); }
#line 2320 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 199 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new SwitchStatement((yyloc), (yyvsp[-4].expression), *(yyvsp[-1].statementList)); delete (yyvsp[-1].statementList); }
#line 2326 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 200 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new CaseStatement((yyloc), (yyvsp[-1].intConst)); }
#line 2332 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 201 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new DefaultStatement((yyloc)); }
#line 2338 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 202 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = new ReturnStatement((yyloc), (yyvsp[-1].expression)); }
#line 2344 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 206 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new AssignExpression((yyloc), (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2350 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 207 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new AssignExpression((yyloc), (yyvsp[-2].expression), new BinaryOperatorExpression((yylsp[0]), (yyvsp[-2].expression)->clone(), "+", (yyvsp[0].expression))); }
#line 2356 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 208 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new AssignExpression((yyloc), (yyvsp[-2].expression), new BinaryOperatorExpression((yylsp[0]), (yyvsp[-2].expression)->clone(), "-", (yyvsp[0].expression))); }
#line 2362 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 209 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new AssignExpression((yyloc), (yyvsp[-2].expression), new BinaryOperatorExpression((yylsp[0]), (yyvsp[-2].expression)->clone(), "*", (yyvsp[0].expression))); }
#line 2368 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 210 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new AssignExpression((yyloc), (yyvsp[-2].expression), new BinaryOperatorExpression((yylsp[0]), (yyvsp[-2].expression)->clone(), "/", (yyvsp[0].expression))); }
#line 2374 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 211 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new AssignExpression((yyloc), (yyvsp[-2].expression), new BinaryOperatorExpression((yylsp[0]), (yyvsp[-2].expression)->clone(), "%", (yyvsp[0].expression))); }
#line 2380 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 212 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new AssignExpression((yyloc), (yyvsp[-2].expression), new BinaryOperatorExpression((yylsp[0]), (yyvsp[-2].expression)->clone(), "&", (yyvsp[0].expression))); }
#line 2386 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 213 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new AssignExpression((yyloc), (yyvsp[-2].expression), new BinaryOperatorExpression((yylsp[0]), (yyvsp[-2].expression)->clone(), "|", (yyvsp[0].expression))); }
#line 2392 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 214 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new AssignExpression((yyloc), (yyvsp[-2].expression), new BinaryOperatorExpression((yylsp[0]), (yyvsp[-2].expression)->clone(), "^", (yyvsp[0].expression))); }
#line 2398 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 215 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new AssignExpression((yyloc), (yyvsp[-2].expression), new BinaryOperatorExpression((yylsp[0]), (yyvsp[-2].expression)->clone(), "<<", (yyvsp[0].expression))); }
#line 2404 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 216 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new AssignExpression((yyloc), (yyvsp[-2].expression), new BinaryOperatorExpression((yylsp[0]), (yyvsp[-2].expression)->clone(), ">>", (yyvsp[0].expression))); }
#line 2410 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 217 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new UnaryAssignExpression((yyloc), (yyvsp[-1].expression), "++"); }
#line 2416 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 218 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new UnaryAssignExpression((yyloc), "++", (yyvsp[0].expression)); }
#line 2422 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 219 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new UnaryAssignExpression((yyloc), (yyvsp[-1].expression), "--"); }
#line 2428 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 220 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new UnaryAssignExpression((yyloc), "--", (yyvsp[0].expression)); }
#line 2434 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 221 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].constant); }
#line 2440 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 222 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[-1].expression); }
#line 2446 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 223 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new FunctionCallExpression((yyloc), *(yyvsp[-3].ident), *(yyvsp[-1].expressionList)); delete (yyvsp[-3].ident); delete (yyvsp[-1].expressionList); }
#line 2452 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 224 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new SizeofExpression((yyloc), (yyvsp[-1].type)); }
#line 2458 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 225 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new UnaryOperatorExpression((yyloc), "!", (yyvsp[0].expression)); }
#line 2464 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 226 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new UnaryOperatorExpression((yyloc), "~", (yyvsp[0].expression)); }
#line 2470 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 227 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new UnaryOperatorExpression((yyloc), "+", (yyvsp[0].expression)); }
#line 2476 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 228 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new UnaryOperatorExpression((yyloc), "-", (yyvsp[0].expression)); }
#line 2482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 229 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new ArraySubscriptExpression((yyloc), (yyvsp[0].expression), new IntConstantExpression((yylsp[0]), 0)); }
#line 2488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 230 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new UnaryOperatorExpression((yyloc), "&", (yyvsp[0].expression)); }
#line 2494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 231 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "+", (yyvsp[0].expression)); }
#line 2500 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 232 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "-", (yyvsp[0].expression)); }
#line 2506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 233 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "*", (yyvsp[0].expression)); }
#line 2512 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 234 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "/", (yyvsp[0].expression)); }
#line 2518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 235 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "%", (yyvsp[0].expression)); }
#line 2524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 236 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "&", (yyvsp[0].expression)); }
#line 2530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 237 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "|", (yyvsp[0].expression)); }
#line 2536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 238 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "^", (yyvsp[0].expression)); }
#line 2542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 239 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "&&", (yyvsp[0].expression)); }
#line 2548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 240 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "||", (yyvsp[0].expression)); }
#line 2554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 241 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "<<", (yyvsp[0].expression)); }
#line 2560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 242 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), ">>", (yyvsp[0].expression)); }
#line 2566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 243 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "==", (yyvsp[0].expression)); }
#line 2572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 244 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "!=", (yyvsp[0].expression)); }
#line 2578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 245 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "<", (yyvsp[0].expression)); }
#line 2584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 246 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), ">", (yyvsp[0].expression)); }
#line 2590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 247 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), "<=", (yyvsp[0].expression)); }
#line 2596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 248 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new BinaryOperatorExpression((yyloc), (yyvsp[-2].expression), ">=", (yyvsp[0].expression)); }
#line 2602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 249 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new VarExpression((yyloc), *(yyvsp[0].ident)); delete (yyvsp[0].ident); }
#line 2608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 250 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new StructMemberExpression((yyloc), (yyvsp[-2].expression), *(yyvsp[0].ident)); delete (yyvsp[0].ident); }
#line 2614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 251 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new StructMemberExpression((yyloc), (yyvsp[-2].expression), *(yyvsp[0].ident)); delete (yyvsp[0].ident); }
#line 2620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 252 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = new ArraySubscriptExpression((yyloc), (yyvsp[-3].expression), (yyvsp[-1].expression)); }
#line 2626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 256 "parser.y" /* yacc.c:1646  */
    { (yyval.expressionList) = (yyvsp[0].expressionList); }
#line 2632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 257 "parser.y" /* yacc.c:1646  */
    { (yyval.expressionList) = new std::vector<Expression*>(); }
#line 2638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 261 "parser.y" /* yacc.c:1646  */
    { (yyval.expressionList) = (yyvsp[-2].expressionList); (yyvsp[-2].expressionList)->push_back((yyvsp[0].expression)); }
#line 2644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 262 "parser.y" /* yacc.c:1646  */
    { (yyval.expressionList) = new std::vector<Expression*>({(yyvsp[0].expression)}); }
#line 2650 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2654 "y.tab.c" /* yacc.c:1646  */
        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
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
  *++yylsp = yyloc;

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
                                        yyesa, &yyes, &yyes_capacity, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if 1
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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}