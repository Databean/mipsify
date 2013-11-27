#include "mips32/Translator.h"

#include "mips32/Arithmetic.h"
#include "Node.h"
#include "Statement.h"
#include "Expression.h"
#include "Declaration.h"
#include "Util.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::for_each;
using std::map;
using std::runtime_error;

namespace mips32 {
	
	/**
	 * Re-inserts escape sequences so that they can be again unescaped
	 * by the assembler.
	 */
	string escapeString(const string& s) {
		string newValue;
		for(auto it = s.begin(); it != s.end(); it++) {
			char c = *it;
			switch(c) {
				case '\n':
					newValue += "\\n";
					break;
				case '\t':
					newValue += "\\t";
					break;
				case '\r':
					newValue += "\\r";
					break;
				default:
					newValue += c;
					break;
			}
		}
		return newValue;
	}
	
	/**
	 * Constructs a Translator.
	 */
	Translator::Translator() {
		
	}
	
	/**
	 * Destroys a Translator.
	 */
	Translator::~Translator() {
		
	}
	
	/**
	 * Gets the current scope off the top of the stack of scopes.
	 */
	map<string, const Declaration*>& Translator::getScope() {
		return scopes.back();
	}
	
	/**
	 * Copies the current scope, and pushes it onto the stack.
	 * Used when entering a new scope.
	 */
	void Translator::pushScope() {
		scopes.push_back(scopes.back());
	}
	
	/**
	 * Pops the top scope off of the stack. Used when exiting a scope.
	 */
	void Translator::popScope() {
		scopes.pop_back();
	}
	
	/**
	 * Gets a register that is not at the moment in use by anything else.
	 * Marks the register as "in use" until it is returned.
	 */
	Register Translator::getFreeRegister() {
		if(remainingRegisters.empty()) {
			throw runtime_error("No free registers left. Somebody program me better to deal with this case.");
		} else {
			Register ret = *(remainingRegisters.begin());
			remainingRegisters.erase(ret);
			registersInUse.insert(ret);
			return ret;
		}
	}
	
	/**
	 * Marks the register as "not in use", and adds it to the pool of registers that are available
	 * for usage.
	 */
	void Translator::returnRegister(Register r) {
		remainingRegisters.insert(r);
		registersInUse.erase(r);
	}
	
	/**
	 * Marks all registers as "not in use".
	 */
	void Translator::reclaimRegisters() {
		remainingRegisters = { R_T0, R_T1, R_T2, R_T3, R_T4, R_T5, R_T6, R_T7, R_T8, R_T9 };
		registersInUse = {};
	}
	
	/**
	 * Translates a program into a list of MIPS instructions, returned as a vector.
	 */
	vector<Instruction*> Translator::translate(const Program& program) {
		labelIndex = 0;
		currentLoopContinueLabel = "";
		currentLoopBreakLabel = "";
		scopes = {map<string, const Declaration*>()};
		instructions = {};
		program.accept(*this);
		return instructions;
	}
	
	/**
	 * Entry point for actually converting the program. This is invoked directly by Translator::translate.
	 */
	void Translator::visit(const Program& elem) {
		reclaimRegisters();
		const vector<Declaration*>& declarations = elem.getDeclarations();
		for_each(declarations.begin(), declarations.end(), [this](Declaration* d){ d->accept(*this); });
	}
	
	
	/**
	 * Allocates global space for a variable that has no initial value and isn't an array.
	 */
	void Translator::visit(const GlobalVarDeclaration& elem) {
		getScope()[elem.getName()] = &elem;
		if(elem.getType() == IntType() || elem.getType() == PointerType(new IntType())) {
			instructions.push_back(new IntGlobal("global_" + elem.getName(), 0));
		} else if(elem.getType() == StringType()) {
			instructions.push_back(new StringGlobal("global_" + elem.getName(), ""));
		} else {
			throw runtime_error("Cannot deal with non-int globals yet.");
		}
	}
	
	/**
	 * Allocates global space for a variable that is an array. The initial values of all the elements
	 * are undefined. Adds the variable to the scope.
	 */
	void Translator::visit(const GlobalArrayDeclaration& elem) {
		getScope()[elem.getName()] = &elem;
		instructions.push_back(new ArrayGlobal("global_" + elem.getName(), elem.getType().getWrapped().getSize(getScope()) * elem.getSize()));
	}
	
	/**
	 * Allocates global space for a variable that isn't an array and gives it a specific initial value. Adds the variable
	 * to the scope.
	 */
	void Translator::visit(const GlobalVarDeclarationInit& elem) {
		getScope()[elem.getName()] = &elem;
		if(elem.getType() == IntType() || elem.getType() == PointerType(new IntType())) {
			instructions.push_back(new IntGlobal("global_" + elem.getName(), dynamic_cast<const IntConstantExpression&>(elem.getInitialValue()).getValue()));
		} else if(elem.getType() == StringType()) {
			instructions.push_back(new StringGlobal("global_" + elem.getName(), escapeString(dynamic_cast<const StringConstantExpression&>(elem.getInitialValue()).getValue())));
		} else {
			throw runtime_error("Cannot deal with non-int globals yet.");
		}
	}
	
