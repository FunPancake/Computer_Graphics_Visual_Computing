#include <GL/glut.h>

using namespace std;

void roadways() {

	//Top Road Line
	glLineWidth(2.0f);
	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 0, 0);
	glVertex2f(-1, -0.6f);
	glVertex2f(1, -0.6f);
	glEnd();

	//Broken Road Line
	glEnable(GL_LINE_STIPPLE);
	glLineWidth(2.0f);
	glLineStipple(2, 0x00FF);
	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 0, 0);
	glVertex2f(-1, -0.7f);
	glVertex2f(1, -0.7f);
	glEnd();
	glDisable(GL_LINE_STIPPLE);


	//Bottom Road Line
	glLineWidth(2.0f);
	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 0, 0);
	glVertex2f(-1, -0.8f);
	glVertex2f(1, -0.8f);
	glEnd();

}

void emptyDoor() {

	//Door
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	glVertex2f(-0.05f, -0.55f);
	glVertex2f(0.05f, -0.55f);
	glVertex2f(0.05f, -0.3f);
	glVertex2f(-0.05f, -0.3f);
	glEnd();
}

void house() {

	//House Body
	glBegin(GL_QUADS);
	glColor3ub(206, 237, 104);
	glVertex2f(-0.4f, -0.55f);
	glVertex2f(0.4f, -0.55f);
	glVertex2f(0.4f, -0.13f);
	glVertex2f(-0.4f, -0.13f);
	glEnd();

	//roof
	glBegin(GL_QUADS);
	glColor3ub(255, 0, 0);
	glVertex2f(-0.4f, -0.05f);
	glVertex2f(0.4f, -0.05f);
	glVertex2f(0.5f, -0.2f);
	glVertex2f(-0.5f, -0.2f);
	glEnd();
	glFlush();
}

void weirdTree() {

	//Tree Body
	glBegin(GL_POLYGON);
	glColor3ub(20, 74, 24);
	glVertex2f(0.8f, -0.55f);
	glVertex2f(0.7f, -0.55f);
	glVertex2f(0.7f, -0.1f);
	glVertex2f(0.8f, -0.1f);
	glEnd();

	//tree leaves
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(36, 120, 42);
	glVertex2f(0.75f, -0.1f);
	glVertex2f(0.85f, -0.1f);
	glVertex2f(0.9f, 0.0f);
	glVertex2f(0.75f, 0.1f);
	glVertex2f(0.6f, 0.0f);
	glVertex2f(0.65f, -0.1f);


	glEnd();

}

void lab5() {

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	
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
	glutCreateWindow("GL-Primitve -DelRosario");
	glutDisplayFunc(lab5);
	glutMainLoop();
	return 0;
}
