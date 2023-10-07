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

// structure for storing 3 2D vertices of a triangle
int numOfVertices = 0;
float v[2 * 3];
float color[3];

// The PolyObject currently being drawn
PolyObject* currentPolyObj;

// Indicates whether the user is done drawing the current PolyObject
bool doneDrawing;

// The list of completed PolyObjects
vector<PolyObject> polyObjects;

float mousePos[2];

void init(void)
{
    // Create the current PolyObject
    currentPolyObj = new PolyObject();

    // Initialize the drawing completion Boolean
    doneDrawing = false;

    for (int i = 0; i < 6; i++)
        v[i] = 0.0f;
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

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3fv(color);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (numOfVertices > 0 && numOfVertices < 3) {

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < numOfVertices; i++)
            glVertex2fv(v + i * 2);
        glVertex2fv(mousePos);
        glEnd();
    }
    else if (numOfVertices == 3) {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < numOfVertices; i++)
            glVertex2fv(v + i * 2);
        glEnd();
    }

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
    // Drawing is done when the user clicks the "ENTER" key
    switch (key) {
    case '\n':
        doneDrawing = true;

        // Add the completed PolyObject to the PolyObject list
        polyObjects.push_back(*currentPolyObj);

        // Create the next object for the user to draw
        currentPolyObj = new PolyObject();
        break;
    }
}

void menu(int value)
{
    switch (value) {
    case 0: // clear
        numOfVertices = 0;
        glutPostRedisplay();
        break;
    case 1: //exit
        exit(0);
    case 2: // red
        color[0] = 1.0f;
        color[1] = 0.0f;
        color[2] = 0.0f;
        glutPostRedisplay();
        break;
    case 3: // green
        color[0] = 0.0f;
        color[1] = 1.0f;
        color[2] = 0.0f;
        glutPostRedisplay();
        break;
    case 4: // blue
        color[0] = 0.0f;
        color[1] = 0.0f;
        color[2] = 1.0f;
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
    glutCreateWindow("Mouse Event - draw a triangle");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    createMenu();
    glutMainLoop();
    return 0;
}