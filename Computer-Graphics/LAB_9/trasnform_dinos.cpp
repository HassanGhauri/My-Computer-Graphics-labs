#include <GL/glut.h>
#include <iostream>
#include <fstream>

const int w = 820;
const int h = 572;
float motifRotation = 0.0f;

void initCT(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void scale2D(double sx, double sy) {
    glMatrixMode(GL_MODELVIEW);
    glScaled(sx, sy, 1.0);
}

void translate2D(double dx, double dy) {
    glMatrixMode(GL_MODELVIEW);
    glTranslated(dx, dy, 1.0);
}

void rotate2D(double angle) {
    glMatrixMode(GL_MODELVIEW);
    glRotated(angle, 0.0, 0.0, 1.0);
}

void window(int xs, int xe, int ys, int ye) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xs, xe, ys, ye);
}

void drawPolyLineFile(std::string fileName) {
    std::fstream inStream;
    inStream.open(fileName, std::ios::in);

    if (inStream.fail()) {
        std::cout << "can't open it!";
        return;
    }

    GLfloat numpolys, numPoints, x, y;
    inStream >> numpolys;

    for (int j = 0; j < numpolys; j++) {
        inStream >> numPoints;
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < numPoints; i++) {
            inStream >> x >> y;
            glVertex2f(x, y);
        }
        glEnd();
    }

    inStream.close();
}

void transform_dinos() {
    glTranslatef(125.0, 125.0, 0.0);
    int numMotifs = 12;

    for (int i = 0; i < numMotifs; i++) {
        for (int j = 0; j < numMotifs; j++) {
            glViewport(i * 24, j * 24, 24, 24);
            initCT();
            rotate2D(i * 360 / numMotifs);
            translate2D(0.0, h);
            // glLoadIdentity();
            drawPolyLineFile("dino.txt");
        }
    }
    glutSwapBuffers();
}

void init() {
    glClearColor(0.0314, 0.0392, 0.3216, 1.0);
    glColor3f(0.9294, 0.1294, 0.5333);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w, 0.0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    window(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // glTranslatef(w / 2, h / 2, 0);
    // glRotatef(motifRotation, 0, 0, 1);
    drawPolyLineFile("dino.txt");
    glutSwapBuffers();
}

void idle() {
    motifRotation += 1.0;
    if (motifRotation >= 360.0) {
        motifRotation -= 360.0;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(w, h);
    glutCreateWindow("LAB 9");

    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}
