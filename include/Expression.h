#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Type.h"
#include "Statement.h"
#include <string>
#include <map>

class Declaration;

/**
 * Represents an expression in the syntax tree. These are the only nodes that will produce a type and value.
 */
class Expression : public Statement {
public:
	Expression(const Position& pos, std::initializer_list<Node*> children);
	template<class T>
	Expression(const Position& pos, std::initializer_list<Node*> children, std::initializer_list<T> childrenVecs) : Statement(pos, children, childrenVecs) {
		
	}
	Expression(const Expression&) = delete;
	virtual ~Expression();
	virtual const Expression& operator=(const Expression&) = delete;
	
	virtual bool operator==(const Node&) const = 0;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const = 0;
	virtual const Type& getType(const std::map<std::string, const Declaration*>& scope) const = 0;
	virtual void accept(NodeVisitor&) const = 0;
	virtual Expression* clone() const = 0;
};

/**
 * Represents assignment to an lvalue. This returns the same value that is is assigned. The parser
 * will expand out "x += y" into "x = x + y" as the syntax tree is constructed, so this class is used
 * for all assignments other than ++ and --.
 */
class AssignExpression : public Expression {
private:
	Expression* assignTo;
	Expression* value;
public:
	AssignExpression(const Position& pos, Expression* assignTo, Expression* value);
	AssignExpression(const AssignExpression&) = delete;
	virtual ~AssignExpression();
	virtual const AssignExpression& operator=(const AssignExpression&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType(const std::map<std::string, const Declaration*>& scope) const;
	virtual const Expression& getAssignTo() const;
	virtual const Expression& getValue() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
	virtual AssignExpression* clone() const;
};

/**
 * Represents the ++ and -- operators as both suffixes and prefixes.
 */
class UnaryAssignExpression : public Expression {
private:
	Expression* expr;
	std::string op;
	bool suffix;
public:
	UnaryAssignExpression(const Position& pos, Expression* expr, const std::string& op);
	UnaryAssignExpression(const Position& pos, const std::string& op, Expression* expr);
	UnaryAssignExpression(const UnaryAssignExpression&) = delete;
	virtual ~UnaryAssignExpression();
	virtual const UnaryAssignExpression& operator=(const UnaryAssignExpression&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType(const std::map<std::string, const Declaration*>& scope) const;
	virtual const Expression& getExpr() const;
	virtual const std::string& getOp() const;
	virtual bool isSuffix() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
	virtual UnaryAssignExpression* clone() const;
};

/**
 * Represents all binary operators that don't do assignment.
 */
class BinaryOperatorExpression : public Expression {
private:
	Expression* left;
	std::string op;
	Expression* right;
public:
	BinaryOperatorExpression(const Position& pos, Expression* left, const std::string& op, Expression* right);
	BinaryOperatorExpression(const BinaryOperatorExpression&) = delete;
	~BinaryOperatorExpression();
	const BinaryOperatorExpression& operator=(const BinaryOperatorExpression&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType(const std::map<std::string, const Declaration*>& scope) const;
	virtual const Expression& getLeft() const;
	virtual const std::string& getOp() const;
	virtual const Expression& getRight() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
	virtual BinaryOperatorExpression* clone() const;
};

/**
 * Represents unary operators that don't do assignment. & expects an lvalue, the rest can take others.
 */
class UnaryOperatorExpression : public Expression {
private:
	std::string op;
	Expression* expr;
public:
	UnaryOperatorExpression(const Position& pos, const std::string& op, Expression* expr);
	UnaryOperatorExpression(const UnaryOperatorExpression&) = delete;
	virtual ~UnaryOperatorExpression();
	virtual const UnaryOperatorExpression& operator=(const UnaryOperatorExpression&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType(const std::map<std::string, const Declaration*>& scope) const;
	virtual const std::string& getOp() const;
	virtual const Expression& getExpr() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
	virtual UnaryOperatorExpression* clone() const;
};

/**
 * Superclass for nodes that represent an "lvalue", which is something that can be on the left
 * side of an assignment operation or as the parameter to the address-of (&) operator.
 */
class LValueExpression : public Expression {
public:
	LValueExpression(const Position& pos, std::initializer_list<Node*> children);
	LValueExpression(const LValueExpression&) = delete;
	virtual ~LValueExpression();
	virtual const LValueExpression& operator=(const LValueExpression&) = delete;
	
