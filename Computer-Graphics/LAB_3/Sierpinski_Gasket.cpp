#include <GL/glut.h>

struct GLintPoint {
    GLfloat x, y;
};

void myInit(void)
{
    glClearColor(0.1, 0.2, 0.2, 1);
    glColor3f(0.192, 0.882, 0.969);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void drawDot(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void sierPinski_render(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLintPoint T[3] = { {10,10},{600,10},{240,480} };
    int index = rand() % 3;
    GLintPoint point = T[index];
    drawDot(point.x, point.y);
    for (int i = 0; i < 55000; i++) {
        index = rand() % 3;
        point.x = (point.x + T[index].x) / 2;
        point.y = (point.y + T[index].y) / 2;
        drawDot(point.x, point.y);
    }
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(840, 600);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("sierpinski Gasket");
    glutDisplayFunc(sierPinski_render);
    myInit();
    glutMainLoop();
    return 0;
}
