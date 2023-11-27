// Course:              IGME 309
// Student Name:        Ben Sultzer
// Assignment Number:   04

#include "Node.h"

/// <summary>
/// The Node's constructor
/// </summary>
/// <param name="p_bodyPart">The BodyParts enum member corresponding to
/// the body part this Node will represent</param>
Node::Node(BodyParts p_bodyPart)
{
	bodyPart = p_bodyPart;
}

/// <summary>
/// The Node's destructor
/// </summary>
Node::~Node()
{
	//delete left;
	//delete center;
	//delete right;
}

/// <summary>
/// Returns the BodyParts enum identifier for this Node
/// </summary>
/// <returns>The BodyParts enum identifier for this Node</returns>
BodyParts Node::getNodeBodyPart()
{
	return bodyPart;
}

/// <summary>
/// Sets the left child Node of this Node
/// </summary>
/// <param name="p_left">The Node to store as this
/// Node's left child Node</param>
void Node::setLeftNode(Node& p_left)
{
	left = &p_left;
}

/// <summary>
/// Returns the left child Node of this Node
/// </summary>
/// <returns>The left child Node of this Node</returns>
Node* Node::getLeftNode() 
{
	return left;
}

/// <summary>
/// Sets the center child Node of this Node
/// </summary>
/// <param name="p_center">The Node to store as this
/// Node's center child Node</param>
void Node::setCenterNode(Node& p_center)
{
	center = &p_center;
}

/// <summary>
/// Returns the center child Node of this Node
/// </summary>
/// <returns>The center child Node of this Node</returns>
Node* Node::getCenterNode()
{
	return center;
}

/// <summary>
/// Sets the right child Node of this Node
/// </summary>
/// <param name="p_right">The Node to store as this
/// Node's right child Node</param>
void Node::setRightNode(Node& p_right)
{
	right = &p_right;
}

/// <summary>
/// Returns the right child Node of this Node
/// </summary>
/// <returns>The right child Node of this Node</returns>
Node* Node::getRightNode() 
{
	return right;
}
