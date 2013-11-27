#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>

/**
 * Converts a type into a string, assuming it has a std::ostream& operator<<(std::ostream&, ...) method.
 * @param t the object to convert.
 */
template<class T>
std::string toString(T t) {
	std::stringstream s;
	s << t;
	return s.str();
}

/**
 * Compares whether the members of a collection of pointers are equal. It does this by dereferencing
 * corresponding members and using their operator== methods to compoare the elements for equality.
 * @param a The first collection to test.
 * @param b The second collection to test.
 */
template<class T>
bool ptrCollectionEqual(const T& a, const T& b) {
	auto aIt = a.begin();
	auto bIt = b.begin();
	for(; aIt != a.end() && bIt != b.end(); aIt++, bIt++) {
		if(!((**aIt) == (**bIt))) {
			return false;
		}
	}
	return aIt == a.end() && bIt == b.end();
}

/**
 * Throws an exception if the given parameter is null.
 * @param preDesc Additional information to give with the message (such as where it came from)
 * @param ptr Throw an exception if this is null.
 */
template<class T>
void exceptIfNull(const std::string& preDesc, const T* ptr) {
	if(ptr == NULL) {
		throw std::invalid_argument(preDesc + ": is NULL");
	}
}

/**
 * Takes a collection of pointers, and checks whether it has any null members. If one is found,
 * it will throw an exception.
 * @param preDesc Additional information to give with the message (such as where it came from)
 * @param collection The collection to search through for null members.
 */
template<class T>
void exceptIfNullMember(const std::string& preDesc, const T& collection) {
	int index = 0;
	for(auto it = collection.begin(); it != collection.end(); it++, index++) {
		if((*it) == NULL) {
			throw std::invalid_argument(preDesc + ": NULL member at index " + toString(index));
		}
	}
}

/**
 * Takes a collection of pointers, and deletes all of the members. They are assumed
 * to be valid, non-NULL pointers.
 * @param collection The collection to iterate through.
 */
template<class T>
void deletePtrVecMembers(const T& collection) {
	for(auto it = collection.begin(); it != collection.end(); it++) {
		delete (*it);
	}
}

/**
 * Takes a vector of pointers, and clones all the members. They are assumed to be valid,
 * non-NULL pointers.
 * @param vec The vector to clone the members of.
 */
template<class T>
std::vector<T*> clonePtrVec(const std::vector<T*> vec) {
	std::vector<T*> ret;
	for(auto it = vec.begin(); it != vec.end(); it++) {
		ret.push_back((*it)->clone());
	}
	return ret;
}

#endif