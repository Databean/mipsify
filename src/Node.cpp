#include "Node.h"
#include <stdexcept>
#include "y.tab.h"

using std::vector;
using std::initializer_list;
using std::string;
using std::runtime_error;
using std::ostream;

/**
 * Prints a position to an output stream. The format of the output will look like
 * [start line:start column - end line:end column]
 * @param output The stream to output to.
 * @param pos The position to output.
 * @return The output stream given as input.
 */
ostream& operator<<(ostream& output, const Position& pos) {
	return output << "[" << pos.getStartLine() << ":" << pos.getStartColumn() << " - " << pos.getEndLine() << ":" << pos.getEndColumn() << "]";
}

/**
 * Constructs a Position, using the bison YYLTYPE struct.
 * @param loc The bison position structure.
 */
Position::Position(const YYLTYPE& loc) :
	startLine(loc.first_line), endLine(loc.last_line),
	startColumn(loc.first_column), endColumn(loc.last_column) {
	
}

/**
 * Copy constructor for Position.
 * @param p Position to copy.
 */
Position::Position(const Position& p) :
	startLine(p.getStartLine()), endLine(p.getEndLine()),
	startColumn(p.getStartColumn()), endColumn(p.getEndColumn()) {
	
}

/**
 * Destructor for position. It does not have any dynamically allocated members.
 */
Position::~Position() {
	
}

/**
 * Assignment operator for position.
 * @param p The new position this should take the values of.
 * @return A const refernce to the Position.
 */
const Position& Position::operator=(const Position& p) {
	startLine = p.getStartLine();
	endLine = p.getEndLine();
	startColumn = p.getStartColumn();
	endColumn = p.getEndColumn();
	return *this;
}

/**
 * The first line of the construct this is attached to.
 * @return The first line.
 */
int Position::getStartLine() const {
	return startLine;
}

/**
 * The last line of the construct this is attached to.
 * @return The last line.
 */
int Position::getEndLine() const {
	return endLine;
}

/**
 * The first column of the construct this is attached to, on the first line.
 * @return The first column.
 */
int Position::getStartColumn() const {
	return startColumn;
}

/**
 * The last column of the construct that this is attached to, on the last line.
 * @return The last column.
 */
int Position::getEndColumn() const {
	return endColumn;
}

/**
 * Constructs a Node, stores the given position. and registers itself as a parent of all of the passed in children.
 * When the number of children is not known at compile time, use the other constructor.
 * @param pos The position of this node.
 * @param children All of the children nodes.
 */
Node::Node(const Position& pos, initializer_list<Node*> children) : parent(NULL), position(pos) {
	for(auto it = children.begin(); it != children.end(); it++) {
		if((*it)->parent != NULL) {
			throw runtime_error("This Node already has a parent added. Don't share nodes between syntax trees.");
		} else {
			(*it)->parent = this;
		}
	}
}

/**
 * Destroys the Node. Subclasses are responsible for deleting their own children, and the base Node class
 * does not store any dynamic members.
 */
Node::~Node() {
	
}

/**
 * Checks whether this class has had a parent member register itself. If it doesn't have a parent and it isn't
 * what you expect the root node to be, check that all subclasses are passing in all of their children into
 * the Node constructor.
 * @return Whether this Node has a registered parent.
 */
bool Node::hasParent() const {
	return parent != NULL;
}

/**
 * Gives a reference to the registered parent. If none is registered, this throws an exception.
 * @return The parent of this node.
 */
const Node& Node::getParent() const {
	if(parent == NULL) {
		throw runtime_error("Node::getParent(): parent is NULL");
	} else {
		return *parent;
	}
}

/**
 * Gets the position object associated with this Node. The position object has start and end lines and columns.
 * @return This Node's position.
 */
const Position& Node::getPosition() const {
	return position;
}
