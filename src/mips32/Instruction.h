#ifndef MIPS32_INSTRUCTION_H
#define MIPS32_INSTRUCTION_H

#include <iostream>
#include <string>

namespace mips32 {
	
	typedef unsigned short Register;
	
	extern const Register R_ZERO;
	
	extern const Register R_AT;
	
	extern const Register R_V0;
	extern const Register R_V1;
	
	extern const Register R_A0;
	extern const Register R_A1;
	extern const Register R_A2;
	extern const Register R_A3;
	
	extern const Register R_T0;
	extern const Register R_T1;
	extern const Register R_T2;
	extern const Register R_T3;
	extern const Register R_T4;
	extern const Register R_T5;
	extern const Register R_T6;
	extern const Register R_T7;
	
	extern const Register R_S0;
	extern const Register R_S1;
	extern const Register R_S2;
	extern const Register R_S3;
	extern const Register R_S4;
	extern const Register R_S5;
	extern const Register R_S6;
	extern const Register R_S7;
	
	extern const Register R_T8;
	extern const Register R_T9;
	
	extern const Register R_K0;
	extern const Register R_K1;
	
	extern const Register R_GP;
	
	extern const Register R_SP;
	
	extern const Register R_S8;
	
	extern const Register R_RA;
	
	std::string registerStr(Register r);
	
	class Instruction;
	
	std::ostream &operator<<(std::ostream& output, const Instruction&);
	
	/**
	 * Superclass of all MIPS instructions. Globals and labels are included under
	 * this, for simplicity.
	 */
	class Instruction {
	private:
		
	public:
		Instruction();
		Instruction(const Instruction&) = delete;
		virtual ~Instruction();
		virtual const Instruction& operator=(const Instruction&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const = 0;
		virtual bool readsRegister(Register) const = 0;
		virtual bool writesToRegister() const = 0;
		virtual Register destinationRegister() const = 0;
	};
	
	class ControlFlowInstruction : public Instruction {
	public:
		ControlFlowInstruction();
		ControlFlowInstruction(const ControlFlowInstruction&) = delete;
		virtual ~ControlFlowInstruction();
		virtual const ControlFlowInstruction& operator=(const ControlFlowInstruction&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const = 0;
		virtual bool readsRegister(Register) const = 0;
		virtual bool writesToRegister() const = 0;
		virtual Register destinationRegister() const = 0;
	};
	
	/**
	 * Represents a label. This isn't executed directly, but is used for the assembler
	 * to figure out the jump offsets necessary for the jump and branch instructions.
	 */
	class Label : public ControlFlowInstruction {
	private:
		std::string name;
	public:
		Label(const std::string& name);
		Label(const Label&) = delete;
		virtual ~Label();
		virtual const Label& operator=(const Label&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual const std::string& getName() const;
	};
	
	/**
	 * Instruction to perform an unconditional jump to a specific place in memory.
	 * This takes in a string for which label it is a jump to.
	 */
	class Jump : public ControlFlowInstruction {
	private:
		std::string target;
	public:
		Jump(const std::string& target);
		Jump(const Jump&) = delete;
		virtual ~Jump();
		virtual const Jump& operator=(const Jump&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual const std::string& getTarget() const;
	};
	
	/**
	 * Instruction to perform an unconditional jump to a location taken from
	 * a register. This takes in the target location register.
	 */
	class JumpRegister : public ControlFlowInstruction {
	private:
		Register target;
	public:
		JumpRegister(Register target);
		JumpRegister(const JumpRegister&) = delete;
		virtual ~JumpRegister();
		virtual const JumpRegister& operator=(const JumpRegister&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual Register getTarget() const;
	};
	
	/**
	 * Instruction to perform an unconditional jump to the label with the target
	 * string. This also loads the current instruction address into the $ra register,
	 * so that it can be jumped back to at a later point.
	 */
	class JumpAndLink : public ControlFlowInstruction {
	private:
		std::string target;
	public:
		JumpAndLink(const std::string& target);
		JumpAndLink(const JumpAndLink&) = delete;
		virtual ~JumpAndLink();
		virtual const JumpAndLink& operator=(const JumpAndLink&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual const std::string& getTarget() const;
	};
	
	/**
	 * Instruction that takes two registers and a target to jump to. It will
	 * jump to the target label if the left and right registers are equal, and
	 * will not jump if the two registers are not equal.
	 */
	class BranchOnEqual : public ControlFlowInstruction {
	private:
		Register left;
		Register right;
		std::string target;
	public:
		BranchOnEqual(Register left, Register right, const std::string& target);
		BranchOnEqual(const BranchOnEqual&) = delete;
		virtual ~BranchOnEqual();
		virtual const BranchOnEqual& operator=(const BranchOnEqual&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual Register getLeft() const;
		virtual Register getRight() const;
		virtual const std::string& getTarget() const;
	};
	
