#include <GL\glut.h>
using namespace std;

void displayPolyone(){

glClearColor(1.0f, 1.0f,1.0f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_POLYGON);
	glColor3ub(3, 252, 227);
	glVertex2f(-0.1f, 0.0f);
	glVertex2f(-0.4f, 0.0f);
	glColor3ub(237, 69, 97);
	glVertex2f(-0.03f, 0.3f);
	glVertex2f(-0.03f, 0.0f);	
glEnd();
glFlush();

glBegin(GL_POLYGON);	
	glColor3ub(237, 69, 97);
	glVertex2f(0.1f, 0.0f);
	glVertex2f(0.4f, 0.0f);
	glColor3ub(3, 252, 227);
	glVertex2f(0.0f, 0.3f);
	glVertex2f(0.0f, 0.0f);	
glEnd();
glFlush();

glBegin(GL_QUADS);	
	glColor3ub(129, 232, 44);
	glVertex2f(-0.5f, -0.05f);
	glVertex2f(0.5f, -0.05f);	
	glVertex2f(0.4f, -0.2f);
	glVertex2f(-0.4f, -0.2f);
glEnd();
glFlush();

glEnable(GL_LINE_STIPPLE);
glLineWidth(2.0f);
glLineStipple(2, 0x00FF);
glBegin(GL_LINE_STRIP);
glColor3ub(0, 0, 0);
glVertex2f(-1, -0.6f);
glVertex2f(1, -0.6f);
glEnd();
glFlush();
glDisable(GL_LINE_STIPPLE);

glEnable(GL_LINE_STIPPLE);
glLineWidth(2.0f);
glLineStipple(1, 0x00FF);
glBegin(GL_LINE_STRIP);
glColor3ub(0, 0, 0);
glVertex2f(-1, -0.7f);
glVertex2f(1, -0.7f);
glEnd();
glFlush();
glDisable(GL_LINE_STIPPLE);

glEnable(GL_LINE_STIPPLE);
glLineWidth(2.0f);
glLineStipple(1, 0x000F);
glBegin(GL_LINE_STRIP);
glColor3ub(0, 0, 0);
glVertex2f(-1, -0.8f);
glVertex2f(1, -0.8f);
glEnd();
glFlush();
glDisable(GL_LINE_STIPPLE);
}


int main(int argc, char** argv){
glutInit(&argc, argv);
glutCreateWindow("Del Rosario, Ian Lindley");
glutDisplayFunc(displayPolyone);
glutMainLoop();
}

