// Course: 		        IGME 309
// Student Name: 	    Ben Sultzer
// Assignment Number: 	01

#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif

#include <math.h>

using namespace std;

// Define a value for pi
const float PI = 3.14159;

// The total number of vertices for a circle
int numVertices = 100;

// The window's width and height
int width, height;

/// <summary>
/// Draw a filled circle using GL_POLYGON
/// </summary>
/// <param name="red">The red value for the circle's color</param>
/// <param name="green">The green value for the circle's color</param>
/// <param name="blue">The blue value for the circle's color</param>
/// <param name="center_x">The x-coordinate of the circle's center</param>
/// <param name="center_y">The y-coordinate of the circle's center</param>
/// <param name="radius">The radius of the circle</param>
void drawFilledCircle(float red, float green, float blue, float center_x, float center_y, float radius) {
    // Set the specified color
    glColor3f(red, green, blue);

    // Draw the circle
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; i++) {
        // Get the current angle increment
        float angle = ((2 * PI) / numVertices) * i;

        // Calculate the x- and y-coordinates of the current vertex
        float currentX = center_x + (radius * cos(angle));
        float currentY = center_y + (radius * sin(angle));

        // Create the vertex
        glVertex2f(currentX, currentY);
    }
    glEnd();
}

/// <summary>
/// Draw a wireframe circle with GL_LINE_LOOP
/// </summary>
/// <param name="red">The red value for the circle's color</param>
/// <param name="green">The green value for the circle's color</param>
/// <param name="blue">The blue value for the circle's color</param>
/// <param name="center_x">The x-component for the circle's center</param>
/// <param name="center_y">The y-component for the circle's center</param>
/// <param name="radius">The radius of the circle</param>
/// <param name="lineWidth">The thickness of the circle</param>
void drawWireframeCircle(float red, float green, float blue, float center_x, float center_y, float radius, float lineWidth) {
    // Set the specified color
    glColor3f(red, green, blue);

    // Set the specified line width
    glLineWidth(lineWidth);

    // Draw the circle
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; i++) {
        // Get the current angle increment
        float angle = ((2 * PI) / numVertices) * i;

        // Calculate the x- and y-coordinates of the current vertex
        float currentX = center_x + (radius * cos(angle));
        float currentY = center_y + (radius * sin(angle));

        // Create the vertex
        glVertex2f(currentX, currentY);
    }
    glEnd();

    // Reset the line width
    glLineWidth(1.0f);
}

/// <summary>
/// Draws a cartoon panda using the drawFilledCircle() and drawWireframeCircle()
/// functions
/// </summary>
void drawPanda() {
    // Back and front leg (behind body)
    drawFilledCircle(0.0f, 0.0f, 0.0f, 5.0f, 2.0f, 0.9f);
    drawFilledCircle(0.0f, 0.0f, 0.0f, 9.0f, 2.0f, 0.9f);

    // Tail
    drawFilledCircle(0.0f, 0.0f, 1.0f, 4.0f, 8.0f, 0.75f);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 4.0f, 8.0f, 0.75f, 2.0f);

    // Body
    drawFilledCircle(0.0f, 0.0f, 1.0f, 6.5f, 5.0f, 3.5f);

    // Back and front leg (in front of body)
    drawFilledCircle(0.0f, 0.0f, 0.0f, 4.0f, 2.0f, 0.9f);
    drawFilledCircle(0.0f, 0.0f, 0.0f, 8.0f, 2.0f, 0.9f);

    // Ear (behind head)
    drawFilledCircle(0.0f, 0.0f, 0.0f, 12.0f, 8.0f, 0.9f);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 12.0f, 8.0f, 0.9f, 2.0f);

    // Head
    drawFilledCircle(0.0f, 0.0f, 1.0f, 10.0f, 5.5f, 2.75f);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 10.0f, 5.5f, 2.75f, 2.0f);

    // Ear (in front of head)
    drawFilledCircle(0.0f, 0.0f, 0.0f, 8.0f, 8.0f, 0.9f);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 8.0f, 8.0f, 0.9f, 2.0f);

    // Horn
    drawFilledCircle(1.0f, 0.75f, 0.0f, 10.0f, 8.0f, 0.6f);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 10.0f, 8.0f, 0.6f, 2.0f);
    drawFilledCircle(1.0f, 0.75f, 0.0f, 10.25f, 8.15f, 0.5f);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 10.25f, 8.15f, 0.5f, 2.0f);
    drawFilledCircle(1.0f, 0.75f, 0.0f, 10.5f, 8.3f, 0.4f);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 10.5f, 8.3f, 0.4f, 2.0f);
    drawFilledCircle(1.0f, 0.75f, 0.0f, 10.75f, 8.45f, 0.3f);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 10.75f, 8.45f, 0.3f, 2.0f);
    drawFilledCircle(1.0f, 0.75f, 0.0f, 11.0f, 8.6f, 0.2f);
    drawWireframeCircle(0.0f, 0.0f, 0.0f, 11.0f, 8.6f, 0.2f, 2.0f);

    // Eyes (pupil)
    drawFilledCircle(0.0f, 0.0f, 0.0f, 10.0f, 5.75f, 0.4f);
    drawFilledCircle(0.0f, 0.0f, 0.0f, 11.0f, 5.75f, 0.4f);

    // Eyes (highlights)
    drawFilledCircle(1.0f, 1.0f, 1.0f, 10.15f, 5.7f, 0.15f);
    drawFilledCircle(1.0f, 1.0f, 1.0f, 11.15f, 5.7f, 0.15f);
    drawFilledCircle(1.0f, 1.0f, 1.0f, 9.85f, 5.9f, 0.1f);
    drawFilledCircle(1.0f, 1.0f, 1.0f, 10.85f, 5.9f, 0.1f);

    // Nose
    drawFilledCircle(0.0f, 0.0f, 0.0f, 10.5f, 5.0f, 0.2f);
    drawFilledCircle(0.0f, 0.0f, 0.0f, 10.25f, 5.0f, 0.2f);
    drawFilledCircle(0.0f, 0.0f, 0.0f, 10.75f, 5.0f, 0.2f);
    drawFilledCircle(0.0f, 0.0f, 0.0f, 10.5f, 4.75f, 0.2f);

    // Mouth
    drawFilledCircle(0.0f, 0.0f, 0.0f, 10.5f, 4.25f, 0.35f);

    // Spots
    drawFilledCircle(1.0f, 0.92f, 0.0f, 4.5f, 4.75f, 1.0f);
    drawFilledCircle(1.0f, 0.92f, 0.0f, 6.5f, 7.0f, 0.45f);
    drawFilledCircle(1.0f, 0.0f, 0.0f, 6.75f, 4.75f, 0.35f);
    drawFilledCircle(1.0f, 0.0f, 0.0f, 12.0f, 5.0f, 0.45f);
    drawFilledCircle(1.0f, 0.0f, 1.0f, 8.5f, 5.5f, 0.6f);
    drawFilledCircle(0.0f, 0.92f, 1.0f, 6.0f, 2.5f, 0.5f);
    drawFilledCircle(1.0f, 0.65f, 0.0f, 4.25f, 8.0f, 0.25f);
}

