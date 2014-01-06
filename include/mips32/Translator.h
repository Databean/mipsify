#ifndef MIPS32_TRANSLATOR_H
#define MIPS32_TRANSLATOR_H

#include "Node.h"
#include "Parser.h"
#include <map>
#include <vector>
#include <set>
#include <string>
#include "mips32/Instruction.h"

class Expression;

namespace mips32 {
	
	/**
	 * Monster class that translates the abstract syntax tree into MIPS assembly.
	 * It visits nodes and produces the MIPS instructions necessary to execute
	 * the program.
	 */
	class Translator : public NodeVisitor {
	private:
		std::set<Register> remainingRegisters;
		std::set<Register> registersInUse;
		
		std::map<const Expression*, Register> intermediate;
		std::vector<Instruction*> instructions;
		std::string label;
		
		std::string currentLoopContinueLabel;
		std::string currentLoopBreakLabel;
		
		std::vector<std::map<std::string, const Declaration*>> scopes;
		std::map<const Declaration*, int> stackPointerOffsets;
		int stackSize;
		
		int labelIndex;
		
		Register getVarAddress(const VarExpression&);
		Register getArraySubscriptAddress(const ArraySubscriptExpression&);
		Register getStructMemberAddress(const StructMemberExpression& elem);
		
		void reclaimRegisters();
		Register getFreeRegister();
		void returnRegister(Register);
		
		std::map<std::string, const Declaration*>& getScope();
		void pushScope();
		void popScope();
		
	public:
		Translator();
		Translator(const Translator&) = delete;
		virtual ~Translator();
		virtual const Translator& operator=(const Translator&) = delete;
		
		virtual std::vector<Instruction*> translate(const Program&);
		
		virtual void visit(const Program&);
		
		virtual void visit(const GlobalVarDeclaration&);
		virtual void visit(const GlobalArrayDeclaration&);
		virtual void visit(const GlobalVarDeclarationInit&);
		virtual void visit(const FunctionParameter&);
		virtual void visit(const FunctionPrototype&);
		virtual void visit(const FunctionDeclaration&);
		virtual void visit(const StructPredeclaration&);
		virtual void visit(const StructMember&);
		virtual void visit(const StructDeclaration&);
		virtual void visit(const VarDeclaration&);
		virtual void visit(const VarDeclarationInit&);
		virtual void visit(const ArrayDeclaration&);
		
		virtual void visit(const StatementBlock&);
		virtual void visit(const IfStatement&);
		virtual void visit(const IfElseStatement&);
		virtual void visit(const WhileStatement&);
		virtual void visit(const DoWhileStatement&);
		virtual void visit(const ForStatement&);
		virtual void visit(const BreakStatement&);
		virtual void visit(const ContinueStatement&);
		virtual void visit(const SwitchStatement&);
		virtual void visit(const CaseStatement&);
		virtual void visit(const DefaultStatement&);
		virtual void visit(const ReturnStatement&);
		
		virtual void visit(const AssignExpression&);
		virtual void visit(const UnaryAssignExpression&);
		virtual void visit(const UnaryOperatorExpression&);
		virtual void visit(const BinaryOperatorExpression&);
		virtual void visit(const VarExpression&);
		virtual void visit(const StructMemberExpression&);
		virtual void visit(const ArraySubscriptExpression&);
		virtual void visit(const FunctionCallExpression&);
		virtual void visit(const SizeofExpression&);
		virtual void visit(const IntConstantExpression&);
		virtual void visit(const StringConstantExpression&);
	};
	
}

#endif