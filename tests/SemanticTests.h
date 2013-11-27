#include <cxxtest/TestSuite.h>
#include "Lexer.h"
#include <iostream>
#include <map>
#include "Parser.h"

using std::vector;
using std::string;
using std::pair;
using std::cout;
using std::endl;
using std::map;

class SemanticTests : public CxxTest::TestSuite
{
private:
	map<string, const Declaration*> scope;
public:
	void testDiffVariables() {
		Lexer::lexString("int x; int z; string q;");
		Program* p = runParser();
		
		TS_ASSERT(p != NULL);
		
		TS_ASSERT(p->check(scope) == true);
	}
	void testSameVariables() {
		Lexer::lexString("int x; int x;");
		Program* p = runParser();
		
		TS_ASSERT(p != NULL);
		 
		TS_ASSERT(p->check(scope) == false);
	}
	void testSameVariablesDiffTypes() {
		Lexer::lexString("int x; string x;");
		Program* p = runParser();
		
		TS_ASSERT(p != NULL);
		 
		TS_ASSERT(p->check(scope) == false);
	}
	void testProperInitialTypes() {
		Lexer::lexString("int x = 1;");
		Program* p = runParser();

		TS_ASSERT(p != NULL);


		TS_ASSERT(p->check(scope) == true);

		Lexer::lexString("int x = \"hello\";");
		p = runParser();

		TS_ASSERT(p != NULL);

		TS_ASSERT(p->check(scope) == false);

		Lexer::lexString("string x = \"hello\";");
		p = runParser();

		TS_ASSERT(p != NULL);

		TS_ASSERT(p->check(scope) == true);
	}
};