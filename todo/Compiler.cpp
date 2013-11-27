#include "Compiler.h"
#include "Parser.h"
#include <unistd.h>
#include <stdexcept>
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
using std::runtime_error;

Compiler::Compiler() {
	
}

Compiler::~Compiler() {
	
}

void Compiler::lexerCleanBuffer() {
	if(currentBuffer != NULL) {
		yy_delete_buffer(currentBuffer);
	}
	currentBuffer = NULL;
}

void Compiler::lexerLoadFile(const string& file) {
	lexerCleanBuffer();
	if(access(file.c_str(), R_OK) == 0) {
		FILE* f = fopen(file.c_str(), "r");
		currentBuffer = yy_create_buffer(f, YY_BUF_SIZE);
		yy_switch_to_buffer(currentBuffer);
	} else {
		throw runtime_error("Compiler could not open file " + file);
	}
}

void Compiler::lexerLoadString(const string& str) {
	lexerCleanBuffer();
	currentBuffer = yy_scan_string(str.c_str());
	yy_switch_to_buffer(currentBuffer);
}

vector<pair<int, YYSTYPE> > Compiler::readAllTokens() {
	vector<pair<int, YYSTYPE> > ret;
	
	int i = yylex();
	while(i != 0) {
		ret.push_back(pair<int, YYSTYPE>(i, yylval));
		i = yylex();
	}
	
	return ret;
}
