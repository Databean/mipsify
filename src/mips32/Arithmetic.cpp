#include "mips32/Arithmetic.h"
#include <sstream>
#include <iostream>

using std::string;
using std::ostream;
using std::endl;

namespace mips32 {
	
	BinOp::BinOp(const std::string& op, Register dest, Register left, Register right) : op(op), dest(dest), left(left), right(right) {
		
	}
	
	BinOp::~BinOp() {
		
	}
	
	const string& BinOp::getOp() const {
		return op;
	}
	
	Register BinOp::getDest() const {
		return dest;
	}
	
	Register BinOp::getLeft() const {
		return left;
	}
	
	Register BinOp::getRight() const {
		return right;
	}
	
	ostream& BinOp::output(ostream& output) const {
		return output << "\t" << op << " " << registerStr(dest) << ", " << registerStr(left) << ", " << registerStr(right) << endl;
	}
	
	bool BinOp::readsRegister(Register r) const {
		return left == r || right == r;
	}
	
	bool BinOp::writesToRegister() const {
		return true;
	}
	
	Register BinOp::destinationRegister() const {
		return getDest();
	}
	
	BinOpImmediate::BinOpImmediate(const std::string& op, Register dest, Register left, short right) : op(op), dest(dest), left(left), right(right) {
		
	}
	
	BinOpImmediate::~BinOpImmediate() {
		
	}
	
	const string& BinOpImmediate::getOp() const {
		return op;
	}
	
	Register BinOpImmediate::getDest() const {
		return dest;
	}
	
	Register BinOpImmediate::getLeft() const {
		return left;
	}
	
	short BinOpImmediate::getRight() const {
		return right;
	}
	
	ostream& BinOpImmediate::output(ostream& output) const {
		return output << "\t" << op << " " << registerStr(dest) << ", " << registerStr(left) << ", " << right << endl;
	}
	
	bool BinOpImmediate::readsRegister(Register r) const {
		return left == r;
	}
	
	bool BinOpImmediate::writesToRegister() const {
		return true;
	}
	
	Register BinOpImmediate::destinationRegister() const {
		return getDest();
	}
	
	LoadImmediate::LoadImmediate(Register reg, int value) : reg(reg), value(value) {
		
	}
	
	LoadImmediate::~LoadImmediate() {
		
	}
	
	ostream& LoadImmediate::output(ostream& output) const {
		return output << "\tli " << registerStr(reg) << ", " << value << endl;
	}
	
	bool LoadImmediate::readsRegister(Register r) const {
		return false;
	}
	
	void LoadImmediate::setRegister(Register r) {
		reg = r;
	}
	
	void LoadImmediate::setValue(int v) {
		value = v;
	}
	
	Register LoadImmediate::getRegister() const {
		return reg;
	}
	
	int LoadImmediate::getValue() const {
		return value;
	}
	
	bool LoadImmediate::writesToRegister() const {
		return true;
	}
	
	Register LoadImmediate::destinationRegister() const {
		return getRegister();
	}
	
	
}