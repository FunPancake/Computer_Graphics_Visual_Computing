#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

GLuint VBOid, VBOcolor, EBOindices, VBOLineVertices, EBOlineIndices;
float wave = 0.0f, speed = 0.05f;

void display();
void displayPolyone();
void text();
void Timer(int value);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Del Rosario, Ian Lindley");
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cerr << "Error initializing GLEW" << endl;
        return -1;
    }



    glutDisplayFunc(display);
    glutTimerFunc(300, Timer, 0);
    glutMainLoop();
}

void displayPolyone() {
    // Polygon vertices
    GLfloat polygonVertices[] = {
        -0.01f - wave, 0.0f,          // Triangle 1
        -0.4f - wave, 0.0f,
        -0.01f - wave, 0.3f,

        0.01f - wave, 0.0f,           // Triangle 2
        0.4f - wave, 0.0f,
        0.01f - wave, 0.3f,

        -0.5f - wave, -0.05f,         // Polygon (Boat)
        0.5f - wave, -0.05f,
        0.4f - wave, -0.2f,
        -0.4f - wave, -0.2f
    };

    // Line vertices (Optional for any extra lines if needed)
    GLfloat lineVertices[] = {
        -2.5f + wave, -0.6f, 1.8f, -0.6f,
        -2.0f + wave, -0.7f, 2.0f, -0.7f,
        -1.8f + wave, -0.8f, 2.0f, -0.8f
    };

    // Polygon indices (Triangle and Quad)
    GLubyte polygonIndices[] = {
        0, 1, 2,    // Triangle 1
        3, 4, 5,    // Triangle 2
        6, 7, 8, 9  // Polygon (Boat)
    };

    // Line indices
    GLubyte lineIndices[] = {
        0, 1,
        2, 3,
        4, 5
    };

    // Color array (Blue for all the vertices of the boat)
    GLfloat colors[] = {
        0.0f, 0.0f, 1.0f,   // Blue for Triangle 1
        0.0f, 0.0f, 1.0f,   // Blue for Triangle 2
        0.0f, 0.0f, 1.0f,   // Blue for the boat polygon
        0.0f, 0.0f, 1.0f    // Blue for the additional polygon parts
    };

    // Set up the VBO and EBO for the polygons (boat)
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygonVertices), polygonVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBOcolor);
    glBindBuffer(GL_ARRAY_BUFFER, VBOcolor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glGenBuffers(1, &EBOindices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOindices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(polygonIndices), polygonIndices, GL_STATIC_DRAW);

    // Set up vertex attributes for position and color
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOcolor);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    // Draw polygons
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOindices);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, (void*)(6));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Line buffer setup (optional lines)
    glGenBuffers(1, &VBOLineVertices);
    glBindBuffer(GL_ARRAY_BUFFER, VBOLineVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBOlineIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOlineIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lineIndices), lineIndices, GL_STATIC_DRAW);

    // Draw lines (optional)
    glBindBuffer(GL_ARRAY_BUFFER, VBOLineVertices);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOlineIndices);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(2.0f);
    glLineStipple(3.0f, 0x0c0f);

    glDrawElements(GL_LINES, 6, GL_UNSIGNED_BYTE, 0);

    glDisable(GL_LINE_STIPPLE);
    glDisableVertexAttribArray(0);
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, 800, 600);
    glClear(GL_COLOR_BUFFER_BIT);
    displayPolyone();
    text();
    glFlush();
}

void text() {
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(-0.4f, -0.9f);
    const char* str = "Ian Lindley Del Rosario";
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)str);
    glFlush();
}

void Timer(int value) {
    wave += speed;
    if (wave > 1.0f) {
        wave = -0.5f;
    }
    glutPostRedisplay();
    glutTimerFunc(300, Timer, 0);
}