	virtual void accept(NodeVisitor&) const = 0;
};

/**
 * Represents a variable access or assignment. These are simply named by identifiers.
 */
class VarExpression : public LValueExpression {
private:
	std::string name;
	
public:
	VarExpression(const Position& pos, const std::string& name);
	VarExpression(const VarExpression&);
	virtual ~VarExpression();
	virtual const VarExpression& operator=(const VarExpression&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType(const std::map<std::string, const Declaration*>& scope) const;
	virtual const std::string& getName() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
	virtual VarExpression* clone() const;
};

/**
 * Represents a member access of a struct object. This looks like "mystruct.mymember". This
 * is an lvalue.
 */
class StructMemberExpression : public LValueExpression {
private:
	Expression* structure;
	std::string name;
public:
	StructMemberExpression(const Position& pos, Expression* structure, const std::string& name);
	StructMemberExpression(const StructMemberExpression&) = delete;
	virtual ~StructMemberExpression();
	virtual const StructMemberExpression& operator=(const StructMemberExpression&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType(const std::map<std::string, const Declaration*>& scope) const;
	virtual const Expression& getStruct() const;
	virtual const std::string& getMemberName() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
	virtual StructMemberExpression* clone() const;
};

/**
 * Represents accessing an array at a certain index, given by the "subscript" expression.
 * This looks like "arr[subscript]". This is an lvalue.
 */
class ArraySubscriptExpression : public LValueExpression {
private:
	Expression* array;
	Expression* subscript;
public:
	ArraySubscriptExpression(const Position& pos, Expression* array, Expression* subscript);
	ArraySubscriptExpression(const ArraySubscriptExpression&) = delete;
	virtual ~ArraySubscriptExpression();
	virtual const ArraySubscriptExpression& operator=(const ArraySubscriptExpression&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType(const std::map<std::string, const Declaration*>& scope) const;
	virtual const Expression& getArray() const;
	virtual const Expression& getSubscript() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
	virtual ArraySubscriptExpression* clone() const;
};

/**
 * Represents a function call. Function pointers are not supported, so all called functions are just
 * referenced by name. These look like "myFunc(myParam, myParam)".
 */
class FunctionCallExpression : public Expression {
private:
	std::string function;
	std::vector<Expression*> arguments;
public:
	FunctionCallExpression(const Position& pos, const std::string& function, const std::vector<Expression*>& arguments);
	FunctionCallExpression(const FunctionCallExpression&) = delete;
	virtual ~FunctionCallExpression();
	virtual const FunctionCallExpression& operator=(const FunctionCallExpression&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType(const std::map<std::string, const Declaration*>& scope) const;
	virtual const std::string& getFunction() const;
	virtual const std::vector<Expression*>& getArguments() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
	virtual FunctionCallExpression* clone() const;
};

/**
 * Takes in a type expression, and determines at compile time how large it is, in bytes. This will include
 * struct padding.
 */
class SizeofExpression : public Expression {
private:
	Type* sizeofType;
	IntType type;
public:
	SizeofExpression(const Position& pos, Type* type);
	SizeofExpression(const SizeofExpression&) = delete;
	virtual ~SizeofExpression();
	virtual const SizeofExpression& operator=(const SizeofExpression&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType(const std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getSizeofType() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
	virtual SizeofExpression* clone() const;
};

/**
 * Superclass for any expression that is a compile-time constant.
 */
class ConstantExpression : public Expression {
public:
	ConstantExpression(const Position& pos, std::initializer_list<Node*> children);
	ConstantExpression(const ConstantExpression&) = delete;
	virtual ~ConstantExpression();
	virtual const ConstantExpression& operator=(const ConstantExpression&) = delete;
};

/**
 * Represents an integer constant. These look like "5".
 */
class IntConstantExpression : public ConstantExpression {
private:
	unsigned int value;
	IntType type;
public:
	IntConstantExpression(const Position& pos, unsigned int value);
	IntConstantExpression(const IntConstantExpression&) = delete;
	virtual ~IntConstantExpression();
	virtual const IntConstantExpression& operator=(const IntConstantExpression&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType(const std::map<std::string, const Declaration*>& scope) const;
	virtual const unsigned int& getValue() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
	virtual IntConstantExpression* clone() const;
};

/**
 * Represents a string constant. These look like " "hello" ".
 */
class StringConstantExpression : public ConstantExpression {
private:
	std::string value;
	StringType type;
public:
	StringConstantExpression(const Position& pos, const std::string& value);
	StringConstantExpression(const StringConstantExpression&);
	virtual ~StringConstantExpression();
	virtual const StringConstantExpression& operator=(const StringConstantExpression&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType(const std::map<std::string, const Declaration*>& scope) const;
	virtual const std::string& getValue() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
	virtual StringConstantExpression* clone() const;
};





#endif