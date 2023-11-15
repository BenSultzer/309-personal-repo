#pragma once
#include <string>

using namespace std;

/// <summary>
/// Defines a node in the Tree structure that represents a robot's body
/// </summary>
class Node {
private:
	string bodyPart = "";		// The body part this Node represents
	Node* left = nullptr;		// The left child of this Node
	Node* center = nullptr;		// The center child of this Node
	Node* right = nullptr;		// The right child of this Node

public:
	/// <summary>
	/// The Node's constructor
	/// </summary>
	/// <param name="p_bodyPart">The name of the body part this
	/// Node will represent</param>
	Node(string p_bodyPart);

	/// <summary>
	/// The Node's destructor
	/// </summary>
	~Node();

	/// <summary>
	/// Gets the name of the body part this Node represents
	/// </summary>
	/// <returns>The name of the body part</returns>
	string getBodyPartName();

	/// <summary>
	/// Returns the ID for this Node
	/// </summary>
	/// <returns>The ID of this Node</returns>
	int getNodeID();

	/// <summary>
	/// Sets the left Node of this Node
	/// </summary>
	/// <param name="p_left">The Node to store as this
	/// Node's left Node</param>
	void setLeftNode(Node p_left);

	/// <summary>
	/// Sets the center Node of this Node
	/// </summary>
	/// <param name="p_center">The Node to store as this
	/// Node's center Node</param>
	void setCenterNode(Node p_center);

	/// <summary>
	/// Sets the right Node of this Node
	/// </summary>
	/// <param name="p_right">The Node to store as this
	/// Node's right Node</param>
	void setRightNode(Node p_right);
};