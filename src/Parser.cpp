#include "Parser.h"
#include "Util.h"
#include <stdexcept>
#include "y.tab.h"
#include <map>
#include <algorithm>

using std::vector;
using std::invalid_argument;
using std::string;
using std::map;
using std::all_of;

Program::Program(const Position& pos, const vector<Declaration*>& declarations) : Node(pos, {}, {declarations}), declarations(declarations) {
	exceptIfNullMember("Program::Program(declarations)", declarations);
}

Program::~Program() {
	deletePtrVecMembers(declarations);
}

bool Program::operator==(const Node& n) const {
	const Program* other = dynamic_cast<const Program*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return ptrCollectionEqual(declarations, other->declarations);
	}
	return true;
}

bool Program::check(map<string, const Declaration*>& scope) const {
	auto checker = [&scope](Declaration* d) { return d->check(scope); };
	return all_of(declarations.begin(), declarations.end(), checker);
}

const vector<Declaration*>& Program::getDeclarations() const {
	return declarations;
}

Program* program_out;

Program* runParser() {
	program_out = NULL;
	yyparse();
	return program_out;
}
