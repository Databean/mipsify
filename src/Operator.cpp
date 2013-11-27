#include <map>
#include "Type.h"
#include <stdexcept>

using std::string;
using std::runtime_error;
using std::invalid_argument;

IntType intType;
PointerType pointerType(new IntType());

bool validOp(const Type& left, const string& op, const Type& right) {
	if(!(left == intType || left == pointerType)) {
		return false;
	} else if(!(right == intType || right == pointerType)) {
		return false;
	} else {
		if(op == "+" || op == "-") { //Only cases where pointer types can be mixed with int types.
			return left == intType || right == intType;
		} else if(op == "==" || op == "!=") { //Only other binary operator that mixes with pointer types.
			return left == right;
		} else {
			return left == intType && right == intType;
		}
	}
}

bool validOp(const string& op, const Type& apply) {
	if(op == "*") {
		return apply == pointerType;
	} else if(op == "&") {
		return true;
	} else {
		return apply == intType;
	}
}

const Type& getOpType(const Type& left, const string& op, const Type& right) {
	if(!(left == intType || left == pointerType)) {
		throw invalid_argument("getType(left): left is not an int or pointer type.");
	} else if(!(right == intType || right == pointerType)) {
		throw invalid_argument("getType(right): right is not an int or pointer type.");
	} else {
		if(op == "+" || op == "-") { //Only cases where pointer types can be mixed with int types.
			if(!(left == intType || right == intType)) {
				throw invalid_argument("pointer + pointer and pointer - pointer are not valid.");
			} else {
				return left == pointerType ? left : right;
			}
		} else if(op == "==" || op == "!=") { //Only other binary operator that mixes with pointer types.
			if(!(left == right)) {
				throw invalid_argument("cannot do equality or inequality on unequal types.");
			} else {
				return intType;
			}
		} else {
			if(!(left == intType && right == intType)) {
				throw invalid_argument("Binary operators other than + - == != are not valid for non-integers.");
			} else {
				return intType;
			}
		}
	}
}

const Type& getOpType(const string& op, const Type& apply) {
	if(op == "*") {
		if(!(apply == pointerType)) {
			throw invalid_argument("Cannot dereference a non-pointer.");
		} else {
			const PointerType* t = dynamic_cast<const PointerType*>(&apply);
			if(t == NULL) {
				throw runtime_error("Type was equal to a pointer type, but could not cast to it.");
			} else {
				return t->getWrapped();
			}
		}
	} else if(op == "&") {
		///TODO: i know this leaks memory, but I don't have anything
		///in place to deal with something like this.
		return *(new PointerType(apply.clone()));
	} else {
		if(!(apply == intType)) {
			throw invalid_argument("Cannot apply any other unary operators to non-integers.");
		} else {
			return intType;
		}
	}
}
