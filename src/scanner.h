#ifndef SCANNER_H
#define SCANNER_H

#include <string>

typedef struct yy_buffer_state *YY_BUFFER_STATE;
int yylex();
void yyerror(const char* s);
int getLexingLineNum();

#endif