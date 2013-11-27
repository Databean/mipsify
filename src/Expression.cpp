#include "Expression.h"
#include "Statement.h"
#include "Util.h"
#include <stdexcept>
#include "Operator.h"
#include <iostream>
#include "Declaration.h"
#include "Type.h"
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::initializer_list;
using std::string;
using std::invalid_argument;
using std::map;
using std::runtime_error;

Expression::Expression(const Position& pos, initializer_list<Node*> children) : Statement(pos, children) {
	
}

Expression::~Expression() {
	
}

AssignExpression::AssignExpression(const Position& pos, Expression* assignTo, Expression* value) : Expression(pos, {assignTo, value}), assignTo(assignTo), value(value) {
	exceptIfNull("AssignExpression::AssignExpression(assignTo)", assignTo);
	exceptIfNull("AssignExpression::AssignExpression(value)", value);
}

AssignExpression::~AssignExpression() {
	delete assignTo;
	delete value;
}

bool AssignExpression::operator==(const Node& n) const {
	const AssignExpression* other = dynamic_cast<const AssignExpression*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getAssignTo() == other->getAssignTo() && getValue() == other->getValue();
	}
	return true;
}

bool AssignExpression::check(map<string, const Declaration*>& scope) const {
	if(!(assignTo->check(scope) && value->check(scope))) {
		return false;
	}
	if(dynamic_cast<LValueExpression*>(assignTo) == NULL) {
		cout << getPosition() << ": Left side of assignment is not an lvalue." << endl;
		return false;
	}
	if(!(assignTo->getType(scope) == value->getType(scope))) {
		cout << getPosition() << ": Left and right side of assignment do not have the same type.";
		return false;
	}
	return true;
}

const Type& AssignExpression::getType(const map<string, const Declaration*>& scope) const {
	return assignTo->getType(scope);
}

const Expression& AssignExpression::getAssignTo() const {
	return *assignTo;
}

const Expression& AssignExpression::getValue() const {
	return *value;
}

AssignExpression* AssignExpression::clone() const {
	return new AssignExpression(getPosition(), assignTo->clone(), value->clone());
}

UnaryAssignExpression::UnaryAssignExpression(const Position& pos, Expression* expr, const string& op) : Expression(pos, {expr}), expr(expr), op(op), suffix(true) {
	exceptIfNull("UnaryAssignExpression::UnaryAssignExpression(expr)", expr);
}

UnaryAssignExpression::UnaryAssignExpression(const Position& pos, const string& op, Expression* expr) : Expression(pos, {expr}), expr(expr), op(op), suffix(false) {
	exceptIfNull("UnaryAssignExpression::UnaryAssignExpression(expr)", expr);
}

UnaryAssignExpression::~UnaryAssignExpression() {
	delete expr;
}

bool UnaryAssignExpression::operator==(const Node& n) const {
	const UnaryAssignExpression* other = dynamic_cast<const UnaryAssignExpression*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getExpr() == other->getExpr() && getOp() == other->getOp() && isSuffix() == other->isSuffix();
	}
	return true;
}

bool UnaryAssignExpression::check(map<string, const Declaration*>& scope) const {
	if(expr->check(scope) && dynamic_cast<LValueExpression*>(expr) != NULL) {
		const Type& type = expr->getType(scope);
		if(!(type == IntType() || type == PointerType(new IntType()))) { // The PointerType destructor will take care of the IntType.
			cout << getPosition() << ": ++ or -- target is not an int or a pointer." << endl;
			return false;
		} else {
			return true;
		}
	} else {
		cout << getPosition() << ": ++ or -- target is not an lvalue." << endl;
		return false;
	}
}

const Type& UnaryAssignExpression::getType(const map<string, const Declaration*>& scope) const {
	return expr->getType(scope);
}

const Expression& UnaryAssignExpression::getExpr() const {
	return *expr;
}

const string& UnaryAssignExpression::getOp() const {
	return op;
}

bool UnaryAssignExpression::isSuffix() const {
	return suffix;
}

UnaryAssignExpression* UnaryAssignExpression::clone() const {
	if(suffix) {
		return new UnaryAssignExpression(getPosition(), expr->clone(), op);
	} else {
		return new UnaryAssignExpression(getPosition(), op, expr->clone());
	}
}

