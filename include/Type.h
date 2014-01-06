#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <map>

class Declaration;

/**
 * Base class for all types.
 */
class Type {
public:
	Type();
	virtual ~Type();
	
	virtual Type* clone() const  = 0;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const = 0;
	virtual bool operator==(const Type& other) const = 0;
	virtual int getSize(std::map<std::string, const Declaration*>& scope) const = 0;
};

/**
 * Represents a 32-bit unsigned integer.
 */
class IntType : public Type {
public:
	IntType();
	virtual ~IntType();
	
	virtual Type* clone() const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual bool operator==(const Type& other) const;
	virtual int getSize(std::map<std::string, const Declaration*>& scope) const;
};

/**
 * Represents an abstracted char array. These do not support the same operations
 * as a char*, for simplicity. That way, addressing particular bytes is not an issue
 * that has to be dealt with.
 */
class StringType : public Type {
public:
	StringType();
	virtual ~StringType();
	
	virtual Type* clone() const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual bool operator==(const Type& other) const;
	virtual int getSize(std::map<std::string, const Declaration*>& scope) const;
};

/**
 * Used as a function return type, this indicates the function will not return
 * anything at all. void* tyypes are also used as generic pointers.
 */
class VoidType : public Type {
public:
	VoidType();
	virtual ~VoidType();
	
	virtual Type* clone() const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual bool operator==(const Type& other) const;
	virtual int getSize(std::map<std::string, const Declaration*>& scope) const;
};

/**
 * Used to indicate a struct type. This simply stores the name of the struct, so if the actual members
 * are needed, whoever uses this type will have to see if the scope has a struct definition associated
 * with the name stored in this struct type.
 */
class StructType : public Type {
private:
	std::string name;
public:
	StructType(const std::string& str);
	StructType(const StructType& s);
	virtual ~StructType();
	virtual const StructType& operator=(const StructType& s);
	
	virtual Type* clone() const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual bool operator==(const Type& other) const;
	virtual const std::string& getName() const;
	virtual int getSize(std::map<std::string, const Declaration*>& scope) const;
};

/**
 * Represents a type that is a pointer to another type. C freely allows implicit casting between pointer types,
 * so any two pointer types are considered equal by the == method.
 */
class PointerType : public Type {
private:
	Type* wrapped;
public:
	PointerType(Type* wrapped);
	PointerType(const PointerType& p);
	virtual ~PointerType();
	virtual const PointerType& operator=(const PointerType& p);
	
	virtual Type* clone() const;
	virtual bool check(std::map<std::string, const Declaration*>& scope) const;
	virtual bool operator==(const Type& other) const;
	const Type& getWrapped() const;
	virtual int getSize(std::map<std::string, const Declaration*>& scope) const;
};

#endif