	/**
	 * Stores the offset of the given function parameter from the beginning of the list of function parameters in memory.
	 * Adds the variable to the scope of the function.
	 */
	void Translator::visit(const FunctionParameter& elem) {
		getScope()[elem.getName()] = &elem;
		stackPointerOffsets[&elem] = stackSize;
		stackSize += elem.getType().getSize(getScope());
	}
	
	/**
	 * Adds the function to the scope so it can be invoked, e.g. for use with mutually recursive functions
	 * for which the types of both have to be available before either can be declared.
	 */
	void Translator::visit(const FunctionPrototype& elem) {
		getScope()[elem.getName()] = &elem;
	}
	
	/**
	 * Determines the MIPS for a function definition. Adjusts the stack to make space for all of the declarations
	 * inside the function, and figures out where the parameters go in the argument list that is passed in.
	 * For an in-depth explanation of calling conventions, see the function application method, 
	 * Translator::visit(const FunctionCallExpression&)
	 */
	void Translator::visit(const FunctionDeclaration& elem) {
		reclaimRegisters();
		getScope()[elem.getName()] = &elem;
		label = elem.getName();
		instructions.push_back(new Label(label));
		
		pushScope();
		const vector<FunctionParameter*>& params = elem.getParameters();
		stackSize = 0;
		for_each(params.begin(), params.end(), [this](FunctionParameter* fp){ fp->accept(*this); });
		//int paramSize = stackSize;
		stackSize = 0;
		
		LoadImmediate* loadStackSize = new LoadImmediate(R_T0, 0);
		
		instructions.push_back(loadStackSize);
		instructions.push_back(new BinOp("sub", R_SP, R_SP, R_T0));
		instructions.push_back(new StoreWord(R_RA, R_SP, 0));
		instructions.push_back(new StoreWord(R_A0, R_SP, 4));
		
		stackSize = 8; //return address is 4 bytes, $a0 is 4 bytes
		
		elem.getBody().accept(*this);
		
		popScope();
		
		loadStackSize->setValue(stackSize);
		instructions.push_back(new Label(elem.getName() + "_end"));
		instructions.push_back(new LoadWord(R_RA, R_SP, 0));
		instructions.push_back(new BinOpImmediate("addi", R_SP, R_SP, stackSize));
		instructions.push_back(new JumpRegister(R_RA));
	}
	
	void Translator::visit(const StructPredeclaration& elem) {
		getScope()[elem.getName()] = &elem;
	}
	
	void Translator::visit(const StructMember& elem) {
		stackPointerOffsets[&elem] = stackSize;
		stackSize += elem.getType().getSize(getScope());
	}
	
	void Translator::visit(const StructDeclaration& elem) {
		getScope()[elem.getName()] = &elem;
		int stackSizeBackup = stackSize;
		stackSize = 0;
		for_each(elem.getMembers().begin(), elem.getMembers().end(), [this](const StructMember* sm){ sm->accept(*this); });
		stackSize = stackSizeBackup;
	}
	
	/**
	 * Adds a variable with no initial value that is not an array to the scope,
	 * and allocates some stack space for it.
	 */
	void Translator::visit(const VarDeclaration& elem) {
		getScope()[elem.getName()] = &elem;
		stackPointerOffsets[&elem] = stackSize;
		stackSize += elem.getType().getSize(getScope());
	}
	
	/**
	 * Adds a non-array variable with an initial value to the scope, allocates
	 * some stack space for it, and puts in the MIPS that calculates the initial
	 * value.
	 */
	void Translator::visit(const VarDeclarationInit& elem) {
		getScope()[elem.getName()] = &elem;
		stackPointerOffsets[&elem] = stackSize;
		stackSize += elem.getType().getSize(getScope());
		
		elem.getInitialValue().accept(*this);
		Register result = intermediate[&(elem.getInitialValue())];
		instructions.push_back(new StoreWord(result, R_SP, stackPointerOffsets[&elem]));
		returnRegister(result);
		
	}
	
	/**
	 * Adds an array declaration to the scope, and allocates some stack space for it.
	 */
	void Translator::visit(const ArrayDeclaration& elem) {
		getScope()[elem.getName()] = &elem;
		stackPointerOffsets[&elem] = stackSize;
		stackSize += elem.getType().getWrapped().getSize(getScope()) * elem.getSize();
	}
	
	/**
	 * Pushes a new scope onto the scope stack, and runs all the statements inside the statement block
	 * in the new child scope.
	 */
	void Translator::visit(const StatementBlock& elem) {
		pushScope();
		for_each(elem.getStatements().begin(), elem.getStatements().end(), [this](Statement* s) { 
			s->accept(*this);
			const Expression* maybeExpression = dynamic_cast<const Expression*>(s);
			if(maybeExpression) {
				returnRegister(intermediate[maybeExpression]);
			}
			reclaimRegisters();
		});
		popScope();
	}
	