BinaryOperatorExpression::BinaryOperatorExpression(const Position& pos, Expression* left, const string& op, Expression* right) :
	Expression(pos, {left, right}), left(left), op(op), right(right) {
	
	exceptIfNull("BinaryOperatorExpression::BinaryOperatorExpression(left)", left);
	exceptIfNull("BinaryOperatorExpression::BinaryOperatorExpression(right)", right);
}

BinaryOperatorExpression::~BinaryOperatorExpression() {
	delete left;
	delete right;
}

bool BinaryOperatorExpression::operator==(const Node& n) const {
	const BinaryOperatorExpression* other = dynamic_cast<const BinaryOperatorExpression*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getLeft() == other->getLeft() && getOp() == other->getOp() && getRight() == other->getRight();
	}
	return true;
}

bool BinaryOperatorExpression::check(map<string, const Declaration*>& scope) const {
	if(!(left->check(scope) && right->check(scope))) {
		return false;
	} else if(!validOp(left->getType(scope), op, right->getType(scope))) {
		cout << getPosition() << ": not valid types for " << op << "." << endl;
		return false;
	} else {
		return true;
	}
}

const Type& BinaryOperatorExpression::getType(const map<string, const Declaration*>& scope) const {
	return getOpType(left->getType(scope), op, right->getType(scope));
}

const Expression& BinaryOperatorExpression::getLeft() const {
	return *left;
}

const string& BinaryOperatorExpression::getOp() const {
	return op;
}

const Expression& BinaryOperatorExpression::getRight() const {
	return *right;
}

BinaryOperatorExpression* BinaryOperatorExpression::clone() const {
	return new BinaryOperatorExpression(getPosition(), left->clone(), op, right->clone());
}

UnaryOperatorExpression::UnaryOperatorExpression(const Position& pos, const std::string& op, Expression* expr) : Expression(pos, {expr}), op(op), expr(expr) {
	exceptIfNull("UnaryOperatorExpression::UnaryOperatorExpression(expr)", expr);
}

UnaryOperatorExpression::~UnaryOperatorExpression() {
	delete expr;
}

bool UnaryOperatorExpression::operator==(const Node& n) const {
	const UnaryOperatorExpression* other = dynamic_cast<const UnaryOperatorExpression*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getOp() == other->getOp() && getExpr() == other->getExpr();
	}
	return true;
}

bool UnaryOperatorExpression::check(map<string, const Declaration*>& scope) const {
	if(!(expr->check(scope))) {
		return false;
	}
	if(!validOp(op, expr->getType(scope))) {
		cout << getPosition() << ": not a valid type for " << op << "." << endl;
		return false;
	}
	if(op == "&") {
		if(dynamic_cast<LValueExpression*>(expr) == NULL) {
			cout << getPosition() << ": argument to & is not an lvalue." << endl;
			return false;
		}
		return true;
	} else {
		return true;
	}
}

const Type& UnaryOperatorExpression::getType(const map<string, const Declaration*>& scope) const {
	return getOpType(op, expr->getType(scope));
}

const string& UnaryOperatorExpression::getOp() const {
	return op;
}

const Expression& UnaryOperatorExpression::getExpr() const {
	return *expr;
}

UnaryOperatorExpression* UnaryOperatorExpression::clone() const {
	return new UnaryOperatorExpression(getPosition(), op, expr->clone());
}

LValueExpression::LValueExpression(const Position& pos, std::initializer_list<Node*> children) : Expression(pos, children) {
	
}

LValueExpression::~LValueExpression() {
	
}

VarExpression::VarExpression(const Position& pos, const string& name) : LValueExpression(pos, {}), name(name) {
	
}

VarExpression::~VarExpression() {
	
}
bool VarExpression::operator==(const Node& n) const {
	const VarExpression* other = dynamic_cast<const VarExpression*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getName() == other->getName();
	}
}

bool VarExpression::check(map<string, const Declaration*>& scope) const {
	if(scope.count(name) == 0) {
		cout << getPosition() << ": there is no declaration by that name." << endl;
		return false;
	} else {
		const Declaration* decl = scope[name];
		auto gvar = dynamic_cast<const GlobalVarDeclaration*>(decl);
		if(gvar != NULL) {
			return true;
		}
		auto garray = dynamic_cast<const GlobalArrayDeclaration*>(decl);
		if(garray != NULL) {
			return true;
		}
		auto ginit = dynamic_cast<const GlobalVarDeclarationInit*>(decl);
		if(ginit != NULL) {
			return true;
		}
		auto var = dynamic_cast<const VarDeclaration*>(decl);
		if(var != NULL) {
			return true;
		}
		auto array = dynamic_cast<const ArrayDeclaration*>(decl);
		if(array != NULL) {
			return true;
		}
		auto init = dynamic_cast<const VarDeclarationInit*>(decl);
		if(init != NULL) {
			return true;
		}
		auto fparam = dynamic_cast<const FunctionParameter*>(decl);
		if(fparam != NULL) {
			return true;
		}
		cout << getPosition() << ": variable expression declaration is not a variable declaration." << endl;
		return false;
	}
}

