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
#include <stack>
#include "Node.h"
using namespace std;
using namespace glm;

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

// The current selected body part
BodyParts currSelectedBodyPart;

// Stores the history of selected nodes to access the parent
// of the currently selected node as it changes
stack<Node*> parentHistory;

// The array of all body parts
Node bodyParts[] = {
        Node(BodyParts::HEAD),
        Node(BodyParts::NECK),
        Node(BodyParts::UPPER_BODY),
        Node(BodyParts::LEFT_ARM),
        Node(BodyParts::LEFT_FOREARM),
        Node(BodyParts::LEFT_HAND),
        Node(BodyParts::RIGHT_ARM),
        Node(BodyParts::RIGHT_FOREARM),
        Node(BodyParts::RIGHT_HAND),
        Node(BodyParts::LOWER_BODY),
        Node(BodyParts::LEFT_THIGH),
        Node(BodyParts::LEFT_LEG),
        Node(BodyParts::LEFT_FOOT),
        Node(BodyParts::RIGHT_THIGH),
        Node(BodyParts::RIGHT_LEG),
        Node(BodyParts::RIGHT_FOOT)
};

/// <summary>
/// Makes the connections between each body part node to 
/// represent the robot as a Tree data structure
/// </summary>
void buildTree() {
    // Set up the Tree data structure
    for (int i = 0; i < 16; i++) {
        // Get the next body part in the array
        BodyParts currBodyPart = bodyParts[i].getNodeBodyPart();

        // Create a variable to store the current body part's enum class 
        // type when determining what the current body part is
        BodyParts bodyPartType;

        if (currBodyPart == BodyParts::HEAD) {
            // Has no child body parts
        }
        else if (currBodyPart == BodyParts::NECK) {
            // Assign the neck's center node
            // Set the body part type to HEAD (The neck's center node)
            bodyPartType = BodyParts::HEAD;

            // Get the integer associated with the head
            int headValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[headValue]);
        }
        else if (currBodyPart == BodyParts::UPPER_BODY) {
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
        else if (currBodyPart == BodyParts::LEFT_ARM) {
            // Assign the left arm's center node
            // Set the body part type to LEFT_FOREARM (The left arm's 
            // center node)
            bodyPartType = BodyParts::LEFT_FOREARM;

            // Get the integer associated with the left forearm
            int leftForearmValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[leftForearmValue]);
        }
        else if (currBodyPart == BodyParts::LEFT_FOREARM) {
            // Assign the left forearm's center node
            // Set the body part type to LEFT_HAND (The left forearm's 
            // center node)
            bodyPartType = BodyParts::LEFT_HAND;

            // Get the integer associated with the left hand
            int leftHandValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[leftHandValue]);
        }
        else if (currBodyPart == BodyParts::LEFT_HAND) {
            // Has no child body parts
        }
        else if (currBodyPart == BodyParts::RIGHT_ARM) {
            // Assign the right arm's center node
            // Set the body part type to RIGHT_FOREARM (The right arm's 
            // center node)
            bodyPartType = BodyParts::RIGHT_FOREARM;

            // Get the integer associated with the right forearm
            int rightForearmValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[rightForearmValue]);
        }
        else if (currBodyPart == BodyParts::RIGHT_FOREARM) {
            // Assign the right forearm's center node
            // Set the body part type to RIGHT_HAND (The right forearm's 
            // center node)
            bodyPartType = BodyParts::RIGHT_HAND;

            // Get the integer associated with the right hand
            int rightHandValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[rightHandValue]);
        }
        else if (currBodyPart == BodyParts::RIGHT_HAND) {
            // Has no child body parts
        }
        else if (currBodyPart == BodyParts::LOWER_BODY) {
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
        else if (currBodyPart == BodyParts::LEFT_THIGH) {
            // Assign the left thigh's center node
            // Set the body part type to LEFT_LEG (The left thigh's 
            // center node)
            bodyPartType = BodyParts::LEFT_LEG;

            // Get the integer associated with the left leg
            int leftLegValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[leftLegValue]);
        }
        else if (currBodyPart == BodyParts::LEFT_LEG) {
            // Assign the left leg's center node
            // Set the body part type to LEFT_FOOT (The left leg's 
            // center node)
            bodyPartType = BodyParts::LEFT_FOOT;

            // Get the integer associated with the left foot
            int leftFootValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[leftFootValue]);
        }
        else if (currBodyPart == BodyParts::LEFT_FOOT) {
            // Has no child body parts
        }
        else if (currBodyPart == BodyParts::RIGHT_THIGH) {
            // Assign the right thigh's center node
            // Set the body part type to RIGHT_LEG (The right thigh's 
            // center node)
            bodyPartType = BodyParts::RIGHT_LEG;

            // Get the integer associated with the right leg
            int rightLegValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[rightLegValue]);
        }
        else if (currBodyPart == BodyParts::RIGHT_LEG) {
            // Assign the right leg's center node
            // Set the body part type to RIGHT_FOOT (The right leg's 
            // center node)
            bodyPartType = BodyParts::RIGHT_FOOT;

            // Get the integer associated with the right foot
            int rightFootValue = static_cast<int>(bodyPartType);

            // Set the center node
            bodyParts[i].setCenterNode(bodyParts[rightFootValue]);
        }
        else if (currBodyPart == BodyParts::RIGHT_FOOT) {
            // Has no child body parts
        }
    }
}

