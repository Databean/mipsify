#include "Declaration.h"
#include "Util.h"
#include "Expression.h"
#include "Statement.h"
#include <stdexcept>
#include <algorithm>
#include <map>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::initializer_list;
using std::vector;
using std::invalid_argument;
using std::map;
using std::all_of;
using std::runtime_error;

Declaration::Declaration(const Position& pos, const string& name, initializer_list<Node*> children) : Statement(pos, children), name(name) {
	
}

Declaration::~Declaration() {
	
}

bool Declaration::check(map<string, const Declaration*>& scope) const {
	if(!declarationSpecificCheck(scope)) {
		return false;
	} else if(scope.count(name) == 0) {
		scope[name] = this;
		return true;
	} else {
		const Declaration* existing = scope[name];
		if(&(existing->getParent()) == &(getParent())) {
			cout << getPosition() << ": there is already a declaration with this name in this scope at " << existing->getPosition() << "." << endl;
			return false;
		} else {
			scope[name] = this;
			return true;
		}
	}
}

const string& Declaration::getName() const {
	return name;
}

GlobalVarDeclaration::GlobalVarDeclaration(const Position& pos, Type* type, const string& name) : Declaration(pos, name, {}), type(type) {
	exceptIfNull("GlobalVarDeclaration::GlobalVarDeclaration(type)", type);
}

GlobalVarDeclaration::~GlobalVarDeclaration() {
	delete type;
}

bool GlobalVarDeclaration::operator==(const Node& n) const {
	const GlobalVarDeclaration* other = dynamic_cast<const GlobalVarDeclaration*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getType() == other->getType() && getName() == other->getName();
	}
}

bool GlobalVarDeclaration::declarationSpecificCheck(map<string, const Declaration*>& scope) const {
	return type->check(scope);
}

const Type& GlobalVarDeclaration::getType() const {
	return *type;
}

GlobalArrayDeclaration::GlobalArrayDeclaration(const Position& pos, Type* type, const string& name, int size) :
	Declaration(pos, name, {}), type(PointerType(type)), size(size) {
	
	exceptIfNull("GlobalArrayDeclaration::GlobalArrayDeclaration(type)", type);
}

GlobalArrayDeclaration::~GlobalArrayDeclaration() {
	
}

bool GlobalArrayDeclaration::operator==(const Node& n) const {
	const GlobalArrayDeclaration* other = dynamic_cast<const GlobalArrayDeclaration*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getType() == other->getType() && getName() == other->getName() && getSize() == other->getSize();
	}
}

bool GlobalArrayDeclaration::declarationSpecificCheck(map<string, const Declaration*>& scope) const {
	return type.check(scope);
}

const PointerType& GlobalArrayDeclaration::getType() const {
	return type;
}

const int& GlobalArrayDeclaration::getSize() const {
	return size;
}

GlobalVarDeclarationInit::GlobalVarDeclarationInit(const Position& pos, Type* type, const string& name, ConstantExpression* initialValue) :
	Declaration(pos, name, {initialValue}), type(type), initialValue(initialValue) {
	
	exceptIfNull("GlobalVarDeclarationInit::GlobalVarDeclarationInit(type)", type);
	exceptIfNull("GlobalVarDeclarationInit::GlobalVarDeclarationInit(initialValue)", initialValue);
}

GlobalVarDeclarationInit::~GlobalVarDeclarationInit() {
	delete type;
	delete initialValue;
}

bool GlobalVarDeclarationInit::operator==(const Node& n) const {
	const GlobalVarDeclarationInit* other = dynamic_cast<const GlobalVarDeclarationInit*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getType() == other->getType() && 
			getName() == other->getName() && 
			getInitialValue() == other->getInitialValue();
	}
	return true;
}

bool GlobalVarDeclarationInit::declarationSpecificCheck(map<string, const Declaration*>& scope) const {
	if(!(type->check(scope) && initialValue->check(scope))) {
		return false;
	}
	if(!(getType() == initialValue->getType(scope) || getType() == PointerType(new IntType()) && initialValue->getType(scope) == IntType())) {
		cout << getPosition() << ": type of variable and type of initial value are not compatible." << endl;
		return false;
	} else {
		return true;
	}
}

const Type& GlobalVarDeclarationInit::getType() const {
	return *type;
}
const ConstantExpression& GlobalVarDeclarationInit::getInitialValue() const {
	return *initialValue;
}

FunctionParameter::FunctionParameter(const Position& pos, Type* type, const string& name) :
	Declaration(pos, name, {}), type(type) {
	
	exceptIfNull("FunctionParameter::FunctionParameter(type)", type);
}

FunctionParameter::~FunctionParameter() {
	delete type;
}

bool FunctionParameter::operator==(const Node& n) const {
	const FunctionParameter* other = dynamic_cast<const FunctionParameter*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getType() == other->getType() && getName() == other->getName();
	}
}

bool FunctionParameter::declarationSpecificCheck(map<string, const Declaration*>& scope) const {
	return type->check(scope);
}

const Type& FunctionParameter::getType() const {
	return *type;
}