const Type& VarExpression::getType(const map<string, const Declaration*>& scope) const {
	if(scope.count(name) == 0) {
		throw runtime_error("VarExpression declaration could not be found.");
	} else {
		const Declaration* decl = scope.find(name)->second;
		auto gvar = dynamic_cast<const GlobalVarDeclaration*>(decl);
		if(gvar != NULL) {
			return gvar->getType();
		}
		auto garray = dynamic_cast<const GlobalArrayDeclaration*>(decl);
		if(garray != NULL) {
			return garray->getType();
		}
		auto ginit = dynamic_cast<const GlobalVarDeclarationInit*>(decl);
		if(ginit != NULL) {
			return ginit->getType();
		}
		auto var = dynamic_cast<const VarDeclaration*>(decl);
		if(var != NULL) {
			return var->getType();
		}
		auto array = dynamic_cast<const ArrayDeclaration*>(decl);
		if(array != NULL) {
			return array->getType();
		}
		auto init = dynamic_cast<const VarDeclarationInit*>(decl);
		if(init != NULL) {
			return init->getType();
		}
		auto fparam = dynamic_cast<const FunctionParameter*>(decl);
		if(fparam != NULL) {
			return fparam->getType();
		}
		throw runtime_error("The VarExpression declaration is not a valid variable one.");
	}
}

const string& VarExpression::getName() const {
	return name;
}

VarExpression* VarExpression::clone() const {
	return new VarExpression(getPosition(), name);
}

StructMemberExpression::StructMemberExpression(const Position& pos, Expression* structure, const string& name) :
	LValueExpression(pos, {structure}), structure(structure), name(name) {
	
	exceptIfNull("StructMemberExpression::StructMemberExpression(structure)", structure);
}

StructMemberExpression::~StructMemberExpression() {
	delete structure;
}

bool StructMemberExpression::operator==(const Node& n) const {
	const StructMemberExpression* other = dynamic_cast<const StructMemberExpression*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getStruct() == other->getStruct() && getMemberName() == other->getMemberName();
	}
	return true;
}

bool StructMemberExpression::check(map<string, const Declaration*>& scope) const {
	if(!structure->check(scope)) {
		return false;
	}
	const PointerType* ptype = dynamic_cast<const PointerType*>(&(structure->getType(scope)));
	const StructType* stype = NULL;
	if(ptype == NULL) {
		stype = dynamic_cast<const StructType*>(&(structure->getType(scope)));
	} else {
		stype = dynamic_cast<const StructType*>(&(ptype->getWrapped()));
	}
	if(stype == NULL) {
		cout << getPosition() << ": there is no struct type declaration for the type of struct being used here." << endl;
		return false;
	} else {
		const string& tname = stype->getName();
		if(scope.count(tname) == 0) {
			cout << getPosition() << ": this struct type does not have any member by this name." << endl;
			return false;
		} else {
			auto sdecl = dynamic_cast<const StructDeclaration*>(scope[tname]);
			if(sdecl == NULL) {
				return false;
			} else {
				return sdecl->hasMember(name);
			}
		}
	}
	return false;
}

const Type& StructMemberExpression::getType(const map<string, const Declaration*>& scope) const {
	const PointerType* ptype = dynamic_cast<const PointerType*>(&(structure->getType(scope)));
	const StructType* stype = NULL;
	if(ptype == NULL) {
		stype = dynamic_cast<const StructType*>(&(structure->getType(scope)));
	} else {
		stype = dynamic_cast<const StructType*>(&(ptype->getWrapped()));
	}
	if(stype == NULL) {
		throw runtime_error("StructMemberExpression::getType(scope): structure does not have a struct type.");
	} else {
		const string& tname = stype->getName();
		if(scope.count(tname) == 0) {
			throw runtime_error("StructMemberExpression::getType(scope): no structure with that type exists.");
		} else {
			auto sdecl = dynamic_cast<const StructDeclaration*>(scope.find(tname)->second);
			if(sdecl == NULL) {
				throw runtime_error("StructMemberExpression::getType(scope): this name does not have a struct declaration.");
			} else {
				if(sdecl->hasMember(name)) {
					return sdecl->getMember(name).getType();
				} else {
					throw runtime_error("StructMemberExpression::getType(scope): This struct does not have a member by that name.");
				}
			}
		}
	}
	throw runtime_error("StructMemberExpression::getType(scope): Something went wrong and i'm not sure what.");
}