	/**
	 * Inserts an If statement, which executes by first calculating the condition, and then either
	 * executing or skipping the "then" statement associated with it.
	 */
	void Translator::visit(const IfStatement& elem) {
		string afterLabel = label + "_endif_" + toString(labelIndex);
		labelIndex++;
		
		elem.getCond().accept(*this);
		Register cond = intermediate[&(elem.getCond())];
		instructions.push_back(new BranchOnEqual(cond, R_ZERO, afterLabel));
		returnRegister(cond);
		elem.getThen().accept(*this);
		instructions.push_back(new Label(afterLabel));
		
	}
	
	/**
	 * Inserts an If-Else statement, which executes by first calculating the condition, and then
	 * executing either the "then" statement or the "else" statement associated with it.
	 */
	void Translator::visit(const IfElseStatement& elem) {
		string elseLabel = label + "_else_" + toString(labelIndex);
		string afterLabel = label + "_endifelse_" + toString(labelIndex);
		labelIndex++;
		
		elem.getCond().accept(*this);
		Register cond = intermediate[&(elem.getCond())];
		instructions.push_back(new BranchOnEqual(cond, R_ZERO, elseLabel));
		returnRegister(cond);
		elem.getThen().accept(*this);
		instructions.push_back(new Jump(afterLabel));
		instructions.push_back(new Label(elseLabel));
		elem.getElse().accept(*this);
		instructions.push_back(new Label(afterLabel));
	}
	
	/**
	 * Inserts a While statement, which executes by running a loop that calculates the condition
	 * and then runs the loop statement, until the condition evaluates to false, at which point
	 * the loop terminates and the program continues past the loop.
	 */
	void Translator::visit(const WhileStatement& elem) {
		string condLabel = label + "_while_cond_" + toString(labelIndex);
		string endLabel = label + "_while_end_" + toString(labelIndex);
		labelIndex++;
		
		string continueBackup = currentLoopContinueLabel;
		string breakBackup = currentLoopBreakLabel;
		
		currentLoopContinueLabel = condLabel;
		currentLoopBreakLabel = endLabel;
		
		instructions.push_back(new Label(condLabel));
		elem.getCond().accept(*this);
		Register cond = intermediate[&(elem.getCond())];
		instructions.push_back(new BranchOnEqual(cond, R_ZERO, endLabel));
		returnRegister(cond);
		elem.getLoop().accept(*this);
		instructions.push_back(new Jump(condLabel));
		instructions.push_back(new Label(endLabel));
		
		currentLoopContinueLabel = continueBackup;
		currentLoopBreakLabel = breakBackup;
	}
	
	/**
	 * Inserts a Do-While statement, which runs a loop that executes the loop statement and then
	 * executes the condition, until the condition is false, at which point it continues execution
	 * of the rest of the program.
	 */
	void Translator::visit(const DoWhileStatement& elem) {
		string beginLabel = label + "_dowhile_begin_" + toString(labelIndex);
		string condLabel = label + "_dowhile_cond_" + toString(labelIndex);
		string endLabel = label + "_dowhile_end_" + toString(labelIndex);
		labelIndex++;
		
		string continueBackup = currentLoopContinueLabel;
		string breakBackup = currentLoopBreakLabel;
		
		currentLoopContinueLabel = condLabel;
		currentLoopBreakLabel = endLabel;
		
		instructions.push_back(new Label(beginLabel));
		elem.getLoop().accept(*this);
		elem.getCond().accept(*this);
		instructions.push_back(new Label(condLabel));
		Register cond = intermediate[&(elem.getCond())];
		instructions.push_back(new BranchNotEqual(cond, R_ZERO, beginLabel));
		instructions.push_back(new Label(endLabel));
		returnRegister(cond);
		
		currentLoopContinueLabel = continueBackup;
		currentLoopBreakLabel = breakBackup;
	}
	
	/**
	 * Inserts a For statement, which first runs the initializer expression, then runs a loop
	 * that executes the conditional expression, the loop statement, and the increment expression.
	 * When the conditional expression evaluates to false, the loop statement and increment expression
	 * are skipped and the program continues execution past the loop statement.
	 */
	void Translator::visit(const ForStatement& elem) {
		string condLabel = label + "_for_cond_" + toString(labelIndex);
		string incrLabel = label + "_for_incr_" + toString(labelIndex);
		string endLabel = label + "_for_end_" + toString(labelIndex);
		labelIndex++;
		
		string continueBackup = currentLoopContinueLabel;
		string breakBackup = currentLoopBreakLabel;
		
		currentLoopContinueLabel = incrLabel;
		currentLoopBreakLabel = endLabel;
		
		elem.getInit().accept(*this);
		returnRegister(intermediate[&(elem.getInit())]);
		instructions.push_back(new Label(condLabel));
		elem.getCond().accept(*this);
		Register cond = intermediate[&(elem.getCond())];
		instructions.push_back(new BranchOnEqual(cond, R_ZERO, endLabel));
		returnRegister(cond);
		elem.getLoop().accept(*this);
		instructions.push_back(new Label(incrLabel));
		elem.getIncr().accept(*this);
		returnRegister(intermediate[&(elem.getIncr())]);
		instructions.push_back(new Jump(condLabel));
		instructions.push_back(new Label(endLabel));
		
		currentLoopContinueLabel = continueBackup;
		currentLoopBreakLabel = breakBackup;
	}
	
