// Course:              IGME 309
// Student Name:        Ben Sultzer
// Assignment Number:   02

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include "PolyObject.h"

using namespace std;

float canvasSize[] = { 10.0f, 10.0f };
int rasterSize[] = { 800, 600 };

// The default color
float color[3];

// The PolyObject currently being drawn
PolyObject* currentPolyObj;

// Indicates whether the user is done drawing the current PolyObject
bool doneDrawing;

// The list of completed PolyObjects
vector<PolyObject> polyObjects;

// Mouse postion vector
vec2 mousePosVector;

// The color to change to during or before drawing
vec3 colorVector;

// The mouse position array
float mousePos[2];

void init(void)
{
    // Create the current PolyObject
    currentPolyObj = new PolyObject();

    // Initialize the drawing completion Boolean
    doneDrawing = false;

    // Initialize the color vector
    colorVector = vec3(1.0f, 0.0f, 0.0f);

    // Initialize the mouse position array and default
    // color
    mousePos[0] = mousePos[1] = 0.0f;
    color[0] = 1.0f;
    color[1] = color[2] = 0.0f;
}

void drawCursor()
{
    glColor3f(1.0f, 0.0f, 1.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2fv(mousePos);
    glEnd();
    glPointSize(1.0f);
}

/// <summary>
/// Draws the previously created PolyObjects and either dynamically draws the current PolyObject
/// or completes the current PolyObject's drawing, depending on whether or not the user is done drawing.
/// </summary>
/// <param name="void">This function takes no parameters</param>
void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3fv(color);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw all the previously made PolyObjects
    for (int i = 0; i < polyObjects.size(); i++) {
        polyObjects[i].draw();
    }

    // Set the drawing color
    currentPolyObj->setColor(colorVector);

    // Draw the PolyObject dynamically if the user is not done
    // drawing, otherwise draw the completed PolyObject
    if (!doneDrawing) {
        // Create a vec2 out of the mouse postion for drawing the
        // completed PolyObject
        mousePosVector = vec2(mousePos[0], mousePos[1]);

        currentPolyObj->draw(mousePosVector);
    }
    else {
        currentPolyObj->draw();

        // Reset the done drawing flag
        doneDrawing = false;
    }

    // Draw the cursor
    drawCursor();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    rasterSize[0] = w;
    rasterSize[1] = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, canvasSize[0], 0.0, canvasSize[1]);
    glViewport(0, 0, rasterSize[0], rasterSize[1]);

    glutPostRedisplay();
}

/// <summary>
/// Adds a new vertex to the current PolyObject, and redraws the screen
/// to show the results, when the left mouse button is clicked
/// </summary>
/// <param name="button">Which button of the mouse was clicked</param>
/// <param name="state">The state of the button press</param>
/// <param name="x">The Windows screen x-position of the mouse at the
/// time the button was clicked</param>
/// <param name="y">The Windows screen y-position of the mouse at the
/// time the button was clicked</param>
void mouse(int button, int state, int x, int y)
{
    // Add a vertex at the mouse position when the left mouse
    // button is clicked
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Get the mouse position in canvas space
        mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
        mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

        // Create a GLM vec2 object out of the mouse position
        vec2 mouseVertex = vec2(mousePos[0], mousePos[1]);

        // Add the vertex
        currentPolyObj->addVertex(mouseVertex);

        // Redraw the screen
        glutPostRedisplay();
    }
}

void motion(int x, int y)
{
    // mouse events are handled by OS, eventually. When using mouse in the raster window, it assumes top-left is the origin.
    // Note: the raster window created by GLUT assumes bottom-left is the origin.
    mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
    mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

    glutPostRedisplay();
}

/// <summary>
/// Handles when a user is done drawing a PolyObject
/// </summary>
/// <param name="key">The key that was pressed</param>
/// <param name="x">The Windows screen x-position of the mouse at the
/// time the key was pressed</param>
/// <param name="y">The Windows screen y-position of the mouse at the
/// time the key was pressed</param>
void keyboard(unsigned char key, int x, int y)
{
    // Drawing is done when the user presses the "ENTER" key
    switch (key) {
    case 13:
        doneDrawing = true;

        // Add the completed PolyObject to the PolyObject list
        polyObjects.push_back(*currentPolyObj);

        // Create the next object for the user to draw
        currentPolyObj = new PolyObject();
        break;
    }

    glutPostRedisplay();
}

/// <summary>
/// Defines the functionality of the various menu options
/// </summary>
/// <param name="value">The menu option that was 
/// selected</param>
void menu(int value)
{
    switch (value) {
    // Clears all of the PolyObjects
    case 0:
        polyObjects.clear();
        glutPostRedisplay();
        break;
    // Quits the program
    case 1:
        exit(0);
    // Changes the drawing color to red for the current PolyObject
    case 2:
        colorVector = vec3(1.0f, 0.0f, 0.0f);
        glutPostRedisplay();
        break;
    // Changes the drawing color to green for the current PolyObject
    case 3:
        colorVector = vec3(0.0f, 1.0f, 0.0f);
        glutPostRedisplay();
        break;
    // Changes the drawing color to blue for the current PolyObject
    case 4:
        colorVector = vec3(0.0f, 0.0f, 1.0f);
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

void createMenu()
{
    int colorMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Blue", 4);

    glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 0);
    glutAddSubMenu("Colors", colorMenu);
    glutAddMenuEntry("Exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(rasterSize[0], rasterSize[1]);
    glutCreateWindow("A02-Ben-Sultzer");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    createMenu();
    glutMainLoop();
    return 0;
}
