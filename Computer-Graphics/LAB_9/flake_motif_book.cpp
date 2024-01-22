#include "GL/glut.h"
#include <math.h>


void initCT(void)
{
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
// set CT to the identity matrix
}
//<<<<<<<<<<<<<< scale2D >>>>>>>>>>>>>>>>>>>>
void scale2D(double sx, double sy)
{
glMatrixMode(GL_MODELVIEW);
glScaled(sx, sy, 1.0); // set CT to CT * (2D scaling)
}
//<<<<<<<<<<<<<<< translate2D >>>>>>>>>>>>>>>>>
void  translate2D(double dx, double dy)
{ glMatrixMode(GL_MODELVIEW);
glTranslated(dx, dy, 1.0); // set CT to CT * (2D translation)
}
//<<<<<<<<<<<<<<<< rotate2D >>>>>>>>>>>>>>>>>>>>
void rotate2D(double angle)
{
glMatrixMode(GL_MODELVIEW);
glRotated(angle, 0.0, 0.0, 1.0); // set CT to CT * (2D rotation)
}
float motifrotation=0.0;
void reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 250.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// void flake_motif()
// {
//     glPushMatrix();
//     glBegin(GL_LINE_LOOP); // Use GL_LINE_LOOP instead of GL_LINE_STRIP
//     glVertex2d(3, 3);
//     glVertex2d(0, 8);
//     glVertex2d(-3, 3);
//     glVertex2d(-2, -1);
//     glVertex2d(0, 5);
//     glEnd();
//     glPopMatrix();
// }
void flake_motif()   // complete windmill in this body
{   
    glPushMatrix();

    glScalef(1.0, 1.0, 0.5);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0,5);
    glVertex2f(20,5);
    glVertex2f(30,25);
    glVertex2f(35,18);
    glVertex2f(25,5);
    glVertex2f(30,5);
    glVertex2f(45,15);
    glVertex2f(50,13);
    glVertex2f(35,5);
    glVertex2f(55,5);
    glVertex2f(60,0);
    
    glEnd();
    glPopMatrix();
    // glutPostRedisplay();
}
void Drawmotif()
{
    // Translate the windmill to its position
    glTranslatef(125.0, 100.0, 0.0);

    // // Rotate the windmill based on the global windmillRotation variable
    // glRotatef(motifrotation, 0.0, 0.0, 1.0);

    // Draw the blades
    for (int i = 0; i < 6; i++) {
        // glRotatef(90.0, 0.0, 0.0, 1.0);
        // flake_motif();
        // motifrotation+=2.0;
        flake_motif();
        scale2D(1.0,-1.0);
        flake_motif();
        scale2D(1.0,-1.0);
        rotate2D(60.0);   
     }
}
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluOrtho2D(0.0, 250.0, 0.0, 250.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
    Drawmotif();

    glutSwapBuffers();
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
    glutCreateWindow("LAB 9");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    // glutTimerFunc(30, Timer, 1);
    glutMainLoop();
}
