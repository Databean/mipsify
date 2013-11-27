%{
#include "scanner.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_STR_CONST 1000
char string_buf[MAX_STR_CONST];
char *string_buf_ptr;
int line_num = 1;
int line_pos = 1;

void updatePosition();
#define YY_USER_ACTION updatePosition();

%}

NUMBER	(0)|([1-9][0-9]*)
HEXNUM	((0x)|(0X))([a-fA-F0-9]+)
IDENT	[a-zA-Z_][a-zA-Z0-9_]*

%x comment
%x str

%option noyywrap
%option yylineno
%option nounput

%%

\"      string_buf_ptr = string_buf; BEGIN(str);
<str>{
\"		{ /* saw closing quote - all done */
			BEGIN(INITIAL);
			*string_buf_ptr = '\0';
			/* return string constant token type and
			* value to parser
			*/
			yylval.strConst = new std::string(string_buf);
			return T_STR_CONST;
		}

\n		{
			/* error - unterminated string constant */
			/* generate error message */
			yyerror("Unterminated string constant.");
		}

<<EOF>>	{ return T_UNTERM_STRING; }

\\[0-7]{1,3} {
		/* octal escape sequence */
		int result;
		
		(void) sscanf( yytext + 1, "%o", &result );

		if ( result > 0xff )
				/* error, constant is out-of-bounds */

		*string_buf_ptr++ = result;
		}

\\[0-9]+ {
		/* generate error - bad escape sequence; something
		* like '\48' or '\0777777'
		*/
		yyerror("Bad string escape sequence.");
		}

\\n			*string_buf_ptr++ = '\n';
\\t			*string_buf_ptr++ = '\t';
\\r			*string_buf_ptr++ = '\r';
\\b			*string_buf_ptr++ = '\b';
\\f			*string_buf_ptr++ = '\f';

\\(.|\n)	*string_buf_ptr++ = yytext[1];

[^\\\n\"]+	{
			char *yptr = yytext;
			
			while ( *yptr )
					*string_buf_ptr++ = *yptr++;
			}
}

"/*"			BEGIN(comment);
<comment>{
[^*\n]*        /* eat anything that's not a '*' */
"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
\n             
<<EOF>>			{ return T_UNTERM_COMMENT; }
"*"+"/"        BEGIN(INITIAL);
}

"do"			{ return T_DO; }
"while"			{ return T_WHILE; }
"for"			{ return T_FOR; }
"if"			{ return T_IF; }
"else"			{ return T_ELSE; }
"int"			{ return T_INT_TYPE; }
"string"		{ return T_STRING_TYPE; }
"void"			{ return T_VOID_TYPE; }
"struct"		{ return T_STRUCT; }
"return"		{ return T_RETURN; }
"switch"		{ return T_SWITCH; }
"case"			{ return T_CASE; }
"default"		{ return T_DEFAULT; }
"break"			{ return T_BREAK; }
"continue"		{ return T_CONTINUE; }
"sizeof"		{ return T_SIZEOF; }

"{"				{ return '{'; }
"}"				{ return '}'; }
"("				{ return '('; }
")"				{ return ')'; }
"["				{ return '['; }
"]"				{ return ']'; }
"+"				{ return '+'; }
"-"				{ return '-'; }
"*"				{ return '*'; }
"/"				{ return '/'; }
"%"				{ return '%'; }
"="				{ return '='; }
">"				{ return '>'; }
"<"				{ return '<'; }
"!"				{ return '!'; }
"|"				{ return '|'; }
"&"				{ return '&'; }
"^"				{ return '^'; }
"~"				{ return '~'; }
"."				{ return '.'; }
":"				{ return ':'; }
";"				{ return ';'; }
","				{ return ','; }

"<<"			{ return T_LEFT_SHIFT; }
">>"			{ return T_RIGHT_SHIFT; }
"&&"			{ return T_BOOL_AND; }
"||"			{ return T_BOOL_OR; }
"+="			{ return T_PLUS_EQUALS; }
"-="			{ return T_MINUS_EQUALS; }
"*="			{ return T_STAR_EQUALS; }
"/="			{ return T_DIV_EQUALS; }
"%="			{ return T_MOD_EQUALS; }
"=="			{ return T_EQUAL; }
"<="			{ return T_LESS_OR_EQUAL; }
">="			{ return T_GREATER_OR_EQUAL; }
"!="			{ return T_NOT_EQUAL; }
"|="			{ return T_BIT_OR_EQUALS; }
"&="			{ return T_BIT_AND_EQUALS; }
"^="			{ return T_BIT_XOR_EQUALS; }
"~="			{ return T_BIT_NOT_EQUALS; }
"->"			{ return T_ARROW; }
"<<="			{ return T_LEFT_SHIFT_EQUALS; }
">>="			{ return T_RIGHT_SHIFT_EQUALS; }
"++"			{ return T_PLUS_PLUS; }
"--"			{ return T_MINUS_MINUS; }

" "|"\t"|"\r"|"\n"	{}
{HEXNUM}		{ yylval.intConst = std::strtoul(yytext, NULL, 0); return T_INT_CONST; }
{NUMBER}		{ yylval.intConst = atoi(yytext); return T_INT_CONST; }
{IDENT}			{ yylval.ident = new std::string(yytext); return T_IDENT; }
.				{{ char err[] = "Unknown Character: a"; err[strlen(err)-1] = *yytext; yyerror(err); }}

%%

/**
 * This function is called on every token, and updates the yylloc global variable, which stores the
 * location/position of the current token.
 */
void updatePosition() {
	yylloc.first_line = line_num;
	yylloc.first_column = line_pos;
	char* text = yytext;
	while(*text != '\0') {
		if(*text == '\n') {
			line_num++;
			line_pos = 1;
		} else {
			line_pos++;
		}
		text++;
	}
	yylloc.last_line = line_num;
	yylloc.last_column = line_pos;
}

