#include "Type.h"
#include "Declaration.h"
#include <map>
#include <string>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::runtime_error;

/**
 * Constructor for Type. The base class does not hold any data.
 */
Type::Type() {
	
}

/**
 * Destructor for Type. The base class does not hold any data.
 */
Type::~Type() {
	
}

/**
 * Constructor for IntType. IntType does not hold any data.
 */
IntType::IntType() {
	
}

/**
 * Destructor for IntType. IntType does not hold any data.
 */
IntType::~IntType() {
	
}

/**
 * Produces a freshly allocated instance of the class. Useful if a generic Type*
 * needs to be copied for some reason.
 */
Type* IntType::clone() const  {
	return new IntType();
}

/**
 * Checks whether the IntType is valid in the current scope. Integer types are always valid.
 */
bool IntType::check(std::map<string, const Declaration*>& scope) const {
	return true;
}

/**
 * This type is equal to any other IntType.
 */
bool IntType::operator==(const Type& t) const {
	return dynamic_cast<const IntType*>(&t) != NULL;
}

int IntType::getSize(map<string, const Declaration*>& scope) const {
	return 4;
}

/**
 * Constructor for StringType. StringType does not hold any data.
 */
StringType::StringType() {
	
}

/**
 * Destructor for StringType. StringType does not hold any data.
 */
StringType::~StringType() {
	
}

/**
 * Produces a freshly allocated instance of the class. Useful if a generic Type*
 * needs to be copied.
 */
Type* StringType::clone() const  {
	return new StringType();
}

/**
 * The StringType is always valid.
 */
bool StringType::check(std::map<string, const Declaration*>& scope) const {
	return true;
}

/**
 * StringTypes are equal to other StringTypes only.
 */
bool StringType::operator==(const Type& t) const {
	return dynamic_cast<const StringType*>(&t) != NULL;
}

int StringType::getSize(map<string, const Declaration*>& scope) const {
	return 4;
}

/**
 * Constructor for VoidType. VoidType does not hold any data.
 */
VoidType::VoidType() {
	
}

/**
 * Destructor for VoidType. VoidTypes does not hold any data.
 */
VoidType::~VoidType() {
	
}

/**
 * Produces a freshly allocated instance of the VoidType. Useful if a generic
 * Type* needs to be allocated.
 */
Type* VoidType::clone() const  {
	return new VoidType();
}

/**
 * VoidTypes are always valid in any scope.
 */
bool VoidType::check(std::map<string, const Declaration*>& scope) const {
	return true;
}

/**
 * The void type is only equal to the void type.
 */
bool VoidType::operator==(const Type& t) const {
	return dynamic_cast<const VoidType*>(&t) != NULL;
}

int VoidType::getSize(map<string, const Declaration*>& scope) const {
	return 4;
}

/**
 * Constructor for StructType. The only data stored is the struct name.
 */
StructType::StructType(const string& name) : name(name) {
	
}

/**
 * Copy constructor for StructType.
 */
StructType::StructType(const StructType& s) : name(s.name) {
	
}

/**
 * Destructor for StructType.
 */
StructType::~StructType() {
	
}

/**
 * Assignment operator for StructType.
 */
const StructType& StructType::operator=(const StructType& s) {
	name = s.name;
	return *this;
}

/**
 * Generic copying function for Types. Produces a freshly allocated
 * StructType.
 */
Type* StructType::clone() const  {
	return new StructType(name);
}

/**
 * Checks whether the StructType is valid. It is onyl valid if there has been
 * a struct declaration; a predeclaration is not good enough. There must also
 * not be anything else that shares the name.
 */
bool StructType::check(std::map<string, const Declaration*>& scope) const {
	if(!scope.count(name)) {
		return false;
	} else {
		if(dynamic_cast<const StructDeclaration*>(scope[name]) == NULL) {
			cout << "No struct by the name " << name << " has been declared." << endl;
			return false;
		} else {
			return true;
		}
	}
}

/**
 * A struct type is equal to any other struct type with the same name.
 */
bool StructType::operator==(const Type& t) const {
	const StructType* structure = dynamic_cast<const StructType*>(&t);
	if(structure == NULL) {
		return false;
	} else {
		return name == structure->name;
	}
}

/**
 * Retrieves the name of the struct type.
 */
const string& StructType::getName() const {
	return name;
}

int StructType::getSize(map<string, const Declaration*>& scope) const {
	if(!scope.count(name)) {
		throw runtime_error("There is no type with this name.");
	} else {
		auto sdecl = dynamic_cast<const StructDeclaration*>(scope[name]);
		if(sdecl == NULL) {
			throw runtime_error("Declaration with the name of the struct type isn't a Struct Declaration.");
		} else {
			int size = 0;
			for(auto it = sdecl->getMembers().begin(); it != sdecl->getMembers().end(); it++) {
				size += (*it)->getType().getSize(scope);
			}
			return size;
		}
	}
	return -1;
}

/**
 * Constructor for PointerType. A pointer type stores the type it is pointing to.
 */
PointerType::PointerType(Type* wrapped) : wrapped(wrapped) {
	
}

/**
 * Copy constructor for PointerType.
 */
PointerType::PointerType(const PointerType& other) : wrapped(other.wrapped->clone()) {
	
}

/**
 * Destructor for PointerType. The pointer type assumes ownership of the type passed into it,
 * so it deletes it when it is destroyed.
 */
PointerType::~PointerType() {
	delete wrapped;
}

/**
 * Assignment operator for PointerType.
 */
const PointerType& PointerType::operator=(const PointerType& p) {
	delete wrapped;
	wrapped = p.wrapped->clone();
	return *this;
}

/**
 * Generic copier for PointerType. Produces a freshly allocated instance
 */
Type* PointerType::clone() const  {
	return new PointerType(wrapped->clone());
}

/**
 * Pointer types are always valid: the type they are pointing to only matters if
 * it is dereferenced, and that is taken care of in the expression type checking.
 */
bool PointerType::check(std::map<string, const Declaration*>& scope) const {
	return true;
}

/**
 * Any two pointer types are equal; C allows free implicit casting between pointer types.
 */
bool PointerType::operator==(const Type& t) const {
	const PointerType* other = dynamic_cast<const PointerType*>(&t);
	return other != NULL;
	/*
	if(other == NULL) {
		return false;
	} else {
		return getWrapped() == other->getWrapped();
	}*/
}

/**
 * Retrieves the wrapped type.
 */
const Type& PointerType::getWrapped() const {
	return *wrapped;
}

int PointerType::getSize(map<string, const Declaration*>& scope) const {
	return 4;
}
