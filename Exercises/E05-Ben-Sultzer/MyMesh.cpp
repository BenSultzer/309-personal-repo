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
	int currentTriIndex;

	// Counter for the vertices array
	int currentVertIndex = 0;

	// Counter for the triangle (indices) array
	int currentTriIndex = 0;

	// Extract the vertices and indices from the file
	while (file.peek() != EOF) {
		// Get the current shape data type character
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
		// Otherwise, the current element is a piece of data
		else {
			// If the current line is a vertex, assign the vertex component
			// to the proper index in the vertices array and increment the 
			// vertices array counter for the next component
			if (isVertex) {
				vertices[currentVertIndex] = shapeDataType;
				currentVertIndex++;
			}
			// If the current line is a face, assign the vertex index
			// to the proper index in the triangle (indices) array, 
			// and increment the triangle array counter for the next 
			// vertex index
			else if (isFace) {
				indices[currentTriIndex] = shapeDataType - 1;
				currentTriIndex++;
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