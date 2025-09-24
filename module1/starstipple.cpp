#include <GL/glut.h>

using namespace std;
void triangle() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(5.0);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(3, 0xAAAA);


	glBegin(GL_LINES);
	glVertex2f(-0.5, 0.4);
	glVertex2f(0.0, -0.6);

	glVertex2f(0.0, -0.6);
	glVertex2f(0.5, 0.4);

	glVertex2f(0.5, 0.4);
	glVertex2f(-0.5, 0.4);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0.5, -0.4);
	glVertex2f(0.0, 0.6);

	glVertex2f(0.0, 0.6);
	glVertex2f(-0.5, -0.4);

	glVertex2f(-0.5, -0.4);
	glVertex2f(0.5, -0.4);
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("exercise -DelRosario");
	glutDisplayFunc(triangle);
	glutMainLoop();
}
