#ifndef NODE_H
#define NODE_H

#include <vector>
#include <initializer_list>
#include <string>
#include <algorithm>
#include <map>
#include <ostream>
#include <functional>
#include <type_traits>

class Declaration;
class Position;
class NodeVisitor;
struct YYLTYPE;

std::ostream &operator<<(std::ostream& output, const Position&);

/**
 * Represents a position in the Node in the source code, from the first line and column,
 * to the last line and column. This could also be used in conjunction with the file itself
 * in order to find the original string representing a particular node. The data for these
 * is assembled by the lexer and parser, and passed in as a YYLTYPE object.
 */
class Position {
private:
	int startLine;
	int endLine;
	int startColumn;
	int endColumn;
public:
	Position(const YYLTYPE&);
	Position(const Position& other);
	~Position();
	virtual const Position& operator=(const Position& other);
	
	virtual int getStartLine() const;
	virtual int getEndLine() const;
	virtual int getStartColumn() const;
	virtual int getEndColumn() const;
};

/**
 * The base class for any node on the abstract syntax tree. Don't add the same node to multiple syntax trees, as that
 * confuses what the parent of the Node is. When subclassing Node, remember to pass in all the children into either one
 * of the constructors. The cosntructor that takes a vector is provided for when the number of children is not known at
 * compile time.
 */
class Node {
private:
	Node* parent;
	Position position;
	
public:
	Node(const Position& pos, std::initializer_list<Node*> children);
	template<class T>
	Node(const Position& pos, std::initializer_list<Node*> children, std::initializer_list<T> childrenVecs) : Node(pos, children) {
		for(auto i = childrenVecs.begin(); i != childrenVecs.end(); i++) {
			for(auto j = i->begin(); j != i->end(); j++) {
				(*j)->parent = this;
			}
		}
	}
	Node(const Node& other) = delete;
	virtual ~Node();
	virtual const Node& operator=(const Node& other) = delete;
	
	/*
	template<class P, class R>
	auto ifInstance(const std::function<R(P)> func) -> R {
		P t = dynamic_cast<P>(this);
		if(t != NULL) {
			return f(t);
		} else {
			return R();
		}
	}*/
	
	virtual const Node& getParent() const;
	virtual const Position& getPosition() const;
	virtual bool hasParent() const;
	virtual bool operator==(const Node&) const = 0;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const = 0;
	virtual void accept(NodeVisitor&) const = 0;
};

class Program;

//Concrete Declarations
class GlobalVarDeclaration;
class GlobalArrayDeclaration;
class GlobalVarDeclarationInit;
class FunctionParameter;
class FunctionPrototype;
class FunctionDeclaration;
class StructPredeclaration;
class StructMember;
class StructDeclaration;
class VarDeclaration;
class VarDeclarationInit;
class ArrayDeclaration;

//Concrete Statements
class StatementBlock;
class IfStatement;
class IfElseStatement;
class WhileStatement;
class DoWhileStatement;
class ForStatement;
class BreakStatement;
class ContinueStatement;
class SwitchStatement;
class CaseStatement;
class DefaultStatement;
class ReturnStatement;

//Concrete Expressions
class AssignExpression;
class UnaryAssignExpression;
class BinaryOperatorExpression;
class UnaryOperatorExpression;
class VarExpression;
class StructMemberExpression;
class ArraySubscriptExpression;
class FunctionCallExpression;
class SizeofExpression;
class ConstantExpression;
class IntConstantExpression;
class StringConstantExpression;

/**
 * A visitor class that can visit any concrete class that has Node as a parent class
 * in the inheritance hierarchy. This class is abstract, so any concrete class that extends it
 * has to implement all of the methods.
 */
class NodeVisitor {
public:
	NodeVisitor() {}
	NodeVisitor(const NodeVisitor&) = delete;
	virtual ~NodeVisitor() {}
	virtual const NodeVisitor& operator=(const NodeVisitor&) = delete;
	
	virtual void visit(const Program&) = 0;
	
	virtual void visit(const GlobalVarDeclaration&) = 0;
	virtual void visit(const GlobalArrayDeclaration&) = 0;
	virtual void visit(const GlobalVarDeclarationInit&) = 0;
	virtual void visit(const FunctionParameter&) = 0;
	virtual void visit(const FunctionPrototype&) = 0;
	virtual void visit(const FunctionDeclaration&) = 0;
	virtual void visit(const StructPredeclaration&) = 0;
	virtual void visit(const StructMember&) = 0;
	virtual void visit(const StructDeclaration&) = 0;
	virtual void visit(const VarDeclaration&) = 0;
	virtual void visit(const VarDeclarationInit&) = 0;
	virtual void visit(const ArrayDeclaration&) = 0;
	
	virtual void visit(const StatementBlock&) = 0;
	virtual void visit(const IfStatement&) = 0;
	virtual void visit(const IfElseStatement&) = 0;
	virtual void visit(const WhileStatement&) = 0;
	virtual void visit(const DoWhileStatement&) = 0;
	virtual void visit(const ForStatement&) = 0;
	virtual void visit(const BreakStatement&) = 0;
	virtual void visit(const ContinueStatement&) = 0;
	virtual void visit(const SwitchStatement&) = 0;
	virtual void visit(const CaseStatement&) = 0;
	virtual void visit(const DefaultStatement&) = 0;
	virtual void visit(const ReturnStatement&) = 0;
	
	virtual void visit(const AssignExpression&) = 0;
	virtual void visit(const UnaryAssignExpression&) = 0;
	virtual void visit(const UnaryOperatorExpression&) = 0;
	virtual void visit(const BinaryOperatorExpression&) = 0;
	virtual void visit(const VarExpression&) = 0;
	virtual void visit(const StructMemberExpression&) = 0;
	virtual void visit(const ArraySubscriptExpression&) = 0;
	virtual void visit(const FunctionCallExpression&) = 0;
	virtual void visit(const SizeofExpression&) = 0;
	virtual void visit(const IntConstantExpression&) = 0;
	virtual void visit(const StringConstantExpression&) = 0;
};

#endif