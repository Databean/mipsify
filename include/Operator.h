#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>

class Type;

bool validOp(const Type& left, const std::string& op, const Type& right);
bool validOp(const std::string& op, const Type& apply);

const Type& getOpType(const Type& left, const std::string& op, const Type& right);
const Type& getOpType(const std::string& op, const Type& apply);

#endif