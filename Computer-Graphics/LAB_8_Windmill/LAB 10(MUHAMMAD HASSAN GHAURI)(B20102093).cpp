#include "GL/glut.h"
#include <math.h>

#define PI 3.141592

// Global variable to store the windmill's rotation angle
float windmillRotation = 0.0;

// Global variables for the plane animation
float planeX = 100.0;      // Initial x-position of the plane
float planeY = 230.0;      // Initial y-position of the plane
float planeSpeedX = 2.0;   // Horizontal speed of the plane
float planeSpeedY = 0.0;   // Vertical speed of the plane
float gravity = -0.2;      // Gravity effect

void display(void); 
void drawWind(void);  
void drawwindmill(void); 
void drawplane();  
void drawlandscape(); 
void Timer(int value); 
void keyboard(unsigned char key, int x, int y);
void init(void);
void reshape(GLsizei w, GLsizei h);

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawlandscape();
    drawplane();
    drawwindmill();

    glutSwapBuffers();
}

void drawWind() // single Triangle
{
    glBegin(GL_TRIANGLES);

    glColor3f(0.8, 0.8, 0.8);
    glVertex2f(0.0, 0.0);
    glVertex2f(15.0, 30.0);
    glVertex2f(35.0, 30.0);

    glEnd();
}

void drawwindmill()   // complete windmill in this body
{
    glPushMatrix();

    // Translate the windmill to its position
    glTranslatef(125.0, 100.0, 0.0);

    // Rotate the windmill based on the global windmillRotation variable
    glRotatef(windmillRotation, 0.0, 0.0, 1.0);

    // Draw the blades
    for (int i = 0; i < 4; i++) {
        glRotatef(90.0, 0.0, 0.0, 1.0);
        drawWind();
    }

    glPopMatrix();
}


// Define a flag to control the jerking behavior
int jerking = 0; // 1 indicates jerking allowed, 0 indicates no jerking

void Timer(int value)
{
    // Update the windmill's rotation angle
    windmillRotation += 2.0; // Adjust the rotation speed as needed

    // Check if the plane is on the ground and jerking is allowed
    if (planeY <= 50.0 && jerking) {
        // Stop the descent
        planeSpeedY = 0.0;
        planeY = 50.0; // Set the plane's position on the ground
        planeSpeedX = 0.0; // Stop horizontal movement

        // Apply a temporary upward force (jerk) when the plane is on the ground
        planeSpeedY = 2.0; // Adjust the jerk strength as needed

        // Disable jerking until the plane takes off again
        jerking = 0;
    } else if (planeY > 50.0) {
        // Re-enable jerking when the plane is in the air
        jerking = 1;

        // Apply gravity effect to vertical speed if the plane is in the air
        planeSpeedY += gravity;
    } else if (planeY <= 50.0 && !jerking) {
        // Plane has finished jerking and landed, stop the Timer
        return;
    }

    // Update the plane's position and velocity
    planeX -= planeSpeedX;     // Move the plane horizontally
    planeY += planeSpeedY;     // Update vertical position

    // Redraw the scene
    glutPostRedisplay();

    // Register the Timer function again, but only if jerking is allowed
    if (jerking) {
        glutTimerFunc(30, Timer, 1);
    }
}

// ...








void drawplane()
{
    /* Draw a plane */
    glBegin(GL_TRIANGLES);

    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(planeX + 30.0, planeY);
    glVertex2f(planeX + 30.0, planeY + 10.0);
    glVertex2f(planeX, planeY);

    glColor3f(0.2, 0.2, 0.2);
    glVertex2f(planeX + 29.0, planeY - 2.0);
    glVertex2f(planeX + 29.0, planeY + 5.0);
    glVertex2f(planeX + 15.0, planeY + 5.0);

    glEnd();
}



void drawlandscape()
{
  
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(250.0, 0.0);
    glColor3f(0.0, 0.9, 0.0);
    glVertex2f(250.0, 50.0);
    glColor3f(0.0, 0.8, 0.0);
    glVertex2f(0.0, 50.0);
    glColor3f(0.0, 0.7, 0.0);
    glVertex2f(0.0, 0.0);
    glEnd();

 
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 0.6);
    glVertex2f(250.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(200.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(150.0, 50.0);

    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(200.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(150.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(100.0, 50.0);

    glColor3f(0.0, 0.0, 0.7);
    glVertex2f(150.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(100.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(50.0, 50.0);

    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(100.0, 50.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(50.0, 150.0);
    glColor3f(0.0, 0.0, 0.5);
    glVertex2f(0.0, 50.0);

    glEnd();

    /* Draw the body of a windmill */
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.0);
    glVertex2f(145.0, 50.0);
    glVertex2f(135.0, 100.0);
    glVertex2f(115.0, 100.0);
    glVertex2f(105.0, 50.0);
    glEnd();
}

void init()
{
    glClearColor(0.8f, 0.8f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 250.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 250.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Lab 8");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(10, Timer, 5);
    glutMainLoop();
}