#include <GL/glut.h>
using namespace std;

void display();
void polygon();

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitWindowSize(200,200);
	glutInitWindowPosition(300,300);
	glutCreateWindow("Reginald");
	glutDisplayFunc(display);
	glutMainLoop();
}

void polygon(){
	
	GLfloat colors[] = {
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f,
		
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		1.0f,1.0f,1.0f,
	
	};
	

	GLfloat polygonindices[] = {
		-.5f,-.5f, //0
		.5f,-.5f,  //1
		0.0f,.5f,  //2
		
		-0.75f, -0.75f, //3
		-0.75f, 0.75f,  //4
		0.75f, 0.75f,   //5
		0.75f, -0.75f   //6
		
	};
	
	GLubyte polygonidx[] = {
		0,1,2
	};
	
	GLubyte pointsidx[] = {
		3,4,5,6
	};
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2,GL_FLOAT,0,polygonindices);
	glColorPointer(3,GL_FLOAT,0,colors);
	glPointSize(20.0f);
	
	glDrawElements(GL_POLYGON,3,GL_UNSIGNED_BYTE,polygonidx);
	glDrawElements(GL_POINTS,4,GL_UNSIGNED_BYTE,pointsidx);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

}


void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	polygon();
	glFlush();
}


