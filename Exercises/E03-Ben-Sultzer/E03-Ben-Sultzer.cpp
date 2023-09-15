// Course: 		        IGME 309
// Student Name: 	    Ben Sultzer
// Friday Exercise: 	03

#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif

// The window's width and height
int width, height;

/// <summary>
/// Initialize non-OpenGL and GLUT members
/// </summary>
/// <param name="">Takes no parameters</param>
void init(void)
{
    // Initialize the size of the window
    width = 600;
    height = 600;
}

/// <summary>
/// Draws a Christmas tree using OpenGL primitive drawing functions
/// </summary>
void DrawTree() {
    // Draw trunk
    glColor3f(0.59f, 0.29f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(4.75f, 1.0f);
    glVertex2f(4.75f, 2.5f);
    glVertex2f(5.25f, 2.5f);
    glVertex2f(5.25f, 1.0f);
    glEnd();

    // Draw leaves
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 7; i++) {
        // 7 triangles with evenly incremented base lengths and vertical positions
        // to create a tapering tree structure
        // Left base vertex x-coordinate is increased by 0.5 each
        // iteration going towards the center and starting at 1.0. The y-
        // coordinate is increased by 0.5 each iteration starting at 2.5
        glVertex2f(1.0 + ((5.0 / 10.0) * i), 2.5 + ((5.0 / 10.0) * i));

        // Top vertex x-coordinate constantly stays in the center at 5.0 
        // and the y-coordinate is incremented by 0.5 each iteration starting
        // at 3.5 
        glVertex2f(5.0f, 3.5 + ((5.0 / 10.0) * i));

        // Right base vertex x-coordinate is decreased by 0.5 each
        // iteration going towards the center and starting at 9.0. The y-
        // coordinate is increased by 0.5 each iteration starting at 2.5.
        glVertex2f(9.0 - ((5.0 / 10.0) * i), 2.5 + ((5.0 / 10.0) * i));
    }
    glEnd();

    // Draw ornaments
    glPointSize(15.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    glVertex2f(4.0f, 3.0f);
    glVertex2f(4.25f, 4.75f);
    glVertex2f(6.5f, 3.0f);
    glVertex2f(5.75f, 4.0f);
    glVertex2f(5.15f, 5.75f);
    glVertex2f(3.75f, 3.75f);
    glVertex2f(4.85f, 3.75f);
    glVertex2f(5.5f, 3.15f);
    glVertex2f(3.25f, 3.25f);
    glVertex2f(5.65f, 5.0f);
    glEnd();
}

/// <summary>
/// Called when the GL context needs to be rendered
/// </summary>
/// <param name="">Takes no parameters</param>
void display(void)
{
    // Clear the screen to white, which is the background color
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Clear the buffer stored for drawing
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Specify the color for drawing
    glColor3f(1.0, 0.0, 0.0);

    // This is the immediate mode of OpenGL used prior to OpenGL 3.0
    DrawTree();

    // Specify the color for new drawing
    glColor3f(0.0, 0.0, 1.0);

    // Reset the point size
    glPointSize(1.0f);

    glutSwapBuffers();
}

/// <summary>
/// Called when window is first created or when window is resized
/// </summary>
/// <param name="w">The width of the window</param>
/// <param name="h">The height of the window</param>
void reshape(int w, int h)
{
    // Update the screen dimensions
    width = w;
    height = h;

    // Do an orthographic parallel projection, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 10.0, 0.0, 10.0);
    //gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

    /* Tell OpenGL to use the whole window for drawing */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    //glViewport((GLsizei) width/2, (GLsizei) height/2, (GLsizei) width, (GLsizei) height);

    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    // Before creating a glut window, initialize stuff not opengl/glut dependent
    init();

    // Initialize GLUT, let it extract command-line GLUT options that you may provide
    // NOTE the '&' comes before argc
    glutInit(&argc, argv);

    // Specifying double buffered can make the display faster
    // Color is specified to RGBA, four color channels with Red, Green, Blue, and Alpha (depth)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    // Set the initial window size
    glutInitWindowSize((int)width, (int)height);

    // Create the window with a title
    glutCreateWindow("First OpenGL Program");

    /* --- Register callbacks with GLUT --- */

    // Register function to handle window resizing
    glutReshapeFunc(reshape);

    // Register function that draws in the window
    glutDisplayFunc(display);

    // Start the glut main loop
    glutMainLoop();

    return 0;
}