FunctionPrototype::FunctionPrototype(const Position& pos, Type* type, const string& name, const vector<FunctionParameter*>& parameters) :
	Declaration(pos, name, {}, {parameters}), type(type), parameters(parameters) {
	
	exceptIfNull("FunctionPrototype::FunctionPrototype(type)", type);
	exceptIfNullMember("FunctionPrototype::FunctionPrototype(parameters)", parameters);
}

FunctionPrototype::~FunctionPrototype() {
	delete type;
	deletePtrVecMembers(parameters);
}

bool FunctionPrototype::operator==(const Node& n) const {
	const FunctionPrototype* other = dynamic_cast<const FunctionPrototype*>(&n);
	if(other == NULL) {
		return false;
	} else {
		if(!(getType() == other->getType())) {
			return false;
		}
		if(!(getName() == other->getName())) {
			return false;
		}
		return ptrCollectionEqual(parameters, other->parameters);
	}
	return true;
}

bool FunctionPrototype::declarationSpecificCheck(map<string, const Declaration*>& scope) const {
	map<string, const Declaration*> paramScope(scope);
	auto checker = [&paramScope](Declaration* d) { return d->check(paramScope); };
	return type->check(scope) && all_of(parameters.begin(), parameters.end(), checker);
}

const Type& FunctionPrototype::getType() const {
	return *type;
}

const vector<FunctionParameter*>& FunctionPrototype::getParameters() const {
	return parameters;
}

FunctionDeclaration::FunctionDeclaration(const Position& pos, Type* type, const string& name, const vector<FunctionParameter*>& parameters, StatementBlock* body) :
	Declaration(pos, name, {body}, {parameters}), type(type), parameters(parameters), body(body) {
	
	exceptIfNull("FunctionDeclaration::FunctionDeclaration(type)", type);
	exceptIfNullMember("FunctionDeclaration::FunctionDeclaration(parameters)", parameters);
	exceptIfNull("FunctionDeclaration::FunctionDeclaration(body)", body);
}

FunctionDeclaration::~FunctionDeclaration() {
	delete type;
	deletePtrVecMembers(parameters);
	delete body;
}

bool FunctionDeclaration::operator==(const Node& n) const {
	const FunctionDeclaration* other = dynamic_cast<const FunctionDeclaration*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getType() == other->getType() &&
			getName() == other->getName() &&
			ptrCollectionEqual(parameters, other->parameters) &&
			getBody() == other->getBody();
	}
	return true;
}

bool FunctionDeclaration::check(map<string, const Declaration*>& scope) const {
	const string& name = getName();
	if(scope.count(name) == 0) {
		scope[name] = this;
		return declarationSpecificCheck(scope);
	} else {
		auto previousPrototype = dynamic_cast<const FunctionPrototype*>(scope[name]);
		if(previousPrototype != NULL) {
			if(ptrCollectionEqual(parameters, previousPrototype->getParameters())) {
				scope[name] = this;
				return declarationSpecificCheck(scope);
			} else {
				cout << getPosition() << ": the parameter lists between declaration and prototype (" << previousPrototype->getPosition() << ") are not equal." << endl;
				return false;
			}
		} else {
			const Declaration* existing = scope[name];
			if(&(existing->getParent()) == &(getParent())) {
				cout << getPosition() << ": there already exists something in the scope with this name, previously defined at " << existing->getPosition() << "." << endl;
				return false;
			} else {
				scope[name] = this;
				return declarationSpecificCheck(scope);
			}
		}
	}
}

bool FunctionDeclaration::declarationSpecificCheck(map<string, const Declaration*>& scope) const {
	map<string, const Declaration*> paramScope(scope);
	auto checker = [&paramScope](Declaration* d) { return d->check(paramScope); };
	return type->check(scope) && all_of(parameters.begin(), parameters.end(), checker) && body->check(paramScope);
}

const Type& FunctionDeclaration::getType() const {
	return *type;
}

const vector<FunctionParameter*>& FunctionDeclaration::getParameters() const {
	return parameters;
}

const StatementBlock& FunctionDeclaration::getBody() const {
	return *body;
}

StructPredeclaration::StructPredeclaration(const Position& pos, const string& name) : Declaration(pos, name, {}) {
	
}

StructPredeclaration::~StructPredeclaration() {
	
}

bool StructPredeclaration::operator==(const Node& n) const {
	const StructPredeclaration* other = dynamic_cast<const StructPredeclaration*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getName() == other->getName();
	}
}

bool StructPredeclaration::declarationSpecificCheck(map<string, const Declaration*>& scope) const {
	return true;
}

StructMember::StructMember(const Position& pos, Type* type, const string& name) : Declaration(pos, name, {}), type(type) {
	if(type == NULL) {
		throw invalid_argument("StructMember::StructMember(type)");
	}
}

StructMember::~StructMember() {
	delete type;
}

bool StructMember::operator==(const Node& n) const {
	const StructMember* other = dynamic_cast<const StructMember*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getType() == other->getType() && getName() == other->getName();
	}
}

bool StructMember::declarationSpecificCheck(map<string, const Declaration*>& scope) const {
	return type->check(scope);
}

