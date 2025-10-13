#include <GL/glut.h>
#include <cmath> 

using namespace std;

GLfloat houseColor[3] = { 206.0f / 255.0f, 237.0f / 255.0f, 104.0f / 255.0f }; // default greenish
GLfloat treeColor[3] = { 36.0f / 255.0f, 120.0f / 255.0f, 42.0f / 255.0f };   // default green
GLfloat treeTrunkColor[3] = { 20.0f / 255.0f, 74.0f / 255.0f, 24.0f / 255.0f }; // default brown

GLfloat treeX = 0.0f; //tree movement

float cloudX = -1.0f; //

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
	glColor3f(houseColor[0], houseColor[1], houseColor[2]);
	glVertex2f(-0.4f, -0.55f);
	glVertex2f(0.4f, -0.55f);
	glVertex2f(0.4f, -0.13f);
	glVertex2f(-0.4f, -0.13f);
	glEnd();

	//Roof
	glBegin(GL_QUADS);
	glColor3ub(255, 0, 0);
	glVertex2f(-0.4f, -0.05f);
	glVertex2f(0.4f, -0.05f);
	glVertex2f(0.5f, -0.2f);
	glVertex2f(-0.5f, -0.2f);
	glEnd();
}

void weirdTree() {
	glPushMatrix();
	glTranslatef(treeX, 0.0f, 0.0f);

	//Tree Body
	glBegin(GL_POLYGON);
	glColor3f(treeTrunkColor[0], treeTrunkColor[1], treeTrunkColor[2]);
	glVertex2f(0.8f, -0.55f);
	glVertex2f(0.7f, -0.55f);
	glVertex2f(0.7f, -0.1f);
	glVertex2f(0.8f, -0.1f);
	glEnd();

	//Tree Leaves
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(treeColor[0], treeColor[1], treeColor[2]);
	glVertex2f(0.75f, -0.1f);
	glVertex2f(0.85f, -0.1f);
	glVertex2f(0.9f, 0.0f);
	glVertex2f(0.75f, 0.1f);
	glVertex2f(0.6f, 0.0f);
	glVertex2f(0.65f, -0.1f);
	glEnd();

	glPopMatrix();
}

void cloud() {
	GLfloat cx = -0.6f + cloudX;
	GLfloat cy = 0.6f;
	GLfloat radius = 0.1f;

	for (int i = 0; i < 5; i++) {
		GLfloat offset = i * 0.1f;

		glColor3f(0.529f, 0.808f, 0.922f);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(cx + offset, cy);
		for (int side = 0; side <= 8; side++) {
			float rad = side * 3.14159f / 8.0f;
			glVertex2f(cx + offset + cos(rad) * radius,
				cy + sin(rad) * radius);
		}
		glEnd();
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
		cloudX += 0.3f; 

		if (cloudX > 1.5f)
			cloudX = -1.5f;

		glutPostRedisplay();
		glutTimerFunc(1000, cloudDrifting, 0);
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
	glutCreateWindow("GL-Primitve -DelRosario");

	glutDisplayFunc(lab6);
	glutMouseFunc(colorChangeMouse);
	glutSpecialFunc(rollingTree);
	glutTimerFunc(1000, cloudDrifting, 0);

	glutMainLoop();
	return 0;
}
