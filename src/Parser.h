#ifndef PARSER_H
#define PARSER_H

#include "Declaration.h"
#include <vector>
#include <string>

/**
 * Represents a single source file. This node will likely not have a parent. The children
 * of this node are the root-level declarations of the file.
 */
class Program : public Node {
private:
	std::vector<Declaration*> declarations;
public:
	Program(const Position&, const std::vector<Declaration*>& declarations);
	Program(const Program&) = delete;
	virtual ~Program();
	virtual const Program& operator=(const Program&) = delete;
	
	virtual bool operator==(const Node& other) const;
	virtual bool check(std::map<std::string, const Declaration*>&) const;
	virtual const std::vector<Declaration*>& getDeclarations() const;
	virtual void accept(NodeVisitor& visitor) const { visitor.visit(*this); }
};

Program* runParser();

#endif