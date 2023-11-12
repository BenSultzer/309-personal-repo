#include "Node.h"

/// <summary>
/// The Node's constructor
/// </summary>
/// <param name="p_bodyPart">The name of the body part this
/// Node will represent</param>
/// <param name="p_id">The ID that will be associated with this
/// Node</param>
Node::Node(string p_bodyPart, int p_id)
{
	bodyPart = p_bodyPart;
	id = p_id;
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