const Type& StructMember::getType() const {
	return *type;
}

StructDeclaration::StructDeclaration(const Position& pos, const string& name, const vector<StructMember*>& members) : 
	Declaration(pos, name, {}, {members}), members(members) {
	
	exceptIfNullMember("StructDeclaration::StructDeclaration(members)", members);
}

StructDeclaration::~StructDeclaration() {
	deletePtrVecMembers(members);
}

bool StructDeclaration::operator==(const Node& n) const {
	const StructDeclaration* other = dynamic_cast<const StructDeclaration*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getName() == other->getName() &&
			ptrCollectionEqual(members, other->members);
	}
	return true;
}

bool StructDeclaration::check(map<string, const Declaration*>& scope) const {
	const string& name = getName();
	if(scope.count(name) == 0) {
		scope[name] = this;
		return declarationSpecificCheck(scope);
	} else {
		auto previousPredecl = dynamic_cast<const StructPredeclaration*>(scope[name]);
		if(previousPredecl != NULL) {
			scope[name] = this;
			return declarationSpecificCheck(scope);
		} else {
			const Declaration* existing = scope[name];
			if(&(existing->getParent()) == &(getParent())) {
				cout << getPosition() << ": there already exists something in this scope with this name, previously defined at " << existing->getPosition() << ".";
				return false;
			} else {
				scope[name] = this;
				return declarationSpecificCheck(scope);
			}
		}
	}
}

bool StructDeclaration::declarationSpecificCheck(map<string, const Declaration*>& scope) const {
	map<string, const Declaration*> memberScope(scope);
	auto checker = [&memberScope](Declaration* d) { return d->check(memberScope); };
	return all_of(members.begin(), members.end(), checker);
}

const vector<StructMember*>& StructDeclaration::getMembers() const {
	return members;
}

bool StructDeclaration::hasMember(const string& name) const {
	for(auto it = members.begin(); it != members.end(); it++) {
		if((*it)->getName() == name) {
			return true;
		}
	}
	return false;
}

const StructMember& StructDeclaration::getMember(const string& name) const {
	for(auto it = members.begin(); it != members.end(); it++) {
		if((*it)->getName() == name) {
			return **it;
		}
	}
	throw runtime_error("StructDeclaration::getMember(name): no member with that name.");
}

VarDeclaration::VarDeclaration(const Position& pos, Type* type, const string& name) : Declaration(pos, name, {}), type(type) {
	exceptIfNull("VarDeclaration::VarDeclaration(type)", type);
}

VarDeclaration::~VarDeclaration() {
	delete type;
}

bool VarDeclaration::operator==(const Node& n) const {
	const VarDeclaration* other = dynamic_cast<const VarDeclaration*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getName() == other->getName() && getType() == other->getType();
	}
}

bool VarDeclaration::declarationSpecificCheck(map<string, const Declaration*>& scope) const {
	return type->check(scope);
}

const Type& VarDeclaration::getType() const {
	return *type;
}

VarDeclarationInit::VarDeclarationInit(const Position& pos, Type* type, const string& name, Expression* initialValue) :
	Declaration(pos, name, {initialValue}), type(type), initialValue(initialValue) {
	
	exceptIfNull("VarDeclarationInit::VarDeclarationInit(type)", type);
	exceptIfNull("VarDeclarationInit::VarDeclarationInit(initialValue)", initialValue);
}

VarDeclarationInit::~VarDeclarationInit() {
	delete type;
	delete initialValue;
}

bool VarDeclarationInit::operator==(const Node& n) const {
	const VarDeclarationInit* other = dynamic_cast<const VarDeclarationInit*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getType() == other->getType() && getName() == other->getName() && getInitialValue() == other->getInitialValue();
	}
	return true;
}

bool VarDeclarationInit::declarationSpecificCheck(map<string, const Declaration*>& scope) const {
	if(!(type->check(scope) && initialValue->check(scope))) {
		return false;
	}
	if(!(getType() == initialValue->getType(scope))) {
		cout << getPosition() << ": variable type and variable initial value type are not compatible." << endl;
		return false;
	} else {
		return true;
	}
}

const Type& VarDeclarationInit::getType() const {
	return *type;
}

const Expression& VarDeclarationInit::getInitialValue() const {
	return *initialValue;
}

ArrayDeclaration::ArrayDeclaration(const Position& pos, Type* type, const string& name, int size) :
	Declaration(pos, name, {}), type(PointerType(type)), size(size) {
	
	exceptIfNull("ArrayDeclaration::ArrayDeclaration(type)", type);
}

ArrayDeclaration::~ArrayDeclaration() {
	
}

bool ArrayDeclaration::operator==(const Node& n) const {
	const ArrayDeclaration* other = dynamic_cast<const ArrayDeclaration*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getType() == other->getType() && getName() == other->getName() && getSize() == other->getSize();
	}
}

bool ArrayDeclaration::declarationSpecificCheck(map<string, const Declaration*>& scope) const {
	return type.check(scope);
}

const PointerType& ArrayDeclaration::getType() const {
	return type;
}

const int& ArrayDeclaration::getSize() const {
	return size;
}

