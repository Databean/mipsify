#include "Statement.h"
#include "Expression.h"
#include "Util.h"
#include "Declaration.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::initializer_list;
using std::string;
using std::invalid_argument;
using std::all_of;
using std::map;

Statement::Statement(const Position& pos, initializer_list<Node*> children) : Node(pos, children) {
	
}

Statement::~Statement() {
	
}

StatementBlock::StatementBlock(const Position& pos, const vector<Statement*>& statements) : Statement(pos, {}, {statements}), statements(statements) {
	exceptIfNullMember("StatementBlock::StatementBlock(statements)", statements);
}

StatementBlock::~StatementBlock() {
	deletePtrVecMembers(statements);
}

bool StatementBlock::operator==(const Node& n) const {
	const StatementBlock* other = dynamic_cast<const StatementBlock*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return ptrCollectionEqual(statements, other->statements);
	}
	return true;
}

bool StatementBlock::check(map<string, const Declaration*>& scope) const {
	map<string, const Declaration*> blockScope(scope);
	auto checker = [&blockScope](Statement* s) { return s->check(blockScope); };
	return all_of(statements.begin(), statements.end(), checker);
}

const vector<Statement*>& StatementBlock::getStatements() const {
	return statements;
}

IfStatement::IfStatement(const Position& pos, Expression* cond, Statement* then) : Statement(pos, {cond, then}), cond(cond), then(then) {
	exceptIfNull("IfStatement::IfStatement(cond)", cond);
	exceptIfNull("IfStatement::IfStatement(then)", then);
}

IfStatement::~IfStatement() {
	delete cond;
	delete then;
}

bool IfStatement::operator==(const Node& o) const {
	const IfStatement* other = dynamic_cast<const IfStatement*>(&o);
	if(other == NULL) {
		return false;
	} else {
		return getCond() == other->getCond() && getThen() == other->getThen();
	}
}

bool IfStatement::check(map<string, const Declaration*>& scope) const {
	map<string, const Declaration*> thenScope(scope);
	if(!(cond->check(scope) && then->check(thenScope))) {
		return false;
	}
	if(!(cond->getType(scope) == IntType() || cond->getType(scope) == PointerType(new IntType()))) {
		cout << cond->getPosition() << ": if statement condition is not an integer or a pointer." << endl;
		return false;
	} else {
		return true;
	}
}

const Expression& IfStatement::getCond() const {
	return *cond;
}

const Statement& IfStatement::getThen() const {
	return *then;
}

IfElseStatement::IfElseStatement(const Position& pos, Expression* cond, Statement* then, Statement* els) : Statement(pos, {cond, then, els}), cond(cond), then(then), els(els) {
	exceptIfNull("IfElseStatement::IfElseStatement(cond)", cond);
	exceptIfNull("IfElseStatement::IfElseStatement(then)", then);
	exceptIfNull("IfElseStatement::IfElseStatement(els)", els);
}

IfElseStatement::~IfElseStatement() {
	delete cond;
	delete then;
	delete els;
}

bool IfElseStatement::operator==(const Node& n) const {
	const IfElseStatement* other = dynamic_cast<const IfElseStatement*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getCond() == other->getCond() &&
			getThen() == other->getThen() &&
			getElse() == other->getElse();
	}
	return true;
}

bool IfElseStatement::check(map<string, const Declaration*>& scope) const {
	map<string, const Declaration*> thenScope(scope);
	map<string, const Declaration*> elseScope(scope);
	if(!(cond->check(scope) && then->check(thenScope) && els->check(elseScope))) {
		return false;
	}
	if(!(cond->getType(scope) == IntType() || cond->getType(scope) == PointerType(new IntType()))) {
		cout << cond->getPosition() << ": if-else statement condition is not an integer or a pointer." << endl;
		return false;
	} else {
		return true;
	}
}

const Expression& IfElseStatement::getCond() const {
	return *cond;
}

const Statement& IfElseStatement::getThen() const {
	return *then;
}

const Statement& IfElseStatement::getElse() const {
	return *els;
}

WhileStatement::WhileStatement(const Position& pos, Expression* cond, Statement* loop) : Statement(pos, {cond, loop}), cond(cond), loop(loop) {
	exceptIfNull("WhileStatement::WhileStatement(cond)", cond);
	exceptIfNull("WhileStatement::WhileStatement(loop)", loop);
}

WhileStatement::~WhileStatement() {
	delete cond;
	delete loop;
}

bool WhileStatement::operator==(const Node& n) const {
	const WhileStatement* other = dynamic_cast<const WhileStatement*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getCond() == other->getCond() && getLoop() == other->getLoop();
	}
	return true;
}

bool WhileStatement::check(map<string, const Declaration*>& scope) const {
	map<string, const Declaration*> loopScope(scope);
	if(!(cond->check(scope) && loop->check(loopScope))) {
		return false;
	}
	if(!(cond->getType(scope) == IntType() || cond->getType(scope) == PointerType(new IntType()))) {
		cout << cond->getPosition() << ": while statement condition is not an integer or a pointer." << endl;
		return false;
	} else {
		return true;
	}
}

