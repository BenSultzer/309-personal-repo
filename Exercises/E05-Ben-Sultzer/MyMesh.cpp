#include "MyMesh.h"
#include <GL/freeglut.h>

#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

MyMesh::MyMesh()
{
	vertNum = triNum = 0;
	vertices = NULL;
	indices = NULL;
	vertColors = NULL;
}

MyMesh::~MyMesh()
{
	if (vertices != NULL)
		delete[] vertices;
	if (indices != NULL)
		delete[] indices;

	if (vertColors != NULL)
		delete[] vertColors;
}

void MyMesh::load(char* fileName)
{
	vertNum = 0;
	triNum = 0;

	vertices = new float[100 * 2];
	indices = new unsigned int[100 * 3];
	vertColors = new float[100 * 3];

	ifstream file;

	// Open the file
	file.open(fileName);

	if (!file.is_open()) {
		// Handle error
		cout << "File could not be opened. Quitting..." << endl;
		exit(0);
	}

	/****************************************/
	// Write your code below
	// Indicate whether the current line is a vertex or a face
	bool isVertex = false;
	bool isFace = false;

	// Store the current shape data type character 
	// in the file
	char shapeDataType;

	// Store the current vertex component in the file
	float currentVertComp;

	// Store the current triangle index in the file
	int currentTriVertexIndex;

	// Counter for the vertices array
	int currentVertIndex = 0;

	// Counter for the triangle (indices) array
	int currentTriIndex = 0;

	// There will always be two vertex components, so reset
	// the shape data type after two passes through the file
	int vertexCompCoundown = 2;

	// There will always be three triangle indices, so reset
	// the shape data type after three passes through the file
	int triangleVertIndexCountdown = 3;

	// Extract the vertices and indices from the file
	while (file.peek() != EOF) {
		// Determine what kind of data the current line is
		// (don't know if its a vertex or a face)
		if (!isVertex && !isFace) {
			file >> shapeDataType;

			// Indicate that the current line is a vertex
			if (shapeDataType == 'v') {
				isVertex = true;
				isFace = false;
			}
			// Indicate that the current line is a face
			else if (shapeDataType == 'f') {
				isVertex = false;
				isFace = true;
			}
		}
		// If the current line is a vertex, store the current 
		// vertex component
		else if (isVertex) {
			// There are still more vertex components to process
			if (vertexCompCoundown > 0) {
				file >> currentVertComp;

				// Assign the vertex component
				// to the proper index in the vertices array and increment the 
				// vertices array counter for the next component
				vertices[currentVertIndex] = currentVertComp;
				currentVertIndex++;

				// Decrement the vertex countdown
				vertexCompCoundown--;
			}
			// If all vertex components have been processed, reset the
			// vertex countdown and the shape data type
			else {
				vertexCompCoundown = 2;
				isVertex = false;
			}
		}
		// if the current line is a face, store the current
		// vertex index
		else if (isFace) {
			// There are still more triangle vertex indices to be processed
			if (triangleVertIndexCountdown > 0) {
				file >> currentTriVertexIndex;

				// Assign the vertex index
				// to the proper index in the triangle (indices) array, 
				// and increment the triangle array counter for the next 
				// vertex index
				indices[currentTriIndex] = currentTriVertexIndex - 1;
				currentTriIndex++;

				// Decrement the triangle vertex index countdown
				triangleVertIndexCountdown--;
			}
			// If all triangle vertex indices have been processed, reset the
			// triangle vertex index countdown and the shape data type
			else {
				triangleVertIndexCountdown = 3;
				isFace = false;
			}
		}
	}

	// Set the number of vertices and triangles
	vertNum = currentVertIndex / 2;
	triNum = currentTriIndex / 3;

	// Close the file
	file.close();
	// Write your code above
	/****************************************/

	// generate random vertex colors
	for (unsigned int i = 0; i < vertNum; i++) {
		vertColors[i * 3 + 0] = float(rand()) / (RAND_MAX + 1);
		vertColors[i * 3 + 1] = float(rand()) / (RAND_MAX + 1);
		vertColors[i * 3 + 2] = float(rand()) / (RAND_MAX + 1);
	}
}

void MyMesh::load(const unsigned int p_vertNum, const unsigned int p_triNum, const float* p_vertices, const unsigned int* p_indices)
{
	vertNum = p_vertNum;
	triNum = p_triNum;

	vertices = new float[vertNum * 2];
	indices = new unsigned int[triNum * 3];
	vertColors = new float[vertNum * 3];

	for (unsigned int i = 0; i < vertNum * 2; i++) {
		vertices[i] = p_vertices[i];
	}

	for (unsigned int i = 0; i < triNum * 3; i++) {
		indices[i] = p_indices[i];
	}

	// generate random vertex colors
	for (unsigned int i = 0; i < vertNum; i++) {
		vertColors[i * 3 + 0] = float(rand()) / (RAND_MAX + 1);
		vertColors[i * 3 + 1] = float(rand()) / (RAND_MAX + 1);
		vertColors[i * 3 + 2] = float(rand()) / (RAND_MAX + 1);
	}

}

void MyMesh::update()
{
	// we will use this for transformations later.... 
}

void MyMesh::draw()
{
	for (int i = 0; i < triNum; ++i) {
		glBegin(GL_TRIANGLES);
		glColor3fv(vertColors + indices[i * 3 + 0] * 3);
		glVertex2fv(vertices + indices[i * 3 + 0] * 2);

		glColor3fv(vertColors + indices[i * 3 + 1] * 3);
		glVertex2fv(vertices + indices[i * 3 + 1] * 2);

		glColor3fv(vertColors + indices[i * 3 + 2] * 3);
		glVertex2fv(vertices + indices[i * 3 + 2] * 2);
		glEnd();
	}
}