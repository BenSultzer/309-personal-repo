// Course: 		        IGME 309
// Student Name: 	    Ben Sultzer
// Friday Exercise: 	08

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <ctime>
#include <cmath>

// Define a value for pi
#define PI 3.14159

using namespace std;

// Define the number of vertices for the ball
int numVertices = 100;

// Define the x- and y-coordinates of the anchor
float anchorX = 10.0f;
float anchorY = 15.0f;

// Define the length and direction of the string
float stringLength = -10.0f; // 10 canvas units in the negative y-direction 
							 //	so the ball will "hang" down

float canvasSize[] = { 20.0f, 20.0f };
int rasterSize[] = { 600, 600 };

// tracking the game time - millisecond 
unsigned int curTime = 0;
unsigned int preTime = 0;
float deltaTime = 0;

float rotationAngle = 0.0f;
float rotateSpeed = 90.0f;

/// <summary>
/// Draw a filled circle using GL_POLYGON
/// </summary>
/// <param name="red">The red value for the circle's color</param>
/// <param name="green">The green value for the circle's color</param>
/// <param name="blue">The blue value for the circle's color</param>
/// <param name="center_x">The x-coordinate of the circle's center</param>
/// <param name="center_y">The y-coordinate of the circle's center</param>
/// <param name="radius">The radius of the circle</param>
void drawFilledCircle(float red, float green, float blue, float radius) {
	// Set the specified color
	glColor3f(red, green, blue);

	// Draw the circle
	glBegin(GL_POLYGON);
	for (int i = 0; i < numVertices; i++) {
		// Get the current angle increment
		float angle = ((2 * PI) / numVertices) * i;

		// Calculate the x- and y-coordinates of the current vertex
		float currentX = radius * cos(angle);
		float currentY = radius * sin(angle);

		// Create the vertex
		glVertex2f(currentX, currentY);
	}
	glEnd();
}

void display(void)
{
	glClearColor(0.9f, 0.9f, 0.7f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	/*****************************/
	// write your code below
	// Draw the anchor
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(15.0f);
	glBegin(GL_POINTS);
	glVertex3f(anchorX, anchorY, 0.0f);
	glEnd();
	glPointSize(1.0f);

	// Translate the ball to the anchor
	glTranslatef(anchorX, anchorY, 0.0f);
	// Rotate the ball around the anchor
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
	// Translate the ball along the string's length
	glTranslatef(0.0f, stringLength, 0.0f);

	// Draw the ball
	drawFilledCircle(0.3f, 0.1f, 0.0f, 1.0f);

	// Draw the string
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.5f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, -stringLength, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glLineWidth(1.0f);
	// write your code above
	/*****************************/

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	rasterSize[0] = w;
	rasterSize[1] = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, canvasSize[0], 0, canvasSize[1]);
	glViewport(0, 0, rasterSize[0], rasterSize[1]);

	glutPostRedisplay();
}


void update() {
	curTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (float)(curTime - preTime) / 1000.0f;


	if (rotationAngle > 45.0f) {
		rotateSpeed = -abs(rotateSpeed);
	}
	else if (rotationAngle < -45.0f) {
		rotateSpeed = abs(rotateSpeed);
	}
	rotationAngle += deltaTime * rotateSpeed;

	preTime = curTime;
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(rasterSize[0], rasterSize[1]);
	glutCreateWindow("Simple Pendulum");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(update);

	preTime = glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
	return 0;
}