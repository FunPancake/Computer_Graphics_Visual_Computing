#include <GL/glut.h>
#include <cmath>
#include <vector>

using namespace std;

GLfloat houseColor[3] = { 206.0f / 255.0f, 237.0f / 255.0f, 104.0f / 255.0f };
GLfloat treeColor[3] = { 36.0f / 255.0f, 120.0f / 255.0f, 42.0f / 255.0f };
GLfloat treeTrunkColor[3] = { 20.0f / 255.0f, 74.0f / 255.0f, 24.0f / 255.0f };

GLfloat treeX = 0.0f;
float cloudX = -1.0f;

static void drawVertexArray2f(const GLfloat* verts, int count, GLenum mode) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, verts);
    glDrawArrays(mode, 0, count);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void roadways() {
    GLfloat topLine[] = { 
        -1.0f, -0.6f,  
        1.0f, -0.6f 
    };

    glLineWidth(2.0f);
    glColor3ub(0, 0, 0);
    drawVertexArray2f(topLine, 2, GL_LINES);

    GLfloat brokenLine[] = { 
        -1.0f, -0.7f,  
        1.0f, -0.7f 
    };

    glEnable(GL_LINE_STIPPLE);
    glLineWidth(2.0f);
    glLineStipple(2, 0x00FF);
    glColor3ub(0, 0, 0);
    drawVertexArray2f(brokenLine, 2, GL_LINES);
    glDisable(GL_LINE_STIPPLE);

    GLfloat bottomLine[] = { 
        -1.0f, -0.8f,  
        1.0f, -0.8f 
    };

    glLineWidth(2.0f);
    glColor3ub(0, 0, 0);
    drawVertexArray2f(bottomLine, 2, GL_LINES);
}

void emptyDoor() {
    GLfloat doorVerts[] = {
        -0.05f, -0.55f,
         0.05f, -0.55f,
         0.05f, -0.3f,
        -0.05f, -0.3f
    };
    glColor3ub(0, 0, 0);
    drawVertexArray2f(doorVerts, 4, GL_QUADS);
}

void house() {
    GLfloat bodyVerts[] = {
        -0.4f, -0.55f,
         0.4f, -0.55f,
         0.4f, -0.13f,
        -0.4f, -0.13f
    };
    glColor3f(houseColor[0], houseColor[1], houseColor[2]);
    drawVertexArray2f(bodyVerts, 4, GL_QUADS);

    GLfloat roofVerts[] = {
        -0.4f, -0.05f,
         0.4f, -0.05f,
         0.5f, -0.2f,
        -0.5f, -0.2f
    };
    glColor3ub(255, 0, 0);
    drawVertexArray2f(roofVerts, 4, GL_QUADS);
}

void weirdTree() {
    glPushMatrix();
    glTranslatef(treeX, 0.0f, 0.0f);

    GLfloat trunkVerts[] = {
         0.8f, -0.55f,
         0.7f, -0.55f,
         0.7f, -0.1f,
         0.8f, -0.1f
    };
    glColor3f(treeTrunkColor[0], treeTrunkColor[1], treeTrunkColor[2]);
    drawVertexArray2f(trunkVerts, 4, GL_QUADS);

    GLfloat leafVerts[] = {
        0.75f, -0.1f,
        0.85f, -0.1f,
        0.9f,  0.0f,
        0.75f, 0.1f,
        0.6f,  0.0f,
        0.65f, -0.1f
    };
    glColor3f(treeColor[0], treeColor[1], treeColor[2]);
    drawVertexArray2f(leafVerts, 6, GL_TRIANGLE_FAN);

    glPopMatrix();
}

void drawCircleFan(GLfloat cx, GLfloat cy, GLfloat radius, int segments = 8) {
    vector<GLfloat> verts;
    verts.reserve((segments + 1) * 2);

    verts.push_back(cx);
    verts.push_back(cy);

    for (int i = 0; i <= segments; ++i) {
        float ang = (float)i * (3.14159265f * 2.0f) / (float)segments;
        verts.push_back(cx + cosf(ang) * radius);
        verts.push_back(cy + sinf(ang) * radius);
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, verts.data());
    glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)(segments + 2)); 
    glDisableClientState(GL_VERTEX_ARRAY);
}

void cloud() {
    GLfloat cx = -0.6f + cloudX;
    GLfloat cy = 0.6f;
    GLfloat radius = 0.1f;

    glColor3f(0.529f, 0.808f, 0.922f);
    for (int i = 0; i < 5; ++i) {
        GLfloat offset = i * 0.1f;
        drawCircleFan(cx + offset, cy, radius, 8);
    }
}

void colorChangeMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            houseColor[0] = 1.0f;
            houseColor[1] = 0.4117f;
            houseColor[2] = 0.7059f;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            treeColor[0] = 0.0f;
            treeColor[1] = 0.0f;
            treeColor[2] = 1.0f;
            treeTrunkColor[0] = 1.0f;
            treeTrunkColor[1] = 1.0f;
            treeTrunkColor[2] = 0.0f;
        }
        glutPostRedisplay();
    }
}

void rollingTree(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        treeX -= 0.05f;
        break;
    case GLUT_KEY_RIGHT:
        treeX += 0.05f;
        break;
    }
    glutPostRedisplay();
}

void cloudDrifting(int value) {
    cloudX += 0.03f;
    if (cloudX > 1.5f) cloudX = -1.5f;
    glutPostRedisplay();
    glutTimerFunc(40, cloudDrifting, 0);
}

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

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(120, 120);
    glutCreateWindow("GL Vertex Arrays - DelRosario");

    glutDisplayFunc(lab6);
    glutMouseFunc(colorChangeMouse);
    glutSpecialFunc(rollingTree);
    glutTimerFunc(40, cloudDrifting, 0);

    glutMainLoop();
    return 0;
}
