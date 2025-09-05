#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>

using namespace std;

GLUquadric* quadric;

float flipAngle = 0.0f;
float liftHeight = 0.0f;
bool isFlipping = false;
bool isLifting = false;

const int TIMER_INTERVAL = 8;

float cameraDistance = 5.0f;
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;

float wallRotationAngle = 90.0f;

float minPancakeRadius = 0.01f;
float maxPancakeRadius = 0.4f;

struct Stove {
    float x, y, z;
    float scaleX, scaleY, scaleZ;
};

struct Burner {
    float x, y, z;
    float innerRadius, outerRadius;
};

struct Pan {
    float x, y, z;
    float radius;
    float handleLength;
};

struct Pancake {
    float x, y, z;
    float radius;
    float thick;
};

struct Wall {
    float x, y, z;
    float width, height, thickness;
    float squareSize;
};

Stove stoves[] = {
    {0.0f, -1.0f, 0.0f, 1.1f, 0.1f, 1.1f},
};

Burner burners[] = {
    {0.0f, -.90f, 0.0f, 0.2f, 0.5f},
};

Pan pans[] = {
    {0.0f, -0.75f, 0.0f, 0.4f, 0.3f},
};

Pancake pancakes[] = {
    {0.0f, -0.78f, 0.0f, 0.35f, 0.03f},
};

Wall wall[] = {
    {-10.0f, 0.0f, 0.0f, 20.0f, 20.0f, 2.0f, 2.0f}
};

void drawStove(Stove stove) {
    glPushMatrix();
    glTranslatef(stove.x, stove.y, stove.z);
    glColor3f(0.2f, 0.2f, 0.2f);
    glScalef(stove.scaleX, stove.scaleY, stove.scaleZ);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawBurner(Burner burner) {
    glPushMatrix();
    glTranslatef(burner.x, burner.y, burner.z);
    glColor3f(0.8f, 0.1f, 0.1f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(quadric, burner.innerRadius, burner.outerRadius, 30, 1);
    glPopMatrix();
}

void drawPan(Pan pan) {
    glPushMatrix();
    glTranslatef(pan.x, pan.y, pan.z);
    glColor3f(0.4f, 0.4f, 0.4f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    
    GLfloat pan_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat pan_diffuse[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat pan_specular[] = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat pan_shininess = 50.0f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, pan_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pan_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, pan_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, pan_shininess);

    gluCylinder(quadric, pan.radius, pan.radius, 0.1f, 36, 1);
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.1f);
    glColor3f(0.3f, 0.3f, 0.3f);
    gluDisk(quadric, 0.0f, pan.radius, 36, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(pan.radius + 0.00f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.3f, 0.3f, 0.3f);
    gluCylinder(quadric, 0.05f, 0.05f, pan.handleLength, 36, 1);
    glPopMatrix();

    glPopMatrix();
}

void drawPancake(Pancake pancake) {
    glPushMatrix();
    glTranslatef(pancake.x, pancake.y + liftHeight, pancake.z);
    
    glColor3f(0.9f, 0.7f, 0.2f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(flipAngle, 0.0f, -1.0f, 0.0f);
    gluCylinder(quadric, pancake.radius, pancake.radius, pancake.thick, 36, 1);
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -pancake.thick / 2.0f);
    glColor3f(0.9f, 0.7f, 0.2f);
    gluDisk(quadric, 0.0f, pancake.radius, 36, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, pancake.thick / 2.0f);
    glColor3f(0.678f, 0.657f, 0.055f);
    gluDisk(quadric, 0.0f, pancake.radius, 36, 1);
    glPopMatrix();
    
    glPopMatrix();
}

void drawWall(Wall wall, float rotationAngle) {
    glPushMatrix();
    glTranslatef(wall.x, wall.y, wall.z);
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glPushMatrix();
    glScalef(wall.width, wall.height, wall.thickness);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPopMatrix();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!isLifting && !isFlipping) {
            isLifting = true;  // Lift the pancake
        } else if (!isLifting && isFlipping) {
            // If pancake is not lifting and is already flipping, reset flip
            flipAngle = 0.0f;
            isFlipping = false;
      }
    }
    glutPostRedisplay();
}

void update(int value) {
    if (isLifting) {
        liftHeight += 0.05f;
        if (liftHeight >= 1.0f) {
            isLifting = false;
            isFlipping = true; // Once lifting is done, start flipping
        }
    }
    
    if (isFlipping) {
        flipAngle += 6.0f;
        if (flipAngle >= 360.0f) {
            flipAngle = 180.0f; // Reset the flip angle to 180 degrees
            isFlipping = false; // Stop flipping
        }
    }
    
    // If not lifting or flipping, slowly decrease the lift height to return the pancake
    if (!isLifting && !isFlipping && liftHeight > 0.0f) {
        liftHeight -= liftHeight * 0.1f;
        if (liftHeight < 0.01f) {
            liftHeight = 0.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(TIMER_INTERVAL, update, value);
}

void keyboardMonitor(unsigned char key, int x, int y) {
    switch (key) {
    	case 'e':
            glutReshapeWindow(800, 600);
            break;
        case 'w':
            cameraAngleY += 0.1f;
            if (cameraAngleY > 89.0f) cameraAngleY = 89.0f;
            break;
       case 's':
            cameraAngleY -= 0.1f;
            if (cameraAngleY < -89.0f) cameraAngleY = -89.0f;
            break;
        case 'a':
            cameraAngleX -= 0.1f;
            if (cameraAngleX < 0.0f) cameraAngleX += 360.0f;
            break;
        case 'd':
            cameraAngleX += 0.1f;
            if (cameraAngleX >= 360.0f) cameraAngleX -= 360.0f;
            break;
        case 'f':
            if (!isLifting && !isFlipping) {
                isLifting = true;
            }
            break;
    }
    float eyeX = cameraDistance * cosf(cameraAngleY * 3.14159f / 180.0f) * sinf(cameraAngleX * 3.14159f / 180.0f);
    float eyeY = cameraDistance * sinf(cameraAngleY * 3.14159f / 180.0f);
    float eyeZ = cameraDistance * cosf(cameraAngleY * 3.14159f / 180.0f) * cosf(cameraAngleX * 3.14159f / 180.0f);
    gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glutPostRedisplay();
}

void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = {0.0f, 1.0f, 0.0f, 1.0f};
    GLfloat spot_direction[] = {0.0f, -1.0f, 0.0f};
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 15.0f); 
}

void init() {
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL); 

    setupLighting();                 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    quadric = gluNewQuadric(); 
}

