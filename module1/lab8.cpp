#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

//-----------------------------------------------------------
// COLOR DEFINITIONS
//-----------------------------------------------------------
GLfloat houseColor[3] = { 206.0f / 255.0f, 237.0f / 255.0f, 104.0f / 255.0f };
GLfloat treeColor[3] = { 36.0f / 255.0f, 120.0f / 255.0f, 42.0f / 255.0f };
GLfloat treeTrunkColor[3] = { 20.0f / 255.0f, 74.0f / 255.0f, 24.0f / 255.0f };

//-----------------------------------------------------------
// ANIMATION VARIABLES
//-----------------------------------------------------------
GLfloat treeX = 0.0f;   // Tree horizontal movement
float cloudX = -1.0f;  // Cloud movement along x-axis

//-----------------------------------------------------------
// Helper Function: Draw vertex array using VBO
// Parameters:
//   verts - pointer to vertex coordinate array
//   count - number of vertices
//   mode  - OpenGL primitive type (e.g., GL_QUADS, GL_LINES)
// Description:
//   Creates a temporary VBO, uploads vertex data, and draws.
//-----------------------------------------------------------
void drawVBO2f(const GLfloat* verts, int count, GLenum mode) {
    GLuint vbo;
    glGenBuffers(1, &vbo); // Create buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * count * 2, verts, GL_STATIC_DRAW);

    // Enable vertex attribute 0 (position)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Draw geometry
    glDrawArrays(mode, 0, count);

    // Cleanup
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vbo);
}

//-----------------------------------------------------------
// Draw roadway lines using VBOs
//-----------------------------------------------------------
void roadways() {
    // Top solid line
    GLfloat topLine[] = { -1.0f, -0.6f, 1.0f, -0.6f };
    glLineWidth(2.0f);
    glColor3ub(0, 0, 0);
    drawVBO2f(topLine, 2, GL_LINES);

    // Middle dashed line
    GLfloat brokenLine[] = { -1.0f, -0.7f, 1.0f, -0.7f };
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x00FF);
    glLineWidth(2.0f);
    glColor3ub(0, 0, 0);
    drawVBO2f(brokenLine, 2, GL_LINES);
    glDisable(GL_LINE_STIPPLE);

    // Bottom solid line
    GLfloat bottomLine[] = { -1.0f, -0.8f, 1.0f, -0.8f };
    glLineWidth(2.0f);
    glColor3ub(0, 0, 0);
    drawVBO2f(bottomLine, 2, GL_LINES);
}

//-----------------------------------------------------------
// Draw black door rectangle
//-----------------------------------------------------------
void emptyDoor() {
    GLfloat doorVerts[] = {
        -0.05f, -0.55f,
         0.05f, -0.55f,
         0.05f, -0.3f,
        -0.05f, -0.3f
    };
    glColor3ub(0, 0, 0);
    drawVBO2f(doorVerts, 4, GL_QUADS);
}

//-----------------------------------------------------------
// Draw house body and roof
//-----------------------------------------------------------
void house() {
    // House body (rectangle)
    GLfloat bodyVerts[] = {
        -0.4f, -0.55f,
         0.4f, -0.55f,
         0.4f, -0.13f,
        -0.4f, -0.13f
    };
    glColor3f(houseColor[0], houseColor[1], houseColor[2]);
    drawVBO2f(bodyVerts, 4, GL_QUADS);

    // Roof (Quads)
    GLfloat roofVerts[] = {
        -0.4f, -0.05f,
         0.4f, -0.05f,
         0.5f, -0.2f,
        -0.5f, -0.2f
    };
    glColor3ub(255, 0, 0);
    drawVBO2f(roofVerts, 4, GL_QUADS);
}