	/**
	 * Breaks out of the current loop, and immediately continues execution
	 * past the loop statement.
	 */
	void Translator::visit(const BreakStatement& elem) {
		if(currentLoopBreakLabel == "") {
			throw runtime_error("Nothing to break out of.");
		}
		instructions.push_back(new Jump(currentLoopBreakLabel));
	}
	
	/**
	 * Skips the rest of the current loop statement. If it is a for loop, this will
	 * run the increment expression.
	 */
	void Translator::visit(const ContinueStatement& elem) {
		if(currentLoopContinueLabel == "") {
			throw runtime_error("No loop to continue.");
		}
		instructions.push_back(new Jump(currentLoopContinueLabel));
	}
	
	void Translator::visit(const SwitchStatement& elem) {
		throw runtime_error("Switch statements are not implemented.");
	}
	
	void Translator::visit(const CaseStatement& elem) {
		throw runtime_error("Case statements are not implemented.");
	}
	
	void Translator::visit(const DefaultStatement& elem) {
		throw runtime_error("Default statements are not implemented.");
	}
	
	/**
	 * Breaks out of the current function, and stores the return value in the $v0 register
	 * for use by the calling function.
	 */
	void Translator::visit(const ReturnStatement& elem) {
		elem.getRet().accept(*this);
		Register ret = intermediate[&(elem.getRet())];
		instructions.push_back(new BinOp("add", R_V0, ret, R_ZERO));
		returnRegister(ret);
		instructions.push_back(new Jump(label + "_end"));
	}
	
	
	/**
	 * Calculates the value that it it will assign, and then the address of what it is assigning to.
	 * It then writes the calculated value to that address and returns the value through the intermediate
	 * map.
	 */
	void Translator::visit(const AssignExpression& elem) {
		elem.getValue().accept(*this);
		Register value = intermediate[&(elem.getValue())];
		Register address;
		const StructType* maybeStructType = dynamic_cast<const StructType*>(&(elem.getType(getScope())));
		
		const VarExpression* maybeVar = dynamic_cast<const VarExpression*>(&(elem.getAssignTo()));
		const ArraySubscriptExpression* maybeArraySub = dynamic_cast<const ArraySubscriptExpression*>(&(elem.getAssignTo()));
		const StructMemberExpression* maybeStructMember = dynamic_cast<const StructMemberExpression*>(&(elem.getAssignTo()));
		if(maybeVar) {
			address = getVarAddress(*maybeVar);
		} else if(maybeArraySub) {
			address = getArraySubscriptAddress(*maybeArraySub);
		} else if(maybeStructMember) {
			address = getStructMemberAddress(*maybeStructMember);
		} else {
			throw runtime_error("Attempting to assign to an unknown sort of expression.");
		}
		
		if(maybeStructType) {
			Register transfer = getFreeRegister();
			for(int i = 0; i < maybeStructType->getSize(getScope()) / 4; i++) {
				instructions.push_back(new LoadWord(transfer, value, 4 * i));
				instructions.push_back(new StoreWord(transfer, address, 4 * i));
			}
			returnRegister(transfer);
		} else {
			instructions.push_back(new StoreWord(value, address, 0));
		}
		returnRegister(address);
		intermediate[&elem] = value;
		return;
	}
	
