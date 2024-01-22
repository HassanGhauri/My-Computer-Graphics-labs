#include <GL/glut.h>
#include <cmath>

const int screenWidth = 640;
const int screenHeight = 480;
GLdouble A, B, C, D;

void myInit(void)
{
    glClearColor(0.1, 0.2, 0.2, 1);
    glColor3f(0.192, 0.882, 0.969);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
    A = screenWidth / 4.0;
    B = 0.0;
    C = D = screenHeight / 2.0;
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (GLdouble x = 0;x < 4.0;x += 0.005)
    {
        GLdouble func = exp(-fabs(x)) * cos(2 * 3.14159265 * x);
        glVertex2d(A * x + B, C * func + D);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Dot plot of a function");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}

