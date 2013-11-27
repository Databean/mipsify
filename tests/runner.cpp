/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_SemanticTests_init = false;
#include "/home/data/classes/cs242/Assignment4/tests/SemanticTests.h"

static SemanticTests suite_SemanticTests;

static CxxTest::List Tests_SemanticTests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SemanticTests( "SemanticTests.h", 14, "SemanticTests", suite_SemanticTests, Tests_SemanticTests );

static class TestDescription_suite_SemanticTests_testDiffVariables : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_SemanticTests_testDiffVariables() : CxxTest::RealTestDescription( Tests_SemanticTests, suiteDescription_SemanticTests, 19, "testDiffVariables" ) {}
 void runTest() { suite_SemanticTests.testDiffVariables(); }
} testDescription_suite_SemanticTests_testDiffVariables;

static class TestDescription_suite_SemanticTests_testSameVariables : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_SemanticTests_testSameVariables() : CxxTest::RealTestDescription( Tests_SemanticTests, suiteDescription_SemanticTests, 27, "testSameVariables" ) {}
 void runTest() { suite_SemanticTests.testSameVariables(); }
} testDescription_suite_SemanticTests_testSameVariables;

static class TestDescription_suite_SemanticTests_testSameVariablesDiffTypes : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_SemanticTests_testSameVariablesDiffTypes() : CxxTest::RealTestDescription( Tests_SemanticTests, suiteDescription_SemanticTests, 35, "testSameVariablesDiffTypes" ) {}
 void runTest() { suite_SemanticTests.testSameVariablesDiffTypes(); }
} testDescription_suite_SemanticTests_testSameVariablesDiffTypes;

static class TestDescription_suite_SemanticTests_testProperInitialTypes : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_SemanticTests_testProperInitialTypes() : CxxTest::RealTestDescription( Tests_SemanticTests, suiteDescription_SemanticTests, 43, "testProperInitialTypes" ) {}
 void runTest() { suite_SemanticTests.testProperInitialTypes(); }
} testDescription_suite_SemanticTests_testProperInitialTypes;

#include "/home/data/classes/cs242/Assignment4/tests/ParserTests.h"

static ParserTests suite_ParserTests;

static CxxTest::List Tests_ParserTests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ParserTests( "ParserTests.h", 12, "ParserTests", suite_ParserTests, Tests_ParserTests );

static class TestDescription_suite_ParserTests_testGlobalVarDeclaration : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ParserTests_testGlobalVarDeclaration() : CxxTest::RealTestDescription( Tests_ParserTests, suiteDescription_ParserTests, 15, "testGlobalVarDeclaration" ) {}
 void runTest() { suite_ParserTests.testGlobalVarDeclaration(); }
} testDescription_suite_ParserTests_testGlobalVarDeclaration;

static class TestDescription_suite_ParserTests_testGlobalVarDeclarationInit : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ParserTests_testGlobalVarDeclarationInit() : CxxTest::RealTestDescription( Tests_ParserTests, suiteDescription_ParserTests, 31, "testGlobalVarDeclarationInit" ) {}
 void runTest() { suite_ParserTests.testGlobalVarDeclarationInit(); }
} testDescription_suite_ParserTests_testGlobalVarDeclarationInit;

static class TestDescription_suite_ParserTests_testFunctionDefinition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ParserTests_testFunctionDefinition() : CxxTest::RealTestDescription( Tests_ParserTests, suiteDescription_ParserTests, 44, "testFunctionDefinition" ) {}
 void runTest() { suite_ParserTests.testFunctionDefinition(); }
} testDescription_suite_ParserTests_testFunctionDefinition;

#include "/home/data/classes/cs242/Assignment4/tests/LexerTests.h"

static LexerTests suite_LexerTests;

static CxxTest::List Tests_LexerTests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_LexerTests( "LexerTests.h", 12, "LexerTests", suite_LexerTests, Tests_LexerTests );

static class TestDescription_suite_LexerTests_testChars : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_LexerTests_testChars() : CxxTest::RealTestDescription( Tests_LexerTests, suiteDescription_LexerTests, 71, "testChars" ) {}
 void runTest() { suite_LexerTests.testChars(); }
} testDescription_suite_LexerTests_testChars;

static class TestDescription_suite_LexerTests_testDoubleChars : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_LexerTests_testDoubleChars() : CxxTest::RealTestDescription( Tests_LexerTests, suiteDescription_LexerTests, 86, "testDoubleChars" ) {}
 void runTest() { suite_LexerTests.testDoubleChars(); }
} testDescription_suite_LexerTests_testDoubleChars;

static class TestDescription_suite_LexerTests_testStrings : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_LexerTests_testStrings() : CxxTest::RealTestDescription( Tests_LexerTests, suiteDescription_LexerTests, 103, "testStrings" ) {}
 void runTest() { suite_LexerTests.testStrings(); }
} testDescription_suite_LexerTests_testStrings;

static class TestDescription_suite_LexerTests_testComments : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_LexerTests_testComments() : CxxTest::RealTestDescription( Tests_LexerTests, suiteDescription_LexerTests, 115, "testComments" ) {}
 void runTest() { suite_LexerTests.testComments(); }
} testDescription_suite_LexerTests_testComments;

static class TestDescription_suite_LexerTests_testIntegers : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_LexerTests_testIntegers() : CxxTest::RealTestDescription( Tests_LexerTests, suiteDescription_LexerTests, 124, "testIntegers" ) {}
 void runTest() { suite_LexerTests.testIntegers(); }
} testDescription_suite_LexerTests_testIntegers;

static class TestDescription_suite_LexerTests_testKeywords : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_LexerTests_testKeywords() : CxxTest::RealTestDescription( Tests_LexerTests, suiteDescription_LexerTests, 133, "testKeywords" ) {}
 void runTest() { suite_LexerTests.testKeywords(); }
} testDescription_suite_LexerTests_testKeywords;

static class TestDescription_suite_LexerTests_testSimpleProgram : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_LexerTests_testSimpleProgram() : CxxTest::RealTestDescription( Tests_LexerTests, suiteDescription_LexerTests, 147, "testSimpleProgram" ) {}
 void runTest() { suite_LexerTests.testSimpleProgram(); }
} testDescription_suite_LexerTests_testSimpleProgram;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
