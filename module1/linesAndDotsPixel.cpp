#include <GL/glut.h>
using namespace std;

void triangle() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(5.0);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2i(600, 600);
    glVertex2i(200, 200);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2i(200, 600);
    glVertex2i(600, 200);
    glEnd();

    glPointSize(8.0);
    glBegin(GL_POINTS);

    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(500, 400);

    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(300, 400);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(400, 500);

    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(400, 300);

    glEnd();

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  
    gluOrtho2D(0, 800, 0, 800);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(120, 120);

    glutCreateWindow("Pixel Coordinate + Double Buffer Example");

    init();
    glutDisplayFunc(triangle);

    glutMainLoop();
    return 0;
}