	/**
	 * Calculates the address of what it is assigning to, then loads that into memory. If it is incrementing
	 * a pointer, it increments it by the size (in bytes) of the object that is being pointed to. Based on whether
	 * the operator is a prefix or a suffix, it returns either the new value or the old value that was stored.
	 */
	void Translator::visit(const UnaryAssignExpression& elem) {
		Register address;
		const VarExpression* maybeVar = dynamic_cast<const VarExpression*>(&(elem.getExpr()));
		if(maybeVar) {
			address = getVarAddress(*maybeVar);
		}
		const ArraySubscriptExpression* maybeArraySub = dynamic_cast<const ArraySubscriptExpression*>(&(elem.getExpr()));
		if(maybeArraySub) {
			address = getArraySubscriptAddress(*maybeArraySub);
		}
		const StructMemberExpression* maybeStructMember = dynamic_cast<const StructMemberExpression*>(&(elem.getExpr()));
		if(maybeStructMember) {
			address = getStructMemberAddress(*maybeStructMember);
		}
		if(!(maybeVar || maybeArraySub || maybeStructMember)) {
			throw runtime_error("Attempting to assign to an unknown sort of expression.");
		}
		
		Register before = getFreeRegister();
		instructions.push_back(new LoadWord(before, address, 0));
		
		Register after = getFreeRegister();
		const Type& type = elem.getType(getScope());
		const IntType* maybeInt = dynamic_cast<const IntType*>(&type);
		if(maybeInt) {
			instructions.push_back(new LoadImmediate(after, 1));
		}
		const StringType* maybeString = dynamic_cast<const StringType*>(&type);
		if(maybeString) {
			instructions.push_back(new LoadImmediate(after, 1));
		}
		const PointerType* maybePointer = dynamic_cast<const PointerType*>(&type);
		if(maybePointer) {
			instructions.push_back(new LoadImmediate(after, maybePointer->getWrapped().getSize(getScope())));
		}
		if(elem.getOp() == "++") {
			instructions.push_back(new BinOp("add", after, before, after));
		} else if(elem.getOp() == "--") {
			instructions.push_back(new BinOp("sub", after, before, after));
		} else {
			throw runtime_error("Unexpected type of unary assign expression: " + elem.getOp());
		}
		instructions.push_back(new StoreWord(after, address, 0));
		returnRegister(address);
		if(elem.isSuffix()) {
			returnRegister(after);
			intermediate[&elem] = before;
		} else {
			returnRegister(before);
			intermediate[&elem] = after;
		}
	}
	
	/**
	 * Handles the unary operators -, ~, !, and & (the * operator is converted by the parser to an array subscript of zero).
	 * -, ~, and ! are more or less straightforward operations, while & calculatest the address and returns it.
	 */
	void Translator::visit(const UnaryOperatorExpression& elem) {
		if(elem.getOp() == "-") {
			elem.getExpr().accept(*this);
			Register ret = intermediate[&(elem.getExpr())];
			instructions.push_back(new BinOp("sub", ret, R_ZERO, ret));
			intermediate[&elem] = ret;
		} else if(elem.getOp() == "~") {
			elem.getExpr().accept(*this);
			Register ret = intermediate[&(elem.getExpr())];
			instructions.push_back(new BinOp("nor", ret, R_ZERO, ret));
			intermediate[&elem] = ret;
		} else if(elem.getOp() == "!") {
			elem.getExpr().accept(*this);
			Register ret = intermediate[&(elem.getExpr())];
			Register snd = getFreeRegister();
			instructions.push_back(new BinOp("slt", snd, R_ZERO, ret));
			instructions.push_back(new BinOp("slt", ret, ret, R_ZERO));
			instructions.push_back(new BinOp("nor", ret, ret, snd));
			instructions.push_back(new LoadImmediate(snd, 1));
			instructions.push_back(new BinOp("and", ret, ret, snd));
			returnRegister(snd);
			intermediate[&elem] = ret;
		} else if(elem.getOp() == "&") {
			const VarExpression* maybeVar = dynamic_cast<const VarExpression*>(&(elem.getExpr()));
			if(maybeVar) {
				Register address = getVarAddress(*maybeVar);
				intermediate[&elem] = address;
				return;
			}
			const ArraySubscriptExpression* maybeArraySub = dynamic_cast<const ArraySubscriptExpression*>(&(elem.getExpr()));
			if(maybeArraySub) {
				Register address = getArraySubscriptAddress(*maybeArraySub);
				intermediate[&elem] = address;
				return;
			}
			throw runtime_error("Attempting to take the address of an unknown sort of expression.");
		} else {
			throw runtime_error("Unary operator " + elem.getOp() + " not implemented.");
		}
	}
	
