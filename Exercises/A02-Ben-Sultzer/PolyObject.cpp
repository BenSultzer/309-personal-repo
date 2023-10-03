#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "PolyObject.h"

PolyObject::PolyObject()
{
}

PolyObject::~PolyObject()
{
}

void PolyObject::addVertex(vec2 p_vert)
{
}

void PolyObject::setColor(vec3 p_color)
{
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
}

/// <summary>
/// Draw the prospective PolyObject while its being created
/// </summary>
/// <param name="p_mousePos"></param>
void PolyObject::draw(vec2 p_mousePos)
{
	// The PolyObject currently has one vertex
	if (getVertNum() == 1) {
		glBegin(GL_LINES);
		glVertex2f(vertices[0].x, vertices[0].y);
	}
}
