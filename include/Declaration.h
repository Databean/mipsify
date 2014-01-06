#ifndef DECLARATION_H
#define DECLARATION_H

#include "Statement.h"
#include <string>
#include <vector>
#include "Type.h"

class Expression;
class ConstantExpression;

/**
 * Represents a declaration of a variable, function, or structure. Every declaration is named, so the
 * name is stored in the superclass. The "check" method passes in a non-const reference to map specifically
 * so that Declarations can insert themselves into the scope when they are "checked".
 */
class Declaration : public Statement {
private:
	std::string name;
public:
	Declaration(const Position&, const std::string& name, std::initializer_list<Node*> children);
	template<class T>
	Declaration(const Position& pos, const std::string& name, std::initializer_list<Node*> children, std::initializer_list<T> childrenVecs) :
		Statement(pos, children, childrenVecs), name(name) {}
	Declaration(const Declaration&) = delete;
	virtual ~Declaration();
	virtual const Declaration& operator=(const Declaration&) = delete;
	
	virtual bool operator==(const Node&) const = 0;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual bool declarationSpecificCheck(std::map<std::string, const Declaration*>& scope) const = 0;
	virtual const std::string& getName() const;
	virtual void accept(NodeVisitor&) const = 0;
};

/**
 * Represents a declaration of a global variable that isn't an array and doesn't have an initializer.
 * Looks like "int i;" in the global scope.
 */
