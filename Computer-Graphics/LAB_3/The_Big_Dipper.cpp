#include <GL/glut.h>

void myInit(void)
{
    glClearColor(0.1, 0.2, 0.2, 1);
    glColor3f(0.192, 0.882, 0.969);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glVertex2i(80, 30);
    glVertex2i(148, 132);
    glVertex2i(150, 130);
    glVertex2i(240, 150);
    glVertex2i(340, 180);
    glVertex2i(390, 128);
    glVertex2i(460, 300);
    glVertex2i(500, 210);
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("draw big dipper");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}