	/**
	 * Instruction that takes two registers and a target to jump to. It will
	 * jump to the target label if the left and right registers are not equal, and
	 * will not jump if the two registers are equal.
	 */
	class BranchNotEqual : public ControlFlowInstruction {
	private:
		Register left;
		Register right;
		std::string target;
	public:
		BranchNotEqual(Register left, Register right, const std::string& target);
		BranchNotEqual(const BranchNotEqual&) = delete;
		virtual ~BranchNotEqual();
		virtual const BranchNotEqual& operator=(const BranchNotEqual&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual Register getLeft() const;
		virtual Register getRight() const;
		virtual const std::string& getTarget() const;
	};
	
	/**
	 * Instruction to store a 32-bit word to a specific location at memory. It takes in
	 * the register containing the data to store, the register containing the location in
	 * memory, and an offset for where to store it relative to the location register. The offset
	 * must be known at compile-time, and is specified as an integer. If the sum of the offset and the
	 * location register is not a multiple of 4, the MIPS processor/emulator will throw an exception
	 * at runtime.
	 */
	class StoreWord : public Instruction {
	private:
		Register data;
		Register location;
		int offset;
	public:
		StoreWord(Register data, Register location, int offset);
		StoreWord(const StoreWord&) = delete;
		virtual ~StoreWord();
		virtual const StoreWord& operator=(const StoreWord&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual Register getData() const;
		virtual Register getLocation() const;
		virtual int getOffset() const;
	};
	
	/**
	 * Instruction to load a 32-bit word into a register from a specific location in memory.
	 * It takes in the register to store the data in, the register containing the location in memory,
	 * and an offset for where to read the memory from relative to the location register. The offset
	 * must be known at compile-time, and is specified as an integer. If the sum of the offset and the
	 * location register is not a multiple of 4, the MIPS processor/emulator will throw an exception
	 * at runtime.
	 */
	class LoadWord : public Instruction {
	private:
		Register data;
		Register location;
		int offset;
	public:
		LoadWord(Register data, Register location, int offset);
		LoadWord(const LoadWord&) = delete;
		virtual ~LoadWord();
		virtual const LoadWord& operator=(const LoadWord&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual Register getData() const;
		virtual Register getLocation() const;
		virtual int getOffset() const;
	};
	
	/**
	 * Psuedoinstruction that the assembler deals with. The instruction takes a register to load the
	 * address into, and a string for a label in the assembly. The assembler will figure out the
	 * actual integer address of the label, and put in an instruction to load that into the register.
	 */
	class LoadAddress : public Instruction {
	private:
		Register data;
		std::string address;
	public:
		LoadAddress(Register data, const std::string& address);
		LoadAddress(const LoadAddress&) = delete;
		virtual ~LoadAddress();
		virtual const LoadAddress& operator=(const LoadAddress&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual Register getData() const;
		virtual const std::string& getAddress() const;
	};
	
	/**
	 * Not technically an instruction. This creates an integer in the data segment with a specific
	 * label attached to it, that can be referred to by LoadAddress.
	 */
	class IntGlobal : public Instruction {
	private:
		std::string name;
		unsigned int value;
	public:
		IntGlobal(const std::string& name, unsigned int value = 0);
		IntGlobal(const IntGlobal&) = delete;
		virtual ~IntGlobal();
		virtual const IntGlobal& operator=(const IntGlobal&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual const std::string& getName() const;
		virtual unsigned int getValue() const;
	};
	
	/**
	 * Not technically an instruction. This creates an array in the data segment with a specific size
	 * (given in bytes). It can be referred to by LoadAddress.
	 */
	class ArrayGlobal : public Instruction {
	private:
		std::string name;
		int size;
	public:
		ArrayGlobal(const std::string& name, int size);
		ArrayGlobal(const ArrayGlobal&) = delete;
		virtual ~ArrayGlobal();
		virtual const ArrayGlobal& operator=(const ArrayGlobal&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual const std::string& getName() const;
		virtual int getSize() const;
	};
	
	/**
	 * Not technically an instruction. This creates a string in the data segment, with a specific value.
	 * It can be referred to by LoadAddress.
	 */
	class StringGlobal : public Instruction {
	private:
		std::string name;
		std::string value;
	public:
		StringGlobal(const std::string& name, const std::string& value);
		StringGlobal(const StringGlobal&) = delete;
		virtual ~StringGlobal();
		virtual const StringGlobal& operator=(const StringGlobal&) = delete;
		
		virtual std::ostream& output(std::ostream& o) const;
		virtual bool readsRegister(Register) const;
		virtual bool writesToRegister() const;
		virtual Register destinationRegister() const;
		
		virtual const std::string& getName() const;
		virtual const std::string& getValue() const;
	};
	
};

#endif