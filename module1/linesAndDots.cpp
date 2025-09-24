#include <GL/glut.h>

using namespace std;
void triangle() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(5.0);
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);
	glVertex2f(0.4, 0.4);
	glVertex2f(-0.4, -0.4);

	glBegin(GL_LINES);
	glVertex2f(-0.4, 0.4);
	glVertex2f(0.4, -0.4);
	
	glEnd();

	glPointSize(5.0);
	glBegin(GL_POINTS);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.3, 0.0);

	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-0.3, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(0.0, 0.3);

	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.0, -0.3);

	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("exercise -DelRosario");
	glutDisplayFunc(triangle);
	glutMainLoop();
}


