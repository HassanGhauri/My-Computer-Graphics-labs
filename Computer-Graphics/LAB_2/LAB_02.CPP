#include <iostream>
#include<fstream>
#include<string>
#include <GL/glut.h>
#include<cmath>


float PI = 3.1416;
const int numVertices = 100;


void drawCircle(float centerX, float centerY, float radius) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; ++i) {
        float angle = 2.0 * PI * static_cast<float>(i) / numVertices;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(0.0f, 0.2f, 0.0f);
    glRectf(0.99f, -0.99f, -0.99f, -0.6f);


    glBegin(GL_QUADS);
    glColor3f(0.18f, 0.30f, 0.30f);
    glVertex2f(0.28f, 0.25f);
    glVertex2f(0.2f, 0.25f);
    glVertex2f(0.2f, 0.65f);
    glVertex2f(0.28f, 0.65f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.3f, 0.00f);
    glVertex2f(0.70f, -0.3f);
    glVertex2f(0.80f, 0.15f);
    glVertex2f(0.88f, -0.3f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.36f, 0.20f, 0.09f);
    glVertex2f(0.75f, -0.3f);
    glVertex2f(0.83f, -0.3f);
    glVertex2f(0.83f, -0.75f);
    glVertex2f(0.75f, -0.75f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.3f, 0.00f);
    glVertex2f(-0.70f, -0.3f);
    glVertex2f(-0.80f, 0.15f);
    glVertex2f(-0.88f, -0.3f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.36f, 0.20f, 0.09f);
    glVertex2f(-0.75f, -0.3f);
    glVertex2f(-0.83f, -0.3f);
    glVertex2f(-0.83f, -0.75f);
    glVertex2f(-0.75f, -0.75f);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(0.18f, 0.30f, 0.30f);
    glVertex2f(-0.50f, 0.06f);
    glVertex2f(0.50f, 0.06f);
    glVertex2f(0.0f, 0.50f);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.18f, 0.50f, 0.50f);
    glVertex2f(-0.40f, 0.06f);
    glVertex2f(0.40f, 0.06f);
    glVertex2f(0.40f, -0.75);
    glVertex2f(-0.40f, -0.75);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.18f, 0.30f, 0.30f);
    glVertex2f(-0.10f, -0.25f);
    glVertex2f(0.10f, -0.25f);
    glVertex2f(0.10f, -0.75f);
    glVertex2f(-0.10f, -0.75f);
    glEnd();


    glLineWidth(1.5);
    glBegin(GL_LINES);
    glVertex2f(-0.4f, -0.1f);
    glVertex2f(0.4f, -0.1f);
    glVertex2f(-0.4f, -0.2f);
    glVertex2f(0.4f, -0.2f);
    glVertex2f(-0.4f, -0.3f);
    glVertex2f(0.4f, -0.3f);
    glVertex2f(-0.4f, -0.4f);
    glVertex2f(0.4f, -0.4f);
    glVertex2f(-0.4f, -0.5f);
    glVertex2f(0.4f, -0.5f);
    glVertex2f(-0.4f, -0.6f);
    glVertex2f(0.4f, -0.6f);
    glVertex2f(-0.4f, -0.7f);
    glVertex2f(0.4f, -0.7f);
    glEnd();

    glColor3f(1,1,0);
    drawCircle(-0.8,0.8,0.09);

    glColor3f(0.65,0.65,0.65);
    drawCircle(-0.3,0.8,0.09);
    drawCircle(-0.2,0.8,0.09);
    drawCircle(-0.26,0.85,0.09);


    glColor3f(0.65,0.65,0.65);
    drawCircle(0.9,0.8,0.09);
    drawCircle(0.8,0.8,0.09);
    drawCircle(0.86,0.85,0.09);

    /*glBegin(GL_POLYGON);
    glColor3f(1,1,0);
    for (int i = 0; i < numVertices; ++i) {
        float angle = 2.0 * PI * static_cast<float>(i) / numVertices;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1,1,0);
    for (int i = 0; i < numVertices; ++i) {
        float angle = 2.0 * PI * static_cast<float>(i) / numVertices;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1,1,0);
    for (int i = 0; i < numVertices; ++i) {
        float angle = 2.0 * PI * static_cast<float>(i) / numVertices;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1,1,0);
    for (int i = 0; i < numVertices; ++i) {
        float angle = 2.0 * PI * static_cast<float>(i) / numVertices;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();*/


    glFlush();
}



void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(150, 10);
    glutInitWindowSize(1000, 600);

    glutCreateWindow("My LAB 02");

    glutDisplayFunc(display);
    init();

    glutMainLoop();

    return 0;
}


