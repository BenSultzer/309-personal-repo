//Usage:
//Hold down the number keys , 1-7, to select one or multiple circles.
//While circle(s) are selected, use the left mouse button to translate and use the right mouse button to rotate.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <math.h>
#include "Node.h"
using namespace std;
using namespace glm;

enum class BodyParts {
    HEAD = 0,
    NECK = 1,
    UPPER_BODY = 2,
    LEFT_ARM = 3,
    LEFT_FOREARM = 4,
    LEFT_HAND = 5, 
    RIGHT_ARM = 6, 
    RIGHT_FOREARM = 7,
    RIGHT_HAND = 8,
    LOWER_BODY = 9,
    LEFT_THIGH = 10,
    LEFT_LEG = 11,
    LEFT_FOOT = 12,
    RIGHT_THIGH = 13,
    RIGHT_LEG = 14,
    RIGHT_FOOT = 15
};

#define MAX_NUM_BODY_PARTS 16
#define CIRCLE_RADIUM 2.0

int win_width = 600, win_height = 600;
float canvas_width = 20.0f; float canvas_height = 20.0f;


bool keyStates[256];
int buttonState;
float colors[3 * MAX_NUM_BODY_PARTS];
float translations[2 * MAX_NUM_BODY_PARTS];
float rotations[MAX_NUM_BODY_PARTS];

float curMouse[2];
float preMouse[2];

// The array of all body parts
Node bodyParts[] = {
        Node("Head"),
        Node("Neck"),
        Node("Upper Body"),
        Node("Left Arm"),
        Node("Left Forearm"),
        Node("Left Hand"),
        Node("Right Arm"),
        Node("Right Forearm"),
        Node("Right Hand"),
        Node("Lower Body"),
        Node("Left Thigh"),
        Node("Left Leg"),
        Node("Left Foot"),
        Node("Right Thigh"),
        Node("Right Leg"),
        Node("Right Foot")
};

