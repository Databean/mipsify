// LexerTests.h
#include <cxxtest/TestSuite.h>
#include <Lexer.h>
#include <iostream>

using std::vector;
using std::string;
using std::pair;
using std::cout;
using std::endl;

class LexerTests : public CxxTest::TestSuite
{
public:
	
	pair<int, YYSTYPE> makeToken(int i) {
		YYSTYPE data;
		return pair<int, YYSTYPE>(i, data);
	}
	
	pair<int, YYSTYPE> makeToken(int i, int j) {
		YYSTYPE data;
		data.intConst = j;
		return pair<int, YYSTYPE>(i, data);
	}
	
	pair<int, YYSTYPE> makeToken(int i, std::string& str) {
		YYSTYPE data;
		data.strConst = &str;
		return pair<int, YYSTYPE>(i, data);
	}
	
	bool compareToken(const pair<int, YYSTYPE>& a, const pair<int, YYSTYPE>& b) {
		if(a.first != b.first) {
			cout << "Token types are different: " << a.first << ", " << b.first << endl;
			return false;
		}
		switch(a.first) {
			case T_INT_CONST:
				return a.second.intConst == b.second.intConst;
				break;
			case T_STR_CONST:
			case T_IDENT:
				return (*a.second.strConst) == (*b.second.strConst);
				break;
		}
		return true;
	}
	
	void deleteTokens(const vector<pair<int, YYSTYPE>>& vec) {
		for(auto it = vec.begin(); it != vec.end(); it++) {
			if(it->first == T_STR_CONST || it->first == T_IDENT) {
				delete it->second.strConst;
			}
		}
	}
	
	bool compareTokenVec(const vector<pair<int, YYSTYPE>>& a, const vector<pair<int, YYSTYPE>>& b) {
		if(a.size() != b.size()) {
			cout << "Lengths are different." << endl;
			return false;
		}
		for(auto itA = a.begin(), itB = b.begin(); itA != a.end() && itB != b.end(); itA++, itB++) {
			if(!compareToken(*itA, *itB)) {
				return false;
			}
		}
		return true;
	}
	
	void testChars() {
		vector<pair<int, YYSTYPE>> expected =
			{ 
				makeToken('('), makeToken(')'), makeToken('{'), makeToken('}'), makeToken('+'), makeToken('-'), makeToken('*'), makeToken('/'),
				makeToken('%'), makeToken('='), makeToken('<'), makeToken('!'), makeToken('>'), makeToken('&'), makeToken('|'), makeToken('~'),
				makeToken('.'), makeToken(':'), makeToken(';'), makeToken(',')
			};
		Lexer::lexString("(\t   )\t\r\n {         } + - * / % = < ! > & | ~ . : ; ,");
		
		vector<pair<int, YYSTYPE>> result = Lexer::getAllTokens();
		
		TS_ASSERT(compareTokenVec(result, expected));
		deleteTokens(result);
	}
	
	void testDoubleChars() {
		vector<pair<int, YYSTYPE>> expected = 
			{
				makeToken(T_LEFT_SHIFT), makeToken(T_RIGHT_SHIFT), makeToken(T_PLUS_EQUALS), makeToken(T_MINUS_EQUALS), 
				makeToken(T_STAR_EQUALS), makeToken(T_DIV_EQUALS), makeToken(T_MOD_EQUALS), makeToken(T_EQUAL), 
				makeToken(T_LESS_OR_EQUAL), makeToken(T_GREATER_OR_EQUAL), makeToken(T_NOT_EQUAL),
				makeToken(T_BIT_OR_EQUALS), makeToken(T_BIT_AND_EQUALS), makeToken(T_BIT_XOR_EQUALS),
				makeToken(T_BIT_NOT_EQUALS), makeToken(T_ARROW), makeToken(T_LEFT_SHIFT_EQUALS),
				makeToken(T_RIGHT_SHIFT_EQUALS), makeToken(T_PLUS_PLUS), makeToken(T_MINUS_MINUS),
			};
		Lexer::lexString("<< >> += -= *= /= %= == <= >= != |= &= ^= ~= -> <<= >>= ++ --");
		vector<pair<int, YYSTYPE>> result = Lexer::getAllTokens();
		
		TS_ASSERT(compareTokenVec(result, expected));
		deleteTokens(result);
	}
	
