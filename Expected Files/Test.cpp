#include <iostream>
#include <windows.h>
#include <GL\glut.h>
#include <GL\freeglut_ext.h>
using namespace std;
void defaultDisplay();
void keyboardMonitor(unsigned char key, int x, int y);
void mouseMonitor(int button, int state, int x, int y);
void detectMotion(int x, int y);
void detectPassiveMotion(int x, int y);
void mouseEntryDetector(int state);
void animateText();
void animateString(int value);
float px, py;
int main(int argc, char **argv){
glutInit(&argc, argv);
glutInitWindowSize(1024,768);
glutInitWindowPosition(200,50);
glutCreateWindow("My First OpenGL");
//glutFullScreen();
glutDisplayFunc(defaultDisplay);
glutKeyboardFunc(keyboardMonitor);
glutMouseFunc(mouseMonitor);
glutMotionFunc(detectMotion);
glutPassiveMotionFunc(detectPassiveMotion);
glutEntryFunc(mouseEntryDetector);
//glutIdleFunc(animateText);
glutMainLoop();
return 0;
}