const Expression& StructMemberExpression::getStruct() const {
	return *structure;
}

const string& StructMemberExpression::getMemberName() const {
	return name;
}

StructMemberExpression* StructMemberExpression::clone() const {
	return new StructMemberExpression(getPosition(), structure->clone(), name);
}

ArraySubscriptExpression::ArraySubscriptExpression(const Position& pos, Expression* array, Expression* subscript) :
	LValueExpression(pos, {array, subscript}), array(array), subscript(subscript) {
	
	exceptIfNull("ArraySubscriptExpression::ArraySubscriptExpression(array)", array);
	exceptIfNull("ArraySubscriptExpression::ArraySubscriptExpression(subscript)", subscript);
}

ArraySubscriptExpression::~ArraySubscriptExpression() {
	delete array;
	delete subscript;
}

bool ArraySubscriptExpression::operator==(const Node& n) const {
	const ArraySubscriptExpression* other = dynamic_cast<const ArraySubscriptExpression*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getArray() == other->getArray() && getSubscript() == other->getSubscript();
	}
	return true;
}

bool ArraySubscriptExpression::check(map<string, const Declaration*>& scope) const {
	if(!(array->check(scope) && subscript->check(scope))) {
		return false;
	}
	if(!(subscript->getType(scope) == IntType())) {
		cout << getPosition() << ": the array subscript is not an integer." << endl;
		return false;
	}
	const PointerType* p = dynamic_cast<const PointerType*>(&(array->getType(scope)));
	if(p == NULL) {
		cout << getPosition() << ": the array expression does not have a pointer type." << endl;
		return false;
	} else {
		return true;
	}
}

const Type& ArraySubscriptExpression::getType(const map<string, const Declaration*>& scope) const {
	const PointerType* p = dynamic_cast<const PointerType*>(&(array->getType(scope)));
	if(p == NULL) {
		throw runtime_error("ArraySubscriptExpression array is not a PointerType.");
	} else {
		return p->getWrapped();
	}
}

const Expression& ArraySubscriptExpression::getArray() const {
	return *array;
}

const Expression& ArraySubscriptExpression::getSubscript() const {
	return *subscript;
}

ArraySubscriptExpression* ArraySubscriptExpression::clone() const {
	return new ArraySubscriptExpression(getPosition(), array->clone(), subscript->clone());
}

FunctionCallExpression::FunctionCallExpression(const Position& pos, const string& function, const vector<Expression*>& arguments) : 
	Expression(pos, {}, {arguments}), function(function), arguments(arguments) {
	
	exceptIfNullMember("FunctionCallExpression::FunctionCallExpression(arguments)", arguments);
}

FunctionCallExpression::~FunctionCallExpression() {
	deletePtrVecMembers(arguments);
}

bool FunctionCallExpression::operator==(const Node& n) const {
	const FunctionCallExpression* other = dynamic_cast<const FunctionCallExpression*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getFunction() == other->getFunction() &&
			ptrCollectionEqual(arguments, other->arguments);
	}
}

bool FunctionCallExpression::check(map<string, const Declaration*>& scope) const {
	for(auto it = arguments.begin(); it != arguments.end(); it++) {
		if(!((*it)->check(scope))) {
			return false;
		}
	}
	
	if(scope.count(function) == 0) {
		cout << getPosition() << ": there is no declaration by the function name in the scope." << endl;
		return false;
	} else {
		const Declaration* decl = scope.find(function)->second;
		auto fdecl = dynamic_cast<const FunctionDeclaration*>(decl);
		auto fprot = dynamic_cast<const FunctionPrototype*>(decl);
		vector<FunctionParameter*> parameters;
		
		if(fdecl != NULL) {
			parameters = fdecl->getParameters();
		} else if(fprot != NULL) {
			parameters = fprot->getParameters();
		} else {
			cout << getPosition() << ": the declaration referred to by the function name is not a function." << endl;
			return false;
		}
		
		if(parameters.size() != arguments.size()) {
			cout << getPosition() << ": the number of parameters in the call does not match the number of parameters the function takes." << endl;
			return false;
		}
		auto argIt = arguments.begin();
		auto prmIt = parameters.begin();
		for(; argIt != arguments.end() && prmIt != parameters.end(); argIt++, prmIt++) {
			if(!((*argIt)->getType(scope) == (*prmIt)->getType())) {
				cout << (*argIt)->getPosition() << ": the argument type does not match the expected parameter type." << endl;
				return false;
			}
		}
		return true;
	}
}