void init(void)
{
    // Create the Tree data structure that represents the robot's body
    buildTree();

    // The program starts with the Lower Body selected
    currSelectedBodyPart = BodyParts::LOWER_BODY;

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
    bid = static_cast<int>(BodyParts::LOWER_BODY);
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1] - 2.0f, 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-2.0f, 2.0f), vec2(-2.0f, 0.0f), vec2(2.0f, 0.0f), vec2(2.0f, 2.0f));
    glPushMatrix(); 
    glPushMatrix(); // Push the Lower Body's matrix

    // Draw the Upper Body and push its coordinate system into the ModelView matrix stack three
    // times, once for each child
    bid = static_cast<int>(BodyParts::UPPER_BODY);
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1] + 2.0f, 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-3.0f, 2.0f), vec2(-3.0f, 0.0f), vec2(3.0f, 0.0f), vec2(3.0f, 2.0f));
    glPushMatrix(); 
    glPushMatrix(); // Push the Upper Body's matrix
    glPushMatrix();

    // Draw the Neck and push its coordinate system into the ModelView matrix stack
    bid = static_cast<int>(BodyParts::NECK);
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1] + 2.0f, 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-0.5f, 1.0f), vec2(-0.5f, 0.0f), vec2(0.5f, 0.0f), vec2(0.5f, 1.0f));
    glPushMatrix(); // Push the Neck's matrix

    // Draw the Head
    bid = static_cast<int>(BodyParts::HEAD);
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1] + 1.0f, 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-1.0f, 2.0f), vec2(-1.0f, 0.0f), vec2(1.0f, 0.0f), vec2(1.0f, 2.0f));
    
    glPopMatrix(); // Pop the Neck's matrix
    glPopMatrix(); // Pop the Upper Body's matrix

    // Draw the Left Arm and push its coordinate system into the ModelView matrix stack
    bid = static_cast<int>(BodyParts::LEFT_ARM);
    glTranslatef(translations[bid * 2 + 0] + 3.0f, translations[bid * 2 + 1] + 1.5f, 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(0.0f, 0.5f), vec2(0.0f, -0.5f), vec2(2.0f, -0.5f), vec2(2.0f, 0.5f));
    glPushMatrix(); // Push the Left Arm's matrix

    // Draw the Left Forearm and push its coordinate system into the ModelView matrix stack
    bid = static_cast<int>(BodyParts::LEFT_FOREARM);
    glTranslatef(translations[bid * 2 + 0] + 2.0f, translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(0.0f, 0.5f), vec2(0.0f, -0.5f), vec2(2.0f, -0.5f), vec2(2.0f, 0.5f));
    glPushMatrix(); // Push the Left Forearm's matrix

    // Draw the Left Hand
    bid = static_cast<int>(BodyParts::LEFT_HAND);
    glTranslatef(translations[bid * 2 + 0] + 2.0f, translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(0.0f, 1.0f), vec2(0.0f, -1.0f), vec2(2.0f, -1.0f), vec2(2.0f, 1.0f));

    glPopMatrix(); // Pop the Left Forearm's matrix
    glPopMatrix(); // Pop the Left Arm's matrix
    glPopMatrix(); // Pop the Upper Body's matrix

    // Draw the Right Arm and push its coordinate system into the ModelView matrix stack
    bid = static_cast<int>(BodyParts::RIGHT_ARM);
    glTranslatef(translations[bid * 2 + 0] - 3.0f, translations[bid * 2 + 1] + 1.5f, 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-2.0f, 0.5f), vec2(-2.0f, -0.5f), vec2(0.0f, -0.5f), vec2(0.0f, 0.5f));
    glPushMatrix(); // Push the Right Arm's matrix

    // Draw the Right Forearm and push its coordinate system into the ModelView matrix stack
    bid = static_cast<int>(BodyParts::RIGHT_FOREARM);
    glTranslatef(translations[bid * 2 + 0] - 2.0f, translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-2.0f, 0.5f), vec2(-2.0f, -0.5f), vec2(0.0f, -0.5f), vec2(0.0f, 0.5f));
    glPushMatrix(); // Push the Right Forearm's matrix

    // Draw the Right Hand
    bid = static_cast<int>(BodyParts::RIGHT_HAND);
    glTranslatef(translations[bid * 2 + 0] - 2.0f, translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-2.0f, 1.0f), vec2(-2.0f, -1.0f), vec2(0.0f, -1.0f), vec2(0.0f, 1.0f));

    glPopMatrix(); // Pop the Right Forearm's matrix
    glPopMatrix(); // Pop the Right Arm's matrix
    glPopMatrix(); // Pop the Upper Body's matrix
    glPopMatrix(); // Pop the Lower Body's matrix

    // Draw the Left Thigh and push its coordinate system into the ModelView matrix stack
    bid = static_cast<int>(BodyParts::LEFT_THIGH);
    glTranslatef(translations[bid * 2 + 0] + 1.25f, translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-0.75f, 0.0f), vec2(-0.75f, -3.0f), vec2(0.75f, -3.0f), vec2(0.75f, 0.0f));
    glPushMatrix(); // Push the Left Thigh's matrix

    // Draw the Left Leg and push its coordinate system into the ModelView matrix stack
    bid = static_cast<int>(BodyParts::LEFT_LEG);
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1] - 3.0f, 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-0.75f, 0.0f), vec2(-0.75f, -3.0f), vec2(0.75f, -3.0f), vec2(0.75f, 0.0f));
    glPushMatrix(); // Push the Left Leg's matrix

    // Draw the Left Foot
    bid = static_cast<int>(BodyParts::LEFT_FOOT);
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1] - 3.0f, 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-0.75f, 0.0f), vec2(-0.75f, -1.0f), vec2(2.75f, -1.0f), vec2(2.75f, 0.0f));

    glPopMatrix(); // Pop the Left Leg's matrix
    glPopMatrix(); // Pop the Left Thigh's matrix
    glPopMatrix(); // Pop the Lower Body's matrix

    // Draw the Right Thigh and push its coordinate system into the ModelView matrix stack
    bid = static_cast<int>(BodyParts::RIGHT_THIGH);
    glTranslatef(translations[bid * 2 + 0] - 1.25f, translations[bid * 2 + 1], 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-0.75f, 0.0f), vec2(-0.75f, -3.0f), vec2(0.75f, -3.0f), vec2(0.75f, 0.0f));
    glPushMatrix(); // Push the Right Thigh's matrix

    // Draw the Right Leg and push its coordinate system into the ModelView matrix stack
    bid = static_cast<int>(BodyParts::RIGHT_LEG);
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1] - 3.0f, 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-0.75f, 0.0f), vec2(-0.75f, -3.0f), vec2(0.75f, -3.0f), vec2(0.75f, 0.0f));
    glPushMatrix(); // Push the Right Leg's matrix

    // Draw the Right Foot
    bid = static_cast<int>(BodyParts::RIGHT_FOOT);
    glTranslatef(translations[bid * 2 + 0], translations[bid * 2 + 1] - 3.0f, 0.0f);
    glRotatef(rotations[bid], 0.0f, 0.0f, 1.0f);
    drawRectangle(vec2(-2.75f, 0.0f), vec2(-2.75f, -1.0f), vec2(0.75f, -1.0f), vec2(0.75f, 0.0f));
    
    glPopMatrix(); // Pop the Right Leg's matrix
    glPopMatrix(); // Pop the Right Thigh's matrix
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the color of the currently selected body part's polygon to show the
    // user which body part they have selected
    colors[(static_cast<int>(currSelectedBodyPart)) * 3 + 0] = 1.0f;
    colors[(static_cast<int>(currSelectedBodyPart)) * 3 + 1] = 0.0f;
    colors[(static_cast<int>(currSelectedBodyPart)) * 3 + 2] = 0.0f;

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

    // If the user presses the 's' key, select the current body part's center
    // child node
    if (key == 115) {
        // Indicate that the 's' key was pressed
        keyStates['s'] = true;
        
        // Get the Node of the current body part
        Node* current = &(bodyParts[static_cast<int>(currSelectedBodyPart)]);

        // If the Node of the currently selected body part has a center child,
        // set the currently selected body part to that child
        if (current->getCenterNode() != nullptr) {
            // Push the Node of the current body part into the parent stack
            parentHistory.push(current);

            currSelectedBodyPart = current->getCenterNode()->getNodeBodyPart();
        }
    }

    // If the user presses the 'w' key, select the parent node of the current
    // body part
    if (key == 119) {
        // Indicate that the 'w' key was pressed
        keyStates['w'] = true;

        // Set the currently selected body part to the parent of the current
        // body part, only if the parent stack is not empty
        if (!parentHistory.empty()) {
            // Get the correct parent node from the stack
            Node* current = parentHistory.top();

            // Pop the correct parent node from the stack
            parentHistory.pop();

            // Set the currently selected body part to that node
            currSelectedBodyPart = current->getNodeBodyPart();
        }
    }

    // If the user presses the 'a' key, select the current body part's left
    // child node
    if (key == 97) {
        // Indicate that the 'a' key was pressed
        keyStates['a'] = true;

        // Get the Node of the current body part
        Node* current = &(bodyParts[static_cast<int>(currSelectedBodyPart)]);

        // If the Node of the currently selected body part has a left child,
        // set the currently selected body part to that child
        if (current->getLeftNode() != nullptr) {
            // Push the Node of the current body part into the parent stack
            parentHistory.push(current);

            currSelectedBodyPart = current->getLeftNode()->getNodeBodyPart();
        }
    }

    // If the user presses the 'd' key, select the current body part's right
    // child node
    if (key == 100) {
        // Indicate that the 'd' key was pressed
        keyStates['d'] = true;

        // Get the Node of the current body part
        Node* current = &(bodyParts[static_cast<int>(currSelectedBodyPart)]);

        // If the Node of the currently selected body part has a right child,
        // set the currently selected body part to that child
        if (current->getRightNode() != nullptr) {
            // Push the Node of the current body part into the parent stack
            parentHistory.push(current);

            currSelectedBodyPart = current->getRightNode()->getNodeBodyPart();
        }
    }

    // Rotate the body part counterclockwise if the 'j' key is pressed
    if (key == 106) {
        // Indicate that the 'j' key was pressed
        keyStates['j'] = true;

        // Rotate the body part
        rotations[static_cast<int>(currSelectedBodyPart)] += 5.0f;
    }

    // Rotate the body part clockwise if the 'l' key is pressed
    if (key == 108) {
        // Indicate that the 'l' key was pressed
        keyStates['l'] = true;

        // Rotate the body part
        rotations[static_cast<int>(currSelectedBodyPart)] -= 5.0f;
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