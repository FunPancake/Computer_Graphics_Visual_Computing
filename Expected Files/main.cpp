//#include <iostream>
//#include <GL/glew.h>
//#include <GL/glut.h>
//#include <GL/freeglut_ext.h>
//#include <windows.h>
//using namespace std;
//
//void displayPolyone();
//void display();
//void text();
//void mouseClick(int button, int state, int x, int y);
//void keyboardMonitor(unsigned char key, int x, int y);
//void keyboardMonitorSpecial(int key, int x, int y);
//void Timer(int value);
//
//float px = 0.0f, py = 0.0f, speed = 0.05f, wave = 0.0f, scale = 1.0f; // Scale factor
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutCreateWindow("Del Rosario, Ian Lindley");
//    glutDisplayFunc(display);
//    glutMouseFunc(mouseClick);
//    glutKeyboardFunc(keyboardMonitor);
//    glutSpecialFunc(keyboardMonitorSpecial);
//    glutTimerFunc(300, Timer, 0);
//    glutMainLoop();
//}
//
//void Timer(int value) {
//    wave += speed;
//    if (wave > 1.0f) {
//        wave = -0.5f;
//    }
//    glutPostRedisplay();
//    glutTimerFunc(300, Timer, 0);
//}
//
//void keyboardMonitor(unsigned char key, int x, int y) {
//    switch (key) {
//        case 'a':
//        case 'A':
//            px -= 0.1f; // Move left
//            break;
//        case 'd':
//        case 'D':
//            px += 0.1f; // Move right
//            break;
//        case 'w':
//        case 'W':
//            scale += 0.1f; // Increase scale
//            break;
//        case 's':
//        case 'S':
//            scale = (scale > 0.1f) ? scale - 0.1f : 0.1f; // Decrease scale, prevent negative scaling
//            break;
//        default:
//            break;
//    }
//    glutPostRedisplay();
//}
//
//void keyboardMonitorSpecial(int key, int x, int y) {
//    switch (key) {
//        case GLUT_KEY_LEFT:
//            px -= 0.1f; // Move left
//            break;
//        case GLUT_KEY_RIGHT:
//            px += 0.1f; // Move right
//            break;
//        default:
//            break;
//    }
//    glutPostRedisplay();
//}
//
//GLfloat colors[] = {
//    1.0f, 0.0f, 0.0f, // red Triangle 1
//    1.0f, 0.0f, 0.0f,
//    1.0f, 0.0f, 0.0f,
//    1.0f, 0.0f, 0.0f, // red Triangle 2
//    1.0f, 0.0f, 0.0f,
//    1.0f, 0.0f, 0.0f,
//    0.0f, 0.0f, 1.0f, // blue Polygon 1
//    0.0f, 0.0f, 1.0f,
//    0.0f, 0.0f, 1.0f,
//    0.0f, 0.0f, 1.0f,
//};
//
//void mouseClick(int button, int state, int x, int y) {
//    if (state == GLUT_UP) {
//        if (button == GLUT_RIGHT_BUTTON) {
//            for (int i = 0; i < 6; i++) {
//                colors[i * 3] = 0.0f;
//                colors[i * 3 + 1] = 0.0f;
//                colors[i * 3 + 2] = 1.0f; // blue
//            }
//            for (int i = 6; i < 10; i++) {
//                colors[i * 3] = 0.5f;
//                colors[i * 3 + 1] = 0.5f;
//                colors[i * 3 + 2] = 0.5f; // grey
//            }
//        } else if (button == GLUT_LEFT_BUTTON) {
//            for (int i = 0; i < 6; i++) {
//                colors[i * 3] = 1.0f;
//                colors[i * 3 + 1] = 0.0f;
//                colors[i * 3 + 2] = 0.0f; // red
//            }
//            for (int i = 6; i < 10; i++) {
//                colors[i * 3] = 1.0f;
//                colors[i * 3 + 1] = 1.0f;
//                colors[i * 3 + 2] = 1.0f; // white
//            }
//        }
//        glutPostRedisplay();
//    }
//}
//
//void displayPolyone() {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // Apply scaling to the vertices
//    GLfloat polygonindices[] = {
//        px - 0.01f * scale, py,               // 0
//        px - 0.4f * scale, py,                // 1
//        px - 0.01f * scale, py + 0.3f * scale, // 2
//
//        px + 0.01f * scale, py,               // 3
//        px + 0.4f * scale, py,                // 4
//        px + 0.01f * scale, py + 0.3f * scale, // 5
//
//        px - 0.5f * scale, py - 0.05f * scale, // 6
//        px + 0.5f * scale, py - 0.05f * scale, // 7
//        px + 0.4f * scale, py - 0.2f * scale,  // 8
//        px - 0.4f * scale, py - 0.2f * scale   // 9
//    };
//
//    GLfloat lineVertices[] = {
//        -2.0f + wave, -0.6f,
//        1.8f + wave, -0.6f,
//
//        -2.0f + wave, -0.7f,
//        2.0f + wave, -0.7f,
//
//        -1.8f + wave, -0.8f,
//        2.0f + wave, -0.8f
//    };
//
//    GLubyte polygonidx[] = {
//        0, 1, 2,
//        3, 4, 5,
//        6, 7, 8, 9
//    };
//
//    GLubyte lineIndices[] = {
//        0, 1,
//        2, 3,
//        4, 5
//    };
//
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_COLOR_ARRAY);
//
//    glVertexPointer(2, GL_FLOAT, 0, polygonindices);
//    glColorPointer(3, GL_FLOAT, 0, colors);
//
//    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, polygonidx);
//    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &polygonidx[3]);
//    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, &polygonidx[6]);
//
//    glDisableClientState(GL_COLOR_ARRAY);
//
//    glColor3f(0.0f, 0.0f, 1.0f);
//
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(2, GL_FLOAT, 0, lineVertices);
//
//    glEnable(GL_LINE_STIPPLE);
//    glLineWidth(3.0f);
//
//    glLineStipple(2, 0x00FF);
//    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, lineIndices);
//    glLineStipple(1, 0x00FF);
//    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, &lineIndices[2]);
//    glLineStipple(2, 0x00FF);
//    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, &lineIndices[4]);
//
//    glDisable(GL_LINE_STIPPLE);
//    glDisableClientState(GL_VERTEX_ARRAY);
//
//    glFlush();
//}
//
//void text() {
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glRasterPos2f(-0.4f, -0.9f);
//    const char* str = "Ian Lindley Del Rosario";
//    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)str);
//    glFlush();
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT);
//    displayPolyone();
//    text();
//    glFlush();
//}

