#include <GL/glut.h>
#include <cmath>

const float PI = 3.14;
const int numVertices = 100; // Number of vertices to approximate the circle

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
    glClearColor(0.1, 0.2, 0.2, 1.0);      
	
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.192, 0.882, 0.969);

    // Draw a circle centered at (0, 0) with radius 5
    drawCircle(0.0, 0.0, 5.0);

    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lab Activity (10): Draw Circle With the help of EQ: x+r cos Ф, y+r sin Ф");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