const Expression& WhileStatement::getCond() const {
	return *cond;
}

const Statement& WhileStatement::getLoop() const {
	return *loop;
}

DoWhileStatement::DoWhileStatement(const Position& pos, Statement* loop, Expression* cond) : Statement(pos, {loop, cond}), loop(loop), cond(cond) {
	exceptIfNull("DoWhileStatement::DoWhileStatement(loop)", loop);
	exceptIfNull("DoWhileStatement::DoWhileStatement(cond)", cond);
}

DoWhileStatement::~DoWhileStatement() {
	delete loop;
	delete cond;
}

bool DoWhileStatement::operator==(const Node& n) const {
	const DoWhileStatement* other = dynamic_cast<const DoWhileStatement*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getLoop() == other->getLoop() && getCond() == other->getCond();
	}
}

bool DoWhileStatement::check(map<string, const Declaration*>& scope) const {
	map<string, const Declaration*> loopScope(scope);
	if(!(cond->check(scope) && loop->check(loopScope))) {
		return false;
	}
	if(!(cond->getType(scope) == IntType() || cond->getType(scope) == PointerType(new IntType()))) {
		cout << cond->getPosition() << ": do-while statement condition is not an integer or a pointer." << endl;
		return false;
	} else {
		return true;
	}
}

const Statement& DoWhileStatement::getLoop() const {
	return *loop;
}

const Expression& DoWhileStatement::getCond() const {
	return *cond;
}

ForStatement::ForStatement(const Position& pos, Expression* init, Expression* cond, Expression* incr, Statement* loop) :
	Statement(pos, {init, cond, incr, loop}), init(init), cond(cond), incr(incr), loop(loop) {
	
	exceptIfNull("ForStatement::ForStatement(init)", init);
	exceptIfNull("ForStatement::ForStatement(cond)", cond);
	exceptIfNull("ForStatement::ForStatement(incr)", incr);
	exceptIfNull("ForStatement::ForStatement(loop)", loop);
}

ForStatement::~ForStatement() {
	delete init;
	delete cond;
	delete incr;
	delete loop;
}

bool ForStatement::operator==(const Node& n) const {
	const ForStatement* other = dynamic_cast<const ForStatement*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getInit() == other->getInit() &&
			getCond() == other->getCond() &&
			getIncr() == other->getIncr() &&
			getLoop() == other->getLoop();
	}
	return true;
}

bool ForStatement::check(map<string, const Declaration*>& scope) const {
	map<string, const Declaration*> loopScope(scope);
	if(!(init->check(scope) && cond->check(scope) && incr->check(scope) && loop->check(loopScope))) {
		return false;
	}
	if(!(cond->getType(scope) == IntType() || cond->getType(scope) == PointerType(new IntType()))) {
		cout << cond->getPosition() << ": for statement condition is not an integer or a pointer." << endl;
		return false;
	} else {
		return true;
	}
}

const Expression& ForStatement::getInit() const {
	return *init;
}

const Expression& ForStatement::getCond() const {
	return *cond;
}

const Expression& ForStatement::getIncr() const {
	return *incr;
}

const Statement& ForStatement::getLoop() const {
	return *loop;
}

BreakStatement::BreakStatement(const Position& pos) : Statement(pos, {}) {
	
}

BreakStatement::~BreakStatement() {
	
}

bool BreakStatement::operator==(const Node& n) const {
	return dynamic_cast<const BreakStatement*>(&n) != NULL;
}

bool BreakStatement::check(map<string, const Declaration*>& scope) const {
	const Node* node = this;
	while(node->hasParent()) {
		node = &(node->getParent());
		if(dynamic_cast<const SwitchStatement*>(node) != NULL) {
			return true;
		} else if(dynamic_cast<const ForStatement*>(node) != NULL) {
			return true;
		} else if(dynamic_cast<const WhileStatement*>(node) != NULL) {
			return true;
		} else if(dynamic_cast<const DoWhileStatement*>(node) != NULL) {
			return true;
		}
	}
	cout << getPosition() << ": break statement is not inside any loops." << endl;
	return false;
}

ContinueStatement::ContinueStatement(const Position& pos) : Statement(pos, {}) {
	
}

ContinueStatement::~ContinueStatement() {
	
}

bool ContinueStatement::operator==(const Node& n) const {
	return dynamic_cast<const ContinueStatement*>(&n) != NULL;
}

bool ContinueStatement::check(map<string, const Declaration*>& scope) const {
	const Node* node = this;
	while(node->hasParent()) {
		node = &(node->getParent());
		if(dynamic_cast<const ForStatement*>(node) != NULL) {
			return true;
		} else if(dynamic_cast<const WhileStatement*>(node) != NULL) {
			return true;
		} else if(dynamic_cast<const DoWhileStatement*>(node) != NULL) {
			return true;
		}
	}
	cout << getPosition() << ": continue statement is not inside any loops." << endl;
	return false;
}