void drawLightMarker() {
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f); 
    glColor3f(1.0f, 1.0f, 0.0f); 
    glutSolidSphere(0.1f, 16, 16);
    glPopMatrix();
}

void mouseScroll(int wheel, int direction, int x, int y) {
    if (direction > 0) { // Scroll up
        pancakes[0].radius += 0.02f;
        if (pancakes[0].radius > maxPancakeRadius)
            pancakes[0].radius = maxPancakeRadius;
    } else { // Scroll down
        pancakes[0].radius -= 0.02f;
        if (pancakes[0].radius < minPancakeRadius)
            pancakes[0].radius = minPancakeRadius;
    }
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraDistance * cos(cameraAngleY) * cos(cameraAngleX), 
              cameraDistance * sin(cameraAngleY), 
              cameraDistance * cos(cameraAngleY) * sin(cameraAngleX),
              0.0f, -0.7f, 0.0f, 0.0f, 1.0f, 0.0f);

    drawWall(wall[0], wallRotationAngle);
    drawStove(stoves[0]);
    drawBurner(burners[0]);
    drawPan(pans[0]);
    for (int i = 0; i < sizeof(pancakes) / sizeof(pancakes[0]); i++) {
        drawPancake(pancakes[i]);
    }


    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Pancake Flip Animation");
    glutFullScreen();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardMonitor);
    glutMouseFunc(mouseClick); // This is for mouse clickss
    glutMouseWheelFunc(mouseScroll); // This is for mouse scrolling
    glutTimerFunc(TIMER_INTERVAL, update, 0);
    glutMainLoop();
    return 0;
}

/*

W A S D to move the camera
/F to flip the pancake
E to exit Fullscreen
mouse wheel will increase size of pancake
*/
