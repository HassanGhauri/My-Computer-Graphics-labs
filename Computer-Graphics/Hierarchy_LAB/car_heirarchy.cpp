#include <GL/glut.h>
#include <cmath>
#include <iostream>

float carPositionX = 0.0; // Initial car position
bool animationPaused = false; // Indication flag if animation is paused

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawCarBody() {
    // Car body
    glColor3f(0.1, 0.2, 0.2); 
    glBegin(GL_POLYGON);
    glVertex2f(-0.6, -0.2); 
    glVertex2f(0.6, -0.2);  
    glVertex2f(0.4, 0.0);   
    glVertex2f(-0.4, 0.0);  
    glEnd();
}

void drawCarRoof() {
    // Car roof
    glColor3f(0.192, 0.882, 0.969); 
    glBegin(GL_POLYGON);
    glVertex2f(-0.3, 0.0); 
    glVertex2f(0.3, 0.0);   
    glVertex2f(0.1, 0.2);   
    glVertex2f(-0.1, 0.2);  
    glEnd();
}

void drawWheel(float x, float y) {
    // Wheel
    glColor3f(0.1f, 0.1f, 0.1f); 
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    drawCircle(0.0, 0.0, 0.1, 100);
    glPopMatrix();
}

void drawRoad() {
    // Road background
    glColor3f(0.2f, 0.2f, 0.2f); 
    glBegin(GL_QUADS);
    glVertex2f(-2.0, -0.3); 
    glVertex2f(2.0, -0.3);  
    glVertex2f(2.0, -2.0);  
    glVertex2f(-2.0, -2.0); 
    glEnd();
}

void drawCar() {
    drawRoad(); // Draw the road background

    // Car body (parent)
    glPushMatrix();
    glTranslatef(carPositionX, 0.0, 0.0); // Apply car's horizontal position
    drawCarBody();

    // Car roof (child of car body)
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    drawCarRoof();
    glPopMatrix();

    // Front wheel (child of car body)
    glPushMatrix();
    glTranslatef(-0.3, -0.2, 0.0);
    drawWheel(0.0, 0.0);
    glPopMatrix();

    // Rear wheel (child of car body)
    glPushMatrix();
    glTranslatef(0.3, -0.2, 0.0);
    drawWheel(0.0, 0.0);
    glPopMatrix();

    glPopMatrix(); // Restore car body's transformation
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawCar();

    if (!animationPaused) {
        carPositionX += 0.0005; // Move the car to the right
        if (carPositionX > 2.0) {
            carPositionX = -2.0; // Reset car's position
        }
    }

    glFlush();
    glutPostRedisplay(); // Request a continuous redisplay
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
}

// Callback function for the menu
void menuCallback(int option) {
    if (option == 1) {
        animationPaused = false; // Start the animation
    } else if (option == 2) {
        animationPaused = true; // Stop the animation
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("LAB : 2D Car ");

    // Create a simple menu
    glutCreateMenu(menuCallback);
    glutAddMenuEntry("Start Animation", 1);
    glutAddMenuEntry("Stop Animation", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutMainLoop();

    return 0;
}