	/**
	 * Handles all of the binary operators. Operators such as += are converted by the parser into combinations
	 * of assignment and binary operators. + and - take into account if the type is a pointer, and multiply the
	 * non-pointer value by the size of the type being pointed to.
	 */
	void Translator::visit(const BinaryOperatorExpression& elem) {
		Register left;
		Register right;
		
		elem.getLeft().accept(*this);
		left = intermediate[&(elem.getLeft())];
			
		if(elem.getOp() != "&&" && elem.getOp() != "||") {
			elem.getRight().accept(*this);
			right = intermediate[&(elem.getRight())];
		}
		Register ret = getFreeRegister();
		
		map<string, string> substitutions;
		substitutions["*"] = "mul";
		substitutions["/"] = "div";
		substitutions["%"] = "rem";
		substitutions["&"] = "and";
		substitutions["|"] = "or";
		substitutions["<"] = "slt";
		substitutions["^"] = "xor";
		substitutions["<<"] = "sllv";
		substitutions[">>"] = "srlv";
		if(substitutions.count(elem.getOp())) {
			instructions.push_back(new BinOp(substitutions[elem.getOp()], ret, left, right));
		} else if(elem.getOp() == "+" || elem.getOp() == "-") {
			const PointerType* leftPtrType = dynamic_cast<const PointerType*>(&(elem.getLeft().getType(getScope())));
			const PointerType* rightPtrType = dynamic_cast<const PointerType*>(&(elem.getRight().getType(getScope())));
			if(leftPtrType || rightPtrType) {
				Register size = getFreeRegister();
				instructions.push_back(new LoadImmediate(size, (leftPtrType ? leftPtrType : rightPtrType)->getWrapped().getSize(getScope())));
				Register side = leftPtrType ? right : left;
				instructions.push_back(new BinOp("mul", side, side, size));
				returnRegister(size);
			}
			instructions.push_back(new BinOp(elem.getOp() == "+" ? "add" : "sub", ret, left, right));
		} else if(elem.getOp() == ">") {
			instructions.push_back(new BinOp("slt", ret, right, left));
		} else if(elem.getOp() == "==") {
			instructions.push_back(new BinOp("sub", ret, right, left));
			instructions.push_back(new BinOp("slt", right, ret, R_ZERO));
			instructions.push_back(new BinOp("slt", left, R_ZERO, ret));
			instructions.push_back(new BinOp("nor", ret, left, right));
			instructions.push_back(new LoadImmediate(left, 1));
			instructions.push_back(new BinOp("and", ret, ret, left));
		} else if(elem.getOp() == "!=") {
			instructions.push_back(new BinOp("sub", ret, right, left));
			instructions.push_back(new BinOp("slt", right, ret, R_ZERO));
			instructions.push_back(new BinOp("slt", left, R_ZERO, ret));
			instructions.push_back(new BinOp("xor", ret, left, right));
		} else if(elem.getOp() == "<=") {
			instructions.push_back(new BinOpImmediate("addi", right, right, 1));
			instructions.push_back(new BinOp("slt", ret, left, right));
		} else if(elem.getOp() == ">=") {
			instructions.push_back(new BinOpImmediate("addi", left, left, 1));
			instructions.push_back(new BinOp("slt", ret, right, left));
		} else if(elem.getOp() == "&&" || elem.getOp() == "||") {
			string shortcircuitLabel = label + "_shortcircuit_" + toString(labelIndex);
			labelIndex++;
			
			instructions.push_back(new BinOp("add", ret, left, R_ZERO));
			if(elem.getOp() == "&&") {
				instructions.push_back(new BranchOnEqual(left, R_ZERO, shortcircuitLabel));
			} else if(elem.getOp() == "||") {
				instructions.push_back(new BranchNotEqual(left, R_ZERO, shortcircuitLabel));
			} else {
				throw runtime_error("Should not have reached this condition, operator should be && or ||.");
			}
			elem.getRight().accept(*this);
			right = intermediate[&(elem.getRight())];
			instructions.push_back(new BinOp("add", ret, right, R_ZERO));
			instructions.push_back(new Label(shortcircuitLabel));
			instructions.push_back(new BinOp("slt", right, ret, R_ZERO));
			instructions.push_back(new BinOp("slt", left, R_ZERO, ret));
			instructions.push_back(new BinOp("xor", ret, left, right));
		} else {
			throw runtime_error("Operator " + elem.getOp() + " not implemented yet.");
		}
		returnRegister(left);
		returnRegister(right);
		intermediate[&elem] = ret;
	}
	
	/**
	 * Calculates the address of a named variable, which can be either be tied to a
	 * local declaration or a global declaration.
	 */
	Register Translator::getVarAddress(const VarExpression& elem) {
		if(getScope().count(elem.getName()) == 0) {
			throw runtime_error("No variable with name " + elem.getName() + " exists in this scope.");
		}
		const Declaration* decl = getScope()[elem.getName()];
		const VarDeclaration* maybeVar = dynamic_cast<const VarDeclaration*>(decl);
		if(maybeVar) {
			Register result = getFreeRegister();
			instructions.push_back(new BinOpImmediate("addi", result, R_SP, stackPointerOffsets[decl]));
			return result;
		}
		const ArrayDeclaration* maybeArray = dynamic_cast<const ArrayDeclaration*>(decl);
		if(maybeArray) {
			Register result = getFreeRegister();
			instructions.push_back(new BinOpImmediate("addi", result, R_SP, stackPointerOffsets[decl]));
			return result;
		}
		const VarDeclarationInit* maybeInit = dynamic_cast<const VarDeclarationInit*>(decl);
		if(maybeInit) {
			Register result = getFreeRegister();
			instructions.push_back(new BinOpImmediate("addi", result, R_SP, stackPointerOffsets[decl]));
			return result;
		}
		const FunctionParameter* maybeParam = dynamic_cast<const FunctionParameter*>(decl);
		if(maybeParam) {
			Register result = getFreeRegister();
			instructions.push_back(new BinOpImmediate("addi", result, R_A0, stackPointerOffsets[decl]));
			return result;
		}
		const GlobalVarDeclaration* maybeGlobal = dynamic_cast<const GlobalVarDeclaration*>(decl);
		if(maybeGlobal) {
			Register result = getFreeRegister();
			instructions.push_back(new LoadAddress(result, "global_" + maybeGlobal->getName()));
			return result;
		}
		const GlobalVarDeclarationInit* maybeGlobalInit = dynamic_cast<const GlobalVarDeclarationInit*>(decl);
		if(maybeGlobalInit) {
			Register result = getFreeRegister();
			instructions.push_back(new LoadAddress(result, "global_" + maybeGlobalInit->getName()));
			return result;
		}
		const GlobalArrayDeclaration* maybeGlobalArray = dynamic_cast<const GlobalArrayDeclaration*>(decl);
		if(maybeGlobalArray) {
			Register result = getFreeRegister();
			instructions.push_back(new LoadAddress(result, "global_" + maybeGlobalArray->getName()));
			return result;
		}
		throw runtime_error("Unknown type of variable declaration for VarExpression " + elem.getName());
	}
	