class GlobalVarDeclaration : public Declaration {
private:
	Type* type;
public:
	GlobalVarDeclaration(const Position&, Type* type, const std::string& name);
	GlobalVarDeclaration(const GlobalVarDeclaration&) = delete;
	virtual ~GlobalVarDeclaration();
	virtual const GlobalVarDeclaration& operator=(const GlobalVarDeclaration&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool declarationSpecificCheck(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
	
};

/**
 * Represents a declaration of a global variable that is an array. It does not have an initial value.
 * Looks like "int i[10];" in the global scope.
 */
class GlobalArrayDeclaration : public Declaration {
private:
	PointerType type;
	int size;
public:
	GlobalArrayDeclaration(const Position&, Type* type, const std::string& name, int size);
	GlobalArrayDeclaration(const GlobalArrayDeclaration&) = delete;
	virtual ~GlobalArrayDeclaration();
	virtual const GlobalArrayDeclaration& operator=(const GlobalArrayDeclaration&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool declarationSpecificCheck(std::map<std::string, const Declaration*>& scope) const;
	virtual const PointerType& getType() const;
	virtual const int& getSize() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents a non-array declaration in the global scope that has an initial value. It looks like
 * "int i = 5;" in the global scope.
 */
class GlobalVarDeclarationInit : public Declaration {
private:
	Type* type;
	ConstantExpression* initialValue;
public:
	GlobalVarDeclarationInit(const Position&, Type* type, const std::string& name, ConstantExpression* initialValue);
	GlobalVarDeclarationInit(const GlobalVarDeclarationInit&) = delete;
	virtual ~GlobalVarDeclarationInit();
	virtual const GlobalVarDeclarationInit& operator=(const GlobalVarDeclarationInit&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool declarationSpecificCheck(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType() const;
	virtual const ConstantExpression& getInitialValue() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents a single parameter of a function, either in a function prototype or a function declaration.
 * The parameter must be named.
 */
class FunctionParameter : public Declaration {
private:
	Type* type;
public:
	FunctionParameter(const Position&, Type* type, const std::string& name);
	FunctionParameter(const FunctionParameter&) = delete;
	virtual ~FunctionParameter();
	virtual const FunctionParameter& operator=(const FunctionParameter&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool declarationSpecificCheck(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents a function prototype. The parser only allows these in the global scope. These look like
 * int myFunction(int i, int j);
 */
class FunctionPrototype : public Declaration {
private:
	Type* type;
	std::vector<FunctionParameter*> parameters;
public:
	FunctionPrototype(const Position&, Type* type, const std::string& name, const std::vector<FunctionParameter*>& parameters);
	FunctionPrototype(const FunctionPrototype&) = delete;
	virtual ~FunctionPrototype();
	virtual const FunctionPrototype& operator=(const FunctionPrototype&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool declarationSpecificCheck(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType() const;
	virtual const std::vector<FunctionParameter*>& getParameters() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents a function declaration. The parser only allows these in the global scope. These look like
 * "int main() { int i = myOtherFunction(); }".
 */
class FunctionDeclaration : public Declaration {
private:
	Type* type;
	std::vector<FunctionParameter*> parameters;
	StatementBlock* body;
public:
	FunctionDeclaration(const Position&, Type* type, const std::string& name, const std::vector<FunctionParameter*>& parameters, StatementBlock* body);
	FunctionDeclaration(const FunctionDeclaration&) = delete;
	virtual ~FunctionDeclaration();
	virtual const FunctionDeclaration& operator=(const FunctionDeclaration&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual bool declarationSpecificCheck(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType() const;
	virtual const std::vector<FunctionParameter*>& getParameters() const;
	virtual const StatementBlock& getBody() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents a struct pre-declaration, which are used to support private data members as well as
 * to support mutual recursion in data structures (through pointers). These look like "struct a;".
 */
class StructPredeclaration : public Declaration {
private:
public:
	StructPredeclaration(const Position&, const std::string& name);
	StructPredeclaration(const StructPredeclaration&) = delete;
	virtual ~StructPredeclaration();
	virtual const StructPredeclaration& operator=(const StructPredeclaration&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool declarationSpecificCheck(std::map<std::string, const Declaration*>& scope) const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents a single member inside a struct declaration. These necessarily have a name and type.
 */
class StructMember : public Declaration {
private:
	Type* type;
public:
	StructMember(const Position&, Type* type, const std::string& name);
	StructMember(const StructMember&) = delete;
	virtual ~StructMember();
	virtual const StructMember& operator=(const StructMember&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool declarationSpecificCheck(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents a struct declaration. These look like "struct a { int i; int j; };".
 */
class StructDeclaration : public Declaration {
private:
	std::vector<StructMember*> members;
public:
	StructDeclaration(const Position&, const std::string& name, const std::vector<StructMember*>& members);
	StructDeclaration(const StructDeclaration&) = delete;
	virtual ~StructDeclaration();
	virtual const StructDeclaration& operator=(const StructDeclaration&) = delete;
	
	virtual bool operator==(const Node& n) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual bool declarationSpecificCheck(std::map<std::string, const Declaration*>& scope) const;
	virtual const std::vector<StructMember*>& getMembers() const;
	virtual bool hasMember(const std::string& name) const;
	virtual const StructMember& getMember(const std::string& name) const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents a variable declaration that exists on the stack. It does not have an initial value
 * and is not an array. These look like "int i;".
 */
class VarDeclaration : public Declaration {
private:
	Type* type;
public:
	VarDeclaration(const Position&, Type* type, const std::string& name);
	VarDeclaration(const VarDeclaration&) = delete;
	virtual ~VarDeclaration();
	virtual const VarDeclaration& operator=(const VarDeclaration&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool declarationSpecificCheck(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents a variable declaration that exists on the stack. It has an initial value and is not an array.
 * These look like "int i = 1 + 2 + 3;".
 */
class VarDeclarationInit : public Declaration {
private:
	Type* type;
	Expression* initialValue;
public:
	VarDeclarationInit(const Position&, Type* type, const std::string& name, Expression* initialValue);
	VarDeclarationInit(const VarDeclarationInit&) = delete;
	virtual ~VarDeclarationInit();
	virtual const VarDeclarationInit& operator=(const VarDeclarationInit&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool declarationSpecificCheck(std::map<std::string, const Declaration*>& scope) const;
	virtual const Type& getType() const;
	virtual const Expression& getInitialValue() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents an array variable declaration that exists on the stack. It does not have an initial value.
 * These look like "int i[10];" inside a scope.
 */
class ArrayDeclaration : public Declaration {
private:
	PointerType type;
	int size;
public:
	ArrayDeclaration(const Position&, Type* type, const std::string& name, int size);
	ArrayDeclaration(const ArrayDeclaration&) = delete;
	virtual ~ArrayDeclaration();
	virtual const ArrayDeclaration& operator=(const ArrayDeclaration&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool declarationSpecificCheck(std::map<std::string, const Declaration*>& scope) const;
	virtual const PointerType& getType() const;
	virtual const int& getSize() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

#endif