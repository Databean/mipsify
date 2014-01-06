#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <utility>
#include "y.tab.h"
#include "scanner.h"

/**
 * Slightly nicer interface to the generated lexer than the one provided by flex.
 * Has convenience methods to set up the lexer to handle a string or a file. The
 * file is assumed to exist.
 */
class Lexer {
private:
	Lexer();
	virtual ~Lexer();
	static YY_BUFFER_STATE currentBuffer;
	
	static void cleanBuffer();
	
public:
	static void lexString(const std::string& s);
	static void lexFile(const std::string& filename);
	
	static int numLexingErrors();
	static std::vector<std::pair<int, YYSTYPE>> getAllTokens();
};

#endif