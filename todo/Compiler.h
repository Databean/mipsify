#ifndef COMPILER_H
#define COMPILER_H

#include <vector>
#include <utility>
#include <string>
#include "scanner.h"
#include "y.tab.h"

class Program;

class Compiler {
private:
	YY_BUFFER_STATE currentBuffer;
	
	void lexerCleanBuffer();
	
	void lexerLoadString(const std::string& str);
	void lexerLoadFile(const std::string& str);
	
	std::vector<std::pair<int, YYSTYPE>> readAllTokens();
	
public:
	Compiler();
	Compiler(const Compiler&) = delete;
	virtual ~Compiler();
	virtual const Compiler& operator=(const Compiler&);
	
	virtual std::vector<std::pair<int, YYSTYPE>> fileTokens(const std::string& file);
	virtual std::vector<std::pair<int, YYSTYPE>> stringTokens(const std::string& str);
	
	virtual Program* fileTree(const std::string& file);
	virtual Program* stringTree(const std::string& str);
	
	virtual bool fileCheck();
	virtual bool stringCheck();
};

#endif