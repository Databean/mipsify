#include "Lexer.h"
#include <cstdio>
#include <iostream>

typedef size_t yy_size_t;

YY_BUFFER_STATE yy_scan_string ( const char *str );
YY_BUFFER_STATE yy_scan_buffer (char *base, yy_size_t size);

YY_BUFFER_STATE yy_create_buffer ( FILE *file, int size );
void yy_switch_to_buffer ( YY_BUFFER_STATE new_buffer );
void yy_delete_buffer ( YY_BUFFER_STATE buffer );

#define YY_BUF_SIZE 16384

using std::string;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

int numLexingErrors = 0;

YY_BUFFER_STATE Lexer::currentBuffer = NULL;

Lexer::Lexer() {
	
}

Lexer::~Lexer() {
	
}

void Lexer::cleanBuffer() {
	if(currentBuffer != NULL) {
		yy_delete_buffer(currentBuffer);
	}
	currentBuffer = NULL;
}

void Lexer::lexString(const string& str) {
	cleanBuffer();
	currentBuffer = yy_scan_string(str.c_str());
	yy_switch_to_buffer(currentBuffer);
}

void Lexer::lexFile(const string& filename) {
	cleanBuffer();
	FILE* f = fopen(filename.c_str(), "r");
	currentBuffer = yy_create_buffer(f, YY_BUF_SIZE);
	yy_switch_to_buffer(currentBuffer);
}

vector<pair<int, YYSTYPE> > Lexer::getAllTokens() {
	vector<pair<int, YYSTYPE> > ret;
	
	int i = yylex();
	while(i != 0) {
		ret.push_back(pair<int, YYSTYPE>(i, yylval));
		i = yylex();
	}
	
	return ret;
}

extern YYLTYPE yylloc;

void yyerror(const char* str) {
	cout << Position(yylloc) << "Error: " << str << endl;
	numLexingErrors++;
}