// Course: 		        IGME 309
// Student Name: 	    Ben Sultzer
// Friday Exercise: 	03

#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif

#include <cstdlib>
#include <time.h>

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
        // Seven triangles with a right base point at half-x coordinates between
        // 5.0 and 10.0 and a left base point at half-x coordinates between 
        // 0.0 and 5.0.
        glVertex2f(1.0 + ((5.0 / 10.0) * i), 2.5 + ((5.0 / 10.0) * i));
        glVertex2f(5.0f, 3.5 + ((5.0 / 10.0) * i));
        glVertex2f(9.0 - ((5.0 / 10.0) * i), 2.5 + ((5.0 / 10.0) * i));
    }
    glEnd();

    // Draw ornanments
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

// called when the GL context need to be rendered
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

    // this is immedidate mode of OpenGL usded prior to OpenGL 3.0
    DrawTree();

    // specify the color for new drawing
    glColor3f(0.0, 0.0, 1.0);

    // Reset the point size
    glPointSize(1.0f);

    glutSwapBuffers();
}

// called when window is first created or when window is resized
void reshape(int w, int h)
{
    // update thescreen dimensions
    width = w;
    height = h;

    //do an orthographic parallel projection, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 10.0, 0.0, 10.0);
    //gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

    /* tell OpenGL to use the whole window for drawing */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    //glViewport((GLsizei) width/2, (GLsizei) height/2, (GLsizei) width, (GLsizei) height);

    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    // Set the random number generator for random ornament colors
    srand(time(0));

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
    glutCreateWindow("First OpenGL Program");

    /* --- register callbacks with GLUT --- */

    //register function to handle window resizes
    glutReshapeFunc(reshape);

    //register function that draws in the window
    glutDisplayFunc(display);

    //start the glut main loop
    glutMainLoop();

    return 0;
}