#include <cxxtest/TestSuite.h>
#include "Lexer.h"
#include <iostream>
#include "Parser.h"

using std::vector;
using std::string;
using std::pair;
using std::cout;
using std::endl;

class ParserTests : public CxxTest::TestSuite
{
public:
	void testGlobalVarDeclaration() {
		Lexer::lexString("int x; int z; string q;");
		Program* p = runParser();
		
		YYLTYPE l;
		Position ps(l);
		
		Program comparison(ps, vector<Declaration*>{
			new GlobalVarDeclaration(ps, new IntType(), "x"), new GlobalVarDeclaration(ps, new IntType(), "z"),
			new GlobalVarDeclaration(ps, new StringType(), "q")
		});
		
		TS_ASSERT(comparison == *p);
		delete p;
	}
	
	void testGlobalVarDeclarationInit() {
		Lexer::lexString("int x = 5;");
		
		YYLTYPE l;
		Position ps(l);
		
		Program* p = runParser();
		Program comparison(ps, vector<Declaration*>{new GlobalVarDeclarationInit(ps, new IntType(),"x", new IntConstantExpression(ps, 5))});
		
		TS_ASSERT(comparison == *p);
		delete p;
	}
	
	void testFunctionDefinition() {
		Lexer::lexString("int sum(int x, int y) { return x + y; }");
		Program* p = runParser();
		
		YYLTYPE l;
		Position ps(l);
		
		Program comparison(ps, vector<Declaration*>{
			new FunctionDeclaration(ps, new IntType(), "sum", vector<FunctionParameter*>({
				new FunctionParameter(ps, new IntType(), "x"),
				new FunctionParameter(ps, new IntType(), "y"),
			}), new StatementBlock(ps, vector<Statement*>({
				new ReturnStatement(ps, new BinaryOperatorExpression(ps, new VarExpression(ps, "x"), "+", new VarExpression(ps, "y")))
			})))
		});
		
		TS_ASSERT(comparison == *p);
		delete p;
	}
};