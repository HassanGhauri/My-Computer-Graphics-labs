#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "pixMap.h"
#include "Mario.h"
Mario m(Point2(0, 0));
void myInit(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_EQUAL, 1.0);
    glViewport(0, 0, 640, 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    m.changeMode(Mario::STAY);
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m.render();
    glFlush();
}
void spinner(int t)
{
    glutPostRedisplay();
    glutTimerFunc(500, spinner, t);

}
bool fKeyPressed = false;
bool jKeypressed = false;
void mySpecialKeyHandler(int key, int mx, int my)
{
    switch (key) {
    case GLUT_KEY_RIGHT:
        m.changeMode(Mario::RUN);
        fKeyPressed = true;
        break;

    case GLUT_KEY_UP:
        if (m.pos_Y <= 0) {
            m.changeMode(Mario::JUMP);
        }
        if (m.pos_Y > 60) {
            m.changeMode(Mario::GROUNDED);
        }
        break;
    }
    glutPostRedisplay();
}
void mySpecialKeyRelease(int key, int mx, int my)
{
    if (key == GLUT_KEY_RIGHT) {
        fKeyPressed = false;
        m.changeMode(Mario::STAY);  // Change mode to STAY when 'f' key is released
    }
    if (key == GLUT_KEY_UP) {
        jKeypressed = false;
        m.changeMode(Mario::GROUNDED);
        // m.changeMode(Mario::STAY);  // Change mode to STAY when 'f' key is released
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Mario");
    glutDisplayFunc(display);
    glutSpecialFunc(mySpecialKeyHandler);
    glutSpecialUpFunc(mySpecialKeyRelease);
    myInit();
    glutIdleFunc(display);
    glutMainLoop();
}

