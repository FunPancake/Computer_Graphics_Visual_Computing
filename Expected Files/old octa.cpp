#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

void display();
void initOpenGL();
void reshape(int width, int height);
void timer(int value);

float rotationAngleY = 0.0f;

GLfloat vertices[][3] = {
    {  0.0f,  1.0f,  0.0f }, // 0
    {  0.0f, -1.0f,  0.0f }, // 1
    { -1.0f,  0.0f,  0.0f }, // 2
    {  1.0f,  0.0f,  0.0f }, // 3
    {  0.0f,  0.0f,  1.0f }, // 4
    {  0.0f,  0.0f, -1.0f }  // 5
};

GLuint triangleFaces[][3] = {
    { 0, 2, 4 }, { 0, 4, 3 }, { 0, 3, 5 }, { 0, 5, 2 },
    { 1, 4, 2 }, { 1, 3, 4 }, { 1, 5, 3 }, { 1, 2, 5 }
};

GLfloat colors[][3] = {
    { 0.4509f, 0.4156f, 0.3098f }, { 0.9098f, 0.8784f, 0.2823f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f }, { 0.4509f, 0.4156f, 0.3098f }, { 0.9098f, 0.8784f, 0.2823f }, { 1.0f, 0.0f, 0.0f }
};

GLuint lineIndices[][2] = {
    { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0, 5 },
    { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 },
    { 2, 4 }, { 3, 4 }, { 3, 5 }, { 2, 5 }
};

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("202020018: Del Rosario, Ian Lindley H.");

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cerr << "GLEW initialization failed: " << glewGetErrorString(err) << endl;
        return -1;
    }

    initOpenGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, timer, 0);
    glutMainLoop();

    return 0;
}

void initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    
}

void timer(int value) {
    rotationAngleY += 0.7f; // rotation speed
    if (rotationAngleY >= 360.0f) rotationAngleY -= 360.0f;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -3.5f);
    glRotatef(rotationAngleY, 1.0f, 1.0f, -1.0f); // rotation direction

    // Draw triangles with solid colors
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 8; i++) {
        glColor3fv(colors[i]); // Set a solid color for the entire triangle
        glVertex3fv(vertices[triangleFaces[i][0]]);
        glVertex3fv(vertices[triangleFaces[i][1]]);
        glVertex3fv(vertices[triangleFaces[i][2]]);
    }
    glEnd();

    // Draw wireframe lines with black color
    glColor3f(0.0f, 0.0f, 0.0f); // Set color for the lines
    glBegin(GL_LINES);
    for (int i = 0; i < 12; i++) {
        glVertex3fv(vertices[lineIndices[i][0]]);
        glVertex3fv(vertices[lineIndices[i][1]]);
    }
    glEnd();

	gluLookAt(0.0,0.0,-1.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
	
    glutSwapBuffers();
}


void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 800 / 600, 1.0f, 10.0f);
    glMatrixMode(GL_MODELVIEW);
    
}