SwitchStatement::SwitchStatement(const Position& pos, Expression* control, const vector<Statement*>& statements) :
	Statement(pos, {control}, {statements}), control(control), statements(statements) {
	
	exceptIfNull("SwitchStatement::SwitchStatement(control)", control);
	exceptIfNullMember("SwitchStatement::SwitchStatement(statements)", statements);
}

SwitchStatement::~SwitchStatement() {
	delete control;
	deletePtrVecMembers(statements);
}

bool SwitchStatement::operator==(const Node& n) const {
	const SwitchStatement* other = dynamic_cast<const SwitchStatement*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getControl() == other->getControl() &&
			ptrCollectionEqual(statements, other->statements);
	}
}

bool SwitchStatement::check(map<string, const Declaration*>& scope) const {
	if(!(control->check(scope))) {
		return false;
	}
	if(!(control->getType(scope) == IntType())) {
		return false;
	}
	map<string, const Declaration*> statementScope(scope);
	map<int, CaseStatement*> caseMap;
	DefaultStatement* defaul = NULL;
	for(auto it = statements.begin(); it != statements.end(); it++) {
		Statement* s = (*it);
		CaseStatement* caseMaybe = dynamic_cast<CaseStatement*>(s);
		if(caseMaybe != NULL) {
			if(caseMap.count(caseMaybe->getValue())) {
				cout << caseMaybe->getPosition() << ": there already exists a case for this value at " << caseMap[caseMaybe->getValue()]->getPosition() << "." << endl;
				return false;
			} else {
				caseMap[caseMaybe->getValue()] = caseMaybe;
			}
			continue;
		}
		DefaultStatement* defaultMaybe = dynamic_cast<DefaultStatement*>(s);
		if(defaultMaybe != NULL) {
			if(defaul == NULL) {
				defaul = defaultMaybe;
			} else {
				cout << defaultMaybe->getPosition() << ": there already default case at at " << defaul->getPosition() << "." << endl;
				return false;
			} continue;
		}
		Declaration* declarationMaybe = dynamic_cast<Declaration*>(s);
		if(declarationMaybe != NULL) {
			return false;
		}
		if(!(s->check(statementScope))) {
			return false;
		}
	}
	return true;
}

const Expression& SwitchStatement::getControl() const {
	return *control;
}

const vector<Statement*>& SwitchStatement::getStatements() const {
	return statements;
}

CaseStatement::CaseStatement(const Position& pos, int value) : Statement(pos, {}), value(value) {
	
}

CaseStatement::~CaseStatement() {
	
}

bool CaseStatement::operator==(const Node& n) const {
	const CaseStatement* other = dynamic_cast<const CaseStatement*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getValue() == other->getValue();
	}
	return true;
}

bool CaseStatement::check(map<string, const Declaration*>& scope) const {
	if(hasParent()) {
		if(dynamic_cast<const SwitchStatement*>(&(getParent())) == NULL) {
			cout << getPosition() << ": case statement parent is not a switch" << endl;
			return false;
		} else {
			return true;
		}
	} else {
		return false;
	}
}

const int& CaseStatement::getValue() const {
	return value;
}

DefaultStatement::DefaultStatement(const Position& pos) : Statement(pos, {}) {
	
}

DefaultStatement::~DefaultStatement() {
	
}

bool DefaultStatement::operator==(const Node& n) const {
	return dynamic_cast<const DefaultStatement*>(&n) != NULL;
}

bool DefaultStatement::check(map<string, const Declaration*>& scope) const {
	if(hasParent()) {
		if(dynamic_cast<const SwitchStatement*>(&(getParent())) == NULL) {
			cout << getPosition() << ": default statement parent is not a switch statement." << endl;
			return false;
		} else {
			return true;
		}
	} else {
		return false;
	}
}

ReturnStatement::ReturnStatement(const Position& pos, Expression* ret) : Statement(pos, {ret}), ret(ret) {
	exceptIfNull("ReturnStatement::ReturnStatement(ret)", ret);
}

ReturnStatement::~ReturnStatement() {
	delete ret;
}

bool ReturnStatement::operator==(const Node& n) const {
	const ReturnStatement* other = dynamic_cast<const ReturnStatement*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getRet() == other->getRet();
	}
}

bool ReturnStatement::check(map<string, const Declaration*>& scope) const {
	if(!ret->check(scope)) {
		return false;
	}
	const Type& retType = ret->getType(scope);
	const Node* n = this;
	while(n->hasParent()) {
		n = &(n->getParent());
		const FunctionDeclaration* fndecl = dynamic_cast<const FunctionDeclaration*>(n);
		if(fndecl != NULL) {
			if(!(retType == fndecl->getType())) {
				cout << getPosition() << ": return statement type clashes with function declaration return type." << endl;
				return false;
			} else {
				return true;
			}
		}
	}
	cout << getPosition() << ": return statement is not inside a function." << endl;
	return false;
}

const Expression& ReturnStatement::getRet() const {
	return *ret; 
}

