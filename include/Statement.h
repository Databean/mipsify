#ifndef STATEMENT_H
#define STATEMENT_H

#include "Node.h"
#include <vector>
#include <map>

class Expression;
class Declaration;

/**
 * The base class for anything that may require something output to the file. Declaration is a subclass of this.
 * Most Statements require some execution, but some Declarations do not. Expression is also a subclass of this.
 * All of the control structures are direct subclasses of Statement.
 */
class Statement : public Node {
public:
	Statement(const Position&, std::initializer_list<Node*> children);
	template<class T>
	Statement(const Position& pos, std::initializer_list<Node*> children, std::initializer_list<T> childrenVecs) : Node(pos, children, childrenVecs) {
		
	}
	Statement(const Statement&) = delete;
	virtual ~Statement();
	virtual const Statement& operator=(const Statement&) = delete;
	
	virtual bool operator==(const Node&) const = 0;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const = 0;
	virtual void accept(NodeVisitor&) const = 0;
};

/**
 * Represents a list of statements that share a scope. The scope is not shared with anything else,
 * except possibly as a parent scope to any children statement blocks. These look like
 * "{int x = 1; int y = x + 1;}".
 */
class StatementBlock : public Statement {
private:
	std::vector<Statement*> statements;
public:
	StatementBlock(const Position&, const std::vector<Statement*>& statements);
	StatementBlock(const StatementBlock&) = delete;
	virtual ~StatementBlock();
	virtual const StatementBlock& operator=(const StatementBlock&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const std::vector<Statement*>& getStatements() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents the If-Then control structure, and specifically not the If-Then-Else control structure.
 * These look like "if (x) y += 2;"
 */
class IfStatement : public Statement {
private:
	Expression* cond;
	Statement* then;
public:
	IfStatement(const Position&, Expression* cond, Statement* then);
	IfStatement(const IfStatement&) = delete;
	virtual ~IfStatement();
	virtual const IfStatement& operator=(const IfStatement&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Expression& getCond() const;
	virtual const Statement& getThen() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents the If-Then-Else control structure, and specifically not the If-Then control structure.
 * These look like "if (x) y += 2; else y -= 2;".
 */
class IfElseStatement : public Statement {
private:
	Expression* cond;
	Statement* then;
	Statement* els;
public:
	IfElseStatement(const Position&, Expression* cond, Statement* then, Statement* els);
	IfElseStatement(const IfStatement&) = delete;
	virtual ~IfElseStatement();
	virtual const IfElseStatement& operator=(const IfElseStatement&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Expression& getCond() const;
	virtual const Statement& getThen() const;
	virtual const Statement& getElse() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents the "while" control structure, and specifically not the "do-while" control structure.
 * These look like "while(x > 0) x--;"
 */
class WhileStatement : public Statement {
private:
	Expression* cond;
	Statement* loop;
public:
	WhileStatement(const Position&, Expression* cond, Statement* loop);
	WhileStatement(const WhileStatement&) = delete;
	virtual ~WhileStatement();
	virtual const WhileStatement& operator=(const WhileStatement&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Expression& getCond() const;
	virtual const Statement& getLoop() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents the "do-while" control structure, and specifically not the "while" control structure.
 * These look like "do x--; while(x>0);
 */
class DoWhileStatement : public Statement {
private:
	Statement* loop;
	Expression * cond;
public:
	DoWhileStatement(const Position&, Statement* loop, Expression* cond);
	DoWhileStatement(const DoWhileStatement&) = delete;
	virtual ~DoWhileStatement();
	virtual const DoWhileStatement& operator=(const DoWhileStatement&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Statement& getLoop() const;
	virtual const Expression& getCond() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents the "for" control structure. Every member of the "for" must be filled out.
 * These look like "for(i = 0; i < 10; i++) printInt(i);"
 */
class ForStatement : public Statement {
private:
	Expression* init;
	Expression* cond;
	Expression* incr;
	Statement* loop;
public:
	ForStatement(const Position&, Expression* init, Expression* cond, Expression* incr, Statement* loop);
	ForStatement(const ForStatement&) = delete;
	virtual ~ForStatement();
	virtual const ForStatement& operator=(const ForStatement&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Expression& getInit() const;
	virtual const Expression& getCond() const;
	virtual const Expression& getIncr() const;
	virtual const Statement& getLoop() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents the "break" statement, which is used to immediately exit a loop. These look
 * like "break;".
 */
class BreakStatement : public Statement {
public:
	BreakStatement(const Position&);
	BreakStatement(const BreakStatement&) = delete;
	virtual ~BreakStatement();
	virtual const BreakStatement& operator=(const BreakStatement&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents the "continue" statement, which is used to continue to the next iteration of a loop,
 * without executing the rest of the statements. These look like "continue;".
 */
class ContinueStatement : public Statement {
public:
	ContinueStatement(const Position&);
	ContinueStatement(const BreakStatement&) = delete;
	virtual ~ContinueStatement();
	virtual const ContinueStatement& operator=(const BreakStatement&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents the "switch" statement, which is used to compress a series of comparisons
 * into a series of "case" statements, which allow for fall-through. These look like
 * "switch(i) { case 1: i--; break; case 2: i++; break; }".
 */
class SwitchStatement : public Statement {
private:
	Expression* control;
	std::vector<Statement*> statements;
public:
	SwitchStatement(const Position&, Expression* control, const std::vector<Statement*>& statements);
	SwitchStatement(const SwitchStatement&) = delete;
	virtual ~SwitchStatement();
	virtual const SwitchStatement& operator=(const SwitchStatement&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Expression& getControl() const;
	virtual const std::vector<Statement*>& getStatements() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents a "case" statement. These are only used together with switch statements, as a
 * point of execution to jump into based on the value of the control expression of the switch.
 * These look like "case 1:".
 */
class CaseStatement : public Statement {
private:
	int value;
public:
	CaseStatement(const Position&, int value);
	CaseStatement(const CaseStatement&) = delete;
	virtual ~CaseStatement();
	virtual const CaseStatement& operator=(const CaseStatement&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const int& getValue() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents a "default" statement. These are only used together with switch statements, as a
 * point of execution to jump into if the control expression of the switch does not match any
 * of the cases. These look like "default:".
 */
class DefaultStatement : public Statement {
public:
	DefaultStatement(const Position&);
	DefaultStatement(const DefaultStatement&) = delete;
	virtual ~DefaultStatement();
	virtual const DefaultStatement& operator=(const DefaultStatement&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

/**
 * Represents the "return" statement, used to send a value to the caller of the function.
 * These will immediately exit the executing function and deliver the value to the caller.
 */
class ReturnStatement : public Statement {
private:
	Expression* ret;
public:
	ReturnStatement(const Position&, Expression* ret);
	ReturnStatement(const ReturnStatement&) = delete;
	virtual ~ReturnStatement();
	virtual const ReturnStatement& operator=(const ReturnStatement&) = delete;
	
	virtual bool operator==(const Node&) const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual const Expression& getRet() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

#endif