/// <summary>
/// Makes the connections between each body part node to 
/// represent the robot as a Tree data structure
/// </summary>
void buildTree() {
    // Set up the Tree data structure
    for (int i = 0; i < 16; i++) {
        // Get the next body part in the array
        string currBodyPart = bodyParts[i].getBodyPartName();

        // Create a variable to store the current body part's enum class 
        // type when determining what the current body part is
        BodyParts bodyPartType;

        if (currBodyPart == "Head") {
            // Has no child body parts
        }
        else if (currBodyPart == "Neck") {
            // Assign the neck's center node
            // Set the body part type to HEAD (The neck's center node)
            bodyPartType = BodyParts::HEAD;

            // Get the integer associated with the head
            int headValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[headValue]);
        }
        else if (currBodyPart == "Upper Body") {
            // Assign the upper body's left, center, and right nodes
            // Set the body part type to RIGHT_ARM (The upper body's
            // left node)
            bodyPartType = BodyParts::RIGHT_ARM;

            // Get the integer associated with the right arm
            int rightArmValue = static_cast<int>(bodyPartType);

            // Set the left node
            bodyParts[i].setLeftNode(bodyParts[rightArmValue]);

            // Do the same for the center node
            bodyPartType = BodyParts::NECK;
            int neckValue = static_cast<int>(bodyPartType);
            bodyParts[i].setCenterNode(bodyParts[neckValue]);

            // Do the same for the right node
            bodyPartType = BodyParts::LEFT_ARM;
            int leftArmValue = static_cast<int>(bodyPartType);
            bodyParts[i].setRightNode(bodyParts[leftArmValue]);
        }
        else if (currBodyPart == "Left Arm") {
            // Assign the left arm's center node
            // Set the body part type to LEFT_FOREARM (The left arm's 
            // center node)
            bodyPartType = BodyParts::LEFT_FOREARM;

            // Get the integer associated with the left forearm
            int leftForearmValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[leftForearmValue]);
        }
        else if (currBodyPart == "Left Forearm") {
            // Assign the left forearm's center node
            // Set the body part type to LEFT_HAND (The left forearm's 
            // center node)
            bodyPartType = BodyParts::LEFT_HAND;

            // Get the integer associated with the left hand
            int leftHandValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[leftHandValue]);
        }
        else if (currBodyPart == "Left Hand") {
            // Has no child body parts
        }
        else if (currBodyPart == "Right Arm") {
            // Assign the right arm's center node
            // Set the body part type to RIGHT_FOREARM (The right arm's 
            // center node)
            bodyPartType = BodyParts::RIGHT_FOREARM;

            // Get the integer associated with the right forearm
            int rightForearmValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[rightForearmValue]);
        }
        else if (currBodyPart == "Right Forearm") {
            // Assign the right forearm's center node
            // Set the body part type to RIGHT_HAND (The right forearm's 
            // center node)
            bodyPartType = BodyParts::RIGHT_HAND;

            // Get the integer associated with the right hand
            int rightHandValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[rightHandValue]);
        }
        else if (currBodyPart == "Right Hand") {
            // Has no child body parts
        }
        else if (currBodyPart == "Lower Body") {
            // Assign the lower body's left, center, and right nodes
            // Set the body part type to RIGHT_THIGH (The lower body's
            // left node)
            bodyPartType = BodyParts::RIGHT_THIGH;

            // Get the integer associated with the right thigh
            int rightThighValue = static_cast<int>(bodyPartType);

            // Set the left node
            bodyParts[i].setLeftNode(bodyParts[rightThighValue]);

            // Do the same for the center node
            bodyPartType = BodyParts::UPPER_BODY;
            int upperBodyValue = static_cast<int>(bodyPartType);
            bodyParts[i].setCenterNode(bodyParts[upperBodyValue]);

            // Do the same for the right node
            bodyPartType = BodyParts::LEFT_THIGH;
            int leftThighValue = static_cast<int>(bodyPartType);
            bodyParts[i].setRightNode(bodyParts[leftThighValue]);
        }
        else if (currBodyPart == "Left Thigh") {
            // Assign the left thigh's center node
            // Set the body part type to LEFT_LEG (The left thigh's 
            // center node)
            bodyPartType = BodyParts::LEFT_LEG;

            // Get the integer associated with the left leg
            int leftLegValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[leftLegValue]);
        }
        else if (currBodyPart == "Left Leg") {
            // Assign the left leg's center node
            // Set the body part type to LEFT_FOOT (The left leg's 
            // center node)
            bodyPartType = BodyParts::LEFT_FOOT;

            // Get the integer associated with the left foot
            int leftFootValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[leftFootValue]);
        }
        else if (currBodyPart == "Left Foot") {
            // Has no child body parts
        }
        else if (currBodyPart == "Right Thigh") {
            // Assign the right thigh's center node
            // Set the body part type to RIGHT_LEG (The right thigh's 
            // center node)
            bodyPartType = BodyParts::RIGHT_LEG;

            // Get the integer associated with the right leg
            int rightLegValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[rightLegValue]);
        }
        else if (currBodyPart == "Right Leg") {
            // Assign the right leg's center node
            // Set the body part type to RIGHT_FOOT (The right leg's 
            // center node)
            bodyPartType = BodyParts::RIGHT_FOOT;

            // Get the integer associated with the right foot
            int rightFootValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[rightFootValue]);
        }
        else if (currBodyPart == "Right Foot") {
            // Has no child body parts
        }
    }
}

void init(void)
{
    // Create the Tree data structure that represents the robot's body
    buildTree();

    for (int i = 0; i < 256; i++) {
        keyStates[i] = false;
    }
    for (int i = 0; i < MAX_NUM_BODY_PARTS; i++) {
        colors[i * 3 + 0] = 0.0f; // red
        colors[i * 3 + 1] = 0.0f; // green
        colors[i * 3 + 2] = 0.0f; // blue

        translations[i * 2 + 0] = 0.0f; // x
        translations[i * 2 + 1] = 0.0f; // y

        rotations[i] = 0.0f;
    }

    buttonState = -1;
}

/// <summary>
/// Draws a rectangle with the four given vertices
/// </summary>
/// <param name="topLeft">The top left vertex of the rectangle</param>
/// <param name="bottomLeft">The bottom left vertex of the rectangle</param>
/// <param name="bottomRight">The bottom right vertex of the rectangle</param>
/// <param name="topRight">The top right vertex of the rectangle</param>
void drawRectangle(vec2 topLeft, vec2 bottomLeft, vec2 bottomRight, vec2 topRight)
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(topLeft.x, topLeft.y);
    glVertex2f(bottomLeft.x, bottomLeft.y);
    glVertex2f(bottomRight.x, bottomRight.y);
    glVertex2f(topRight.x, topRight.y);
    glEnd();
}