/// <summary>
/// Initialize program-specific members
/// </summary>
/// <param name="">Takes no parameters</param>
void init(void)
{
    // initialize the size of the window
    width = 854;
    height = 480;
}

/// <summary>
/// Called when the GL context needs to be rendered
/// </summary>
/// <param name="">Takes no parameters</param>
void display(void)
{
    // clear the screen to white, which is the background color
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // clear the buffer stored for drawing
    glClear(GL_COLOR_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // specify the color for drawing
    glColor3f(1.0, 0.0, 0.0);

    // Draw the panda
    drawPanda();

    // specify the color for new drawing
    glColor3f(0.0, 0.0, 1.0);

    glutSwapBuffers();
}

/// <summary>
/// Called when window is first created or when window is resized
/// </summary>
/// <param name="w">The window width</param>
/// <param name="h">The window height</param>
void reshape(int w, int h)
{
    // update the screen dimensions
    width = w;
    height = h;

    //do an orthographic parallel projection, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 16.0, 0.0, 9.0);
    //gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

    /* tell OpenGL to use the whole window for drawing */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    //glViewport((GLsizei) width/2, (GLsizei) height/2, (GLsizei) width, (GLsizei) height);

    glutPostRedisplay();
}

/// <summary>
/// Handles keyboard input for dynamically increasing or decreasing the resolution
/// of the character by increasing or decreasing the number of vertices 
/// to draw per circle
/// </summary>
/// <param name="key">The ASCII code of the key that was pressed</param>
/// <param name="x">the x-coordinate of the mouse position at the time
/// the key was pressed</param>
/// <param name="y">The y-coordinate of the mouse position at the time
/// the key was pressed</param>
void keyboard(unsigned char key, int x, int y) {
    // When the user presses the "plus" key, add more vertices. The maximum
    // number of vertices is 100
    if ((key == 43) && (numVertices < 100)) {
        numVertices++;
    }
    // When the user presses the "minus" key, subtract vertices. The minimum
    // number of vertices is 3
    else if ((key == 45) && (numVertices > 3)) {
        numVertices--;
    }

    // Re-render the window
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    // before create a glut window,
    // initialize stuff not opengl/glut dependent
    init();

    //initialize GLUT, let it extract command-line GLUT options that you may provide
    //NOTE that the '&' before argc
    glutInit(&argc, argv);

    // specify as double bufferred can make the display faster
    // Color is speicfied to RGBA, four color channels with Red, Green, Blue and Alpha(depth)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    //set the initial window size */
    glutInitWindowSize((int)width, (int)height);

    // create the window with a title
    glutCreateWindow("A01-Ben-Sultzer");

    /* --- register callbacks with GLUT --- */

    //register function to handle window resizes
    glutReshapeFunc(reshape);

    //register function that draws in the window
    glutDisplayFunc(display);

    // Register function that handles keyboard input
    glutKeyboardFunc(keyboard);

    //start the glut main loop
    glutMainLoop();

    return 0;
}