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