const Type& FunctionCallExpression::getType(const map<string, const Declaration*>& scope) const {
	if(scope.count(function) == 0) {
		throw runtime_error("FunctionCallExpression declaration could not be found.");
	} else {
		const Declaration* decl = scope.find(function)->second;
		auto fdecl = dynamic_cast<const FunctionDeclaration*>(decl);
		if(fdecl != NULL) {
			return fdecl->getType();
		}
		auto fprot = dynamic_cast<const FunctionPrototype*>(decl);
		if(fprot != NULL) {
			return fprot->getType();
		}
		throw runtime_error("The function name does not refer to a function declaration.");
	}
}

const string& FunctionCallExpression::getFunction() const {
	return function;
}

const vector<Expression*>& FunctionCallExpression::getArguments() const {
	return arguments;
}

FunctionCallExpression* FunctionCallExpression::clone() const {
	return new FunctionCallExpression(getPosition(), function, clonePtrVec(arguments));
}

SizeofExpression::SizeofExpression(const Position& pos, Type* sizeofType) : Expression(pos, {}), sizeofType(sizeofType) {
	exceptIfNull("SizeofExpression::SizeofExpression(sizeofType)", sizeofType);
}

SizeofExpression::~SizeofExpression() {
	delete sizeofType;
}

bool SizeofExpression::operator==(const Node& n) const {
	const SizeofExpression* other = dynamic_cast<const SizeofExpression*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getSizeofType() == other->getSizeofType();
	}
}

bool SizeofExpression::check(map<string, const Declaration*>& scope) const {
	return sizeofType->check(scope);
}

const Type& SizeofExpression::getType(const map<string, const Declaration*>& scope) const {
	return type;
}

const Type& SizeofExpression::getSizeofType() const {
	return *sizeofType;
}

SizeofExpression* SizeofExpression::clone() const {
	return new SizeofExpression(getPosition(), sizeofType->clone());
}

ConstantExpression::ConstantExpression(const Position& pos, std::initializer_list<Node*> children) : Expression(pos, children) {
	
}

ConstantExpression::~ConstantExpression() {
	
}

IntConstantExpression::IntConstantExpression(const Position& pos, unsigned int value) : ConstantExpression(pos, {}), value(value) {
	
}

IntConstantExpression::~IntConstantExpression() {
	
}

bool IntConstantExpression::operator==(const Node& n) const {
	const IntConstantExpression* other = dynamic_cast<const IntConstantExpression*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getValue() == other->getValue();
	}
}

bool IntConstantExpression::check(map<string, const Declaration*>& scope) const {
	return true;
}

const Type& IntConstantExpression::getType(const map<string, const Declaration*>& scope) const {
	return type;
}

const unsigned int& IntConstantExpression::getValue() const {
	return value;
}

IntConstantExpression* IntConstantExpression::clone() const {
	return new IntConstantExpression(getPosition(), value);
}

StringConstantExpression::StringConstantExpression(const Position& pos, const string& value) : ConstantExpression(pos, {}), value(value) {
	
}

StringConstantExpression::~StringConstantExpression() {
	
}

bool StringConstantExpression::operator==(const Node& n) const {
	const StringConstantExpression* other = dynamic_cast<const StringConstantExpression*>(&n);
	if(other == NULL) {
		return false;
	} else {
		return getValue() == other->getValue();
	}
}

bool StringConstantExpression::check(map<string, const Declaration*>& scope) const {
	return true;
}

const Type& StringConstantExpression::getType(const map<string, const Declaration*>& scope) const {
	return type;
}

const string& StringConstantExpression::getValue() const {
	return value;
}

StringConstantExpression* StringConstantExpression::clone() const {
	return new StringConstantExpression(getPosition(), value);
}