/// <summary>
/// Uses the drawRectangle() function to draw the robot as a group
/// of rectangles 
/// </summary>
void drawRobot() {
    // Stores the index of the current body part
    int bid = -1; 

    // Draw the root body part (Lower Body) and push its coordinate system into
    // the ModelView matrix stack two times, once for each child
    bid = 0;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-2.0f, 0.0f), vec2(-2.0f, -2.0f), vec2(2.0f, -2.0f), vec2(2.0f, 0.0f));
    glPushMatrix(); 
    glPushMatrix(); // Push the Lower Body's matrix

    // Draw the Upper Body and push its coordinate system into the ModelView matrix stack three
    // times, once for each child
    bid = 1;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-3.0f, 2.0f), vec2(-3.0f, 0.0f), vec2(3.0f, 0.0f), vec2(3.0f, 2.0f));
    glPushMatrix(); 
    glPushMatrix(); // Push the Upper Body's matrix
    glPushMatrix();

    // Draw the Neck and push its coordinate system into the ModelView matrix stack
    bid = 2;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-0.5f, 3.0f), vec2(-0.5f, 2.0f), vec2(0.5f, 2.0f), vec2(0.5f, 3.0f));
    glPushMatrix(); // Push the Neck's matrix

    // Draw the Head
    bid = 3;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-1.0f, 5.0f), vec2(-1.0f, 3.0f), vec2(1.0f, 3.0f), vec2(1.0f, 5.0f));
    
    glPopMatrix(); // Pop the Neck's matrix
    glPopMatrix(); // Pop the Upper Body's matrix

    // Draw the Left Arm and push its coordinate system into the ModelView matrix stack
    bid = 4;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(3.0f, 2.0f), vec2(3.0f, 1.0f), vec2(5.0f, 1.0f), vec2(5.0f, 2.0f));
    glPushMatrix(); // Push the Left Arm's matrix

    // Draw the Left Forearm and push its coordinate system into the ModelView matrix stack
    bid = 5;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(5.0f, 2.0f), vec2(5.0f, 1.0f), vec2(7.0f, 1.0f), vec2(7.0f, 2.0f));
    glPushMatrix(); // Push the Left Forearm's matrix

    // Draw the Left Hand
    bid = 6;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(7.0f, 2.5f), vec2(7.0f, 0.5f), vec2(9.0f, 0.5f), vec2(9.0f, 2.5f));

    glPopMatrix(); // Pop the Left Forearm's matrix
    glPopMatrix(); // Pop the Left Arm's matrix
    glPopMatrix(); // Pop the Upper Body's matrix

    // Draw the Right Arm and push its coordinate system into the ModelView matrix stack
    bid = 7;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-5.0f, 2.0f), vec2(-5.0f, 1.0f), vec2(-3.0f, 1.0f), vec2(-3.0f, 2.0f));
    glPushMatrix(); // Push the Right Arm's matrix

    // Draw the Right Forearm and push its coordinate system into the ModelView matrix stack
    bid = 8;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-7.0f, 2.0f), vec2(-7.0f, 1.0f), vec2(-5.0f, 1.0f), vec2(-5.0f, 2.0f));
    glPushMatrix(); // Push the Right Forearm's matrix

    // Draw the Right Hand
    bid = 9;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-9.0f, 2.5f), vec2(-9.0f, 0.5f), vec2(-7.0f, 0.5f), vec2(-7.0f, 2.5f));

    glPopMatrix(); // Pop the Right Forearm's matrix
    glPopMatrix(); // Pop the Right Arm's matrix
    glPopMatrix(); // Pop the Upper Body's matrix
    glPopMatrix(); // Pop the Lower Body's matrix

    // Draw the Left Thigh and push its coordinate system into the ModelView matrix stack
    bid = 10;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(0.5f, -2.0f), vec2(0.5f, -5.0f), vec2(2.0f, -5.0f), vec2(2.0f, -2.0f));
    glPushMatrix(); // Push the Left Thigh's matrix

    // Draw the Left Leg and push its coordinate system into the ModelView matrix stack
    bid = 11;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(0.5f, -5.0f), vec2(0.5f, -8.0f), vec2(2.0f, -8.0f), vec2(2.0f, -5.0f));
    glPushMatrix(); // Push the Left Leg's matrix

    // Draw the Left Foot
    bid = 12;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(0.5f, -8.0f), vec2(0.5f, -9.0f), vec2(3.5f, -9.0f), vec2(3.5f, -8.0f));

    glPopMatrix(); // Pop the Left Leg's matrix
    glPopMatrix(); // Pop the Left Thigh's matrix
    glPopMatrix(); // Pop the Lower Body's matrix

    // Draw the Right Thigh and push its coordinate system into the ModelView matrix stack
    bid = 13;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-2.0f, -2.0f), vec2(-2.0f, -5.0f), vec2(-0.5f, -5.0f), vec2(-0.5f, -2.0f));
    glPushMatrix(); // Push the Right Thigh's matrix

    // Draw the Right Leg and push its coordinate system into the ModelView matrix stack
    bid = 14;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-2.0f, -5.0f), vec2(-2.0f, -8.0f), vec2(-0.5f, -8.0f), vec2(-0.5f, -5.0f));
    glPushMatrix(); // Push the Right Leg's matrix

    // Draw the Right Foot
    bid = 15;
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-3.5f, -8.0f), vec2(-3.5f, -9.0f), vec2(-0.5f, -9.0f), vec2(-0.5f, -8.0f));
    
    glPopMatrix(); // Pop the Right Leg's matrix
    glPopMatrix(); // Pop the Right Thigh's matrix
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the robot
    drawRobot();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    win_width = w;
    win_height = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-canvas_width / 2.0f, canvas_width / 2.0f, -canvas_height / 2.0f, canvas_height / 2.0f);
    glViewport(0, 0, (GLsizei)win_width, (GLsizei)win_height);

    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) // 'esc' key
        exit(0);

    unsigned char asciiOffset = 49; // see an ascii table
    for (unsigned char i = '1'; i < '7'; i++) {
        if (key == i) {
            keyStates[i] = true;
            colors[(i - asciiOffset) * 3 + 0] = 1.0f;
            colors[(i - asciiOffset) * 3 + 1] = 0.0f;
            colors[(i - asciiOffset) * 3 + 2] = 0.0f;
        }
    }
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
    unsigned char asciiOffset = 49; // see an ascii table
    for (unsigned char i = '1'; i < '7'; i++) {
        if (key == i) {
            keyStates[i] = false;
            colors[(i - asciiOffset) * 3 + 0] = 0.0f;
            colors[(i - asciiOffset) * 3 + 1] = 0.0f;
            colors[(i - asciiOffset) * 3 + 2] = 0.0f;
        }
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
        buttonState = button;
        curMouse[0] = ((float)x / win_width - 0.5f) * canvas_width;
        curMouse[1] = ((float)(win_height - y) - 0.5f) / win_height * canvas_height;
        preMouse[0] = ((float)x / win_width - 0.5f) * canvas_width;
        preMouse[1] = ((float)(win_height - y) - 0.5f) / win_height * canvas_height;
    }
    else if (state == GLUT_UP)
        button = -1;
}

void motion(int x, int y)
{
    unsigned char asciiOffset = 49; // see an ascii table

    curMouse[0] = ((float)x / win_width - 0.5f) * canvas_width;
    curMouse[1] = ((float)(win_height - y) - 0.5f) / win_height * canvas_height;

    if (buttonState == GLUT_LEFT_BUTTON) {
        for (unsigned char i = '1'; i < '7'; i++) {
            if (keyStates[i]) {
                translations[(i - asciiOffset) * 2 + 0] += curMouse[0] - preMouse[0];
                translations[(i - asciiOffset) * 2 + 1] += curMouse[1] - preMouse[1];
            }
        }
        glutPostRedisplay();
    }

    else if (buttonState == GLUT_RIGHT_BUTTON) {
        for (unsigned char i = '1'; i < '7'; i++) {
            if (keyStates[i]) {
                rotations[i - asciiOffset] += curMouse[0] - preMouse[0];
            }
        }
        glutPostRedisplay();
    }

    preMouse[0] = curMouse[0];
    preMouse[1] = curMouse[1];

}

int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("2D Transformation Tree");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;

}