//-----------------------------------------------------------
// Draw tree (trunk + leaves) using VBOs
//-----------------------------------------------------------
void weirdTree() {
    glPushMatrix();
    glTranslatef(treeX, 0.0f, 0.0f); // Move tree left/right

    // Trunk
    GLfloat trunkVerts[] = {
         0.8f, -0.55f,
         0.7f, -0.55f,
         0.7f, -0.1f,
         0.8f, -0.1f
    };
    glColor3f(treeTrunkColor[0], treeTrunkColor[1], treeTrunkColor[2]);
    drawVBO2f(trunkVerts, 4, GL_QUADS);

    // Leaves (fan shape)
    GLfloat leafVerts[] = {
        0.75f, -0.1f,
        0.85f, -0.1f,
        0.9f,  0.0f,
        0.75f, 0.1f,
        0.6f,  0.0f,
        0.65f, -0.1f
    };
    glColor3f(treeColor[0], treeColor[1], treeColor[2]);
    drawVBO2f(leafVerts, 6, GL_TRIANGLE_FAN);

    glPopMatrix();
}

//-----------------------------------------------------------
// Draw circular fan (used for clouds)
// Parameters:
//   cx, cy  - circle center
//   radius  - radius of circle
//   segments - how many sides (smoothness)
//-----------------------------------------------------------
void drawCircleFan(GLfloat cx, GLfloat cy, GLfloat radius, int segments = 8) {
    vector<GLfloat> verts;
    verts.reserve((segments + 2) * 2);

    // Center vertex
    verts.push_back(cx);
    verts.push_back(cy);

    // Circle points
    for (int i = 0; i <= segments; ++i) {
        float ang = (float)i * (3.14159265f * 2.0f) / (float)segments;
        verts.push_back(cx + cosf(ang) * radius);
        verts.push_back(cy + sinf(ang) * radius);
    }

    glColor3f(0.529f, 0.808f, 0.922f); // Light blue cloud color
    drawVBO2f(verts.data(), segments + 2, GL_TRIANGLE_FAN);
}

//-----------------------------------------------------------
// Draw a group of circular fans as clouds
//-----------------------------------------------------------
void cloud() {
    GLfloat cx = -0.6f + cloudX;
    GLfloat cy = 0.6f;
    GLfloat radius = 0.1f;

    for (int i = 0; i < 5; ++i) {
        GLfloat offset = i * 0.1f;
        drawCircleFan(cx + offset, cy, radius, 8);
    }
}

//-----------------------------------------------------------
// Mouse callback - change colors when clicking
// Left Click  → Change house color
// Right Click → Change tree color and trunk color
//-----------------------------------------------------------
void colorChangeMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            houseColor[0] = 1.0f;  // Pink
            houseColor[1] = 0.4117f;
            houseColor[2] = 0.7059f;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            treeColor[0] = 0.0f;  // Blue leaves
            treeColor[1] = 0.0f;
            treeColor[2] = 1.0f;

            treeTrunkColor[0] = 1.0f;  // Yellow trunk
            treeTrunkColor[1] = 1.0f;
            treeTrunkColor[2] = 0.0f;
        }
        glutPostRedisplay();
    }
}

//-----------------------------------------------------------
// Keyboard callback (arrow keys)
// Left/Right → Move tree
//-----------------------------------------------------------
void rollingTree(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT)  
        treeX -= 0.05f;
    if (key == GLUT_KEY_RIGHT) 
        treeX += 0.05f;
    glutPostRedisplay();
}

//-----------------------------------------------------------
// Timer callback
// Moves clouds and resets when off-screen
//-----------------------------------------------------------
void cloudDrifting(int value) {
    cloudX += 0.03f;
    if (cloudX > 1.5f) 
        cloudX = -1.5f;

    glutPostRedisplay();
    glutTimerFunc(40, cloudDrifting, 0); // Schedule again
}

//-----------------------------------------------------------
// Display callback
// Clears screen and draws all scene objects
//-----------------------------------------------------------
void lab6() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    cloud();
    weirdTree();
    house();
    roadways();
    emptyDoor();

    glFlush();
}

//-----------------------------------------------------------
// Main Function
// Initializes GLUT and registers callbacks
//-----------------------------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(120, 120);
    glutCreateWindow("GL VBO Version - DelRosario");

    glewInit(); // Initialize GLEW before using modern GL

    // Register callbacks
    glutDisplayFunc(lab6);
    glutMouseFunc(colorChangeMouse);
    glutSpecialFunc(rollingTree);
    glutTimerFunc(40, cloudDrifting, 0);

    glutMainLoop(); // Start event loop
    return 0;
}