	/**
	 * Finds the address of a named variable, then retrieves its value from memory, and puts it in a register.
	 */
	void Translator::visit(const VarExpression& elem) {
		Register address = getVarAddress(elem);
		const Declaration* decl = getScope()[elem.getName()];
		if(!(dynamic_cast<const StructType*>(&(elem.getType(getScope()))) ||
			dynamic_cast<const GlobalArrayDeclaration*>(decl) || 
			dynamic_cast<const ArrayDeclaration*>(decl))) {
			
			const GlobalVarDeclaration* maybeGlobalVar = dynamic_cast<const GlobalVarDeclaration*>(decl);
			const GlobalVarDeclarationInit* maybeGlobalVarInit = dynamic_cast<const GlobalVarDeclarationInit*>(decl);
			if(!((maybeGlobalVar && maybeGlobalVar->getType() == StringType()) ||
				(maybeGlobalVarInit && maybeGlobalVarInit->getType() == StringType()))) {
				
				instructions.push_back(new LoadWord(address, address, 0));
			}
		}
		intermediate[&elem] = address;
	}
	
	Register Translator::getStructMemberAddress(const StructMemberExpression& elem) {
		elem.getStruct().accept(*this);
		Register address = intermediate[&(elem.getStruct())];
		const PointerType* ptype = dynamic_cast<const PointerType*>(&(elem.getStruct().getType(getScope())));
		const StructType& structureType = ptype ? dynamic_cast<const StructType&>(ptype->getWrapped()) : dynamic_cast<const StructType&>(elem.getStruct().getType(getScope()));
		const StructDeclaration* structureDeclaration = dynamic_cast<const StructDeclaration*>(getScope()[structureType.getName()]);
		StructMember* member = NULL;
		for(auto it = structureDeclaration->getMembers().begin(); it != structureDeclaration->getMembers().end(); it++) {
			if((*it)->getName() == elem.getMemberName()) {
				member = *it;
				break;
			}
		}
		if(member == NULL) {
			throw runtime_error("No such member in the struct.");
		}
		instructions.push_back(new BinOpImmediate("addi", address, address, stackPointerOffsets[member]));
		return address;
	}
	
	void Translator::visit(const StructMemberExpression& elem) {
		Register address = getStructMemberAddress(elem);
		if(!dynamic_cast<const StructType*>(&(elem.getType(getScope())))) {
			instructions.push_back(new LoadWord(address, address, 0));
		}
		intermediate[&elem] = address;
	}
	
	/**
	 * Retrieves the address of a particular index in an array, and puts it in a register.
	 */
	Register Translator::getArraySubscriptAddress(const ArraySubscriptExpression& elem) {
		elem.getSubscript().accept(*this);
		Register subReg = intermediate[&(elem.getSubscript())];
		Register arrElemSize = getFreeRegister();
		const PointerType* p = dynamic_cast<const PointerType*>(&(elem.getArray().getType(getScope())));
		if(!p) {
			throw runtime_error("Type of the Array expression is not a pointer type.");
		}
		instructions.push_back(new LoadImmediate(arrElemSize, p->getWrapped().getSize(getScope())));
		instructions.push_back(new BinOp("mul", subReg, subReg, arrElemSize));
		returnRegister(arrElemSize);
		elem.getArray().accept(*this);
		Register arrReg = intermediate[&(elem.getArray())];
		instructions.push_back(new BinOp("add", arrReg, arrReg, subReg));
		returnRegister(subReg);
		return arrReg;
	}
	
	/**
	 * Retrieves the address of the index of an array, and then loads the value stored in it into a register.
	 */
	void Translator::visit(const ArraySubscriptExpression& elem) {
		Register result = getArraySubscriptAddress(elem);
		const Type& wrapped = dynamic_cast<const PointerType&>(elem.getArray().getType(getScope())).getWrapped();
		if(!dynamic_cast<const StructType*>(&wrapped)) {
			instructions.push_back(new LoadWord(result, result, 0));
		}
		intermediate[&elem] = result;
	}
	
