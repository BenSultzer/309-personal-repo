#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "PolyObject.h"

/// <summary>
/// PolyObject constructor
/// </summary>
PolyObject::PolyObject()
{
	color = vec3(0.0f, 0.0f, 0.0f);
}

/// <summary>
/// PolyObject destructor
/// </summary>
PolyObject::~PolyObject()
{
}

/// <summary>
/// Adds a vertex at the end of the vertex list
/// </summary>
/// <param name="p_vert">The vertex to add</param>
void PolyObject::addVertex(vec2 p_vert)
{
	vertices.push_back(p_vert);
}

// CHECK THIS FUNCTION
/// <summary>
/// Set the color of the current PolyObject
/// </summary>
/// <param name="p_color">The new color</param>
void PolyObject::setColor(vec3 p_color)
{
	glColor3f(p_color.x, p_color.y, p_color.z);
}

unsigned int PolyObject::getVertNum()
{
	return 0;
}

/// <summary>
/// Draw the complete PolyObject to the screen
/// </summary>
void PolyObject::draw()
{
	// The PolyObject contains one vertex
	if (getVertNum() == 1) {
		glBegin(GL_POINTS);
		glVertex2f(vertices[0].x, vertices[0].y);
		glEnd();
	}
	// The PolyObject contains two vertices
	else if (getVertNum() == 2) {
		glBegin(GL_LINES);
		glVertex2f(vertices[0].x, vertices[0].y);
		glVertex2f(vertices[1].x, vertices[1].y);
		glEnd();
	}
	// The PolyObject contains more than two vertices
	else if (getVertNum() > 2) {
		glBegin(GL_POLYGON);
		for (int i = 0; i < getVertNum(); i++) {
			glVertex2f(vertices[i].x, vertices[i].y);
		}
		glEnd();
	}
}

/// <summary>
/// Draw the prospective PolyObject while its being created
/// </summary>
/// <param name="p_mousePos">The possible next vertex
/// (it will be drawn as well)</param>
void PolyObject::draw(vec2 p_mousePos)
{
	// The PolyObject currently has one vertex
	if (getVertNum() == 1) {
		glBegin(GL_LINES);
		glVertex2f(vertices[0].x, vertices[0].y);
		glVertex2f(p_mousePos.x, p_mousePos.y);
		glEnd();
	}
	// The PolyObject has two or more vertices
	else if (getVertNum() >= 2) {
		glBegin(GL_POLYGON);
		for (int i = 0; i < getVertNum(); i++) {
			glVertex2f(vertices[i].x, vertices[i].y);
		}
		glVertex2f(p_mousePos.x, p_mousePos.y);
		glEnd();
	}
}
