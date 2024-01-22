#include <GL/glut.h>

const float GOLDEN_RATIO = 1.61803398875; // Golden ratio constant
const int NUM_OF_LEVELS = 10;              // Number of levels of recursion
float height = 400.0;
int screenWidth = 800;
int screenHeight = 600;

enum Direction
{
    RIGHT,
    DOWN,
    LEFT,
    UP
};

void drawGoldenRectangle(float x, float y, float height, int level, Direction direction)
{
    if (level == 0)
        return;

    float width = height * GOLDEN_RATIO;

    
    float newHeight = height / GOLDEN_RATIO;
    // cal new direction
    Direction newDirection;
    float newX, newY;
    if (direction == Direction::RIGHT)
    {
        glColor3f(0.192, 0.882, 0.969);
        glBegin(GL_LINE_LOOP); // Use GL_LINE_LOOP to draw an unfilled rectangle

        glVertex2f(x, y);
        glVertex2f(x + height, y);
        glVertex2f(x + height, y - width);
        glVertex2f(x, y - width);

        glEnd();
        glFlush();

        newDirection = Direction::DOWN;
        newX = x + height;
        newY = y - height;
    }
    else if (direction == Direction::DOWN)
    {
        glColor3f(0.192, 0.882, 0.969);
        glBegin(GL_LINE_LOOP); // Use GL_LINE_LOOP to draw an unfilled rectangle

        glVertex2f(x, y);
        glVertex2f(x - width, y);
        glVertex2f(x - width, y - height);
        glVertex2f(x, y - height);

        glEnd();
        glFlush();
        newDirection = Direction::LEFT;
        newX = x - height;
        newY = y - height;
    }
    else if (direction == Direction::LEFT)
    {
        
        glColor3f(0.192, 0.882, 0.969);
        glBegin(GL_LINE_LOOP); // Use GL_LINE_LOOP to draw an unfilled rectangle

        glVertex2f(x, y);
        glVertex2f(x - height, y);
        glVertex2f(x - height, y + width);
        glVertex2f(x, y + width);

        glEnd();
        glFlush();
        newDirection = Direction::UP;
        newX = x - height;
        newY = y + height;
    }
    else
    {
        glColor3f(0.192, 0.882, 0.969);
        glBegin(GL_LINE_LOOP); // Use GL_LINE_LOOP to draw an unfilled rectangle

        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);

        glEnd();

        glFlush();

        newDirection = Direction::RIGHT;
        newX = x + height;
        newY = y + height;
    }

    // // Recursive call to draw the smaller rectangle
    drawGoldenRectangle(newX, newY, newHeight, level - 1, newDirection);
}

void display()
{
    glClearColor(0.1, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);

    drawGoldenRectangle(80, 100, height, NUM_OF_LEVELS, UP);

    glutSwapBuffers();
}



void myInit(void)
{
    glClearColor(0.1, 0.2, 0.2, 1.0); // background color is white
    glColor3f(0.192, 0.882, 0.969);         // drawing color is black
    // glPointSize(2.0);                          // a 'dot' is 2 by 2 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight); // dino window
    glViewport(0, 0, screenWidth, screenHeight);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("Fibonacci Spiral of Golden Rectangles");

    glutDisplayFunc(display);

    myInit();

    glutMainLoop();
    return 0;
}