	/**
	 * Calls a function.
	 * 
	 * This allocates space on the stack to store both the registers that are currently in use and the function
	 * parameters. The address to the function parameters is passed into the called function using the $a0 register,
	 * and the parameters are all offset from that. After the function returns, the registers currently in use are 
	 * restored to their values prior to the function call. The stack is then also restored to what it was prior to
	 * making the function call (releasing the space used by the parameters and the stored registers, as the called
	 * function will clean up its own stack space), and the return value is moved from $v0 to another register and
	 * returned to avoid being overwritten by a following function call.
	 */
	void Translator::visit(const FunctionCallExpression& elem) {
		if(getScope().count(elem.getFunction()) == 0) {
			throw runtime_error("No declaration by that name.");
		}
		const Declaration* d = getScope()[elem.getFunction()];
		const FunctionDeclaration* maybeDeclaration = dynamic_cast<const FunctionDeclaration*>(d);
		const FunctionPrototype* maybePrototype = dynamic_cast<const FunctionPrototype*>(d);
		if(!(maybeDeclaration || maybePrototype)) {
			throw runtime_error("Declaration at " + elem.getFunction() + " is not a function prototype or declaration.");
		}
		const vector<FunctionParameter*>& params = maybeDeclaration ? maybeDeclaration->getParameters() : maybePrototype->getParameters();
		const vector<Expression*>& args = elem.getArguments();
		if(params.size() != args.size()) {
			throw runtime_error("Function call does not have the same number of arguments as the function itself.");
		}
		
		int oldStackOffset = stackSize;
		for(size_t i = 0; i < params.size(); i++) {
			stackSize += params[i]->getType().getSize(getScope());
		}
		
		int paramOffset = oldStackOffset;
		for(size_t i = 0; i < args.size(); i++) {
			args[i]->accept(*this);
			Register argValue = intermediate[args[i]];
			
			const StructType* maybeStructType = dynamic_cast<const StructType*>(&(params[i]->getType()));
			if(maybeStructType) {
				Register transfer = getFreeRegister();
				for(int i = 0; i < maybeStructType->getSize(getScope()); i++) {
					instructions.push_back(new LoadWord(transfer, argValue, i * 4));
					instructions.push_back(new StoreWord(transfer, R_SP, paramOffset + i * 4));
				}
				returnRegister(transfer);
			} else {
				instructions.push_back(new StoreWord(argValue, R_SP, paramOffset));
			}
			
			paramOffset += params[i]->getType().getSize(getScope());
			returnRegister(argValue);
		}
		
		instructions.push_back(new BinOpImmediate("addi", R_A0, R_SP, oldStackOffset));
		
		int regOffset = 0;
		if(registersInUse.size() > 0) {
			
			for(auto it = registersInUse.begin(); it != registersInUse.end(); it++) {
				regOffset -= 4;
				instructions.push_back(new StoreWord(*it, R_SP, regOffset));
			}
			instructions.push_back(new BinOpImmediate("addi", R_SP, R_SP, regOffset));
		}
		
		instructions.push_back(new JumpAndLink(elem.getFunction()));
		
		if(registersInUse.size() > 0) {
			instructions.push_back(new BinOpImmediate("addi", R_SP, R_SP, -regOffset));
			regOffset = 0;
			for(auto it = registersInUse.begin(); it != registersInUse.end(); it++) {
				regOffset -= 4;
				instructions.push_back(new LoadWord(*it, R_SP, regOffset));
			}
		}
		
		
		Register ret = getFreeRegister();
		instructions.push_back(new BinOp("add", ret, R_V0, R_ZERO));
		instructions.push_back(new LoadWord(R_A0, R_SP, 4));
		intermediate[&elem] = ret;
	}
	
	/**
	 * The sizes of types are known at compile time, so this simply loads the size of a type into
	 * a register to be used.
	 */
	void Translator::visit(const SizeofExpression& elem) {
		Register result = getFreeRegister();
		instructions.push_back(new LoadImmediate(result, elem.getSizeofType().getSize(getScope())));
		intermediate[&elem] = result;
	}
	
	/**
	 * Loads a constant integer into a register.
	 */
	void Translator::visit(const IntConstantExpression& elem) {
		Register result = getFreeRegister();
		instructions.push_back(new LoadImmediate(result, elem.getValue()));
		intermediate[&elem] = result;
	}
	
	/**
	 * Allocates global space for a string constant, and puts a pointer to it in a register.
	 */
	void Translator::visit(const StringConstantExpression& elem) {
		string newValue = escapeString(elem.getValue());
		string strLabel = label + "_strconst_" + toString(labelIndex);
		instructions.push_back(new StringGlobal(strLabel, newValue));
		Register ret = getFreeRegister();
		instructions.push_back(new LoadAddress(ret, strLabel));
		intermediate[&elem] = ret;
		
		labelIndex++;
	}

	
}