	void testStrings() {
		string str1 = " a \n b \r c \" d ";
		string id1 = "abc";
		string id2 = "abc123";
		vector<pair<int, YYSTYPE>> expected = { makeToken(T_STR_CONST, str1), makeToken(T_IDENT, id1), makeToken(T_IDENT, id2) };
		Lexer::lexString("\" a \\n b \\r c \\\" d \" abc\n abc123");
		vector<pair<int, YYSTYPE>> result = Lexer::getAllTokens();
		
		TS_ASSERT(compareTokenVec(result, expected));
		deleteTokens(result);
	}
	
	void testComments() {
		vector<pair<int, YYSTYPE>> expected;
		Lexer::lexString("/* *** \" aaa bbb cc \\n \" defdef 123 */");
		vector<pair<int, YYSTYPE>> result = Lexer::getAllTokens();
		
		TS_ASSERT(compareTokenVec(result, expected));
		deleteTokens(result);
	}
	
	void testIntegers() {
		vector<pair<int, YYSTYPE>> expected = { makeToken(T_INT_CONST, 123), makeToken(T_INT_CONST, 456), makeToken(T_INT_CONST, 0) };
		Lexer::lexString("123 /*****/ 456 \n\n\n 0");
		vector<pair<int, YYSTYPE>> result = Lexer::getAllTokens();
		
		TS_ASSERT(compareTokenVec(result, expected));
		deleteTokens(result);
	}
	
	void testKeywords() {
		vector<pair<int, YYSTYPE>> expected = {
			makeToken(T_IF), makeToken(T_ELSE), makeToken(T_FOR), makeToken(T_WHILE), makeToken(T_DO),
			makeToken(T_INT_TYPE), makeToken(T_STRING_TYPE),
			makeToken(T_RETURN), makeToken(T_SWITCH), makeToken(T_CASE), makeToken(T_DEFAULT), makeToken(T_BREAK), makeToken(T_CONTINUE),
		};
		
		Lexer::lexString("if else for while do int string return switch case default break continue");
		vector<pair<int, YYSTYPE>> result = Lexer::getAllTokens();
		
		TS_ASSERT(compareTokenVec(result, expected));
		deleteTokens(result);
	}
	
	void testSimpleProgram() {
		string main = "main";
		string i = "i";
		string sum = "sum";
		string printf = "printf";
		string printf_str = "sum = %d\n";
		vector<pair<int, YYSTYPE>> expected = 
			{
				makeToken(T_INT_TYPE), makeToken(T_IDENT, main), makeToken('('), makeToken(')'),
				makeToken('{'),
				makeToken(T_INT_TYPE), makeToken(T_IDENT, i), makeToken(','), makeToken(T_IDENT, sum), makeToken('='), makeToken(T_INT_CONST, 0), makeToken(';'),
				makeToken(T_FOR), makeToken('('), makeToken(T_IDENT, i), makeToken('='), makeToken(T_INT_CONST, 1), makeToken(';'),
				makeToken(T_IDENT, i), makeToken(T_LESS_OR_EQUAL), makeToken(T_INT_CONST, 10), makeToken(';'), makeToken(T_IDENT, i), makeToken(T_PLUS_PLUS),
				makeToken(')'), makeToken('{'), makeToken(T_IDENT, sum), makeToken(T_PLUS_EQUALS), makeToken(T_IDENT, i), makeToken(';'),
				makeToken('}'),
				makeToken(T_IDENT, printf), makeToken('('), makeToken(T_STR_CONST, printf_str), makeToken(','), makeToken(T_IDENT, sum), makeToken(')'), makeToken(';'),
				makeToken(T_RETURN), makeToken(T_INT_CONST, 0), makeToken(';'),
				makeToken('}')
			};
		Lexer::lexString(string("int main() \n")+
		string("{ \n")+
			string("int i, sum = 0; \n")+
			string("\n")+
			string("for ( i = 1; i <= 10; i++ ) { \n")+
				string("sum += i; \n")+
			string("} /*-for-*/ \n")+
			string("printf(\"sum = %d\\n\", sum); \n")+
			string("\n")+
			string("return 0; \n")+
		string("}\n"));
		vector<pair<int, YYSTYPE>> result = Lexer::getAllTokens();
		
		TS_ASSERT(compareTokenVec(result, expected));
		deleteTokens(result);
	}
}; 