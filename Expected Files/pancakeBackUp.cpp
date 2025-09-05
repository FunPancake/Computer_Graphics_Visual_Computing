//#include <iostream>
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <cmath> // For trigonometric functions
//
//using namespace std;
//
//GLUquadric* quadric;
//
//// Timer and flip variables
//float flipAngle = 0.0f;  // Angle of rotation for the pancake flip
//float liftHeight = 0.0f;  // Height of the pancake lift
//bool isFlipping = false;  // Flag to check if flipping should happen
//bool isLifting = false;   // Flag for lifting
//
//const int TIMER_INTERVAL = 8; // Timer interval for smooth animation
//
//// Camera control variables
//float cameraDistance = 5.0f;
//float cameraAngleX = 0.0f;
//float cameraAngleY = 0.0f;
//
//float wallRotationAngle = 90.0f;
//
//struct Stove {
//    float x, y, z; // Position
//    float scaleX, scaleY, scaleZ; // Scale
//};
//
//struct Burner {
//    float x, y, z; // Position
//    float innerRadius, outerRadius; // Burner size (radii)
//};
//
//struct Pan {
//    float x, y, z; // Position
//    float radius;  // Pan size (radius)
//    float handleLength; // Handle length
//};
//
//struct Pancake {
//    float x, y, z; // Position
//    float radius;  // Pancake size (radius)
//    float thick;   // Thickness of the pancake
//};
//
//struct Wall {
//    float x, y, z; // Position
//    float width, height, thickness; // Wall dimensions
//    float squareSize; // Size of the hollow square
//};
//
//Stove stoves[] = {
//    {0.0f, -1.0f, 0.0f, 1.1f, 0.1f, 1.1f},  // Reduced stove size slightly larger than burner
//};
//
//Burner burners[] = {
//    {0.0f, -.90f, 0.0f, 0.2f, 0.5f},  // Single burner setup
//};
//
//Pan pans[] = {
//    {0.0f, -0.75f, 0.0f, 0.4f, 0.3f},  // Single pan setup
//};
//
//Pancake pancakes[] = {
//    {0.0f, -0.78f, 0.0f, 0.35f, 0.03f}, // Single pancake setup, positioned on the pan
//};
//
//Wall wall[] = {
//	{-10.0f, 0.0f, 0.0f, 20.0f, 20.0f, 2.0f, 2.0f}
//};
//
//// Function to draw the stove (a simple 3D square)
//void drawStove(Stove stove) {
//    glPushMatrix();
//    glTranslatef(stove.x, stove.y, stove.z); // Move stove to the correct position
//    glColor3f(0.2f, 0.2f, 0.2f);     // Dark gray for stove
//    glScalef(stove.scaleX, stove.scaleY, stove.scaleZ);      // Scale stove size
//    glutSolidCube(1.0f);             // Draw a solid cube to represent the stove
//    glPopMatrix();
//}
//
//// Function to draw the burner (a flat circular disk, rotated 90 degrees)
//void drawBurner(Burner burner) {
//    glPushMatrix();
//    glTranslatef(burner.x, burner.y, burner.z); // Position burner slightly above the stove
//    glColor3f(0.8f, 0.1f, 0.1f);     // Red color for the burner
//    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotate burner to lie flat
//    gluDisk(quadric, burner.innerRadius, burner.outerRadius, 30, 1); // Draw burner as a disk
//    glPopMatrix();
//}
//
//// Function to draw the pan (a flat 3D cylinder with a handle and bottom)
//void drawPan(Pan pan) {
//    glPushMatrix();
//    glTranslatef(pan.x, pan.y, pan.z); // Move pan just above the burner
//    glColor3f(0.4f, 0.4f, 0.4f);     // Gray color for the pan
//    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotate to lie flat
//    gluCylinder(quadric, pan.radius, pan.radius, 0.1f, 36, 1); // Draw the pan as a cylinder
//
//    // Drawing the bottom of the pan (a disk)
//    glPushMatrix();
//    glTranslatef(0.0f, 0.0f, 0.1f); // Position the bottom slightly below the pan
//    glColor3f(0.3f, 0.3f, 0.3f);     // Darker color for the bottom
//    gluDisk(quadric, 0.0f, pan.radius, 36, 1); // Bottom as a disk
//    glPopMatrix();
//
//    // Drawing the handle
//    glPushMatrix();
//    glTranslatef(pan.radius + 0.00f, 0.0f, 0.0f); // Position the handle closer to the pan
//    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotate to make the handle extend sideways
//    glColor3f(0.3f, 0.3f, 0.3f);     // Darker color for the handle
//    gluCylinder(quadric, 0.05f, 0.05f, pan.handleLength, 36, 1); // Handle as a cylinder
//    glPopMatrix();
//
//    glPopMatrix();
//}
//
////Function to draw the pancake (as a flat disk with thickness)
//void drawPancake(Pancake pancake) {
//    glPushMatrix();
//    glTranslatef(pancake.x, pancake.y + liftHeight, pancake.z); // Move pancake on top of the pan
//    glColor3f(0.9f, 0.7f, 0.2f);  // Light brown color for the pancake
//    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotate the pancake to lie flat
//
//    // Apply the flip rotation only around the x-axis
//    glRotatef(flipAngle, 0.0f, 1.0f, 0.0f);  // Rotate around the x-axis (for the flip effect)
//
//    // Draw the body of the pancake (a cylinder)
//    gluCylinder(quadric, pancake.radius, pancake.radius, pancake.thick, 36, 1);  // Draw pancake as a cylinder with thickness    
//
//    // Draw the top of the pancake (disk)
//    glPushMatrix();
//    glTranslatef(0.0f, 0.0f, -pancake.thick / 2.0f); // Position the top at the bottom of the cylinder
//    glColor3f(0.9f, 0.7f, 0.2f);  // Light brown color for the top of the pancake
//    gluDisk(quadric, 0.0f, pancake.radius, 36, 1); // top disk
//    glPopMatrix();
//
//    // Draw the bottom of the pancake (disk)
//    glPushMatrix();
//    glTranslatef(0.0f, 0.0f, pancake.thick / 2.0f); // Position the bottom at the top of the cylinder
//    glColor3f(0.678f, 0.657f, 0.055f);  // Light brown color for the bottom of the pancake
//    gluDisk(quadric, 0.0f, pancake.radius, 36, 1); // bottom disk
//    glPopMatrix();
//
//    glPopMatrix();
//}
//
//void drawWall(Wall wall, float rotationAngle) {
//    glPushMatrix();
//    glTranslatef(wall.x, wall.y, wall.z); // Move the wall to the correct position
//    
//     glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
//    
//    glColor3f(1.0f, 1.0f, 1.0f); // Brown color for the wall
//    glPushMatrix();
//    glScalef(wall.width, wall.height, wall.thickness); // Scale the wall
//    glutSolidCube(1.0f); // Draw the solid cube for the wall
//    glPopMatrix();
//
//    glPopMatrix();
//}
//
//
//// Function to update the animation (called by the timer)
//void update(int value) {
//    if (isLifting) {
//        liftHeight += 0.05f; // Move the pancake upwards (lifting)
//        if (liftHeight >= 1.0f) {  // Lift complete, start flipping
//            isLifting = false;
//            isFlipping = true;
//        }
//    }
//    if (isFlipping) {
//        flipAngle += 6.0f;  // Rotate pancake during the flip
//        if (flipAngle >= 360.0f) {  // Flip complete
//            flipAngle = 180.0f;
//            isFlipping = false;
//        }
//    }
//    if (!isLifting && !isFlipping && liftHeight > 0.0f) {
//        // Smooth descent using easing
//        liftHeight -= liftHeight * 0.1f; // Reduce the height by a fraction
//        if (liftHeight < 0.01f) { // Threshold to stop descent
//            liftHeight = 0.0f;
//        }
//    }
//
//    glutPostRedisplay();
//    glutTimerFunc(TIMER_INTERVAL, update, value);
//}
//
//
//// Keyboard monitoring function (WSAD movement + pancake flip)
//void keyboardMonitor(unsigned char key, int x, int y) {
//    switch (key) {
//        case 'w': // Tilt camera up
//            cameraAngleY += 0.1f;
//            if (cameraAngleY > 89.0f) cameraAngleY = 89.0f; // Prevent flipping
//            break;
//        case 's': // Tilt camera down
//            cameraAngleY -= 0.1f;
//            if (cameraAngleY < -89.0f) cameraAngleY = -89.0f;
//            break;
//        case 'a': // Rotate camera left
//            cameraAngleX -= 0.1f;
//            if (cameraAngleX < 0.0f) cameraAngleX += 360.0f;
//            break;
//        case 'd': // Rotate camera right
//            cameraAngleX += 0.1f;
//            if (cameraAngleX >= 360.0f) cameraAngleX -= 360.0f;
//            break;
//        case 'f': // Start flipping the pancake
//            if (!isLifting && !isFlipping) {
//                isLifting = true; // Start the lifting phase
//            }
//            break;
//    }
//
//    float eyeX = cameraDistance * cosf(cameraAngleY * 3.14159f / 180.0f) * sinf(cameraAngleX * 3.14159f / 180.0f);
//    float eyeY = cameraDistance * sinf(cameraAngleY * 3.14159f / 180.0f);
//    float eyeZ = cameraDistance * cosf(cameraAngleY * 3.14159f / 180.0f) * cosf(cameraAngleX * 3.14159f / 180.0f);
//
//    gluLookAt(	eyeX, eyeY, eyeZ, 
//				0.0, 0.0, 0.0, 
//				0.0, 1.0, 0.0); // Update camera position based on angles
//
//    glutPostRedisplay();
//}
//// Display function to draw everything
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen and depth buffer
//
//    // Set up the camera
//    glLoadIdentity();
//    gluLookAt(cameraDistance * cos(cameraAngleY) * cos(cameraAngleX), cameraDistance * sin(cameraAngleY), cameraDistance * cos(cameraAngleY) * sin(cameraAngleX),
//              0.0f, -0.7f, 0.0f, 
//			  0.0f, 1.0f, 0.0f); // Set camera position and view
//
//    // Draw the stove, burner, pan, and pancake
//    drawWall(wall[0], wallRotationAngle);
//    drawStove(stoves[0]);
//    drawBurner(burners[0]);
//    drawPan(pans[0]);
//    for (int i = 0; i < sizeof(pancakes) / sizeof(pancakes[0]); i++) {
//        drawPancake(pancakes[i]);
//    }
//    
//
//    glFlush();
//}
//
//// Function to initialize OpenGL settings
//void init() {
//    glClearColor(0.6f, 0.6f, 0.6f, 1.0f); // Set background color to white
//    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f); // Set perspective projection
//    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix
//    quadric = gluNewQuadric(); // Initialize the quadric object for rendering shapes
//}
//
//// Main function
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);                // Initialize GLUT
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);  // Set display mode
//    glutInitWindowSize(800, 600);          // Set window size
//    glutCreateWindow("Pancake Flip Animation");    // Create window with title
//    init();                               // Initialize OpenGL settings
//
//    glutDisplayFunc(display);              // Register display callback
//    glutKeyboardFunc(keyboardMonitor);      // Register keyboard input callback
//    glutTimerFunc(TIMER_INTERVAL, update, 0); // Set the timer for updating animation
//
//    glutMainLoop();                        // Enter the GLUT main loop
//    return 0;
//}
