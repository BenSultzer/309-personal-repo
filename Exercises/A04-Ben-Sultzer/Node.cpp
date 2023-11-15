#include "Node.h"

/// <summary>
/// The Node's constructor
/// </summary>
/// <param name="p_bodyPart">The name of the body part this
/// Node will represent</param>
Node::Node(string p_bodyPart)
{
	bodyPart = p_bodyPart;
}

/// <summary>
/// The Node's destructor
/// </summary>
Node::~Node()
{
	delete left;
	delete center;
	delete right;
}

/// <summary>
/// Gets the name of the body part this Node represents
/// </summary>
/// <returns>The name of the body part</returns>
string Node::getBodyPartName()
{
	return bodyPart;
}

/// <summary>
/// Returns the ID for this Node
/// </summary>
/// <returns>The ID of this Node</returns>
int Node::getNodeID()
{
	return id;
}

/// <summary>
/// Sets the left Node of this Node
/// </summary>
/// <param name="p_left">The Node to store as this
/// Node's left Node</param>
void Node::setLeftNode(Node p_left)
{
	left = &p_left;
}

/// <summary>
/// Sets the center Node of this Node
/// </summary>
/// <param name="p_center">The Node to store as this
/// Node's center Node</param>
void Node::setCenterNode(Node p_center)
{
	center = &p_center;
}

/// <summary>
/// Sets the right Node of this Node
/// </summary>
/// <param name="p_right">The Node to store as this
/// Node's right Node</param>
void Node::setRightNode(Node p_right)
{
	right = &p_right;
}
