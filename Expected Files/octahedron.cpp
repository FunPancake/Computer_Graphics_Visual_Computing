//#include <iostream>
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <cmath>
//
//using namespace std;
//
//void reshape(int width, int height);
//void timer(int value);
//void keyboardMonitor(unsigned char key, int x, int y);
//void initLighting();
//void display(); // Display function declaration
//
//float rotationAngleY = 0.0f;
//float cameraAngleX = 0.0f;
//float cameraAngleY = 20.0f;
//float cameraDistance = 5.0f;
//
//GLfloat vertices[][3] = {
//    {  0.0f,  1.0f,  0.0f }, // 0
//    {  0.0f, -1.0f,  0.0f }, // 1
//    { -1.0f,  0.0f,  0.0f }, // 2
//    {  1.0f,  0.0f,  0.0f }, // 3
//    {  0.0f,  0.0f,  1.0f }, // 4
//    {  0.0f,  0.0f, -1.0f }  // 5
//};
//
//GLuint triangleFaces[][3] = {
//    { 0, 2, 4 }, { 0, 4, 3 }, { 0, 3, 5 }, { 0, 5, 2 },
//    { 1, 4, 2 }, { 1, 3, 4 }, { 1, 5, 3 }, { 1, 2, 5 }
//};
//
//GLfloat colors[][3] = {
//    { 0.4509f, 0.4156f, 0.3098f }, { 0.9098f, 0.8784f, 0.2823f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f },  // top side color
//    { 0.0f, 0.0f, 1.0f }, { 0.4509f, 0.4156f, 0.3098f }, { 0.9098f, 0.8784f, 0.2823f }, { 1.0f, 0.0f, 0.0f }   // bottom side color
//};
//
//GLuint lineIndices[][2] = {
//    { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0, 5 },
//    { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 },
//    { 2, 4 }, { 3, 4 }, { 3, 5 }, { 2, 5 }
//};
//
//void initLighting() {
//    // Enable lighting and depth test
//    glEnable(GL_LIGHTING);
//    glEnable(GL_DEPTH_TEST);
//
//    // Ambient light setup
//    GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Low-intensity white light
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
//
//    // Spotlight 1 (GL_LIGHT0 with GL_AMBIENT)
//    GLfloat light0_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Soft white light
//    GLfloat light0_position[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Light position
//    GLfloat light0_direction[] = { -1.0f, -1.0f, -1.0f }; // Spotlight direction
//    glEnable(GL_LIGHT0);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
//    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
//    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f); // Spotlight cutoff angle
//    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
//
//    // Spotlight 2 (GL_LIGHT1 with GL_DIFFUSE)
//    GLfloat light1_diffuse[] = { 0.8f, 0.2f, 0.2f, 1.0f }; // Red diffuse light
//    GLfloat light1_position[] = { -1.0f, 1.0f, 1.0f, 1.0f }; // Light position
//    GLfloat light1_direction[] = { 1.0f, -1.0f, -1.0f }; // Spotlight direction
//    glEnable(GL_LIGHT1);
//    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
//    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
//    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f); // Spotlight cutoff angle
//    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
//
//    // Spotlight 3 (GL_LIGHT2 with GL_SPECULAR)
//    GLfloat light2_specular[] = { 0.0f, 0.5f, 1.0f, 1.0f }; // Blue specular light
//    GLfloat light2_position[] = { 1.0f, -1.0f, 1.0f, 1.0f }; // Light position
//    GLfloat light2_direction[] = { -1.0f, 1.0f, -1.0f }; // Spotlight direction
//    glEnable(GL_LIGHT2);
//    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
//    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
//    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20.0f); // Spotlight cutoff angle
//    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_direction);
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//
//    float eyeX = cameraDistance * cosf(cameraAngleY * 3.14159f / 180.0f) * sinf(cameraAngleX * 3.14159f / 180.0f);
//    float eyeY = cameraDistance * sinf(cameraAngleY * 3.14159f / 180.0f);
//    float eyeZ = cameraDistance * cosf(cameraAngleY * 3.14159f / 180.0f) * cosf(cameraAngleX * 3.14159f / 180.0f);
//
//    gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//
//    glRotatef(rotationAngleY, 0.0f, 0.0f, 1.0f);
//
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_COLOR_ARRAY);
//
//    glVertexPointer(3, GL_FLOAT, 0, vertices);
//    glColorPointer(3, GL_FLOAT, 0, colors);
//
//    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, triangleFaces);
//
//    glColor3f(0.0f, 0.0f, 0.0f);
//    glBegin(GL_LINES);
//    for (int i = 0; i < 12; i++) {
//        glVertex3fv(vertices[lineIndices[i][0]]);
//        glVertex3fv(vertices[lineIndices[i][1]]);
//    }
//    glEnd();
//
//    glutSwapBuffers();
//}
//
//void timer(int value) {
//    rotationAngleY += 0.2f; // Rotation speed
//    if (rotationAngleY >= 360.0f) rotationAngleY -= 360.0f;
//    glutPostRedisplay();
//    glutTimerFunc(16, timer, 0);
//}
//
//void reshape(int width, int height) {
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(50.0f, static_cast<float>(width) / height, 0.1f, 10.0f);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void keyboardMonitor(unsigned char key, int x, int y) {
//    switch (key) {
//        case 'w': // Tilt camera up
//            cameraAngleY += 10.0f;
//            if (cameraAngleY > 89.0f) cameraAngleY = 89.0f; // Prevent flipping
//            break;
//        case 's': // Tilt camera down
//            cameraAngleY -= 10.0f;
//            if (cameraAngleY < -89.0f) cameraAngleY = -89.0f;
//            break;
//        case 'a': // Rotate camera left
//            cameraAngleX -= 10.0f;
//            if (cameraAngleX < 0.0f) cameraAngleX += 360.0f;
//            break;
//        case 'd': // Rotate camera right
//            cameraAngleX += 10.0f;
//            if (cameraAngleX >= 360.0f) cameraAngleX -= 360.0f;
//            break;
//        case '1': // Toggle Spotlight 1 (GL_LIGHT0)
//            if (glIsEnabled(GL_LIGHT0)) {
//                glDisable(GL_LIGHT0);
//            } else {
//                glEnable(GL_LIGHT0);
//            }
//            break;
//        case '2': // Toggle Spotlight 2 (GL_LIGHT1)
//            if (glIsEnabled(GL_LIGHT1)) {
//                glDisable(GL_LIGHT1);
//            } else {
//                glEnable(GL_LIGHT1);
//            }
//            break;
//        case '3': // Toggle Spotlight 3 (GL_LIGHT2)
//            if (glIsEnabled(GL_LIGHT2)) {
//                glDisable(GL_LIGHT2);
//            } else {
//                glEnable(GL_LIGHT2);
//            }
//            break;
//        default:
//            break;
//    }
//    glutPostRedisplay();
//}
//
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("202020018: Del Rosario, Ian Lindley H.");
//
//    GLenum err = glewInit();
//    if (err != GLEW_OK) {
//        cerr << "GLEW initialization failed: " << glewGetErrorString(err) << endl;
//        return -1;
//    }
//
//    initLighting();
//    glEnable(GL_COLOR_MATERIAL); 
//    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//
//    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
//
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutTimerFunc(16, timer, 0);
//    glutKeyboardFunc(keyboardMonitor);
//    glutMainLoop();
//
//    return 0;
//}
