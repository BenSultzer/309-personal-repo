// Course:              IGME 309
// Student Name:        Ben Sultzer
// Assignment Number:   04

#pragma once

using namespace std;

// The enum for all body part names and corresponding values (to
// be used as array indices)
enum class BodyParts {
	HEAD = 0,
	NECK = 1,
	UPPER_BODY = 2,
	LEFT_ARM = 3,
	LEFT_FOREARM = 4,
	LEFT_HAND = 5,
	RIGHT_ARM = 6,
	RIGHT_FOREARM = 7,
	RIGHT_HAND = 8,
	LOWER_BODY = 9,
	LEFT_THIGH = 10,
	LEFT_LEG = 11,
	LEFT_FOOT = 12,
	RIGHT_THIGH = 13,
	RIGHT_LEG = 14,
	RIGHT_FOOT = 15
};

/// <summary>
/// Defines a node in the Tree structure that represents a robot's body
/// </summary>
class Node {
private:
	BodyParts bodyPart;			// The body part this Node represents
	Node* left = nullptr;		// The left child of this Node
	Node* center = nullptr;		// The center child of this Node
	Node* right = nullptr;		// The right child of this Node

public:
	/// <summary>
	/// The Node's constructor
	/// </summary>
	/// <param name="p_bodyPart">The BodyParts enum member corresponding to
	/// the body part this Node will represent</param>
	Node(BodyParts p_bodyPart);

	/// <summary>
	/// The Node's destructor
	/// </summary>
	~Node();

	/// <summary>
	/// Returns the BodyParts enum identifier for this Node
	/// </summary>
	/// <returns>The BodyParts enum identifier for this Node</returns>
	BodyParts getNodeBodyPart();

	/// <summary>
	/// Sets the left child Node of this Node
	/// </summary>
	/// <param name="p_left">The Node to store as this
	/// Node's left child Node</param>
	void setLeftNode(Node p_left);

	/// <summary>
	/// Returns the left child Node of this Node
	/// </summary>
	/// <returns>The left child Node of this Node</returns>
	Node* getLeftNode();

	/// <summary>
	/// Sets the center child Node of this Node
	/// </summary>
	/// <param name="p_center">The Node to store as this
	/// Node's center child Node</param>
	void setCenterNode(Node p_center);

	/// <summary>
	/// Returns the center child Node of this Node
	/// </summary>
	/// <returns>The center child Node of this Node</returns>
	Node* getCenterNode();

	/// <summary>
	/// Sets the right child Node of this Node
	/// </summary>
	/// <param name="p_right">The Node to store as this
	/// Node's right child Node</param>
	void setRightNode(Node p_right);

	/// <summary>
	/// Returns the right child Node of this Node
	/// </summary>
	/// <returns>The right child Node of this Node</returns>
	Node* getRightNode();
};