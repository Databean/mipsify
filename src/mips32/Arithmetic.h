#ifndef MIPS32_ARITHMETIC_H
#define MIPS32_ARITHMETIC_H

#include "mips32/Instruction.h"
#include <string>

namespace mips32 {
	
	/**
	 * Catch-all instruction for the MIPS binary operators. These include "add", "sub",
	 * "mul", "div", "nor", "and", "or", "xor", and so on.
	 * The first parameter of the constructor is the operator, then the destination register,
	 * then the left and right elements to the operator.
	 */
	class BinOp : public Instruction {
	private:
		std::string op;
		Register dest;
		Register left;
		Register right;
	public:
		BinOp(const std::string& op, Register dest, Register left, Register right);
		BinOp(const BinOp&) = delete;
		virtual ~BinOp();
		virtual const BinOp& operator=(const BinOp&) = delete;
		
		virtual std::ostream& output(std::ostream&) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual const std::string& getOp() const;
		virtual Register getDest() const;
		virtual Register getLeft() const;
		virtual Register getRight() const;
	};
	
	/**
	 * Catch-call instruction for the MIPS binary operators that take an immediate value
	 * as the second parameter. These include "addi", "andi", "ori", and so on.
	 * The first parameter of the constructor is the operator, then the destination register,
	 * then the left register, then the immediate as the right side of the operator.
	 */
	class BinOpImmediate : public Instruction {
	private:
		std::string op;
		Register dest;
		Register left;
		short right;
	public:
		BinOpImmediate(const std::string& op, Register dest, Register left, short right);
		BinOpImmediate(const BinOpImmediate&) = delete;
		virtual ~BinOpImmediate();
		virtual const BinOpImmediate& operator=(const BinOpImmediate&) = delete;
		
		virtual std::ostream& output(std::ostream&) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual const std::string& getOp() const;
		virtual Register getDest() const;
		virtual Register getLeft() const;
		virtual short getRight() const;
	};
	
	/**
	 * MIPS instruction to immediately put a 32-bit value into a register.
	 */
	class LoadImmediate : public Instruction {
	private:
		Register reg;
		int value;
	public:
		LoadImmediate(Register reg, int value);
		LoadImmediate(const LoadImmediate&);
		virtual ~LoadImmediate();
		virtual const LoadImmediate& operator=(const LoadImmediate&) = delete;
		
		virtual std::ostream& output(std::ostream&) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual void setRegister(Register);
		virtual void setValue(int);
		
		virtual Register getRegister() const;
		virtual int getValue() const;
	};
	
};

#endif