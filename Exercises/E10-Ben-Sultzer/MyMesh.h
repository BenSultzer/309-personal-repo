// Course:			IGME 309
// Student Name:	Ben Sultzer
// Friday Exercise:	10

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <set>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/constants.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace std;
using namespace glm;

enum ViewMode { SHADED, SHADED_WITH_WIREFRAME};


class MyMesh
{
public:
	ViewMode viewMode;

private:
	vec3 maxVert;	// Stores the maximum x, y, and z values for the bunny's AABB vertices 
	vec3 minVert;	// Stores the minimum x, y, and z values for the bunny's AABB vertices

	float* vertices;
	unsigned int* indices;
	float* vNormals;

	unsigned int vertNum;
	unsigned int triNum;

	// In the future, we will define more vertex and triangle related parameters...
	// vertex normals; - vertNum *3
	// face normals;  - triNum *3
	// texCoords;  - vertNum *2 

	// buffer object ids
	unsigned int vbo_id; // vertex buffer id
	unsigned int nbo_id; // vertex normal buffer id
	unsigned int ibo_id; // index buffer id


	/** mesh shading properties **/
	vec3 amb, diff, spec;
	float shinness;

	vec3 setFaceNormal(vec3 v0, vec3 v1, vec3 v2);
	void prepareBufferObjects();
	/** mutiple private drawing calls **/
	void drawShadedMesh();		// draw shaded mesh and can be used to draw inteermediate versions of the mesh
	void drawWireframeMesh();	// draw the mesh in wireframe and can be used to draw intermediate versions of the mesh
	void computeAABB();			// Determines the maximum and minimum x, y, and z values for the bunny's AABB vertices


public:
	MyMesh();
	~MyMesh();

	void loadFromOBJ(const char* fileName);     // called at initialization
	void update();   // usually called in idle, mouse, motion, keyboard callbacks
	void draw();     // called in display callback;

	unsigned int getVertNum() { return vertNum; };
	unsigned int getTriNum() { return triNum; };
	vec3 getAmbient() { return amb; };
	vec3 getDiffuse() { return diff; };
	vec3 getSpecular() { return spec; };
	float getShinness() { return shinness; };
	void drawAABB();	// Draw the bunny's AABB as a red wireframe box using the values calculated and stored in maxVert and minVert


};

#endif